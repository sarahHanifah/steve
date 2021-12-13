#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("steve.vs", "steve.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    // -------------------------- OBJEK 1 ----------------------------------

    float vertices[] = {

        // KEPALA
        // 
        // depan
        -0.16f, 0.48f, -0.16f,   0.192f, 0.188f, 0.168f, // BL
         0.16f, 0.48f, -0.16f,   0.192f, 0.188f, 0.168f, // BR
         0.16f,  0.8f, -0.16f,   0.192f, 0.188f, 0.168f, // TR
         0.16f,  0.8f, -0.16f,   0.192f, 0.188f, 0.168f, // TR
        -0.16f,  0.8f, -0.16f,   0.192f, 0.188f, 0.168f, // TL
        -0.16f, 0.48f, -0.16f,   0.192f, 0.188f, 0.168f, // BL

        // belakang
        -0.16f, 0.48f, 0.16f,   0.662f, 0.490f, 0.392f, // BL
         0.16f, 0.48f, 0.16f,   0.662f, 0.490f, 0.392f, // BR
         0.16f,  0.8f, 0.16f,   0.662f, 0.490f, 0.392f, // TR
         0.16f,  0.8f, 0.16f,   0.662f, 0.490f, 0.392f, // TR
        -0.16f,  0.8f, 0.16f,   0.662f, 0.490f, 0.392f, // TL
        -0.16f, 0.48f, 0.16f,   0.662f, 0.490f, 0.392f, // BL

        // kiri
        -0.16f, 0.48f, 0.16f,   0.192f, 0.188f, 0.168f, // BL
        -0.16f, 0.48f, -0.16f,   0.192f, 0.188f, 0.168f, // BR
        -0.16f,  0.8f, -0.16f,   0.192f, 0.188f, 0.168f, // TR
        -0.16f,  0.8f, -0.16f,   0.192f, 0.188f, 0.168f, // TR
        -0.16f,  0.8f, 0.16f,   0.192f, 0.188f, 0.168f, // TL
        -0.16f, 0.48f, 0.16f,   0.192f, 0.188f, 0.168f, // BL

        // kanan
         0.16f, 0.48f, 0.16f,   0.192f, 0.188f, 0.168f, // BL
         0.16f, 0.48f, -0.16f,   0.192f, 0.188f, 0.168f, // BR
         0.16f,  0.8f, -0.16f,   0.192f, 0.188f, 0.168f, // TR
         0.16f,  0.8f, -0.16f,   0.192f, 0.188f, 0.168f, // TR
         0.16f,  0.8f, 0.16f,   0.192f, 0.188f, 0.168f, // TL
         0.16f, 0.48f, 0.16f,   0.192f, 0.188f, 0.168f, // BL

        // bawah
        -0.16f, 0.48f, 0.16f,   0.662f, 0.490f, 0.392f, // BL
         0.16f, 0.48f, 0.16f,   0.662f, 0.490f, 0.392f, // BR
         0.16f, 0.48f, -0.16f,   0.662f, 0.490f, 0.392f, // TR
         0.16f, 0.48f, -0.16f,   0.662f, 0.490f, 0.392f, // TR
        -0.16f, 0.48f, -0.16f,   0.662f, 0.490f, 0.392f, // TL
        -0.16f, 0.48f, 0.16f,   0.662f, 0.490f, 0.392f, // BL

        // atas
        -0.16f,  0.8f, 0.16f,   0.192f, 0.188f, 0.168f, // BL
         0.16f,  0.8f, 0.16f,   0.192f, 0.188f, 0.168f, // BR
         0.16f,  0.8f, -0.16f,   0.192f, 0.188f, 0.168f, // TR
         0.16f,  0.8f, -0.16f,   0.192f, 0.188f, 0.168f, // TR
        -0.16f,  0.8f, -0.16f,   0.192f, 0.188f, 0.168f, // TL
        -0.16f,  0.8f, 0.16f,   0.192f, 0.188f, 0.168f, // BL

        // BADAN

        // depan
        -0.16f,  0.0f,  -0.08f,   0.054f, 0.682f, 0.682f, // BL
         0.16f,  0.0f,  -0.08f,   0.054f, 0.682f, 0.682f, // BR
         0.16f, 0.48f,  -0.08f,   0.054f, 0.682f, 0.682f, // TR
         0.16f, 0.48f,  -0.08f,   0.054f, 0.682f, 0.682f, // TR
        -0.16f, 0.48f,  -0.08f,   0.054f, 0.682f, 0.682f, // TL
        -0.16f,  0.0f,  -0.08f,   0.054f, 0.682f, 0.682f, // BL

        // belakang
        -0.16f, 0.0f,  0.08f,   0.054f, 0.682f, 0.682f, // BL
         0.16f, 0.0f,  0.08f,   0.054f, 0.682f, 0.682f, // BR
         0.16f,  0.48f,  0.08f,   0.054f, 0.682f, 0.682f, // TR
         0.16f,  0.48f,  0.08f,   0.054f, 0.682f, 0.682f, // TR
        -0.16f,  0.48f,  0.08f,   0.054f, 0.682f, 0.682f, // TL
        -0.16f, 0.0f,  0.08f,   0.054f, 0.682f, 0.682f, // BL

        // kiri
        -0.16f, 0.0f,  0.08f,   0.054f, 0.682f, 0.682f, // BL
        -0.16f, 0.0f, -0.08f,   0.054f, 0.682f, 0.682f, // BR
        -0.16f, 0.48f,  -0.08f,   0.054f, 0.682f, 0.682f, // TR
        -0.16f, 0.48f,  -0.08f,   0.054f, 0.682f, 0.682f, // TR
        -0.16f,  0.48f,  0.08f,   0.054f, 0.682f, 0.682f, // TL
        -0.16f, 0.0f,  0.08f,   0.054f, 0.682f, 0.682f, // BL

        // kanan
         0.16f, 0.0f, 0.08f,   0.054f, 0.682f, 0.682f, // BL
         0.16f, 0.0f,  -0.08f,   0.054f, 0.682f, 0.682f, // BR
         0.16f, 0.48f, -0.08f,   0.054f, 0.682f, 0.682f, // TR
         0.16f, 0.48f, -0.08f,   0.054f, 0.682f, 0.682f, // TR
         0.16f,  0.48f,  0.08f,   0.054f, 0.682f, 0.682f, // TL
         0.16f, 0.0f, 0.08f,   0.054f, 0.682f, 0.682f, // BL

        // bawah
        -0.16f, 0.0f, 0.08f,   0.054f, 0.682f, 0.682f, // BL
         0.16f, 0.0f, 0.08f,   0.054f, 0.682f, 0.682f, // BR
         0.16f, 0.0f,  -0.08f,   0.054f, 0.682f, 0.682f, // TR
         0.16f, 0.0f,  -0.08f,   0.054f, 0.682f, 0.682f, // TR
        -0.16f, 0.0f, -0.08f,   0.054f, 0.682f, 0.682f, // TL
        -0.16f, 0.0f,  0.08f,   0.054f, 0.682f, 0.682f, // BL

        // atas
        -0.16f, 0.48f, 0.08f,   0.054f, 0.682f, 0.682f, // BL
         0.16f, 0.48f, 0.08f,   0.054f, 0.682f, 0.682f, // BR
         0.16f, 0.48f,  -0.08f,   0.054f, 0.682f, 0.682f, // TR
         0.16f, 0.48f,  -0.08f,   0.054f, 0.682f, 0.682f, // TR
        -0.16f, 0.48f,  -0.08f,   0.054f, 0.682f, 0.682f, // TL
        -0.16f, 0.48f, 0.08f,   0.054f, 0.682f, 0.682f, // BL

        // TANGAN KANAN

        // depan V
         0.16f, 0.0f, -0.08f,   0.662f, 0.490f, 0.392f, // BL
         0.32f,  0.0f,  -0.08f,   0.662f, 0.490f, 0.392f, // BR
         0.32f, 0.48f,  -0.08f,   0.662f, 0.490f, 0.392f, // TR
         0.32f, 0.48f,  -0.08f,   0.662f, 0.490f, 0.392f, // TR
         0.16f, 0.48f, -0.08f,   0.662f, 0.490f, 0.392f, // TL
         0.16f, 0.0f, -0.08f,   0.662f, 0.490f, 0.392f, // BL

        // belakang V
         0.16f, 0.0f, 0.08f,   0.662f, 0.490f, 0.392f, // BL
         0.32f, 0.0f,  0.08f,   0.662f, 0.490f, 0.392f, // BR
         0.32f,  0.48f,  0.08f,   0.662f, 0.490f, 0.392f, // TR
         0.32f,  0.48f,  0.08f,   0.662f, 0.490f, 0.392f, // TR
         0.16f, 0.48f, 0.08f,   0.662f, 0.490f, 0.392f, // TL
         0.16f, 0.0f, 0.08f,   0.662f, 0.490f, 0.392f, // BL

        // kiri V
         0.16f, 0.0f, 0.08f,   0.662f, 0.490f, 0.392f, // BL
         0.16f, 0.0f, -0.08f,   0.662f, 0.490f, 0.392f, // BR
         0.16f, 0.48f, -0.08f,   0.662f, 0.490f, 0.392f, // TR
         0.16f, 0.48f, -0.08f,   0.662f, 0.490f, 0.392f, // TR
         0.16f, 0.48f, 0.08f,   0.662f, 0.490f, 0.392f, // TL
         0.16f, 0.0f, 0.08f,   0.662f, 0.490f, 0.392f, // BL

        // kanan V
         0.32f, 0.0f, 0.08f,   0.662f, 0.490f, 0.392f, // BL
         0.32f, 0.0f,  -0.08f,   0.662f, 0.490f, 0.392f, // BR
         0.32f, 0.48f, -0.08f,   0.662f, 0.490f, 0.392f, // TR
         0.32f, 0.48f, -0.08f,   0.662f, 0.490f, 0.392f, // TR
         0.32f, 0.48f,  0.08f,   0.662f, 0.490f, 0.392f, // TL
         0.32f, 0.0f, 0.08f,   0.662f, 0.490f, 0.392f, // BL

        // bawah
         0.16f, 0.0f, 0.08f,   0.662f, 0.490f, 0.392f, // BL
         0.32f, 0.0f, 0.08f,   0.662f, 0.490f, 0.392f, // BR
         0.32f, 0.0f,  -0.08f,   0.662f, 0.490f, 0.392f, // TR
         0.32f, 0.0f,  -0.08f,   0.662f, 0.490f, 0.392f, // TR
         0.16f, 0.0f, -0.08f,   0.662f, 0.490f, 0.392f, // TL
         0.16f, 0.0f,  0.08f,   0.662f, 0.490f, 0.392f, // BL

        // atas
         0.16f, 0.48f, 0.08f,   0.662f, 0.490f, 0.392f, // BL
         0.32f, 0.48f, 0.08f,   0.662f, 0.490f, 0.392f, // BR
         0.32f, 0.48f,  -0.08f,   0.662f, 0.490f, 0.392f, // TR
         0.32f, 0.48f,  -0.08f,   0.662f, 0.490f, 0.392f, // TR
         0.16f, 0.48f,  -0.08f,   0.662f, 0.490f, 0.392f, // TL
         0.16f, 0.48f, 0.08f,   0.662f, 0.490f, 0.392f, // BL

        // TANGAN KIRI

        // depan
        -0.32f,  0.0f,  -0.08f,   0.662f, 0.490f, 0.392f, // BL
        -0.16f, 0.0f, -0.08f,   0.662f, 0.490f, 0.392f, // BR
        -0.16f, 0.48f,  -0.08f,   0.662f, 0.490f, 0.392f, // TR
        -0.16f, 0.48f,  -0.08f,   0.662f, 0.490f, 0.392f, // TR
        -0.32f, 0.48f,  -0.08f,   0.662f, 0.490f, 0.392f, // TL
        -0.32f,  0.0f,  -0.08f,   0.662f, 0.490f, 0.392f, // BL

        // belakang
        -0.32f, 0.0f,  0.08f,   0.662f, 0.490f, 0.392f, // BL
        -0.16f, 0.0f,  0.08f,   0.662f, 0.490f, 0.392f, // BR
        -0.16f,  0.48f,  0.08f,   0.662f, 0.490f, 0.392f, // TR
        -0.16f,  0.48f,  0.08f,   0.662f, 0.490f, 0.392f, // TR
        -0.32f,  0.48f,  0.08f,   0.662f, 0.490f, 0.392f, // TL
        -0.32f, 0.0f,  0.08f,   0.662f, 0.490f, 0.392f, // BL

        // kiri
        -0.32f, 0.0f,  0.08f,   0.662f, 0.490f, 0.392f, // BL
        -0.32f, 0.0f, -0.08f,   0.662f, 0.490f, 0.392f, // BR
        -0.32f, 0.48f,  -0.08f,   0.662f, 0.490f, 0.392f, // TR
        -0.32f, 0.48f,  -0.08f,   0.662f, 0.490f, 0.392f, // TR
        -0.32f,  0.48f,  0.08f,   0.662f, 0.490f, 0.392f, // TL
        -0.32f, 0.0f,  0.08f,   0.662f, 0.490f, 0.392f, // BL

        // kanan
        -0.16f, 0.0f, 0.08f,   0.662f, 0.490f, 0.392f, // BL
        -0.16f, 0.0f, -0.08f,   0.662f, 0.490f, 0.392f, // BR
        -0.16f, 0.48f, -0.08f,   0.662f, 0.490f, 0.392f, // TR
        -0.16f, 0.48f, -0.08f,   0.662f, 0.490f, 0.392f, // TR
        -0.16f, 0.48f, 0.08f,   0.662f, 0.490f, 0.392f, // TL
        -0.16f, 0.0f, 0.08f,   0.662f, 0.490f, 0.392f, // BL

        // bawah
        -0.32f, 0.0f, 0.08f,   0.662f, 0.490f, 0.392f, // BL
        -0.16f, 0.0f, 0.08f,   0.662f, 0.490f, 0.392f, // BR
        -0.16f, 0.0f,  -0.08f,   0.662f, 0.490f, 0.392f, // TR
        -0.16f, 0.0f,  -0.08f,   0.662f, 0.490f, 0.392f, // TR
        -0.32f, 0.0f, -0.08f,   0.662f, 0.490f, 0.392f, // TL
        -0.32f, 0.0f,  0.08f,   0.662f, 0.490f, 0.392f, // BL

        // atas
        -0.32f, 0.48f, 0.08f,   0.662f, 0.490f, 0.392f, // BL
        -0.16f, 0.48f, 0.08f,   0.662f, 0.490f, 0.392f, // BR
        -0.16f, 0.48f,  -0.08f,   0.662f, 0.490f, 0.392f, // TR
        -0.16f, 0.48f,  -0.08f,   0.662f, 0.490f, 0.392f, // TR
        -0.32f, 0.48f,  -0.08f,   0.662f, 0.490f, 0.392f, // TL
        -0.32f, 0.48f, 0.08f,   0.662f, 0.490f, 0.392f, // BL

        // KAKI KIRI

        // depan
        -0.16f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BL
        0.0f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BR
        0.0f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.0f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // TR
        -0.16f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // TL
        -0.16f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BL

        // belakang
        -0.16f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // BL
        0.0f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // BR
        0.0f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.0f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TR
        -0.16f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TL
        -0.16f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // BL

        // kiri
        -0.16f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BL
        -0.16f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // BR
        -0.16f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TR
        -0.16f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TR
        -0.16f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // TL
        -0.16f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BL
        // kanan
        0.0f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // BL
        0.0f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BR
        0.0f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.0f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.0f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TL
        0.0f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // BL
    // bawah
        -0.16f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BL
        0.0f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BR
        0.0f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.0f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // TR
        -0.16f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // TL
        -0.16f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BL
        // atas
        -0.16f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // BL
        0.0f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // BR
        0.0f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.0f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TR
        -0.16f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TL
        -0.16f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // BL

        // KAKI KANAN

        // depan
        0.0f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BL
        0.16f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BR
        0.16f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.16f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.0f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // TL
        0.0f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BL

        // belakang
        0.0f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // BL
        0.16f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // BR
        0.16f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.16f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.0f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TL
        0.0f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // BL

        // kiri
        0.0f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // BL
        0.0f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BR
        0.0f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.0f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.0f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TL
        0.0f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // BL

        // kanan
        0.16f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // BL
        0.16f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BR
        0.16f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.16f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.16f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TL
        0.16f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // BL

        // bawah
        0.0f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BL
        0.16f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BR
        0.16f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.16f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.0f, -0.48f, 0.08f, 0.286f, 0.274f, 0.592f, // TL
        0.0f, -0.48f, -0.08f, 0.286f, 0.274f, 0.592f, // BL

        // atas
        0.0f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // BL
        0.16f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f, // BR
        0.16f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.16f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TR
        0.0f, 0.0f, 0.08f, 0.286f, 0.274f, 0.592f, // TL
        0.0f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f // BL
    };

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f)
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // -------------------------- OBJEK 2 ----------------------------------

    float vertices_floor[] = {
         1.0f, -0.48f, -1.0f,   0.419f, 0.419f, 0.419f,  // top right
         1.0f, -0.48f, 1.0f,    0.419f, 0.419f, 0.419f,// bottom right
        -1.0f, -0.48f, 1.0f,    0.419f, 0.419f, 0.419f,// bottom left
        -1.0f, -0.48f, -1.0f,   0.419f, 0.419f, 0.419f  // top left 
    };
    unsigned int indices_floor[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO_floor, VAO_floor, EBO_floor;
    glGenVertexArrays(1, &VAO_floor);
    glGenBuffers(1, &VBO_floor);
    glGenBuffers(1, &EBO_floor);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO_floor);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_floor);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_floor), vertices_floor, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_floor);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_floor), indices_floor, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //// bind textures on corresponding texture units
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, texture1);
        //glActiveTexture(GL_TEXTURE1);
        //glBindTexture(GL_TEXTURE_2D, texture2);

        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 1; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 216);
        }

        // merender object ke 2
        glBindVertexArray(VAO_floor);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO_floor);
    glDeleteBuffers(1, &VBO_floor);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}