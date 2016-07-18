#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

  // escape close
  glfwSetKeyCallback(window, key_callback);

  glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

  GLfloat vertices[] = {
    -.5f, -.5f, .0f,
    .5f, -.5f, .0f,
    .0f, .5f, .0f
  };

  // vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLchar const *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;"
    "void main() {"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);"
    "}";
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  // fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  GLchar const *fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;"
    "void main() {"
    "color = vec4(1.0f, .5f, .2f, 1.0f);"
    "}";
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // shader program linking
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // cleanup
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // generate VAO
  GLuint VAO;
  glGenVertexArrays(1, &VAO);

  // vertex buffer object
  GLuint VBO;
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO); // Step 1: bind vertex array object

  glBindBuffer(GL_ARRAY_BUFFER, VBO); // Step 2: copy vertices in a buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Step 3: set vertex attribute pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid *)0 );
  glEnableVertexAttribArray(0);

  glBindVertexArray(0); // Step 4: unbind vertex array object


  // event loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    // rendering
    glClear(GL_COLOR_BUFFER_BIT);

    // use shader program
    glUseProgram(shaderProgram);
    // use VBO
    glBindVertexArray(VAO);
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
