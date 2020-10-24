#version 330 core
out vec4 fragment;

in vec2 texCoords;

uniform sampler2D image;
uniform vec4 color;

void main() {
	fragment = color * texture(image, texCoords);
}