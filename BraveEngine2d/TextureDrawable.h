#pragma once

#include "Drawable.h"
#include "Texture.h"

class TextureDrawable : public Drawable {
public:
	WeakTexturePtr texture;

	TextureDrawable(WeakShaderPtr shader, WeakTexturePtr texture, const float* texCoords = nullptr);

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