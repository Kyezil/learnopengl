#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../lib/shader.hh"
// use our lib

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

int main() {
  // start glfw
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // create window
  GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);

  // escape close
  glfwSetKeyCallback(window, key_callback);

  // start glew
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  // set viewport
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  Shader ourShader("shaders/shader_ex1.vs", "shaders/shader_ex1.frag");

  GLfloat vertices1[] = { // {position, color} x 3
    -.5f, -.5f, .0f,  1.0f,  0.0f,  0.0f,
     .0f,  .5f, .0f,  0.0f,  1.0f,  0.0f,
     .5f, -.5f, .0f,  0.0f,  0.0f,  1.0f
  };
  // generate VAO, VBO
  GLuint VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  // Step 1: bind vertex array object
  glBindVertexArray(VAO);
  // Step 2: copy vertices in a buffer
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
  // Step 3: set vertex attribute pointers
  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid *)0 );
  glEnableVertexAttribArray(0);
  // color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  // Step 4: unbind vertex array object
  glBindVertexArray(0);

  // event loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    // rendering
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // use shader program
    ourShader.use();

    glBindVertexArray(VAO); // use VAO
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // refresh
    glfwSwapBuffers(window);
  }
  glfwTerminate();
  return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE and action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
