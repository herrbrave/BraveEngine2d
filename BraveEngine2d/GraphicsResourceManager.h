#pragma once

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <GL/glew.h>
#include <GL/GL.h>
#include <SDL_image.h>

#include "Texture.h"
#include "Shader.h"

class GraphicsResourceManager {
public:
	static std::map<std::string, ShaderPtr> shaders;
	static std::map<std::string, TexturePtr> textures;

	static WeakShaderPtr loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
	static WeakShaderPtr getShader(std::string name);
	static WeakTexturePtr loadTexture(const char* file, bool alpha, std::string name);
	static WeakTexturePtr getTexture(std::string name);
	static void clear();

private:
	GraphicsResourceManager() {}
	
	static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	static Texture loadTextureFromFile(const char* file, bool alpha);
};