#pragma once

#include <glm\glm.hpp>

#include "Component.h"

static const std::string PHYSICS_COMPONENT_TYPE = "PhysicsComponent";

class PhysicsComponent : public Component {
public:
	glm::vec2 position;
	glm::vec2 velocity;

	PhysicsComponent() : Component(PHYSICS_COMPONENT_TYPE), position(glm::vec2(0.0f, 0.0f)), velocity(glm::vec2(0.0f, 0.0f)) {}
};

typedef std::shared_ptr<PhysicsComponent> PhysicsComponentPtr;
typedef std::weak_ptr<PhysicsComponent> WeakPhysicsComponentPtr;