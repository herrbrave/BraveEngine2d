#include"Graphics.h"

Graphics::Graphics(GraphicsConfig* graphicsConfig) {
	this->graphicsConfig.reset(graphicsConfig);
	initVideoSystems();
}
Graphics::~Graphics() {
	SDL_DestroyWindow(window.get());
	SDL_Quit();
}

void Graphics::initVideoSystems() {

	// initialize
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Unable to initialize SDL:\n %s", SDL_GetError());
		SDL_Quit();
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window.reset(SDL_CreateWindow(graphicsConfig->title.c_str(), graphicsConfig->windowX, graphicsConfig->windowY, graphicsConfig->width, graphicsConfig->height, graphicsConfig->flags));

	if (!window) {
		printf("Unable to create SDL Window:\n %s", SDL_GetError());
		SDL_Quit();
	}

	SDL_GLContext ctxt = SDL_GL_CreateContext(window.get());
	context.reset(&ctxt);
	if (!context) {
		printf("Unable to create GL context:\n %s", SDL_GetError());
		SDL_Quit();
	}

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		printf("Unable to initialize Glew:\n %s", glewGetErrorString(glewError));
		SDL_Quit();
	}

	if (SDL_GL_SetSwapInterval(1) < 0) {
		printf("Unable to set vsync\n %s", SDL_GetError());
		SDL_Quit();
	}

	glViewport(0, 0, this->graphicsConfig->width, this->graphicsConfig->height);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	this->projection = glm::ortho<float>(0.0f, this->graphicsConfig->width * 2, this->graphicsConfig->height * 2, 0.0f, -1.0f, 1.0f);
	this->view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}