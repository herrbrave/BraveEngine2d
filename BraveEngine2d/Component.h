#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Asset.h"

class Component {
public:
	std::string type;

	Component(std::string id, std::string type) {
		this->id.assign(id);
		this->type.assign(type);
	}

protected:
	std::string id;
};

typedef std::shared_ptr<Component> ComponentPtr;
typedef std::weak_ptr<Component> WeakComponentPtr;
typedef std::unordered_map<std::string, ComponentPtr> ComponentContainer;