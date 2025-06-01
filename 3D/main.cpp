#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "shaderClass.h"
#include "Texture.h"
#include "VAO.h"

// Window dimensions
const unsigned int width = 1920;
const unsigned int height = 1080;

// Vertices for a cube (will be used for all objects)
GLfloat vertices[] = {
    // Positions          // Normals           // Texture coords
    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

    // Left face
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    // Right face
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     // Bottom face
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

     // Top face
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

GLfloat skyBoxVertices[] = {
    // Back face (col 3, row 1)
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  3.0f * 0.25f, 1.0f * 0.333333f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  4.0f * 0.25f, 1.0f * 0.333333f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  4.0f * 0.25f, 2.0f * 0.333333f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  4.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  3.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  3.0f * 0.25f, 1.0f * 0.333333f,

    // Front face (col 1, row 1)
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f * 0.25f, 1.0f * 0.333333f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  2.0f * 0.25f, 1.0f * 0.333333f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  2.0f * 0.25f, 2.0f * 0.333333f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  2.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f * 0.25f, 1.0f * 0.333333f,

    // Left face (col 0, row 1)
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f * 0.25f, 1.0f * 0.333333f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f * 0.25f, 1.0f * 0.333333f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f * 0.25f, 1.0f * 0.333333f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f * 0.25f, 2.0f * 0.333333f,

    // Right face (col 2, row 1)
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  3.0f * 0.25f, 2.0f * 0.333333f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  2.0f * 0.25f, 2.0f * 0.333333f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  2.0f * 0.25f, 1.0f * 0.333333f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  2.0f * 0.25f, 1.0f * 0.333333f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  3.0f * 0.25f, 1.0f * 0.333333f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  3.0f * 0.25f, 2.0f * 0.333333f,

     // Bottom face (col 1, row 2) - ODWRÓCONE V
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f * 0.25f, 0.0f * 0.333333f,  // V: 0.0 zamiast 2/3
      0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  2.0f * 0.25f, 0.0f * 0.333333f,  // V: 0.0 zamiast 2/3
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  2.0f * 0.25f, 1.0f * 0.333333f,  // V: 1/3 zamiast 1
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  2.0f * 0.25f, 1.0f * 0.333333f,  // V: 1/3 zamiast 1
     -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f * 0.25f, 1.0f * 0.333333f,  // V: 1/3 zamiast 1
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f * 0.25f, 0.0f * 0.333333f,  // V: 0.0 zamiast 2/3

     // Top face (col 1, row 0) - ODWRÓCONE V i poprawiona kolejnoœæ
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f * 0.25f, 3.0f * 0.333333f,  // V: 1.0 zamiast 1/3
     -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f * 0.25f, 2.0f * 0.333333f,  // V: 2/3 zamiast 0
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  2.0f * 0.25f, 2.0f * 0.333333f,  // V: 2/3 zamiast 0
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  2.0f * 0.25f, 2.0f * 0.333333f,  // V: 2/3 zamiast 0
      0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  2.0f * 0.25f, 3.0f * 0.333333f,  // V: 1.0 zamiast 1/3
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f * 0.25f, 3.0f * 0.333333f   // V: 1.0 zamiast 1/3
};

// Camera variables
glm::vec3 cameraPos = glm::vec3(0.0f, 2.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Timing
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f;

// Mouse variables
bool firstMouse = true;
float lastX = width / 2.0f;
float lastY = height / 2.0f;
float yaw = -90.0f;
float pitch = 0.0f;

// Creeper position and movement
glm::vec3 creeperPos = glm::vec3(3.0f, 0.0f, 3.0f);  // Starts right-front of house
glm::vec3 creeperFront = glm::vec3(0.0f, 0.0f, -1.0f); // Initial facing direction
//float creeperSpeed = 0.0f;
//float maxSpeed = 2.5f;
//float acceleration = 1.5f;
//float deceleration = 2.0f;
//bool creeperMoving = false;

// Light position (sun)
glm::vec3 lightPos = glm::vec3(5.0f, 5.0f, 5.0f);
float lightAngle = 0.0f;

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void renderCube(Shader& shader, Texture& texture, glm::vec3 position, glm::vec3 scale = glm::vec3(1.0f));
void renderSkyBox(Shader& shader, Texture& skyBoxTex);
void renderTree(Shader& shader, Texture& woodTex, Texture& leavesTex);
void renderHouse(Shader& shader, Texture& houseTex);
void renderCreeper(Shader& shader, Texture& creeperTex);
void updateCreeper(float deltaTime, GLFWwindow* window);

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(width, height, "Maincamp - Projekt", NULL, NULL);
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Configure global OpenGL state
    glEnable(GL_DEPTH_TEST);

    // Build and compile shaders
    Shader defaultShader("default.vert", "default.frag");
    Shader lightCubeShader("lightCube.vert", "lightCube.frag");
    Shader skyBoxShader("skyBox.vert", "skyBox.frag");

    // Load textures
    Texture woodTex("tree.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture leavesTex("leaves.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture houseTex("house.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture creeperTex("creeper.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture groundTex("grass.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture skyTex("skyBox.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    VAO cubeVAO;
    cubeVAO.Bind();
    VBO cubeVBO(vertices, sizeof(vertices));
    cubeVAO.LinkAttrib(cubeVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    cubeVAO.LinkAttrib(cubeVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    cubeVAO.LinkAttrib(cubeVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    cubeVAO.Unbind();
    cubeVBO.Unbind();

    VAO skyVAO;
    skyVAO.Bind();
    VBO skyVBO(skyBoxVertices, sizeof(skyBoxVertices));
    skyVAO.LinkAttrib(skyVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    skyVAO.LinkAttrib(skyVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    skyVAO.LinkAttrib(skyVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    skyVAO.Unbind();
    skyVBO.Unbind();

    glm::vec4 defaultSkyColor = glm::vec4(0.53f, 0.81f, 0.92f, 1.0f);
    glm::vec4 nightColor = glm::vec4(0.13f, 0.31f, 0.42f, 1.0f);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window);

        // Update light position (sun movement)
        lightAngle += 0.5f * deltaTime;
        if (lightAngle > 360.0f) lightAngle -= 360.0f;
        lightPos.x = 30.0f * cos(lightAngle);
        lightPos.y = 30.0f * sin(lightAngle);

        // Creeper movement when button is pressed
        updateCreeper(deltaTime, window);

        // Clear screen
        glm::vec4 skyColor = glm::mix(nightColor, defaultSkyColor, sin(lightAngle));
        glClearColor(skyColor.x, skyColor.y, skyColor.z, skyColor.w); // Sky blue
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate shader
        defaultShader.Activate();

        // Pass light properties to shader
        glm::vec4 defaultLightColor = glm::vec4(1.0f, 1.0f, 0.9f, 1.0f); // Slightly yellow sunlight
        GLuint lightColorLoc = glGetUniformLocation(defaultShader.ID, "lightColor");
        glm::vec3 lightColor = glm::mix(nightColor, defaultLightColor, sin(lightAngle));
        glUniform3f(lightColorLoc, lightColor.x, lightColor.y, lightColor.z);

        GLuint lightPosLoc = glGetUniformLocation(defaultShader.ID, "lightPos");
        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

        GLuint viewPosLoc = glGetUniformLocation(defaultShader.ID, "viewPos");
        glUniform3f(viewPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);

        // Material properties (Phong shading)
        GLuint shininessLoc = glGetUniformLocation(defaultShader.ID, "material.shininess");
        glUniform1f(shininessLoc, 32.0f);

        // View/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(100.0f), (float)width / (float)height, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        GLuint projectionLoc = glGetUniformLocation(defaultShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

        GLuint viewLoc = glGetUniformLocation(defaultShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        // Render ground
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
        model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));

        GLuint modelLoc = glGetUniformLocation(defaultShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

        groundTex.Bind();
        //glBindVertexArray(vao);
        cubeVAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Render objects
        renderTree(defaultShader, woodTex, leavesTex);
        renderHouse(defaultShader, houseTex);
        renderCreeper(defaultShader, creeperTex);

        // Render sky
        skyVAO.Bind();
        skyBoxShader.Activate();

        GLuint skyBoxLightColorLoc = glGetUniformLocation(skyBoxShader.ID, "lightColor");
        glm::vec3 skyBoxlightColor = glm::mix(nightColor, defaultLightColor, sin(lightAngle));
        glUniform3f(skyBoxLightColorLoc, skyBoxlightColor.x, skyBoxlightColor.y, skyBoxlightColor.z);

        GLuint skyProjectionLoc = glGetUniformLocation(skyBoxShader.ID, "projection");
        glUniformMatrix4fv(skyProjectionLoc, 1, GL_FALSE, &projection[0][0]);

        GLuint skyViewLoc = glGetUniformLocation(skyBoxShader.ID, "view");
        glUniformMatrix4fv(skyViewLoc, 1, GL_FALSE, &view[0][0]);

        renderSkyBox(skyBoxShader, skyTex);

        // Also draw the light source (sun)
        lightCubeShader.Activate();

        GLuint lightProjectionLoc = glGetUniformLocation(lightCubeShader.ID, "projection");
        glUniformMatrix4fv(lightProjectionLoc, 1, GL_FALSE, &projection[0][0]);

        GLuint lightViewLoc = glGetUniformLocation(lightCubeShader.ID, "view");
        glUniformMatrix4fv(lightViewLoc, 1, GL_FALSE, &view[0][0]);

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(5.0f));

        GLuint lightModelLoc = glGetUniformLocation(lightCubeShader.ID, "model");
        glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, &model[0][0]);

        //glBindVertexArray(vao);
        cubeVAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    cubeVAO.Delete();
    cubeVBO.Delete();
    woodTex.Delete();
    leavesTex.Delete();
    houseTex.Delete();
    creeperTex.Delete();
    groundTex.Delete();
    defaultShader.Delete();
    lightCubeShader.Delete();

    glfwTerminate();
    return 0;
}

void updateCreeper(float deltaTime, GLFWwindow* window) {
    const float moveSpeed = 3.0f * deltaTime; // Base movement speed
    bool moved = false;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        creeperPos.z -= moveSpeed;
        creeperFront = glm::vec3(0.0f, 0.0f, -1.0f);
        moved = true;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        creeperPos.z += moveSpeed;
        creeperFront = glm::vec3(0.0f, 0.0f, 1.0f);
        moved = true;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        creeperPos.x -= moveSpeed;
        creeperFront = glm::vec3(-1.0f, 0.0f, 0.0f);
        moved = true;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        creeperPos.x += moveSpeed;
        creeperFront = glm::vec3(1.0f, 0.0f, 0.0f);
        moved = true;
    }

    // Keep creeper within bounds
    creeperPos.x = glm::clamp(creeperPos.x, -5.0f, 5.0f);
    creeperPos.z = glm::clamp(creeperPos.z, -5.0f, 5.0f);

    // Only rotate if we actually moved
    if (!moved) {
        // Keep the current facing direction
    }
}

void renderCube(Shader& shader, Texture& texture, glm::vec3 position, glm::vec3 scale)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // Get the uniform location and set the matrix directly
    GLuint modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

    texture.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void renderSkyBox(Shader& shader, Texture& skyBoxTex)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(100.0f));

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &model[0][0]);
    skyBoxTex.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void renderTree(Shader& shader, Texture& woodTex, Texture& leavesTex)
{
    // Trunk (4 blocks tall)
    for (int i = 0; i < 4; i++) {
        renderCube(shader, woodTex, glm::vec3(2.0f, 0.5f + i, 0.0f));
    }

    // Leaves on top
    renderCube(shader, leavesTex, glm::vec3(2.0f, 3.5f, 0.0f));
    renderCube(shader, leavesTex, glm::vec3(2.0f, 4.5f, 0.0f));
    renderCube(shader, leavesTex, glm::vec3(1.0f, 3.5f, 0.0f));
    renderCube(shader, leavesTex, glm::vec3(3.0f, 3.5f, 0.0f));
    renderCube(shader, leavesTex, glm::vec3(2.0f, 3.5f, 1.0f));
    renderCube(shader, leavesTex, glm::vec3(2.0f, 3.5f, -1.0f));
}

void renderHouse(Shader& shader, Texture& houseTex)
{
    // Base (4x4x4)
    for (int x = 0; x < 4; x++) {
        for (int z = 0; z < 4; z++) {
            for (int y = 0; y < 4; y++) {
                // Only render outer walls and roof
                if (y == 0 || y == 3 || x == 0 || x == 3 || z == 0 || z == 3) {
                    // Skip some blocks for door and windows
                    if (!(y == 0 && x == 1 && z == 0)) { // Door
                        if (!(y == 1 || y == 2) || !((x == 1 && (z == 1 || z == 2)) && !(z == 1 && (x == 1 || x == 2)))) { // Windows
                            renderCube(shader, houseTex, glm::vec3(-5.0f + x, 0.5f + y, -3.0f + z));
                        }
                    }
                }
            }
        }
    }
}

void renderCreeper(Shader& shader, Texture& creeperTex)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, creeperPos);
    model = glm::rotate(model, atan2(creeperFront.x, creeperFront.z), glm::vec3(0.0f, 1.0f, 0.0f));

    // Bottom block
    glm::mat4 bottomModel = model;
    bottomModel = glm::translate(bottomModel, glm::vec3(0.0f, 0.5f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &bottomModel[0][0]);
    creeperTex.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Top block
    glm::mat4 topModel = model;
    topModel = glm::translate(topModel, glm::vec3(0.0f, 1.5f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &topModel[0][0]);
    creeperTex.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 5.0f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraUp;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

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

    float sensitivity = 0.1f;
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // Adjust field of view
    float fov = 45.0f;
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}