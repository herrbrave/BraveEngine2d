#pragma once

#include "Asset.h"
#include "Constants.h"
#include "DrawableComponent.h"
#include "Entity.h"
#include "Graphics.h"
#include "PhysicsComponent.h"

class Renderer {
public:
	GraphicsPtr graphics;
	std::vector<WeakEntityPtr> drawOrder;

	Renderer(GraphicsPtr graphics, AssetVendorPtr assetVendor) : graphics(std::move(graphics)), assetVendor(assetVendor) {}

	void render();
	void registerEntity(WeakEntityPtr entity);
	void deregisterEntity(const std::string id);
private:
	AssetVendorPtr assetVendor;
};

typedef std::shared_ptr<Renderer> RendererPtr;
typedef std::weak_ptr<Renderer> WeakRendererPtr;