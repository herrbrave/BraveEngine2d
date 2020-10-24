#pragma once

#include<gl\glew.h>
#include<GL\GL.h>

#include<iostream>
#include<string>

#include"Shader.h"

void use(const Shader& shader);
Shader* compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);
void setFloat(const Shader& shader, const char* name, float value, bool useShader = false);
void setInteger(const Shader& shader, const char* name, int value, bool useShader = false);
void setVector2f(const Shader& shader, const char* name, float x, float y, bool useShader = false);
void setVector3f(const Shader& shader, const char* name, float x, float y, float z, bool useShader = false);
void setVector4f(const Shader& shader, const char* name, float x, float y, float z, float w, bool useShader = false);

void checkCompileErrors(unsigned int object, std::string type);


void use(const Shader& shader) {
	glUseProgram(shader.id);
}

Shader* compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr) {
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

	Shader* shader = new Shader(glCreateProgram());
	glAttachShader(shader->id, sVertex);
	glAttachShader(shader->id, sFragment);
	if (geometrySource != nullptr) {
		glAttachShader(shader->id, gShader);
	}

	glLinkProgram(shader->id);
	checkCompileErrors(shader->id, "Program");

	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource != nullptr) {
		glDeleteShader(gShader);
	}

	return shader;
}

void setFloat(const Shader& shader, const char* name, float value, bool useShader = false) {
	if (useShader) {
		use(shader);
	}

	glUniform1f(glGetUniformLocation(shader.id, name), value);
}

void setInteger(const Shader& shader, const char* name, int value, bool useShader = false) {
	if (useShader) {
		use(shader);
	}

	glUniform1i(glGetUniformLocation(shader.id, name), value);
}

void setVector2f(const Shader& shader, const char* name, float x, float y, bool useShader = false) {
	if (useShader) {
		use(shader);
	}

	glUniform2f(glGetUniformLocation(shader.id, name), x, y);
}

void setVector3f(const Shader& shader, const char* name, float x, float y, float z, bool useShader = false) {
	if (useShader) {
		use(shader);
	}

	glUniform3f(glGetUniformLocation(shader.id, name), x, y, z);
}
void setVector4f(const Shader& shader, const char* name, float x, float y, float z, float w, bool useShader = false) {
	if (useShader) {
		use(shader);
	}

	glUniform4f(glGetUniformLocation(shader.id, name), x, y, z, w);
}

void checkCompileErrors(unsigned int object, std::string type) {
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
		std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
			<< infoLog << "\n -- ------------------------------------------------------ --"
			<< std::endl;
	}
}