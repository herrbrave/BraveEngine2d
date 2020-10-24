#include"Game.h"

void Game::loadGame(const std::string& path) {

}

float lastDT = 0.0f;
void Game::update(unsigned int ticks) {
	if (ticks + lastDT > 1000) {
		glm::vec2 update = glm::vec2(this->velocity);
		glm::normalize(update);
		update *= 10;
		this->position += update;
		lastDT = 0.0f;
	}
	lastDT += ticks;
}

void Game::draw() {

	glClear(GL_COLOR_BUFFER_BIT);

	this->drawable->render(0, this->projection, this->view, glm::vec2(250.0f, 250.0f), glm::vec2(150.0f, 150.0f), 45.0f, this->color);
	this->player->render(0, this->projection, this->view, this->position, this->size, this->rotation, this->color);
	this->graphics->render();
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
				this->velocity.y = -1;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				this->velocity.y = 1;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				this->velocity.x = -1;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				this->velocity.x = 1;
				break;
			}
		}
		else if (evt.type == SDL_KEYUP) {
			switch (evt.key.keysym.sym) {
			case SDLK_w:
			case SDLK_UP:
				if(this->velocity.y == -1)
					this->velocity.y = 0;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				if(this->velocity.y == 1)
					this->velocity.y = 0;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				if(this->velocity.x == -1)
					this->velocity.x = 0;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				if (this->velocity.x == 1)
					this->velocity.x = 0;
				break;
			}
		}
		else if (evt.type == SDL_MOUSEMOTION) {
			glm::vec2 mousePos = glm::vec2((float)evt.motion.x, (float)evt.motion.y);
			glm::vec2 dir = mousePos - this->position;
			glm::normalize(dir - glm::vec2(1.0f, 0.0));
			this->rotation = (glm::acos(glm::dot(glm::vec2(0.0f, 0.0f), dir)) * 180.0f) / 3.1469f;
			std::cout << "Rotation: " << this->rotation << " dir: " << glm::to_string(dir) <<  std::endl;
		}
	}
}

/* Main game loop */
void Game::play() {
	// initialize
	this->graphics.reset(new Graphics(new GraphicsConfig()));

	ResourceManager::loadShader("Shaders/rect.vs", "Shaders/rect.fs", nullptr, "rectangle");
	ResourceManager::loadShader("Shaders/texture.vs", "Shaders/texture.fs", nullptr, "texture");
	ResourceManager::loadTexture("Assets/Textures/Player/playerShip1_blue.png", true, "ship");
	this->drawable.reset(new RectangleDrawable(ResourceManager::getShader("rectangle")));
	this->player.reset(new TextureDrawable(ResourceManager::getShader("texture"), ResourceManager::getTexture("ship")));

	this->projection = glm::ortho<float>(0.0f, this->graphics->graphicsConfig->width * 2, this->graphics->graphicsConfig->height * 2, 0.0f, -1.0f, 1.0f);
	this->view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	this->velocity = glm::vec2(0.0f);

	Uint32 lastFrame = SDL_GetTicks();
	while (this->playing) {
		Uint32 startTime = SDL_GetTicks();
		Uint32 dt = lastFrame - startTime;
		lastFrame = startTime;

		update(dt);
		handleInput();
		draw();

		Uint32 endTime = SDL_GetTicks();
		
		// Currently hard coded to 60 fps
		if (endTime - startTime < 16) {
			SDL_Delay((Uint32) 16 - (endTime - startTime));
		}
	}
}