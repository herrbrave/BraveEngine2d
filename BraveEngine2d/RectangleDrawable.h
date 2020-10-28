#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Drawable.h"
#include "GraphicsResourceManager.h"
#include "Shader.h"

class RectangleDrawable : public Drawable {
public:

	RectangleDrawable(std::string shader);

	void render(
		float dt, 
		glm::mat4 projection, 
		glm::mat4 view, 
		glm::vec2 position,
		glm::vec2 size,
		float rotation,
		glm::vec4 color) override;
};