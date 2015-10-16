#include "stdafx.h"
#include "Music.h"



CMusic::CMusic()
{
	Mix_Init(MIX_INIT_OGG);
	//Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_OpenAudio(88200, MIX_DEFAULT_FORMAT, 2, NULL);

	//music
	music[0] = Mix_LoadMUS("music/Blood-and-Sand-OST.wav");

	//sound
	sound[0] = Mix_LoadWAV("music/sounds/click.wav");
	sound[1] = Mix_LoadWAV("music/sounds/pickup.wav");
	sound[2] = Mix_LoadWAV("music/sounds/gunshot.wav");


	if (music[0] == NULL)
	{
		std::cout << "music was not loaded!";
	}
}


CMusic::~CMusic()
{
	Mix_FreeMusic(music[0]);

	Mix_FreeChunk(sound[0]);
	Mix_FreeChunk(sound[1]);
	Mix_FreeChunk(sound[2]);

	Mix_CloseAudio();
}

void CMusic::playMusic(int song)
{
	Mix_PlayMusic(music[song], -1);
}

void CMusic::fadeInMusic(int song, int loopAmount, int ms)
{
	Mix_FadeInMusic(music[song], loopAmount, ms);
}

void CMusic::fadeOutMusic(int ms)
{
	Mix_FadeOutMusic(ms);
}

void CMusic::playSound(int soundNumber)
{
	Mix_PlayChannel(-1, sound[soundNumber], 0);
}

void CMusic::loopSound(int soundNumber, int numberOfTimes)
{
	Mix_PlayChannel(-1, sound[soundNumber], numberOfTimes);
}
