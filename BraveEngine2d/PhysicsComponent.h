#pragma once

#include <glm\glm.hpp>

#include "Component.h"
#include "Physics.h"

static const std::string PHYSICS_COMPONENT_TYPE = "PhysicsComponent";

class PhysicsComponent : public Component {
public:
	WeakPhysicsPtr physics;

	PhysicsComponent(WeakPhysicsPtr physics) : Component(PHYSICS_COMPONENT_TYPE), physics(std::move(physics)) {}
};

typedef std::shared_ptr<PhysicsComponent> PhysicsComponentPtr;
typedef std::weak_ptr<PhysicsComponent> WeakPhysicsComponentPtr;