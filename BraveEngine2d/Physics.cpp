#include "Physics.h"

void Physics::applyForce(glm::vec2 force) {
	this->force = force;
}

void Physics::applyTorque(float torque) {
	this->torque = torque;
}

void Physics::applyLinearImpulse(glm::vec2 force) {
	this->impulse = force;
}

void Physics::applyAngularImpulse(float impulse) {
	this->angImpulse = impulse;
}

glm::vec2 Physics::getPosition() {
	return this->position;
}

float Physics::getAngleRadians() {
	return this->angleRadians;
}