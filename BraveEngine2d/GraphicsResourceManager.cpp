#include "GraphicsResourceManager.h"

std::map<std::string, ShaderPtr> GraphicsResourceManager::shaders;
std::map<std::string, TexturePtr> GraphicsResourceManager::textures;

WeakShaderPtr GraphicsResourceManager::loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name) {
	shaders[name] = std::make_shared<Shader>(loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile));
	return shaders[name];
}

WeakShaderPtr GraphicsResourceManager::getShader(std::string name) {
	return shaders[name];
}

WeakTexturePtr GraphicsResourceManager::loadTexture(const char* file, bool alpha, std::string name) {
	textures[name] = std::make_shared<Texture>(loadTextureFromFile(file, alpha));
	return textures[name];
}

WeakTexturePtr GraphicsResourceManager::getTexture(std::string name) {
	return textures[name];
}

void GraphicsResourceManager::clear() {
	for (auto iter : shaders)
		glDeleteProgram(iter.second->id);
	for (auto iter : textures)
		glDeleteTextures(1, &iter.second->id);
}

Shader GraphicsResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile) {	

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

	Shader shader;
	shader.compile(vertexCode.c_str(), fragmentCode.c_str(), gShaderFile != nullptr ? geometryCode.c_str() : nullptr);

	return shader;
}


Texture GraphicsResourceManager::loadTextureFromFile(const char* file, bool alpha) {

	Texture texture;
	if (alpha) {
		texture.internalFormat = GL_RGBA;
		texture.imageFormat = GL_RGBA;
	}

	SDL_Surface* surface = IMG_Load(file);
	if (surface == nullptr) {
		std::cout << "Failed to load surface " << SDL_GetError() << std::endl;
	}

	int width = surface->w;
	int height = surface->h;
	int nrChannels = surface->pitch;
	std::cout << "Loading image with width " << width << " height " << height << " channels "  << nrChannels << " and data " << sizeof(surface->pixels) << std::endl;;

	texture.generate(width, height, surface->pixels);

	SDL_FreeSurface(surface);

	return texture;
}