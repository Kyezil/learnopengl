#version 330 core
layout (location = 0) in vec3 position;
out vec3 ourColor;
out vec4 vertexPosition;

void main() {
  gl_Position = vertexPosition = vec4(position, 1.0);
}
