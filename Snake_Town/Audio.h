#include <Windows.h>
#ifndef AUDIO
#define AUDIO

namespace Audio //audio namespace
{

enum class Sounds //enum of all available sound clips
{
	death,
	option,
	pickUp,
	menuMusic,
	playMusic,
	timedPickUp,
	timedSpawn
};


void playSoundClip ( Sounds sound, bool looping )
{
	LPCWSTR soundToPlay = TEXT ( "" ); //sets soundToPlay to default value, if not changed by statements below will play classic windows "ding" noise

	switch (sound)
	{

	case Sounds::death:
		soundToPlay = TEXT ( "Death.wav" );
		break;

	case Sounds::option:
		soundToPlay = TEXT ( "Option.wav" );
		break;

	case Sounds::pickUp:
		soundToPlay = TEXT ( "PickUp.wav" );
		break;

	case Sounds::menuMusic:
		soundToPlay = TEXT ( "MenuMusic.wav" );
		break;

	case Sounds::playMusic:
		soundToPlay = TEXT ( "PlayModeMusic.wav" );
		break;

	case Sounds::timedPickUp:
		soundToPlay = TEXT ( "timedPickUp.wav" );
		break;

	case Sounds::timedSpawn:
		soundToPlay = TEXT ( "timedSpawn.wav" );
		break;

	default:
		break;
	}


	if (looping)
	{
		PlaySound ( soundToPlay, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );
	}
	else
	{
		PlaySound ( soundToPlay, NULL, SND_FILENAME | SND_ASYNC );
	}
}

void stopAudio ()
{
	PlaySound ( NULL, NULL, SND_ASYNC );
}


}

#endif