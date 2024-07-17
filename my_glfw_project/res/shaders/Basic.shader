#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 vColor;

uniform mat4 u_MVP;

void main() {
    vColor = aColor;
    gl_Position = u_MVP * vec4(aPos, 1.0);
}
#shader fragment
#version 330 core

in vec3 vColor;

out vec4 color;

void main() {
    color = vec4(vColor, 1.0);
}
