#shader vertex
#version 330 core
layout(location = 0) in vec4 positon;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord; 

uniform mat4 u_MVP; // uniform variable for the model-view-projection matrix

void main() {
    gl_Position = u_MVP * positon;
    v_TexCoord = texCoord; // pass the texture coordinates to the fragment shader after adding texture coordinates
}

#shader fragment
#version 330 core
uniform vec4 u_Color;
uniform sampler2D u_Texture;

in vec2 v_TexCoord;

out vec4 color;
void main() {
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor;
}