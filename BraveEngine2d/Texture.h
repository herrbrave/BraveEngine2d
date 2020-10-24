#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <memory>

class Texture {
public:
	unsigned int id;

	unsigned int width;
	unsigned int height;

	unsigned int internalFormat;
	unsigned int imageFormat;

	unsigned int wrapS;
	unsigned int wrapT;

	unsigned int filterMin;
	unsigned int filterMax;

	Texture() : width(0), height(0), internalFormat(GL_RGB), imageFormat(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMax(GL_LINEAR) {
		glGenTextures(1, &this->id);
	}

	void generate(unsigned int width, unsigned int height, void* data);
	void bind() const;
};

typedef std::shared_ptr<Texture> TexturePtr;
typedef std::weak_ptr<Texture> WeakTexturePtr;