#pragma once

#include "Component.h"
#include "Drawable.h"

static const std::string DRAWABLE_COMPONENT_TYPE = "DrawableComponent";

class DrawableComponent : public Component {
public:
	WeakDrawablePtr drawable; 
	glm::vec2 size;
	float rotation;
	glm::vec4 color;
	unsigned int depth;

	DrawableComponent(std::string id, WeakDrawablePtr drawable) : Component(id, DRAWABLE_COMPONENT_TYPE), drawable(drawable), size(glm::vec2(64.0f, 64.0f)), rotation(0.0f), color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), depth(1) {}
};

typedef std::shared_ptr<DrawableComponent> DrawableComponentPtr;
typedef std::weak_ptr<DrawableComponent> WeakDrawableComponentPtr;