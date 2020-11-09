#pragma once

#include <glm\glm.hpp>

#include "Component.h"
#include "Constants.h"
#include "Physics.h"

static const std::string PHYSICS_COMPONENT_TYPE = "PhysicsComponent";

class PhysicsComponent : public Component {
public:
	PhysicsComponent(std::string id, PhysicsBodyPtr body) : Component(id, PHYSICS_COMPONENT_TYPE), body(body) {}

	void applyForce(float x, float y);
	void applyForce(glm::vec2 force);

	void applyTorque(float torque);

	void applyLinearImpulse(float x, float y);
	void applyLinearImpulse(glm::vec2 force);

	void applyAngularImpulse(float torque);

	glm::vec2 getPosition();
	float getAngle();
private:
	PhysicsBodyPtr body;
};

typedef std::shared_ptr<PhysicsComponent> PhysicsComponentPtr;
typedef std::weak_ptr<PhysicsComponent> WeakPhysicsComponentPtr;