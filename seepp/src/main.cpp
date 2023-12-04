#include <cstdio>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <format>

#define WIDTH 800
#define HEIGHT 600

void handleInput(GLFWwindow* window);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

int main(int argc, char *argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "[glad] GL with GLFW", NULL, NULL);
    if (window == nullptr) {
        std::cout << "coul not create window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    int version = gladLoadGL(glfwGetProcAddress);
    if (!version) {
        std::cout << "could not init Glad" << std::endl;
        return -1;
    }
    std::cout << std::format("GL v{}.{}\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // main loop
    while (!glfwWindowShouldClose(window)) {
        handleInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void handleInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
