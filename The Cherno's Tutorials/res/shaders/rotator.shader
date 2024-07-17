# Shader Vertex
# version 330 core
layout(location = 0) in vec4 position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_Rotation;

void main(){
	gl_Position = u_Projection * u_View * u_Rotation * u_Model * vec4(position.x, position.y, position.z, 1.0);
}


# Shader Fragment
# version 330 core
layout(location = 0) out vec4 colour;

uniform vec4 u_Colour;

void main(){
	colour = u_Colour;
}
