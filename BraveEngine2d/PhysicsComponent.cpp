#include "PhysicsComponent.h"

void PhysicsComponent::applyForce(float x, float y) {
	this->body->applyForce(x, y);
}

void PhysicsComponent::applyForce(glm::vec2 force) {
	this->body->applyForce(force);
}

void PhysicsComponent::applyTorque(float torque) {
	this->body->applyTorque(torque);
}

void PhysicsComponent::applyLinearImpulse(float x, float y) {
	this->body->applyLinearImpulse(x, y);
}

void PhysicsComponent::applyLinearImpulse(glm::vec2 force) {
	this->body->applyLinearImpulse(force);
}

void PhysicsComponent::applyAngularImpulse(float torque) {
	this->body->applyAngularImpulse(torque);
}

glm::vec2 PhysicsComponent::getPosition() {
	return this->body->getPosition();
}

float PhysicsComponent::getAngle() {
	return this->body->getAngle();
}