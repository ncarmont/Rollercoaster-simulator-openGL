#include "Window.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

const char* window_title = "GLFW Starter Project";
Cube * cube;
OBJObject * antenna;
OBJObject * body;
OBJObject * eyeball;
OBJObject * head;
OBJObject * limb;
GLint shaderProgram;


// On some systems you need to change this to the absolute path
#define VERTEX_SHADER_PATH "/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/shader.vert"
#define FRAGMENT_SHADER_PATH "/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/shader.frag"


// Default camera parameters
glm::vec3  Window::cam_pos(0.0f, 0.0f, 20.0f);		// e  | Position of camera
glm::vec3  Window::cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3  Window::cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

//float radius = 10.0f;
//float camX = sin(glfwGetTime()) * radius;
//float camZ = cos(glfwGetTime()) * radius;
//glm::mat4 view = glm::lookAt(cam_pos, cam_pos + cam_look_at, cam_up);
//float cameraSpeed = 0.05f;

int Window::width;
int Window::height;

double Window::yoffset;
double Window::xoffset;

double Window::oldX=0;
double Window::oldY=0;

glm::mat4 Window::P;
glm::mat4 Window::V;

void Window::initialize_objects()
{
    
//    Transform* root = new Transform(glm::mat4(1.0f));
//
//    Node* antenna1 = new Geometry(glm::mat4(1.0f),"/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/robotParts/antenna_s.obj" );
//    Node* antenna2 = new Geometry(glm::mat4(1.0f),"/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/robotParts/antenna_s.obj" );
//    Node* body1 = new Geometry(glm::mat4(1.0f), "/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/robotParts/body_s.obj");
//    Node* eyeball1 = new Geometry(glm::mat4(1.0f),"/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/robotParts/eyeball_s.obj");
//    Node* eyeball2 = new Geometry(glm::mat4(1.0f),"/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/robotParts/eyeball_s.obj");
//    Node* leg1 = new Geometry(glm::mat4(1.0f), "/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/robotParts/head_s.obj");
//    Node* leg2 = new Geometry(glm::mat4(1.0f), "/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/robotParts/head_s.obj");
//    Node* arm1 = new Geometry(glm::mat4(1.0f), "/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/robotParts/head_s.obj");
//    Node* arm2 = new Geometry(glm::mat4(1.0f), "/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/robotParts/head_s.obj");
//
//    Node* head1 = new Geometry(glm::mat4(1.0f),"/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/robotParts/limb_s.obj");
//
//    arm1->update(glm::vec3(1.0f,1.0f,1.0f));
//    arm2->update(glm::vec3(1.0f,1.0f,1.0f));
//    leg1->update(glm::vec3(1.0f,1.0f,1.0f));
//    leg2->update(glm::vec3(1.0f,1.0f,1.0f));
//
//
//    root -> addChild(antenna1);    // Two antennas, two eyeballs, two legs, two arms
//    root -> addChild(antenna2);
//    root-> addChild(body1);
//    root-> addChild(eyeball1);
//    root-> addChild(eyeball2);
//    root-> addChild(leg1);
//    root-> addChild(leg2);
//    root-> addChild(arm1);
//    root-> addChild(arm2);
//    root-> addChild(head1);
//
//
//    root -> draw(Window::V);
    
    
//    limb1 -> SetTransform (  glm::rotate ( - msec / 10.0 f , Vector3 (0 ,1 ,0)));
//    antenna1 - > SetTransform ( leftArm - > GetTransform () *Matrix4 :: Rotation ( - msec / 10.0 f , Vector3 (1 ,0 ,0)));
//

    antenna = new OBJObject("/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/robotParts/antenna_s.obj");
    body = new OBJObject("/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/robotParts/body_s.obj");
    eyeball = new OBJObject("/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/robotParts/eyeball_s.obj");
    head = new OBJObject("/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/robotParts/head_s.obj");
    limb = new OBJObject("/Users/computerscience/Desktop/Hw3CSE167TurnIn/Hw3CSE167TurnIn/robotParts/limb_s.obj");
    cube = new Cube();
    
//    OBJObject1 bear("/Users/computerscience/Desktop/Hw2CSE167/Hw2CSE167/bear1.obj");
//    OBJObject1 dragon("/Users/computerscience/Desktop/Hw2CSE167/Hw2CSE167/dragon1.obj");

	// Load the shader program. Make sure you have the correct filepath up top
	shaderProgram = LoadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
}

// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{
	delete(antenna);
    delete(body);
    delete(eyeball);
    delete(head);
    delete(limb);
    delete(cube);
	glDeleteProgram(shaderProgram);
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ // Because Apple hates comforming to standards
	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		fprintf(stderr, "Either GLFW is not installed or your graphics card does not support modern OpenGL.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(window, &width, &height);
	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(window, &width, &height); // In case your Mac has a retina display
#endif
	Window::width = width;
	Window::height = height;
	// Set the viewport size. This is the only matrix that OpenGL maintains for us in modern OpenGL!
	glViewport(0, 0, width, height);

	if (height > 0)
	{
		P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
        
        V = glm::lookAt(Window::cam_pos, Window::cam_look_at, Window::cam_up);
	}
}

void Window::idle_callback()
{
	// Call the update function the cube
	cube->update();
}

