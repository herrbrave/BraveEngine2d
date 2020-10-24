#pragma once

#include <string>
#include <iostream>
#include <memory>

#include <GL/glew.h>
#include <GL/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	unsigned int id;
	
	Shader() {}
	Shader& use();

	void compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);

	void setFloat(const char* name, float value, bool userShader = false);
	void setInt(const char* name, int value, bool useShader = false);
	void setVector2f(const char* name, glm::vec2 value, bool useShader = false);
	void setVector2f(const char* name, float x, float y, bool useShader = false);
	void setVector3f(const char* name, glm::vec3 value, bool useShader = false);
	void setVector3f(const char* name, float x, float y, float z, bool useShader = false);
	void setVector4f(const char* name, glm::vec4 value, bool useShader = false);
	void setVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);
	void setMatrix4(const char* name, glm::mat4& value, bool useShader = false);

private:
	void checkCompileErrors(unsigned int object, std::string type);
};

typedef std::shared_ptr<Shader> ShaderPtr;
typedef std::weak_ptr<Shader> WeakShaderPtr;