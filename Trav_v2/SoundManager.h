#pragma once


#include "SoundEffect.h"

class SoundManager 
{
	std::unordered_map<std::string, SoundEffect> m_soundFX;
	float pl = 0.0f;;
	float volume = 1.0f;
public:
	SoundManager() {}
	~SoundManager() {}
	void AddSound(std::string name, std::wstring file);
	void Play(std::string sound, float in_volume);
	void Play(std::string sound);
	void SetVolume(float vol);
};