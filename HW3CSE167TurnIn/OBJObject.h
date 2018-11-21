#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h> // Remove this line in future projects
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class OBJObject
{
    
private:
std::vector<unsigned int> indices;
std::vector<glm::vec3> vertices;
std::vector<glm::vec3> normals;
std::vector<glm::vec2> uvs;
glm::mat4 toWorld;
glm::mat4 modelView;
float angle;
float point_size;
float x_position;

public:
	OBJObject(const char* filepath);
    ~OBJObject();
	void parse(const char* filepath);
    void draw(GLuint shaderProgram, glm::mat4 C);
    void spin(float);
    void adjust_point_size(float);  // adjust size of points
    // These variables are needed for the shader program
    GLuint VBO, VAO, EBO;
    GLuint uProjection, uModelview, uTransform;
    void scale_up();
    void scale_down();
    void rotateToWorld(float rot_angle, glm::vec3 rotAxis);
    void setModelView(glm::mat4 C );
};

#endif
