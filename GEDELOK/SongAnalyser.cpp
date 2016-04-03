#include "stdafx.h"
#include "SongAnalyser.h"

template<> SongAnalyser* Ogre::Singleton<SongAnalyser>::msSingleton = 0;

SongAnalyser* SongAnalyser::getSingletonPtr(void)
{
	return msSingleton;
}
SongAnalyser& SongAnalyser::getSingleton(void)
{
	assert( msSingleton );  return ( *msSingleton );
}

SongAnalyser::SongAnalyser()
{
	loadSongs();

	// play a song
	if (!BASS_Init(-1,44100,0,NULL,NULL)) {
		Ogre::LogManager::getSingleton().logMessage("can't initialize BASS");
	}
	else {
		char *file = _songs[0];
		if (!(chan = BASS_StreamCreateFile(FALSE, file, 0, 0, BASS_SAMPLE_LOOP))
			&& !(chan = BASS_MusicLoad(FALSE, file, 0, 0, BASS_MUSIC_RAMP | BASS_SAMPLE_LOOP, 0))) {
				Ogre::LogManager::getSingleton().logMessage("can't play music file");
		}
		BASS_ChannelPlay(chan,FALSE);
	}
	// Open the Log file
	logFile.open("log.txt");

	// Initilaze frequentcy ranges
	for (int i = 0; i <= RANGES ; i++ )  {
		ranges[i] = (FREQUENCIES/RANGES) * i;
	}
	_current = 0;
}

SongAnalyser::~SongAnalyser()
{
	BASS_Free(); // free up BASS
	logFile.close();
}

void SongAnalyser::loadSongs()
{
	_songs.push_back("../songs/UnitySong.mp3");
	_songs.push_back("../songs/Idioteque.mp3");
	_songs.push_back("../songs/dab.mp3");
	_songs.push_back("../songs/LovelyDay.mp3");
	_songs.push_back("../songs/army.mp3");
	_songs.push_back("../songs/808.mp3");
}

void SongAnalyser::changeSong()
{
	// Stop the current song
	BASS_ChannelStop(chan);
	BASS_Free();

	// Update song index
	if (_current >= (_songs.size() - 1)) {
		_current = 0;
	} else {
		_current++;
	}
	char *file = _songs[_current];

	// Play next song
	if (!BASS_Init(-1,44100,0,NULL,NULL)) {
		Ogre::LogManager::getSingleton().logMessage("can't initialize BASS");
	}
	else {
		if (!(chan = BASS_StreamCreateFile(FALSE, file, 0, 0, BASS_SAMPLE_LOOP))
			&& !(chan = BASS_MusicLoad(FALSE, file, 0, 0, BASS_MUSIC_RAMP | BASS_SAMPLE_LOOP, 0))) {
				Ogre::LogManager::getSingleton().logMessage("can't play music file");
				std::cout << "cant play: " << _songs[_current] << "\n";
		}
		BASS_ChannelPlay(chan,FALSE);
	}
}

void SongAnalyser::addObserver(Observer* ob)
{
	obs.push_back(ob);
}


void SongAnalyser::update()
{
	// analyse channel data
	float fft[FREQUENCIES];
	BASS_ChannelGetData(chan, fft, BASS_DATA_FFT256); // get the FFT data

	float value = fft[0];
	float freq[8] = {0, 0, 0, 0, 0, 0, 0, 0 };
	float avg[8] = {0, 0, 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < FREQUENCIES; i++) { 
		value = fft[i] <= 0.0 ? 0 : fft[i]; // make sure it's non-negative
		logFile << "[" << i << "]:\t" << fft[i]  << " = " << value << "\n";
		
		// Summerise value for the frequentcy ranges
		for (int j = 0; j < RANGES; j++) {
			if ( i >= ranges[j] && i < ranges[j+1] ) {
				freq[j] += value;
			}
		}
	}

	// Update observers...
	for(unsigned int i = 0; i < obs.size(); i++) {
		float value = freq[obs[i]->getFrequentcyRange()];
		obs[i]->update(value > 0 ? value : 0);
	}
}





