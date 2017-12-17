#include "stdafx.h"
#include "SoundManager.h"

void SoundManager::AddSound(std::string name, std::wstring file)

{
	m_soundFX[name] = SoundEffect({ file.c_str() });
}

void SoundManager::Play(std::string sound, float in_volume)
{
	m_soundFX[sound].Play(pl, in_volume);
}

void SoundManager::Play(std::string sound)
{
	m_soundFX[sound].Play(pl, volume);
}

void SoundManager::SetVolume(float vol)
{
	volume = vol;
}
