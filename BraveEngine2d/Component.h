#pragma once

#include <memory>
#include <string>
#include <unordered_map>

class Component {
public:
	std::string type;

	Component(std::string type) {
		this->type = type;
	}
};

typedef std::shared_ptr<Component> ComponentPtr;
typedef std::weak_ptr<Component> WeakComponentPtr;
typedef std::unordered_map<std::string, ComponentPtr> ComponentContainer;