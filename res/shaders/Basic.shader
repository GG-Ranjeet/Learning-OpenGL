#shader vertex
#version 330 core
layout(location = 0) in vec4 positon;
void main() {
    gl_Position = positon;
}

#shader fragment
#version 330 core
out vec4 color;
void main() {
    color = vec4(1.0, 0.5, 0.2, 1.0);
}