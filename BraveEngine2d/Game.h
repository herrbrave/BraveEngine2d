#pragma once

#include "AssetManager.h"
#include "DrawableComponent.h"
#include "Entity.h"
#include "RectangleDrawable.h"
#include "PhysicsComponent.h"
#include "TextureDrawable.h"
#include "Graphics.h"
#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

class Game {
public:
	void loadGame(const std::string& path);
	void play();

private:
	AssetManagerPtr assetManager{ nullptr };
	AssetVendorPtr assetVendor{ nullptr };
	PhysicsPtr physics{ nullptr };
	RendererPtr renderer{ nullptr };
	bool playing = true;
	std::vector<EntityPtr> entities;
	glm::vec2 impulse{ 0.0f, 0.0f };

	void update(unsigned int ticks);
	void draw();
	void handleInput();
};