#shader vertex
#version 330 core
layout(location = 0) in vec4 positon;
void main() {
    gl_Position = positon;
}

#shader fragment
#version 330 core
uniform vec4 u_Color;
out vec4 color;
void main() {
    color = u_Color;
}