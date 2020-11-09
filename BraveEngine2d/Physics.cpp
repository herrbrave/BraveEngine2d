#include "Physics.h"

void PhysicsBody::applyForce(float x, float y) {
	BodyPtr body = makeShared(this->body);
	body->ApplyForceToCenter(b2Vec2(x, y), true);
}

void PhysicsBody::applyForce(glm::vec2 force) {
	BodyPtr body = makeShared(this->body);
	body->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
}

void PhysicsBody::applyTorque(float torque) {
	BodyPtr body = makeShared(this->body);
	body->ApplyTorque(torque, true);
}

void PhysicsBody::applyLinearImpulse(float x, float y) {
	BodyPtr body = makeShared(this->body);
	body->ApplyLinearImpulseToCenter(b2Vec2(x, y), true);
}

void PhysicsBody::applyLinearImpulse(glm::vec2 force) {
	BodyPtr body = makeShared(this->body);
	body->ApplyLinearImpulseToCenter(b2Vec2(force.x, force.y), true);
}

void PhysicsBody::applyAngularImpulse(float torque) {
	BodyPtr body = makeShared(this->body);
	body->ApplyAngularImpulse(torque, true);
}

glm::vec2 PhysicsBody::getPosition() {
	BodyPtr body = makeShared(this->body);
	b2Vec2 pos = body->GetPosition();
	return glm::vec2(pos.x, pos.y);
}

float PhysicsBody::getAngle() {
	BodyPtr body = makeShared(this->body);
	return body->GetAngle();
}

void Physics::initPhysics(glm::vec2 gravity) {
	b2Vec2 grav(gravity.x, gravity.y);
	b2World* worldObject = new b2World(grav);
	this->world.reset(worldObject);
}

PhysicsBodyPtr Physics::loadPhysics(PhysicsConfigPtr physicsConfig, std::string name) {
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

	b2Body* body = world->CreateBody(&bodydef);

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

	bodies.emplace(name, BodyPtr(body, PhysicsDeleters()));
	return PhysicsBodyPtr(new PhysicsBody(bodies.at(name)));
}

void Physics::update(float dt) {
	this->world->Step(dt, 2, 4);
}