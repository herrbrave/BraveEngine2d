#pragma once

#include "Constants.h"
#include "Shader.h"

class Drawable {
public:
	Drawable(std::string shader) {
		this->shader = std::move(shader);
	}

	virtual ~Drawable() {
		glDeleteBuffers(1, &vbo);
	}

	virtual void render(
		float dt,
		glm::mat4 projection,
		glm::mat4 view,
		glm::vec2 position,
		glm::vec2 size,
		float rotation,
		glm::vec4 color) = 0;

protected:
	std::string shader;
	unsigned int vbo;
};

typedef std::shared_ptr<Drawable> DrawablePtr;
typedef std::weak_ptr<Drawable> WeakDrawablePtr;