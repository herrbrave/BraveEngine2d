#pragma once

#include "RectangleDrawable.h"
#include "TextureDrawable.h"
#include "Graphics.h"
#include "ResourceManager.h"
#include <glm/gtc/matrix_transform.hpp>

class Game {
public:
	void loadGame(const std::string& path);
	void play();

private:
	GraphicsPtr graphics;
	std::shared_ptr<RectangleDrawable> drawable;
	std::shared_ptr<TextureDrawable> player;
	glm::mat4 projection;
	glm::mat4 view;
	glm::vec2 velocity;
	bool playing = true;

	glm::vec2 position = glm::vec2(100.0f, 100.0f);
	glm::vec2 size = glm::vec2(500.0f, 180.0f);
	float rotation = 0.0f;
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	void update(unsigned int ticks);
	void draw();
	void handleInput();
};