#include "main.hpp"
#include <iostream>
#include "shader.hpp"
#include "camera.hpp"
#include "polyplane.hpp"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

//#include <unistd.h>

// settings
const GLuint SCR_WIDTH = 800, SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;    // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main(int argc, const char * argv[])
{
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x << vec.y << vec.z << std::endl;
    
    
    glfwInit();
    //std::cout << glfwGetVersionString() << std::endl;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL", nullptr, nullptr);
    
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window."  << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glewExperimental = GL_TRUE;
    
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    
    // build the shader program from our vert and frag shaders...
    Shader simpleShader("shaders/simpleVertexShader.vert", "shaders/simpleFragmentShader.frag");
    
    // set up vertex data (and buffer(s)) and configure vertex attributes
    int vertsX = 2;
    int vertsY = 5;
    if (vertsX < 2 || vertsY < 2)
    {
        cout << "Number of vertices in the X and Y direction must be greater than 1." << endl;
        return -1;
    }
    
    PolyPlane *polyplane = new PolyPlane(vertsX, vertsY);
    
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // bind the VAO and VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, polyplane->numVertices * sizeof(Vertex), polyplane->vertices, GL_STATIC_DRAW);
    
    // copy our index array in a element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, polyplane->numTriangles * sizeof(Triangle), polyplane->indices, GL_STATIC_DRAW);
    
    // set our vertex attributes pointers
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    simpleShader.Use();
    
    // Center it
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));
    simpleShader.SetMatrix("model", model);
    
    // Leave view matrix as identity
    glm::mat4 view(1.0);
    simpleShader.SetMatrix("view", view);
    
    // Leave projection matrix as identity
    glm::mat4 projection(1.0f);
    //projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    simpleShader.SetMatrix("projection", projection);
    
    // Set to draw wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while (glfwWindowShouldClose(window) == false)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Render
        simpleShader.Use();
        
        glBindVertexArray(VAO);
        
        int size = 0;
        glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
        glDrawElements(GL_TRIANGLES, size/sizeof(GLuint), GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    delete polyplane;
    
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
