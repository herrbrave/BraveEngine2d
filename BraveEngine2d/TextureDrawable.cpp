#include "TextureDrawable.h"

TextureDrawable::TextureDrawable(
		std::string shader, 
		std::string texture,
		glm::vec2 size,
		float rotation,
		glm::vec4 color,
		const float* texCoords) : Drawable(shader, size, rotation, color) {
	if (texCoords == nullptr) {
		texCoords = DEFAULT_TEX_COORDS;
	}

	this->texture = std::move(texture);

	GLfloat points[] = {
		0.0f, 1.0f, texCoords[0], texCoords[1],
		1.0f, 0.0f, texCoords[2], texCoords[3],
		0.0f, 0.0f, texCoords[4], texCoords[5],

		0.0f, 1.0f, texCoords[6], texCoords[7],
		1.0f, 1.0f, texCoords[8], texCoords[9],
		1.0f, 0.0f, texCoords[10], texCoords[11]
	};

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
}

void TextureDrawable::render(
	AssetVendorPtr assetVendor,
	float dt,
	glm::mat4 projection,
	glm::mat4 view,
	glm::vec2 position) {

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	AssetPtr shaderAsset = assetVendor->getAsset(this->shader);
	ShaderPtr shader = shaderAsset->getAsset<Shader>();
	shader->use();
	shader->setMatrix4("view", view);
	shader->setMatrix4("model", model);
	shader->setMatrix4("projection", projection);
	shader->setVector4f("color", color);

	glActiveTexture(GL_TEXTURE0);
	AssetPtr textureAsset = assetVendor->getAsset(this->texture);
	TexturePtr texture = textureAsset->getAsset<Texture>();
	texture->bind();

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
}