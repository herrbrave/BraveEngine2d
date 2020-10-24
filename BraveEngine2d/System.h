#pragma once

#include <memory>

enum class SystemType : unsigned short {
	ASSET = 0,
	GRAPHCIS = 1,
};

class System;
typedef std::shared_ptr<System> SystemPtr;
typedef std::weak_ptr<System> WeakSystemPtr;


class System {
public:
	System(SystemType type) : type(type) {}

	SystemType type;
	virtual void clear() = 0;
};