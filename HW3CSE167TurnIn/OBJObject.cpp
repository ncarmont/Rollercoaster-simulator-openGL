#include "OBJObject.h"
#include "Window.h"
#include <iostream>
#include "SOIL2/SOIL2.h"
//#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL

OBJObject::OBJObject(const char *filepath) 
{
	toWorld = glm::mat4(1.0f);
	parse(filepath);
//    Window::modelview = glm::mat4(1.0f);
    modelView = glm::mat4(1.0f);
    this->angle = 0.0f;
    this->x_position=0.0f;
    this->point_size = 10.000f;
    // Create array object and buffers. Remember to delete your buffers when the object is destroyed!
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Bind the Vertex Array Object (VAO) first, then bind the associated buffers to it.
    // Consider the VAO as a container for all your buffers.
    glBindVertexArray(VAO);
    
    // Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
    // you want to draw, such as vertices, normals, colors, etc.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
    // the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_DYNAMIC_DRAW);
    // Enable the usage of layout location 0 (check the vertex shader to see what this is)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
                          3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
                          GL_FLOAT, // What type these components are
                          GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
                          3 * sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
                          (GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.
    
    // We've sent the vertex data over to OpenGL, but there's still something missing.
    // In what order should it draw those vertices? That's why we'll need a GL_ELEMENT_ARRAY_BUFFER for this.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);
    
    // Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind the VAO now so we don't accidentally tamper with it.
    // NOTE: You must NEVER unbind the element array buffer associated with a VAO!
    glBindVertexArray(0);
    
    
    GLuint texture;
    
    int width, height;
    
    
    // ===================
    // Texture
    // ===================
    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    // Set our texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    // Set texture filtering
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    // Load, create texture and generate mipmaps
    unsigned char *image = SOIL_load_image( "musk.jpg", &width, &height, 0, SOIL_LOAD_RGBA );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
    glGenerateMipmap( GL_TEXTURE_2D );
    SOIL_free_image_data( image );
    glBindTexture( GL_TEXTURE_2D, 0 );

}


OBJObject::~OBJObject()
{
    // Delete previously generated buffers. Note that forgetting to do this can waste GPU memory in a
    // large project! This could crash the graphics driver due to memory leaks, or slow down application performance!
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void OBJObject::parse(const char *filepath) 
{
    FILE* fp;     // file pointer
    std::vector< glm::vec3 >  input_vertices, input_normals;
    std::vector <glm::vec2> input_uvs;
    std::vector< unsigned int > vertex_indices_, normal_indices_, uv_indices_;
    
    fp = fopen(filepath,"rb");  // make the file name configurable so you can load other files
    if (fp==NULL) { std::cerr << "error loading file" << std::endl; exit(-1); }
    
    while( 1==1 ){
        char entireRow[128];
        // read the first word of the line
        int line = fscanf(fp, "%s", entireRow);
        if (line == EOF){
            break;
        }
        if ( strcmp( entireRow, "v" ) == 0 ){
            glm::vec3 vertex;
            fscanf(fp, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
             input_vertices.push_back(vertex);
        }else if ( strcmp( entireRow, "vn" ) == 0 ){
            glm::vec3 normal;
            fscanf(fp, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            input_normals.push_back(normal);
        }else if ( strcmp( entireRow, "vt" ) == 0 ){
            glm::vec2 tempUv;
            fscanf(fp, "%f %f\n", &tempUv.x, &tempUv.y );
            input_uvs.push_back(tempUv);
        }
        else if ( strcmp( entireRow, "f" ) == 0 ){
            unsigned int vertexIndex[3], normalIndex[3], uvIndex[3];
            fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            vertex_indices_.push_back(vertexIndex[0]-1);
            vertex_indices_.push_back(vertexIndex[1]-1);
            vertex_indices_.push_back(vertexIndex[2]-1);
            normal_indices_.push_back(normalIndex[0]-1);
            normal_indices_.push_back(normalIndex[1]-1);
            normal_indices_.push_back(normalIndex[2]-1);
            uv_indices_.push_back(uvIndex[0]-1);
            uv_indices_.push_back(uvIndex[1]-1);
            uv_indices_.push_back(uvIndex[2]-1);
        }
    }
    
    for (unsigned i = 0; i < vertex_indices_.size(); i++) {
        vertices.push_back(input_vertices[vertex_indices_[i]]);
        normals.push_back(input_normals[normal_indices_[i]]);
        uvs.push_back(input_uvs[uv_indices_[i]]);
        indices.push_back(i);
    }


    
        float max_x = vertices[0].x;   // Set Initial max and min values to first arg
        float max_y = vertices[0].y;
        float max_z = vertices[0].z;
        float min_x = vertices[0].x;
        float min_y = vertices[0].y;
        float min_z = vertices[0].z;

        for (unsigned int i = 0; i < vertices.size(); ++i){  // Traverse matrix vertices for true max/min
            if (vertices[i].x  > max_x){
                max_x = vertices[i].x;
            }
            if (vertices[i].y  > max_y){
                max_y = vertices[i].y;
            }
            if (vertices[i].z  > max_z){
                max_z = vertices[i].z;
            }
            if (vertices[i].x  < min_x){
                min_x = vertices[i].x;
            }
            if (vertices[i].y < min_y){
                min_y = vertices[i].y;
            }
            if (vertices[i].z < min_z){
                min_z = vertices[i].z;
            }
        };
        float midpoint_x = (max_x+min_x)/2.000;  // Find midpoint for translating properly
        float midpoint_y = (max_y+min_y)/2.000;
        float midpoint_z = (max_z+min_z)/2.000;
        float scale_mult = 1.2; //13.5 Dragon //1.2 Bear //8.4 Bunny  <- Multipliers Found to scale Models best

        for (unsigned int i = 0; i < vertices.size(); ++i)
        {
            vertices[i].x = (vertices[i].x - midpoint_x)*scale_mult;  // Scale models properly
            vertices[i].y = (vertices[i].y - midpoint_y)*scale_mult;
            vertices[i].z = (vertices[i].z - midpoint_z)*scale_mult;
        };
    

    fclose(fp);   // make sure you don't forget to close the file when done
}
    

void OBJObject::draw(GLuint shaderProgram, glm::mat4 C) {
    // Calculate the combination of the model and view (camera inverse) matrices
    
    modelView =  C* Window::V * toWorld; // ;  glm::mat4(1.0f);
    // We need to calcullate this because modern OpenGL does not keep track of any matrix other than the viewport (D)
    // Consequently, we need to forward the projection, view, and model matrices to the shader programs
    // Get the location of the uniform variables "projection" and "modelview"
    
    
    
    uProjection = glGetUniformLocation(shaderProgram, "projection");
    uModelview = glGetUniformLocation(shaderProgram, "modelview");
    glm::mat4 transform = glm::mat4(1.0);
//    std::cout<<"outpt " << transform[0][0]<<std::endl;
    transform = glm::translate(transform, glm::vec3(0.0f,0.0f,0.0f));
//    std::cout<<"outpt " << transform[0][0]<<std::endl;
    transform = glm::rotate(transform, 1.0f, glm::vec3(0.0f,0.0f,0.0f));
    
    uTransform = glGetUniformLocation(shaderProgram, "transform");
    
    
    // Now send these values to the shader program
    glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]); //Window::P[0][0]
    glUniformMatrix4fv(uModelview, 1, GL_FALSE, &modelView[0][0]);
    glUniformMatrix4fv(uTransform, 1, GL_FALSE, &transform[0][0]);
    // Now draw the cube. We simply need to bind the VAO associated with it.
    glBindVertexArray(VAO);
    // Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
    glDrawElements(GL_TRIANGLES, 3*indices.size(), GL_UNSIGNED_INT, 0);
    // Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
    glBindVertexArray(0);
    
    GLuint texture;
    
    int width, height;
    
    
    // ===================
    // Texture
    // ===================
    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    // Set our texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    // Set texture filtering
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    // Load, create texture and generate mipmaps
    unsigned char *image = SOIL_load_image( "musk.jpg", &width, &height, 0, SOIL_LOAD_RGBA );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
    glGenerateMipmap( GL_TEXTURE_2D );
    SOIL_free_image_data( image );
    glBindTexture( GL_TEXTURE_2D, 0 );
    
    
}

void OBJObject::spin(float deg)
{
    this->angle += deg;
    if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;
    // This creates the matrix to rotate the cube
    this->toWorld = glm::rotate(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
}

void OBJObject::adjust_point_size(float size){
     glPointSize(point_size + size);
}

void OBJObject::scale_up(){
   toWorld = glm::scale(toWorld, glm::vec3(1.1f,1.1f,1.1f));
};

void OBJObject::scale_down(){
    toWorld = glm::scale(toWorld, glm::vec3(0.9f,0.9f,0.9f));
};


void OBJObject::rotateToWorld(float rot_angle, glm::vec3 rotAxis){
    toWorld= glm::rotate(rot_angle, rotAxis)*toWorld;
};

//void OBJObject::setModelView( glm::mat4 C ){
//    modelView = glm::mat4(C);
//};





