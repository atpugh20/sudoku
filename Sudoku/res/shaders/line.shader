#shader vertex
#version 460 core

layout(location = 0) in vec3 aPos;

void main() {
	gl_Position = vec4(aPos, 1.0);
}

#shader fragment
#version 460 core
out vec4 u_Color;

void main() {
	u_Color = vec4(1.0, 1.0, 1.0, 1.0);
}