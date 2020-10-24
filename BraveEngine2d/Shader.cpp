#include "Shader.h"


Shader& Shader::use() {
	glUseProgram(this->id);
	return *this;
}

void Shader::compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource) {
	unsigned int sVertex;
	unsigned int sFragment;
	unsigned int gShader;

	// Vertex Shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "Vertex Shader");

	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "Fragment Shader");

	if (geometrySource != nullptr) {
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, NULL);
		glCompileShader(gShader);
		checkCompileErrors(gShader, "Geometry Shader");
	}

	this->id = glCreateProgram();
	glAttachShader(this->id, sVertex);
	glAttachShader(this->id, sFragment);
	if (geometrySource != nullptr) {
		glAttachShader(this->id, gShader);
	}

	glLinkProgram(this->id);
	checkCompileErrors(this->id, "Program");

	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource != nullptr) {
		glDeleteShader(gShader);
	}
}

void Shader::setFloat(const char* name, float value, bool useShader) {
	if (useShader)
		this->use();
	glUniform1f(glGetUniformLocation(this->id, name), value);
}

void Shader::setInt(const char* name, int value, bool useShader) {
	if (useShader)
		this->use();
	glUniform1i(glGetUniformLocation(this->id, name), value);
}

void Shader::setVector2f(const char* name, glm::vec2 value, bool useShader) {
	if (useShader)
		this->use();
	glUniform2f(glGetUniformLocation(this->id, name), value.x, value.y);
}

void Shader::setVector2f(const char* name, float x, float y, bool useShader) {
	if (useShader)
		this->use();
	glUniform2f(glGetUniformLocation(this->id, name), x, y);
}

void Shader::setVector3f(const char* name, glm::vec3 value, bool useShader) {
	if (useShader)
		this->use();
	glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
}

void Shader::setVector3f(const char* name, float x, float y, float z, bool useShader) {
	if (useShader)
		this->use();
	glUniform3f(glGetUniformLocation(this->id, name), x, y, z);
}

void Shader::setVector4f(const char* name, glm::vec4 value, bool useShader) {
	if (useShader)
		this->use();
	unsigned int id = glGetUniformLocation(this->id, name);
	glUniform4f(glGetUniformLocation(this->id, name), value.x, value.y, value.z, value.w);
}

void Shader::setVector4f(const char* name, float x, float y, float z, float w, bool useShader) {
	if (useShader)
		this->use();
	glUniform4f(glGetUniformLocation(this->id, name), x, y, z, w);
}

void Shader::setMatrix4(const char* name, glm::mat4& value, bool useShader) {
	if (useShader)
		this->use();
	unsigned int id = glGetUniformLocation(this->id, name);
	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, false, glm::value_ptr(value));
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
	int success;
	if ("Program" != type) {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
	}
	else {
		glGetProgramiv(object, GL_LINK_STATUS, &success);
	}
	if (!success) {
		char infoLog[1024];
		if ("Program" != type) {
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
		}
		else {
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
		}
		std::cout << "| ERROR::SHADER: Compile-time error: Type: "
			<< type.c_str()
			<< "\n"
			<< infoLog
			<< "\n -- ------------------------------------------------------ --"
			<< std::endl;
	}
}