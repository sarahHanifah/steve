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

// movement steve
float posX = 0.0f;
float posY = 0.0f;
float posY_hand = 0.48f;
float posX_rf = 0.0f;
float posX_lf = 0.16f;
float posX_rh = -0.16f;
float posX_lh = 0.32f;
float posZ = 0.0f;
float steveSpeed = 0.007f;
float steveSwing = 2.0f;
float depan = 0.0f;
float belakang = 0.0f;

bool status = true;

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
    Shader ShaderFace("face.vs", "face.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    // -------------------------- OBJEK 1 (KEPALA DAN BADAN) ----------------------------------

    float vertices[] = {

        // KEPALA
        // 
        // depan
        -0.16f, 0.48f, -0.16f,   0.18f, 0.121f, 0.058f, // BL
         0.16f, 0.48f, -0.16f,   0.18f, 0.121f, 0.058f, // BR
         0.16f,  0.8f, -0.16f,   0.18f, 0.121f, 0.058f, // TR
         0.16f,  0.8f, -0.16f,   0.18f, 0.121f, 0.058f, // TR
        -0.16f,  0.8f, -0.16f,   0.18f, 0.121f, 0.058f, // TL
        -0.16f, 0.48f, -0.16f,   0.18f, 0.121f, 0.058f, // BL

        // kiri
        -0.16f, 0.48f, 0.16f,   0.18f, 0.121f, 0.058f, // BL
        -0.16f, 0.48f, -0.16f,   0.18f, 0.121f, 0.058f, // BR
        -0.16f,  0.8f, -0.16f,   0.18f, 0.121f, 0.058f, // TR
        -0.16f,  0.8f, -0.16f,   0.18f, 0.121f, 0.058f, // TR
        -0.16f,  0.8f, 0.16f,   0.18f, 0.121f, 0.058f, // TL
        -0.16f, 0.48f, 0.16f,   0.18f, 0.121f, 0.058f, // BL

        // kanan
         0.16f, 0.48f, 0.16f,   0.18f, 0.121f, 0.058f, // BL
         0.16f, 0.48f, -0.16f,   0.18f, 0.121f, 0.058f, // BR
         0.16f,  0.8f, -0.16f,   0.18f, 0.121f, 0.058f, // TR
         0.16f,  0.8f, -0.16f,   0.18f, 0.121f, 0.058f, // TR
         0.16f,  0.8f, 0.16f,   0.18f, 0.121f, 0.058f, // TL
         0.16f, 0.48f, 0.16f,   0.18f, 0.121f, 0.058f, // BL

        // bawah
        -0.16f, 0.48f, 0.16f,   0.662f, 0.490f, 0.392f, // BL
         0.16f, 0.48f, 0.16f,   0.662f, 0.490f, 0.392f, // BR
         0.16f, 0.48f, -0.16f,   0.662f, 0.490f, 0.392f, // TR
         0.16f, 0.48f, -0.16f,   0.662f, 0.490f, 0.392f, // TR
        -0.16f, 0.48f, -0.16f,   0.662f, 0.490f, 0.392f, // TL
        -0.16f, 0.48f, 0.16f,   0.662f, 0.490f, 0.392f, // BL

        // atas
        -0.16f,  0.8f, 0.16f,   0.18f, 0.121f, 0.058f, // BL
         0.16f,  0.8f, 0.16f,   0.18f, 0.121f, 0.058f, // BR
         0.16f,  0.8f, -0.16f,   0.18f, 0.121f, 0.058f, // TR
         0.16f,  0.8f, -0.16f,   0.18f, 0.121f, 0.058f, // TR
        -0.16f,  0.8f, -0.16f,   0.18f, 0.121f, 0.058f, // TL
        -0.16f,  0.8f, 0.16f,   0.18f, 0.121f, 0.058f, // BL

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
        -0.16f, 0.48f, 0.08f,   0.054f, 0.682f, 0.682f // BL
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

    // -------------------------- OBJEK 1.5 (MUKA) ----------------------------------

    float vertices_face[] = {
        // depan
         0.16f,  0.8f, 0.16f,   1.0f, 1.0f, // TR
         0.16f, 0.48f, 0.16f,   1.0f, 0.0f, // BR
        -0.16f, 0.48f, 0.16f,   0.0f, 0.0f, // BL
        -0.16f,  0.8f, 0.16f,   0.0f, 1.0f // TL
    };

    unsigned int indices_face[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VBO_face, VAO_face, EBO_face;
    glGenVertexArrays(1, &VAO_face);
    glGenBuffers(1, &VBO_face);
    glGenBuffers(1, &EBO_face);

    glBindVertexArray(VAO_face);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_face);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_face), vertices_face, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_face);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_face), indices_face, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // load and create a texture 
    // -------------------------
    unsigned int ourTexture;
    // texture 1
    // ---------
    glGenTextures(1, &ourTexture);
    glBindTexture(GL_TEXTURE_2D, ourTexture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load(("Textures/1.jpg"), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    
    // -------------------------- OBJEK 2 (TANGAN) ----------------------------------

    float vertices2[] = {

        // TANGAN

        // depan
        -0.16f, -0.48f, -0.08f, 0.662f, 0.490f, 0.392f, // BL
        0.0f, -0.48f, -0.08f, 0.662f, 0.490f, 0.392f, // BR
        0.0f, 0.0f, -0.08f, 0.662f, 0.490f, 0.392f, // TR
        0.0f, 0.0f, -0.08f, 0.662f, 0.490f, 0.392f, // TR
        -0.16f, 0.0f, -0.08f, 0.662f, 0.490f, 0.392f, // TL
        -0.16f, -0.48f, -0.08f, 0.662f, 0.490f, 0.392f, // BL

        // belakang
        -0.16f, -0.48f, 0.08f, 0.662f, 0.490f, 0.392f, // BL
        0.0f, -0.48f, 0.08f, 0.662f, 0.490f, 0.392f, // BR
        0.0f, 0.0f, 0.08f, 0.662f, 0.490f, 0.392f, // TR
        0.0f, 0.0f, 0.08f, 0.662f, 0.490f, 0.392f, // TR
        -0.16f, 0.0f, 0.08f, 0.662f, 0.490f, 0.392f, // TL
        -0.16f, -0.48f, 0.08f, 0.662f, 0.490f, 0.392f, // BL

        // kiri
        -0.16f, -0.48f, -0.08f, 0.662f, 0.490f, 0.392f, // BL
        -0.16f, -0.48f, 0.08f, 0.662f, 0.490f, 0.392f, // BR
        -0.16f, 0.0f, 0.08f, 0.662f, 0.490f, 0.392f, // TR
        -0.16f, 0.0f, 0.08f, 0.662f, 0.490f, 0.392f, // TR
        -0.16f, 0.0f, -0.08f, 0.662f, 0.490f, 0.392f, // TL
        -0.16f, -0.48f, -0.08f, 0.662f, 0.490f, 0.392f, // BL
        // kanan
        0.0f, -0.48f, 0.08f, 0.662f, 0.490f, 0.392f, // BL
        0.0f, -0.48f, -0.08f, 0.662f, 0.490f, 0.392f, // BR
        0.0f, 0.0f, -0.08f, 0.662f, 0.490f, 0.392f, // TR
        0.0f, 0.0f, -0.08f, 0.662f, 0.490f, 0.392f, // TR
        0.0f, 0.0f, 0.08f, 0.662f, 0.490f, 0.392f, // TL
        0.0f, -0.48f, 0.08f, 0.662f, 0.490f, 0.392f, // BL
        // bawah
        -0.16f, -0.48f, -0.08f, 0.662f, 0.490f, 0.392f, // BL
        0.0f, -0.48f, -0.08f, 0.662f, 0.490f, 0.392f, // BR
        0.0f, -0.48f, 0.08f, 0.662f, 0.490f, 0.392f, // TR
        0.0f, -0.48f, 0.08f, 0.662f, 0.490f, 0.392f, // TR
        -0.16f, -0.48f, 0.08f, 0.662f, 0.490f, 0.392f, // TL
        -0.16f, -0.48f, -0.08f, 0.662f, 0.490f, 0.392f, // BL
        // atas
        -0.16f, 0.0f, -0.08f, 0.662f, 0.490f, 0.392f, // BL
        0.0f, 0.0f, -0.08f, 0.662f, 0.490f, 0.392f, // BR
        0.0f, 0.0f, 0.08f, 0.662f, 0.490f, 0.392f, // TR
        0.0f, 0.0f, 0.08f, 0.662f, 0.490f, 0.392f, // TR
        -0.16f, 0.0f, 0.08f, 0.662f, 0.490f, 0.392f, // TL
        -0.16f, 0.0f, -0.08f, 0.662f, 0.490f, 0.392f // BL
    };

    unsigned int VBO2, VAO2;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // -------------------------- OBJEK 3 (KAKI) ----------------------------------

    float vertices3[] = {

        // KAKI

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
        -0.16f, 0.0f, -0.08f, 0.286f, 0.274f, 0.592f // BL
    };

    unsigned int VBO3, VAO3;
    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);

    glBindVertexArray(VAO3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // -------------------------- OBJEK 4 (LANTAI) ----------------------------------

    float vertices_floor[] = {
         1.5f, -0.48f, -1.5f,   0.419f, 0.419f, 0.419f,  // top right
         1.5f, -0.48f, 1.5f,    0.419f, 0.419f, 0.419f, // bottom right
        -1.5f, -0.48f, 1.5f,    0.419f, 0.419f, 0.419f, // bottom left
        -1.5f, -0.48f, -1.5f,   0.419f, 0.419f, 0.419f  // top left 
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

        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ourShader.setMat4("view", view);


        // merender object kepala dan badan
        glBindVertexArray(VAO);
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(posX, posY, posZ));
        float angle = 0.0f;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 66);

        // merender object tangan kanan
        glBindVertexArray(VAO2);
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model_rh = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model_rh = glm::translate(model_rh, glm::vec3(posX_rh, posY_hand, posZ));
        float angle_rh = depan;
        model_rh = glm::rotate(model_rh, glm::radians(angle_rh), glm::vec3(1.0f, 0.0f, 0.0f));
        ourShader.setMat4("model", model_rh);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // merender object tangan kiri
        glBindVertexArray(VAO2);
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model_lh = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model_lh = glm::translate(model_lh, glm::vec3(posX_lh, posY_hand, posZ));
        float angle_lh = belakang;
        model_lh = glm::rotate(model_lh, glm::radians(angle_lh), glm::vec3(1.0f, 0.0f, 0.0f));
        ourShader.setMat4("model", model_lh);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // merender object kaki kanan
        glBindVertexArray(VAO3);
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model_rf = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model_rf = glm::translate(model_rf, glm::vec3(posX, posY, posZ));
        float angle_rf = belakang;
        model_rf = glm::rotate(model_rf, glm::radians(angle_rf), glm::vec3(1.0f, 0.0f, 0.0f));
        ourShader.setMat4("model", model_rf);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // merender object kaki kiri
        glBindVertexArray(VAO3);
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model_lf = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model_lf = glm::translate(model_lf, glm::vec3(posX_lf, posY, posZ));
        float angle_lf = depan;
        model_lf = glm::rotate(model_lf, glm::radians(angle_lf), glm::vec3(1.0f, 0.0f, 0.0f));
        ourShader.setMat4("model", model_lf);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // 
        // 
        // merender object lantai
        glBindVertexArray(VAO_floor);
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model_floor = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model_floor = glm::translate(model_floor, glm::vec3(0.0f, 0.0f, 0.0f));
        float angle_floor = 0.0f;
        model_floor = glm::rotate(model_floor, glm::radians(angle_floor), glm::vec3(1.0f, 1.0f, 1.0f));
        ourShader.setMat4("model", model_floor);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // bind textures on corresponding texture units

        glBindTexture(GL_TEXTURE_2D, ourTexture);
        // activate shader
        ShaderFace.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection_face = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ShaderFace.setMat4("projection", projection_face);

        // camera/view transformation
        glm::mat4 view_face = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ShaderFace.setMat4("view", view_face);

        // merender object face (muka)
        glBindVertexArray(VAO_face);
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model_face = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model_face = glm::translate(model_face, glm::vec3(posX, posY, posZ));
        float angle_face = 0.0f;
        model_face = glm::rotate(model_face, glm::radians(angle_face), glm::vec3(1.0f, 1.0f, 1.0f));
        ShaderFace.setMat4("model", model_face);
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
    glDeleteVertexArrays(1, &VAO_face);
    glDeleteBuffers(1, &VBO_face);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);
    glDeleteVertexArrays(1, &VAO3);
    glDeleteBuffers(1, &VBO3);
    glDeleteVertexArrays(1, &VAO_floor);
    glDeleteBuffers(1, &VBO_floor);
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
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (posX < 1.34f) {
            posX = posX + steveSpeed;
            posX_lf = posX_lf + steveSpeed;
            posX_lh = posX_lh + steveSpeed;
            posX_rf = posX_rf + steveSpeed;
            posX_rh = posX_rh + steveSpeed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (posX > -1.34f) {
            posX = posX - steveSpeed;
            posX_lf = posX_lf - steveSpeed;
            posX_lh = posX_lh - steveSpeed;
            posX_rf = posX_rf - steveSpeed;
            posX_rh = posX_rh - steveSpeed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        if (!(posZ <= -1.34f))
            posZ = posZ - steveSpeed;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        if (!(posZ >= 1.34f))
            posZ = posZ + steveSpeed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (status) {
            if (depan >= 45.0f) {
                depan = 45.0f;
                belakang = -45.0f;
                status = false;
            }
            else {
                depan = depan + steveSwing;
                belakang = belakang - steveSwing;
            }
        }
        else {
            if (depan <= -45.0f) {
                depan = -45.0f;
                belakang = 45.0f;
                status = true;
            }
            else {
                depan = depan - steveSwing;
                belakang = belakang + steveSwing;
            }
        }
    }
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