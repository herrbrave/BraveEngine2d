#pragma once

#include <box2d/box2d.h>
#include <unordered_map>

#include "Physics.h"

class PhysicsResourceManager {
public:
	WeakPhysicsPtr loadPhysics(std::string name, PhysicsConfigPtr physicsConfig);
	WeakPhysicsPtr getPhysics(std::string name);

	void initPhysics(glm::vec2 gravity = glm::vec2(0.0f, 0.0f));

	void update(float dt);
private:
	const float PHYSICS_SCALING_FACTOR = 0.01f;
	std::unordered_map<std::string, PhysicsPtr> physicMap;
	std::shared_ptr<b2World> world;
};

