#pragma once

#include<memory>
#include<string>

#include<SDL.h>
#include<SDL_mixer.h>


struct SDL_DELETERS {
	void operator()(SDL_Window* window) const { SDL_DestroyWindow(window); }
	void operator()(SDL_Renderer* renderer) const { SDL_DestroyRenderer(renderer); }
	void operator()(SDL_GLContext* context) const { SDL_GL_DeleteContext(context); }
	void operator()(SDL_Texture* texture) const { SDL_DestroyTexture(texture); }
	void operator()(Mix_Chunk* mix) const { Mix_FreeChunk(mix); }
	void operator()(Mix_Music* mix) const { Mix_FreeMusic(mix); }
};