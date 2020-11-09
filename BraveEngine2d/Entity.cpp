#include "Entity.h"

void EntityContainer::clear() {
	this->entities.clear();
}

WeakEntityPtr EntityContainer::getEntity(const std::string id) {
	return this->entities.at(id);
}

void EntityContainer::deregisterEntity(const std::string id) {
	this->entities.erase(this->entities.find(id));
}

void EntityContainer::registerEntity(EntityPtr entity) {
	this->entities.emplace(entity->id, entity);
}