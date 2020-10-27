#pragma once

#include <random>
#include <sstream>

static std::random_device random;
static std::mt19937 gen(random());
static std::uniform_int_distribution<> distroFront(0, 15);
static std::uniform_int_distribution<> distroBack(8, 11);

class Uuid {
public:
	static std::string createUuid() {
		std::stringstream stream;
		int index;
		stream << std::hex;
		for (index = 0; index < 8; index++) {
			stream << distroFront(gen);
		}
		stream << "-";
		for (index = 0; index < 4; index++) {
			stream << distroFront(gen);
		}
		stream << "-4";
		for (index = 0; index < 3; index++) {
			stream << distroFront(gen);
		}
		stream << "-";
		stream << distroBack(gen);
		for (index = 0; index < 3; index++) {
			stream << distroFront(gen);
		}
		stream << "-";
		for (index = 0; index < 12; index++) {
			stream << distroFront(gen);
		}
		return stream.str();
	}
};