#include"Game.h"

void Game::loadGame(const std::string& path) {

}

float speed = 800.0f;
void Game::update(unsigned int ticks) {
	float scalar = speed * ((float)ticks / 1000.0f);
	PhysicsComponentPtr physicsComponent = static_pointer_cast<PhysicsComponent>(this->entity->components.at(PHYSICS_COMPONENT_TYPE));
	if (physicsComponent->velocity.x != 0.0f || physicsComponent->velocity.y != 0.0f) {
		glm::vec2 vecCopy(physicsComponent->velocity);
		vecCopy = glm::normalize(vecCopy);
		vecCopy *= scalar;
		physicsComponent->position += vecCopy;
		std::cout << "position: [" << physicsComponent->position.x << ", " << physicsComponent->position.y << "]" << std::endl;
	}
}

void Game::draw() {

	glClear(GL_COLOR_BUFFER_BIT);

	DrawableComponentPtr drawableComponent = static_pointer_cast<DrawableComponent>(this->entity->components.at(DRAWABLE_COMPONENT_TYPE));
	PhysicsComponentPtr physicsComponent = static_pointer_cast<PhysicsComponent>(this->entity->components.at(PHYSICS_COMPONENT_TYPE));
	DrawablePtr drawable = makeShared(drawableComponent->drawable);
	drawable->render(0.0f, this->projection, this->view, physicsComponent->position, drawableComponent->size, drawableComponent->rotation, drawableComponent->color);

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
				physicsComponent->velocity.y = -1;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				physicsComponent->velocity.y = 1;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				physicsComponent->velocity.x = -1;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				physicsComponent->velocity.x = 1;
				break;
			}
		}
		else if (evt.type == SDL_KEYUP) {
			switch (evt.key.keysym.sym) {
			case SDLK_w:
			case SDLK_UP:
				if(physicsComponent->velocity.y == -1)
					physicsComponent->velocity.y = 0;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				if(physicsComponent->velocity.y == 1)
					physicsComponent->velocity.y = 0;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				if(physicsComponent->velocity.x == -1)
					physicsComponent->velocity.x = 0;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				if (physicsComponent->velocity.x == 1)
					physicsComponent->velocity.x = 0;
				break;
			}
		}
	}
}

/* Main game loop */
void Game::play() {
	// initialize
	this->graphics.reset(new Graphics(new GraphicsConfig()));

	ResourceManager::loadShader("Shaders/texture.vs", "Shaders/texture.fs", nullptr, "texture");
	ResourceManager::loadTexture("Assets/Textures/Player/playerShip1_blue.png", true, "ship");

	DrawablePtr textureDrawable;
	textureDrawable.reset(new TextureDrawable("texture", "ship"));

	this->entity.reset(new Entity());
	this->entity->components.emplace(DRAWABLE_COMPONENT_TYPE, new DrawableComponent(textureDrawable));
	this->entity->components.emplace(PHYSICS_COMPONENT_TYPE, new PhysicsComponent());


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