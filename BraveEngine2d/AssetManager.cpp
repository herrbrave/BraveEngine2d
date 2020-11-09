#include "AssetManager.h"

void AssetManager::loadPhysics(float physicsScalingFactor, b2World* world, PhysicsConfigPtr physicsConfig, std::string name) {
	AssetPtr asset = nullptr;

	b2BodyDef bodydef;
	bodydef.type = physicsConfig->type == STATIC ? b2BodyType::b2_staticBody : b2BodyType::b2_dynamicBody;
	bodydef.position.Set(physicsScalingFactor * physicsConfig->position.x, physicsScalingFactor * physicsConfig->position.y);
	bodydef.angle = physicsConfig->angleRadians;
	bodydef.linearVelocity.Set(physicsScalingFactor * physicsConfig->linearVel.x, physicsScalingFactor * physicsConfig->linearVel.y);
	bodydef.fixedRotation = physicsConfig->fixedRotation;
	bodydef.bullet = physicsConfig->bullet;
	bodydef.enabled = true;
	bodydef.angularVelocity = physicsConfig->angularVel;
	bodydef.userData.pointer = reinterpret_cast<uintptr_t>(new std::string(name.c_str()));

	b2Body* body = world->CreateBody(&bodydef);

	if (physicsConfig->shape->type == CIRCLE) {
		b2CircleShape shape;
		shape.m_radius = physicsScalingFactor * ((CircleShape*)physicsConfig->shape.get())->radius;
		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 1.0f;
		fixture.friction = 0.3f;
		body->CreateFixture(&fixture);
	}
	else {
		b2PolygonShape shape;
		shape.SetAsBox(physicsScalingFactor * ((BoxShape*)physicsConfig->shape.get())->width, physicsScalingFactor * ((BoxShape*)physicsConfig->shape.get())->height);
		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 1.0f;
		fixture.friction = 0.3f;
		body->CreateFixture(&fixture);
	}

	asset.reset(new Asset(VoidPtr(body, PhysicsDeleters()), nullptr, name));
	assets.emplace(name, asset);
}

void AssetManager::loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name) {
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;

	try {
		std::ifstream vertexShaderFile(vShaderFile);
		std::stringstream vShaderStream;
		vShaderStream << vertexShaderFile.rdbuf();
		vertexShaderFile.close();
		vertexCode = vShaderStream.str();

		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream fShaderStream;
		fShaderStream << fragmentShaderFile.rdbuf();
		fragmentShaderFile.close();
		fragmentCode = fShaderStream.str();

		if (gShaderFile != nullptr) {
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception ex) {
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}

	Shader* shader = new Shader();
	shader->compile(vertexCode.c_str(), fragmentCode.c_str(), gShaderFile != nullptr ? geometryCode.c_str() : nullptr);

	assets.emplace(name, AssetPtr(new Asset(VoidPtr(shader, GLDeleters()), "", name)));
}

void AssetManager::loadTexture(const char* file, bool alpha, std::string name) {


	Texture* texture = new Texture();
	if (alpha) {
		texture->internalFormat = GL_RGBA;
		texture->imageFormat = GL_RGBA;
	}

	SDL_Surface* surface = IMG_Load(file);
	if (surface == nullptr) {
		std::cout << "Failed to load surface " << SDL_GetError() << std::endl;
	}

	int width = surface->w;
	int height = surface->h;
	int nrChannels = surface->pitch;
	std::cout << "Loading image with width " << width << " height " << height << " channels " << nrChannels << " and data " << sizeof(surface->pixels) << std::endl;;

	texture->generate(width, height, surface->pixels);

	SDL_FreeSurface(surface);

	VoidPtr voidPtr(texture, GLDeleters());
	assets.emplace(name, AssetPtr(new Asset(voidPtr, file, name)));
}

void AssetManager::loadSound(const char* file, std::string name) {
	VoidPtr assetPtr(Mix_LoadWAV(file), SDL_DELETERS());
	assets.emplace(name, AssetPtr(new Asset(assetPtr, file, name)));
}

void AssetManager::loadMusic(const char* file, std::string name) {
	VoidPtr assetPtr(Mix_LoadMUS(file), SDL_DELETERS());
	assets.emplace(name, AssetPtr(new Asset(assetPtr, file, name)));
}

AssetPtr DefaultAssetVendor::getAsset(const std::string& tag) {
	AssetManagerPtr manager = makeShared(this->assetManager);
	return manager->assets.at(tag);
}