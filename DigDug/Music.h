#pragma once
class CMusic
{
public:
	CMusic();
	~CMusic();
	void playMusic(int song);
	void fadeInMusic(int song, int loopAmount, int ms);
	void fadeOutMusic(int ms);

	void playSound(int soundNumber);
	void loopSound(int soundNumber, int numberOfTimes);

private:
	Mix_Music *music[1];
	Mix_Chunk *sound[3];
};

