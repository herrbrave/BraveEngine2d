#pragma once

#include <string>
#include <unordered_map>

#include "Component.h"
#include "Uuid.h"

class Entity {
public:
	std::string id = Uuid::createUuid();
	ComponentContainer components;

	template<class ClassType>
	std::weak_ptr<ClassType> getComponent(const std::string type) {
		std::shared_ptr<ClassType> component = static_pointer_cast<ClassType>(this->components.at(type));
		return component;
	}
};
typedef std::shared_ptr<Entity> EntityPtr;
typedef std::weak_ptr<Entity> WeakEntityPtr;

class EntityContainer {
public:
	void registerEntity(EntityPtr entity);
	void deregisterEntity(const std::string id);
	WeakEntityPtr getEntity(const std::string id);
	void clear();
private:
	std::unordered_map<std::string, EntityPtr> entities;
};
typedef std::shared_ptr<EntityContainer> EntityContainerPtr;
typedef std::weak_ptr<EntityContainer> WeakEntityContainerPtr;

class EntityVendor {
public:
	virtual WeakEntityPtr vendEntity(const std::string id) = 0;
};