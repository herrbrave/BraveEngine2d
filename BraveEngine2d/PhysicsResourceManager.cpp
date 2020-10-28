#include "PhysicsResourceManager.h"

void PhysicsResourceManager::initPhysics(glm::vec2 gravity) {
	b2Vec2 grav(gravity.x, gravity.y);
	b2World* worldObject = new b2World(grav);
	this->world.reset(worldObject);
}

WeakPhysicsPtr PhysicsResourceManager::loadPhysics(std::string name, PhysicsConfigPtr physicsConfig) {
	b2BodyDef bodydef;
	bodydef.type = physicsConfig->type == STATIC ? b2BodyType::b2_staticBody : b2BodyType::b2_dynamicBody;
	bodydef.position.Set(PHYSICS_SCALING_FACTOR * physicsConfig->position.x, PHYSICS_SCALING_FACTOR * physicsConfig->position.y);
	bodydef.angle = physicsConfig->angleRadians;
	bodydef.linearVelocity.Set(PHYSICS_SCALING_FACTOR * physicsConfig->linearVel.x, PHYSICS_SCALING_FACTOR * physicsConfig->linearVel.y);
	bodydef.fixedRotation = physicsConfig->fixedRotation;
	bodydef.bullet = physicsConfig->bullet;
	bodydef.enabled = true;
	bodydef.angularVelocity = physicsConfig->angularVel;
	bodydef.userData.pointer = reinterpret_cast<uintptr_t>(new std::string(name.c_str()));

	b2Body* body = this->world->CreateBody(&bodydef);

	if (physicsConfig->shape->type == CIRCLE) {
		b2CircleShape shape;
		shape.m_radius = PHYSICS_SCALING_FACTOR * ((CircleShape*)physicsConfig->shape.get())->radius;
		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 1.0f;
		fixture.friction = 0.3f;
		body->CreateFixture(&fixture);
	}
	else {
		b2PolygonShape shape;
		shape.SetAsBox(PHYSICS_SCALING_FACTOR * ((BoxShape*)physicsConfig->shape.get())->width, PHYSICS_SCALING_FACTOR * ((BoxShape*)physicsConfig->shape.get())->height);
		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 1.0f;
		fixture.friction = 0.3f;
		body->CreateFixture(&fixture);
	}

	Physics* physics = new Physics(name, glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.0f, 0.0f), 0.0f);
	this->physicMap.emplace(name, PhysicsPtr(physics));
	return this->physicMap.at(name);
}

WeakPhysicsPtr PhysicsResourceManager::getPhysics(std::string name) {
	return this->physicMap.at(name);
}

void PhysicsResourceManager::update(float dt) {
	this->world->Step(dt, 2, 4);

	b2Body* body = PhysicsResourceManager::world->GetBodyList();
	while (body != nullptr) {
		std::string* name = (std::string*) body->GetUserData().pointer;
		PhysicsPtr physics = this->physicMap.at(*name);
		if (physics->impulse.x != 0.0f || physics->impulse.y != 0.0f) {
			body->ApplyLinearImpulseToCenter(this->PHYSICS_SCALING_FACTOR * b2Vec2(physics->impulse.x, physics->impulse.y), true);\
		}

		physics->position.x = body->GetWorldCenter().x / PHYSICS_SCALING_FACTOR;
		physics->position.y = body->GetWorldCenter().y / PHYSICS_SCALING_FACTOR;

		body = body->GetNext();
	}
}