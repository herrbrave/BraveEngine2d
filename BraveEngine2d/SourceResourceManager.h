#pragma once

#include <unordered_map>

#include "Asset.h"
#include "Sound.h"

class SoundResourceManager {
public:
	std::unordered_map<std::string, SoundPtr> sounds;

};