#pragma once

#include<SDL.h>
#include<gl\glew.h>
#include<SDL_opengl.h>
#include<gl\GLU.h>

#include<algorithm>
#include<string>
#include<memory>
#include<unordered_map>

#include "Constants.h"
#include "Drawable.h"
#include"Entity.h"
#include"SDL_Helpers.h"
#include"Shader.h"
#include"Texture.h"

enum ScreenMode {
	FULL_SCREEN,
	FULL_SCREEN_WINDOWED,
	WINDOW
};

class GraphicsConfig;

typedef std::unique_ptr<SDL_Window, SDL_DELETERS> SDLWindowPtr;
typedef std::unique_ptr<SDL_GLContext, SDL_DELETERS> SDL_GLContextPtr;

class GraphicsConfig {
public:

	GraphicsConfig() {}

	~GraphicsConfig() {}

	std::string title = "Game";
	std::string fontPath = "./Assets/Fonts/KenPixel.tff";
	int windowX = SDL_WINDOWPOS_CENTERED;
	int windowY = SDL_WINDOWPOS_CENTERED;
	int width = 1024;
	int height = 762;
	int fontSize = 12;
	Uint32 flags{ SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL };
};

typedef std::shared_ptr<GraphicsConfig> GraphicsConfigPtr;
typedef std::weak_ptr<GraphicsConfig> WeakGraphicsConfigPtr;

class Graphics {
public:
	GraphicsConfigPtr graphicsConfig;
	SDLWindowPtr window{ nullptr };
	SDL_GLContextPtr context{ nullptr };

	glm::mat4 projection;
	glm::mat4 view;

	Graphics(GraphicsConfig* graphicsConfig);
	~Graphics();
private:
	void initVideoSystems();
};

typedef std::shared_ptr<Graphics> GraphicsPtr;
typedef std::weak_ptr<Graphics> WeakGraphicsPtr;

struct GLDeleters {
	void operator()(Shader* shader) const { glDeleteProgram(shader->id); }
	void operator()(Texture* texture) const { glDeleteTextures(1, &texture->id); }
};