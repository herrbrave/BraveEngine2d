#pragma once

#include "Asset.h"
#include "Constants.h"
#include "Shader.h"

class Drawable {
public:
	glm::vec2 size;
	float rotation;
	glm::vec4 color;

	Drawable(
			std::string shader,
			glm::vec2 size,
			float rotation,
			glm::vec4 color) {
		this->shader = std::move(shader);
		this->size = std::move(size);
		this->rotation = rotation;
		this->color = std::move(color);
	}

	virtual ~Drawable() {
		glDeleteBuffers(1, &vbo);
	}

	virtual void render(
		AssetVendorPtr assetVendor,
		float dt,
		glm::mat4 projection,
		glm::mat4 view,
		glm::vec2 position) = 0;

protected:
	std::string shader;
	unsigned int vbo;
};

typedef std::shared_ptr<Drawable> DrawablePtr;
typedef std::weak_ptr<Drawable> WeakDrawablePtr;