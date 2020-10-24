#pragma once

#include<SDL.h>
#include<gl\glew.h>
#include<SDL_opengl.h>
#include<gl\GLU.h>

#include<string>
#include<memory>
#include<unordered_map>

#include"Shader.h"

enum ScreenMode {
	FULL_SCREEN,
	FULL_SCREEN_WINDOWED,
	WINDOW
};

class GraphicsConfig;

typedef std::shared_ptr<SDL_Window> SDLWindowPtr;
typedef std::weak_ptr<SDL_Window> WeakSDLWindowPtr;

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

	Graphics(GraphicsConfig* graphicsConfig);
	~Graphics();
	void render();

private:
	SDLWindowPtr window;
	SDL_GLContext context;
	void initVideoSystems();
	void initGL();

	std::unordered_map<std::string, TexturePtr> textures;
	std::unordered_map<std::string, ShaderPtr> shaders;
};

typedef std::shared_ptr<Graphics> GraphicsPtr;
typedef std::weak_ptr<Graphics> WeakGraphicsPtr;