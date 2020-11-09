#include"Game.h"

void Game::loadGame(const std::string& path) {

}

void Game::update(unsigned int ticks) {
	if (impulse.x != 0.0f || impulse.y != 0.0f) {
		PhysicsComponentPtr physicsComponent = static_pointer_cast<PhysicsComponent>(this->entities.front()->components.at(PHYSICS_COMPONENT_TYPE));
		physicsComponent->applyLinearImpulse(glm::normalize(this->impulse));
	}
	std::cout << "Impulse: " << glm::to_string(this->impulse) << std::endl;
	this->physics->update(ticks);
}

void Game::draw() {
	this->renderer->render();
}

void Game::handleInput() {
	SDL_Event evt;
	while (SDL_PollEvent(&evt) != 0) {
		if (evt.type == SDL_QUIT) {
			this->playing = false;
		}
		else if (evt.type == SDL_KEYDOWN) {
			switch (evt.key.keysym.sym) {
			case SDLK_w:
			case SDLK_UP:
				this->impulse.y = -1.0f;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				this->impulse.y = 1.0f;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				this->impulse.x = -1.0f;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				this->impulse.x = 1.0f;
				break;
			}
		}
		else if (evt.type == SDL_KEYUP) {
			switch (evt.key.keysym.sym) {
			case SDLK_w:
			case SDLK_UP:
				this->impulse.y = 0.0f;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				this->impulse.y = 0.0f;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				this->impulse.x = 0.0f;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				this->impulse.x = 0.0f;
				break;
			}
		}
	}
}

/* Main game loop */
void Game::play() {
	// initialize
	this->assetManager.reset(new AssetManager());
	this->assetVendor.reset(new DefaultAssetVendor(this->assetManager));

	GraphicsPtr graphics;
	graphics.reset(new Graphics(new GraphicsConfig()));

	this->renderer.reset(new Renderer(graphics, this->assetVendor));
	this->physics.reset(new Physics());
	this->physics->initPhysics();

	assetManager->loadShader("Shaders/rect.vs", "Shaders/rect.fs", nullptr, "rect");
	assetManager->loadShader("Shaders/texture.vs", "Shaders/texture.fs", nullptr, "texture");
	assetManager->loadTexture("Assets/Textures/Player/playerShip1_blue.png", true, "ship");

	DrawablePtr textureDrawable;
	textureDrawable.reset(new TextureDrawable("texture", "ship", glm::vec2(64.0f, 64.0f), 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
	
	EntityPtr entity;
	entity.reset(new Entity());
	entity->components.emplace(DRAWABLE_COMPONENT_TYPE, new DrawableComponent(entity->id, textureDrawable));

	PhysicsConfigPtr physicsConfig{ new PhysicsConfig(DYNAMIC, BoxShapePtr(new BoxShape(64.0f, 64.0f)), 0.0f, glm::vec2(600.0f, 200.0f)) };
	PhysicsBodyPtr physicsBody = this->physics->loadPhysics(physicsConfig, entity->id);
	entity->components.emplace(PHYSICS_COMPONENT_TYPE, new PhysicsComponent(entity->id, physicsBody));

	entities.push_back(entity);

	renderer->registerEntity(entity);

	Uint32 lastFrame = SDL_GetTicks();
	while (this->playing) {
		Uint32 startTime = SDL_GetTicks();

		update(startTime - lastFrame);
		handleInput();
		draw();

		Uint32 endTime = SDL_GetTicks();
		lastFrame = startTime;
		// Currently hard coded to 60 fps
		if (endTime - startTime < 16) {
			SDL_Delay((Uint32) 16 - (endTime - startTime));
		}
	}
}