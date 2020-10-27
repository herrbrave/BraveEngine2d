#pragma once

#include "Drawable.h"
#include "ResourceManager.h"
#include "Texture.h"

class TextureDrawable : public Drawable {
public:
	std::string texture;

	TextureDrawable(std::string shader, std::string texture, const float* texCoords = nullptr);

	void render(
		float dt,
		glm::mat4 projection,
		glm::mat4 view,
		glm::vec2 position,
		glm::vec2 size,
		float rotation,
		glm::vec4 color) override;

private:
	const float DEFAULT_TEX_COORDS[12] = { 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f };
};

