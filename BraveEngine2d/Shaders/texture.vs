#version 330 core
layout (location = 0) in vec4 pos;

out vec2 texCoords;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

void main() {
	texCoords = pos.zw;
	gl_Position = projection * view * model * vec4(pos.xy, 0.0, 1.0);
}