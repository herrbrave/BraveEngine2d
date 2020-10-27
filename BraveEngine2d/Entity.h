#pragma once

#include <string>

#include "Component.h"
#include "Uuid.h"

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;
typedef std::weak_ptr<Entity> WeakEntityPtr;

class Entity {
public:
	std::string id = Uuid::createUuid();
	WeakEntityPtr parent;
	std::unordered_map<std::string, WeakEntityPtr> children;
	ComponentContainer components;
};