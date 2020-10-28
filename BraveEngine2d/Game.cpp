#include"Game.h"

void Game::loadGame(const std::string& path) {

}

void Game::update(unsigned int ticks) {
	this->physicsResourceManager->update(ticks);
}

void Game::draw() {

	glClear(GL_COLOR_BUFFER_BIT);

	DrawableComponentPtr drawableComponent = static_pointer_cast<DrawableComponent>(this->entity->components.at(DRAWABLE_COMPONENT_TYPE));
	PhysicsComponentPtr physicsComponent = static_pointer_cast<PhysicsComponent>(this->entity->components.at(PHYSICS_COMPONENT_TYPE));
	DrawablePtr drawable = makeShared(drawableComponent->drawable);
	drawable->render(0.0f, this->projection, this->view, makeShared(physicsComponent->physics)->position, drawableComponent->size, drawableComponent->rotation, drawableComponent->color);

	this->graphics->render();
}

void Game::handleInput() {
	SDL_Event evt;
	while (SDL_PollEvent(&evt) != 0) {
		PhysicsComponentPtr physicsComponent = static_pointer_cast<PhysicsComponent>(this->entity->components.at(PHYSICS_COMPONENT_TYPE));
		if (evt.type == SDL_QUIT) {
			this->playing = false;
		}
		else if (evt.type == SDL_KEYDOWN) {
			switch (evt.key.keysym.sym) {
			case SDLK_w:
			case SDLK_UP:
				makeShared(physicsComponent->physics)->applyLinearImpulse(glm::vec2(0.0f, -1.0f));
				break;
			case SDLK_s:
			case SDLK_DOWN:
				makeShared(physicsComponent->physics)->applyLinearImpulse(glm::vec2(0.0f, 1.0f));
				break;
			case SDLK_a:
			case SDLK_LEFT:
				makeShared(physicsComponent->physics)->applyLinearImpulse(glm::vec2(-1.0f, 0.0f));
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				makeShared(physicsComponent->physics)->applyLinearImpulse(glm::vec2(1.0f, 0.0f));
				break;
			}
		}
	}
}

/* Main game loop */
void Game::play() {
	// initialize
	this->graphics.reset(new Graphics(new GraphicsConfig()));
	this->physicsResourceManager = new PhysicsResourceManager();
	this->physicsResourceManager->initPhysics();

	GraphicsResourceManager::loadShader("Shaders/texture.vs", "Shaders/texture.fs", nullptr, "texture");
	GraphicsResourceManager::loadTexture("Assets/Textures/Player/playerShip1_blue.png", true, "ship");

	DrawablePtr textureDrawable;
	textureDrawable.reset(new TextureDrawable("texture", "ship"));

	this->entity.reset(new Entity());
	this->entity->components.emplace(DRAWABLE_COMPONENT_TYPE, new DrawableComponent(textureDrawable));
	this->entity->components.emplace(PHYSICS_COMPONENT_TYPE, new PhysicsComponent(this->physicsResourceManager->loadPhysics(this->entity->id, PhysicsConfigPtr(new PhysicsConfig(DYNAMIC, BoxShapePtr(new BoxShape(64.0f, 64.0f)), 0.0f, glm::vec2(200.0f, 200.0f))))));


	this->projection = glm::ortho<float>(0.0f, this->graphics->graphicsConfig->width * 2, this->graphics->graphicsConfig->height * 2, 0.0f, -1.0f, 1.0f);
	this->view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

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