#include <cstddef>
#include <cstring>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>
#include <spdlog/spdlog.h>
#include <type_traits>

#include "glm/ext/vector_bool3.hpp"
#include "shader.h"
#include "buffer.h"
#include "shader_program.h"
#include "vertex_array.h"
#include "vertex.h"

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
spdlog::set_level(spdlog::level::debug); 
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "SeePP", NULL, NULL);
  if (window == nullptr) {
    SPDLOG_CRITICAL("could not create window");
    return -1;
  }

  glfwMakeContextCurrent(window);

  int version = gladLoadGL(glfwGetProcAddress);
  if (!version) {
    SPDLOG_CRITICAL("could not init Glad\n");
    return -1;
  }
  SPDLOG_DEBUG("GL v{}.{} initialized", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
  int flags;
  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
    glDebugMessageCallbackARB(glDebugOutput, nullptr);
    glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr,
                          GL_TRUE);
  }
  //glViewport(0, 0, WIDTH, HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  {
    ShaderProgram shader_program;
    {
      // TODO: load shaders source from file
      const char *vertexShaderSource =
          "#version 420 core\n"
          "layout (location = 0) in vec3 aPos;\n"
          "void main()\n"
          "{\n"
          "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
          "}\0";
      Shader vertex_shader(ShaderType::Vertex, vertexShaderSource);

      const char *fragmentShaderSource =
          "#version 420 core\n"
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

    Vertex vertices[] = {
      Vertex({0.5f,  0.5f, 0.0f}),  // top right
      Vertex({0.5f, -0.5f, 0.0f}),  // bottom right
      Vertex({-0.5f, -0.5f, 0.0f}),  // bottom left
      Vertex({-0.5f,  0.5f, 0.0f})   // top left
    };

    uint8_t indices[] = {
        0, 1, 3, // trig1
        1, 2, 3  // trig2
    };

    VertexArray vertex_array;
    vertex_array.Bind();

    Buffer vertex_buffer(BufferType::Vertex);
    vertex_buffer.Bind();
    vertex_buffer.BindData(vertices, sizeof(vertices), BindType::Static);

    Buffer index_buffer(BufferType::Index);
    index_buffer.Bind();
    index_buffer.BindData(indices, sizeof(indices), BindType::Static);

    vertex_array.BindAttributePointer(0, 3, DataType::F32, false,
                                9 * sizeof(float), (void *)0);
    vertex_array.BindAttributePointer(1, 4, DataType::F32, false,
                                9 * sizeof(float), (void *)3);
    vertex_array.BindAttributePointer(2, 2, DataType::F32, false,
                                9 * sizeof(float), (void *)7);
    // main loop
    while (!glfwWindowShouldClose(window)) {
      handleInput(window);

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      shader_program.Use();
      vertex_array.Bind();
      glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_BYTE, 0);

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
