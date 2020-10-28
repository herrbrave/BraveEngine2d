#pragma once

#include "DrawableComponent.h"
#include "Entity.h"
#include "PhysicsComponent.h"
#include "TextureDrawable.h"
#include "Graphics.h"
#include "GraphicsResourceManager.h"
#include "PhysicsResourceManager.h"

#include <glm/gtc/matrix_transform.hpp>

class Game {
public:
	void loadGame(const std::string& path);
	void play();

private:
	GraphicsPtr graphics;
	PhysicsResourceManager* physicsResourceManager;
	EntityPtr entity;
	bool playing = true;

	glm::mat4 projection;
	glm::mat4 view;

	void update(unsigned int ticks);
	void draw();
	void handleInput();
};