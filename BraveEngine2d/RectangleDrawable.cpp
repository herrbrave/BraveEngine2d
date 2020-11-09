#include "RectangleDrawable.h"

RectangleDrawable::RectangleDrawable(
		std::string,
		glm::vec2 size,
		float rotation,
		glm::vec4 color) : Drawable(shader, size, rotation, color) {

	GLfloat points[] = {
		0.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
	};

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
}

void RectangleDrawable::render(
							AssetVendorPtr assetVendor,
							float dt,
							glm::mat4 projection,
							glm::mat4 view,
							glm::vec2 position) {

	AssetPtr shaderAsset = assetVendor->getAsset(this->shader);
	ShaderPtr shad = shaderAsset->getAsset<Shader>();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	shad->use();
	shad->setMatrix4("view", view);
	shad->setMatrix4("model", model);
	shad->setMatrix4("projection", projection);
	shad->setVector4f("color", color);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
}