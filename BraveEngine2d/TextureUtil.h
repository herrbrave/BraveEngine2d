#pragma once

#include"Texture.h"
#include<gl\glew.h>
#include<GL\GL.h>

Texture* generateTexture(const Texture & texture, unsigned char * data) {
	bind(texture);

	glTexImage2D(GL_TEXTURE_2D, 0, texture.internalFormat, texture.width, texture.height, 0, texture.imageFormat, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture.wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture.wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture.filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture.filterMax);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void bind(const Texture& texture) {
	glBindTexture(GL_TEXTURE_2D, texture.id);
}