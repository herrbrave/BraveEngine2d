#version 330 core

out vec4 color;

uniform vec4 inputColor;

void main() {
	color = vec4(inputColor.xyzw);
}