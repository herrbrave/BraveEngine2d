#pragma once

#include <box2d/b2_body.h>
#include <glm/glm.hpp>
#include <memory>
#include <string>

enum PhysicsType {
	STATIC = b2_staticBody,
	KINEMATIC = b2_kinematicBody,
	DYNAMIC = b2_dynamicBody,
};

enum PhysicsShapeType {
	CIRCLE = b2Shape::Type::e_circle,
	BOX = b2Shape::Type::e_polygon,
};

class PhysicsShape {
public:
	PhysicsShapeType type;
};

typedef std::shared_ptr<PhysicsShape> PhysicsShapePtr;
typedef std::weak_ptr<PhysicsShape> WeakPhysicsShapePtr;

class CircleShape : public PhysicsShape {
public:
	float radius;
	CircleShape(float radius) {
		this->type = CIRCLE;
		this->radius = radius;
	}
};

typedef std::shared_ptr<CircleShape> CircleShapePtr;
typedef std::weak_ptr<CircleShape> WeakCircleShapePtr;

class BoxShape : public PhysicsShape {
public:
	float width;
	float height;
	BoxShape(float width, float height) {
		this->type = BOX;
		this->width = width;
		this->height = height;
	}
};

typedef std::shared_ptr<BoxShape> BoxShapePtr;
typedef std::weak_ptr<BoxShape> WeakBoxShapePtr;

class PhysicsConfig {
public:
	PhysicsType type;
	float angleRadians;
	glm::vec2 position;
	glm::vec2 linearVel;
	glm::vec2 linearImpulse;
	float angularVel;
	bool fixedRotation;
	bool bullet;
	PhysicsShapePtr shape;
	PhysicsConfig(
		PhysicsType type = STATIC,
		PhysicsShapePtr shape = BoxShapePtr(new BoxShape(32.0f, 32.0f)),
		float angleRadians = 0.0f,
		glm::vec2 position = glm::vec2(0.0f, 0.0f),
		glm::vec2 linearVel = glm::vec2(0.0f, 0.0f),
		glm::vec2 linearImpulse = glm::vec2(0.0f, 0.0f),
		float angularVel = 0.0f,
		bool fixedRotation = false,
		bool bullet = false) : type(type), shape(shape), angleRadians(angleRadians), position(position), linearVel(linearVel), angularVel(angularVel), fixedRotation(fixedRotation), bullet(bullet) {}
};

typedef std::shared_ptr<PhysicsConfig> PhysicsConfigPtr;
typedef std::weak_ptr<PhysicsConfig> WeakPhysicsConfigPtr;

class Physics {
public:
	std::string physicsId;

	glm::vec2 force;
	float torque;
	glm::vec2 impulse;
	float angImpulse;
	glm::vec2 position;
	float angleRadians;

	void applyForce(glm::vec2 force);
	void applyTorque(float torque);
	void applyLinearImpulse(glm::vec2 force);
	void applyAngularImpulse(float impulse);
	glm::vec2 getPosition();
	float getAngleRadians();
	Physics(
		std::string physicsId,
		glm::vec2 force,
		float torque,
		glm::vec2 impulse,
		float angImpulse,
		glm::vec2 position,
		float angleRadians) : physicsId(physicsId), force(force), torque(torque), impulse(impulse), angImpulse(angImpulse), position(position), angleRadians(angleRadians) {};
}; 

typedef std::shared_ptr<Physics> PhysicsPtr;
typedef std::weak_ptr<Physics> WeakPhysicsPtr;