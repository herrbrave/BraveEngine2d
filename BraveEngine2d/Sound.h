#pragma once

#include <memory>
#include <string>

enum class SoundType {
	SOUND = 0,
	MUSIC = 1,
};

enum class SoundState {
	STOPPED = 0,
	STOP = 1,
	PLAY = 2,
	PLAYING = 3,
	LOOP = 4,
	LOOPING = 5,
	PAUSE = 6,
	PAUSED = 7,
};

class Sound {
public:
	std::string id;
	std::string name;
	SoundType type;
	SoundState state;
	Sound(std::string id, std::string name, SoundType type = SoundType::SOUND, SoundState state = SoundState::STOPPED) : id(id), name(name), type(type), state(state) {}
};

typedef std::shared_ptr<Sound> SoundPtr;
typedef std::weak_ptr<Sound> WeakSoundPtr;