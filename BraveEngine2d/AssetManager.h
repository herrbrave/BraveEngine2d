#pragma once

#include <box2d/box2d.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>

#include "Asset.h"
#include "Graphics.h"
#include "Physics.h"
#include "SDL_Helpers.h"
#include "Shader.h"

class AssetManager {
public:
	std::unordered_map<std::string, AssetPtr> assets;

	void loadPhysics(float physicsScalingFactor, b2World* world, PhysicsConfigPtr physicsConfig, std::string name);
	void loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
	void loadTexture(const char* file, bool alpha, std::string name);
	void loadSound(const char* file, std::string name);
	void loadMusic(const char* file, std::string name);
};

typedef std::shared_ptr<AssetManager> AssetManagerPtr;
typedef std::weak_ptr<AssetManager> WeakAssetManagerPtr;

class DefaultAssetVendor : public AssetVendor {
public:
	DefaultAssetVendor(WeakAssetManagerPtr assetManager) : assetManager(assetManager) {}

	AssetPtr getAsset(const std::string& tag) override;

private:
	WeakAssetManagerPtr assetManager;
};