void Window::display_callback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
	// Use the shader of programID
	glUseProgram(shaderProgram);
	
	// Render the cube
//    cube->draw(shaderProgram);
    
    glm::mat4 translateHead = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.8f, 0.0f));
    glm::mat4 translateLeftArm = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.6f, 0.0f));
    glm::mat4 translateRightArm = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.6f, 0.0f));
    glm::mat4 translateLeftLeg = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f,-1.8f, 0.0f));
    glm::mat4 translateRightLeg = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -1.8f, 0.0f));
    glm::mat4 translateLeftAnt= glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f,1.8f, 0.0f));
    glm::mat4 translateRightAnt = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 1.8f, 0.0f));
    
//    translateBody = glm::rotate(translateBody, (GLfloat)glfwGetTime()*1.0f,glm::vec3(0.0,0.0,1.0f));

    body->draw(shaderProgram,glm::mat4(1.0f));
    eyeball->draw(shaderProgram,glm::mat4(1.0f));
    head->draw(shaderProgram,translateHead);
    antenna->draw(shaderProgram,glm::mat4(1.0f));
    limb->draw(shaderProgram,translateLeftArm);
    limb->draw(shaderProgram,translateRightArm);
    limb->draw(shaderProgram,translateLeftLeg);
    limb->draw(shaderProgram,translateRightLeg);
    limb->draw(shaderProgram,translateLeftAnt);
    limb->draw(shaderProgram,translateRightAnt);


	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    std::cout<< xoffset;
    std::cout<< yoffset;
    std::cout<< "\n";

    if(yoffset<0){
//        model->scale_up();

    } else if (yoffset>0){
//       model->scale_down();
    }

}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS)
	{
		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
        } else if (key == GLFW_KEY_1 )
        {
            // Close the window. This causes the program to also terminate.
//             model = bunny;
        }
        else if (key == GLFW_KEY_2 )
        {
            // Close the window. This causes the program to also terminate.
//             model = bear;
        }
        else if (key == GLFW_KEY_3 )
        {
//             model = dragon;
        }
}
}
void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
//    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
//        //glm::vec3 lastPoint = trackBallMapping( xoffset, yoffset, width, height );
//
//
////        std::cout<<"yes goig \n";
////        std::cout<<xoffset;
//
//    };
}

glm::vec3 Window::trackBallMapping(double xoffset, double yoffset){
    glm::vec3 vector;

    float depth;
    vector.x = (2.0*xoffset - Window::width)/Window::width;
    vector.y = (Window::height - 2.0*yoffset)/ Window::height;
    vector.z = 0.0;
    depth = glm::length(vector);
    depth = (depth<1.0) ? depth : 1.0;   //
    vector.z = sqrtf(1.001 - depth*depth);
    vector =glm::normalize(vector);
  return vector;
}

void Window::onMoveMouse(GLuint nFlags, double xoffset, double yoffset, glm::vec3 lastPoint){
    
    glm::vec3 curPoint = trackBallMapping( xoffset, yoffset);

    glm::vec3 dir = curPoint - lastPoint;
    std::cout<< "yes"<<dir.x<<":"<<dir.y<< ":"<< dir.z<<std::endl;
    
    glm::vec3 cam_dir = cam_look_at - cam_pos;
    cam_dir = glm::mat3(glm::rotate(dir.x,  cam_up)) *  cam_dir ;
    Window::cam_look_at = Window::cam_pos + cam_dir;
    Window::V = glm::lookAt(cam_pos, cam_look_at, cam_up);

    
    Window::oldX = xoffset;
    Window::oldY = yoffset;
    
    
//    glm::vec3 dir;
////    float pixel_diff;
//    float rot_angle; // zoom_factor;
//    glm::vec3 curPoint;
//
//    curPoint = trackBallMapping( xoffset, yoffset); // Map the mouse position to a logical
//
//            // sphere location.
//            dir = curPoint - lastPoint;
//    std::cout<< "yes"<<dir.x<<":"<<dir.y<< ":"<< dir.z<<std::endl;
//            double m_ROTSCALE = 10;
//            float velocity = glm::length(dir);
//            if( velocity > 0.0001 ) // If little movement - do nothing.
//            {
//                glm::vec3 rotAxis;
//                rotAxis = glm::cross(lastPoint, curPoint );
//                rot_angle = velocity * m_ROTSCALE;
//                glm::mat4 rotMat = glm::rotate(rot_angle, rotAxis);
//                Window::cam_pos = rotMat * cam_pos;
//
//
//                //model->rotateToWorld(rot_angle,rotAxis);
//
//                Window::oldX = xoffset;
//                Window:oldY =yoffset;
//}
}
void Window::cursorPositionCallback (GLFWwindow* window, double x, double y){
//    std::cout<< x << ":" << y << std::endl;
    
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS){
//        std::cout<< x << " ++++" <<y<<std::endl;
          glm::vec3 lastPoint = trackBallMapping(oldX,oldY);
          onMoveMouse(1, x, y, lastPoint);
//        std::cout<< "ye"<<lastPoint.x<<":"<<lastPoint.y<< ":"<< lastPoint.z<<std::endl;
    }
// std::cout<< x << " :" <<y<<std::endl;
//
};
