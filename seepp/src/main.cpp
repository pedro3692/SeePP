#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <format>
#include <iostream>

#include "shader.h"
#include "shader_program.h"
#include "vertex_array.h"
#include "vertex_buffer.h"

#define WIDTH 800
#define HEIGHT 600

using namespace SeePP;

void handleInput(GLFWwindow *window);
void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id,
                            GLenum severity, GLsizei length,
                            const char *message, const void *userParam);

bool g_wireframe_mode = false;

int main(int argc, char *argv[]) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "[glad] GL with GLFW", NULL, NULL);
  if (window == nullptr) {
    std::cout << "could not create window\n";
    return -1;
  }

  glfwMakeContextCurrent(window);

  int version = gladLoadGL(glfwGetProcAddress);
  if (!version) {
    std::cout << "could not init Glad" << std::endl;
    return -1;
  }
  std::cout << std::format("GL v{}.{}\n", GLAD_VERSION_MAJOR(version),
                           GLAD_VERSION_MINOR(version));

  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
  int flags;
  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr,
                          GL_TRUE);
  }
  glViewport(0, 0, WIDTH, HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  {
    ShaderProgram shader_program;
    {
      // TODO: load shaders source from file
      const char *vertexShaderSource =
          "#version 330 core\n"
          "layout (location = 0) in vec3 aPos;\n"
          "void main()\n"
          "{\n"
          "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
          "}\0";
      Shader vertex_shader(ShaderType::Vertex, vertexShaderSource);

      const char *fragmentShaderSource =
          "#version 330 core\n"
          "out vec4 FragColor;\n"
          "void main()\n"
          "{\n"
          "   FragColor = vec4(1.0f, 0.0f, 0.0f, 0.1f);\n"
          "}\0";
      Shader fragment_shader(ShaderType::Fragment, fragmentShaderSource);

      shader_program.AttachShader(vertex_shader.id());
      shader_program.AttachShader(fragment_shader.id());
      shader_program.Link();
    }

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // v1
        0.5f,  -0.5f, 0.0f, // v2
        -0.0f, 0.5f,  0.0f, // v3
    };

    VertexArray vertex_array;
    vertex_array.Bind();

    VertexBuffer vertex_buffer;
    vertex_buffer.Bind();
    vertex_buffer.BindData(vertices, sizeof(vertices), BindType::Static);

    vertex_array.BindAttributePointer(0, 3, DataType::F32, false,
                                3 * sizeof(float), (void *)0);

    uint32_t polyMode = GL_FILL;
    // main loop
    while (!glfwWindowShouldClose(window)) {
      handleInput(window);

      polyMode = g_wireframe_mode ? GL_LINE : GL_FILL;

      glPolygonMode(GL_FRONT_AND_BACK, polyMode);
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      vertex_array.Bind();
      shader_program.Use();
      glDrawArrays(GL_TRIANGLES, 0, 3);

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }

  glfwTerminate();
  return 0;
}

void handleInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    g_wireframe_mode = !g_wireframe_mode;
  }
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id,
                            GLenum severity, GLsizei length,
                            const char *message, const void *userParam) {
  // ignore non-significant error/warning codes
  if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
    return;

  std::cout << "---------------" << std::endl;
  std::cout << "Debug message (" << id << "): " << message << std::endl;

  switch (source) {
  case GL_DEBUG_SOURCE_API:
    std::cout << "Source: API";
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    std::cout << "Source: Window System";
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    std::cout << "Source: Shader Compiler";
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:
    std::cout << "Source: Third Party";
    break;
  case GL_DEBUG_SOURCE_APPLICATION:
    std::cout << "Source: Application";
    break;
  case GL_DEBUG_SOURCE_OTHER:
    std::cout << "Source: Other";
    break;
  }
  std::cout << std::endl;

  switch (type) {
  case GL_DEBUG_TYPE_ERROR:
    std::cout << "Type: Error";
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    std::cout << "Type: Deprecated Behaviour";
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    std::cout << "Type: Undefined Behaviour";
    break;
  case GL_DEBUG_TYPE_PORTABILITY:
    std::cout << "Type: Portability";
    break;
  case GL_DEBUG_TYPE_PERFORMANCE:
    std::cout << "Type: Performance";
    break;
  case GL_DEBUG_TYPE_MARKER:
    std::cout << "Type: Marker";
    break;
  case GL_DEBUG_TYPE_PUSH_GROUP:
    std::cout << "Type: Push Group";
    break;
  case GL_DEBUG_TYPE_POP_GROUP:
    std::cout << "Type: Pop Group";
    break;
  case GL_DEBUG_TYPE_OTHER:
    std::cout << "Type: Other";
    break;
  }
  std::cout << std::endl;

  switch (severity) {
  case GL_DEBUG_SEVERITY_HIGH:
    std::cout << "Severity: high";
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    std::cout << "Severity: medium";
    break;
  case GL_DEBUG_SEVERITY_LOW:
    std::cout << "Severity: low";
    break;
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    std::cout << "Severity: notification";
    break;
  }
  std::cout << std::endl;
  std::cout << std::endl;
}
