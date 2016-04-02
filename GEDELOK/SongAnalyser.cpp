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

SongAnalyser::SongAnalyser(Ogre::SceneManager* sceneManager)
{
	mSceneMgr = sceneManager;
	for (int i = 0; i < BANDS; i++) {
		Ogre::Entity* ent = mSceneMgr->createEntity("mycube" + Ogre::StringConverter::toString(i),"cube.mesh");
		cubes[i] = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		cubes[i]->attachObject(ent);
		cubes[i]->setScale(Ogre::Vector3(0.1,0.1,0.1));
		cubes[i]->setPosition(Ogre::Vector3(-1000,0,(i*20) - 1000));
	}

	_songs.push_back("../songs/UnitySong.mp3");
	_songs.push_back("../songs/dab.mp3");
	_songs.push_back("../songs/LovelyDay.mp3");
	_songs.push_back("../songs/army.mp3");
	_songs.push_back("../songs/wave.mp3");
	_songs.push_back("../songs/808.mp3");

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

void SongAnalyser::changeSong()
{
	if (_current >= (_songs.size() - 1)) {
		_current = 0;
	} else {
		_current++;
	}
	char *file = _songs[_current];
	BASS_ChannelStop(chan);
	BASS_Free();
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

void SongAnalyser::update()
{
	// analyse channel data
	float fft[FREQUENCIES];
	BASS_ChannelGetData(chan,fft,BASS_DATA_FFT256); // get the FFT data
	int y = 0, b0 = 0;

	for (int x = 0; x < BANDS; x++) {
		float sum = 0;
		int b1 = pow(2, x * 10.0 / (BANDS-1));

		if (b1 > BANDS) {
			b1 = BANDS;
		}

		if (b1 <= b0) {
			b1 = b0 + 1; // make sure it uses at least 1 FFT bin
		}

		int sc = 10 + b1 - b0;
		for (; b0 < b1; b0++) { 
			sum += fft[1 + b0];
		}
		y = (sqrt(sum / log10((float)sc)) * 1.7 * SPECHEIGHT) - 4; // scale it
		if (y > SPECHEIGHT) { 
			y = SPECHEIGHT; // cap it
		}

		// x will range from 0 to BANDS
		// y will range from 0 (sometimes negative) to SPECHEIGHT
		// now let's visualize it with cubes
		Ogre::Vector3 currentpos = cubes[x]->getPosition();
		cubes[x]->setScale(0.1, (float)y / 200, 0.1);
		cubes[x]->setPosition(currentpos.x, 0.5 * 106.08 * (float)y / 50.0 , currentpos.z);
	}
}

void SongAnalyser::addObserver(Observer* ob)
{
	obs.push_back(ob);
}


void SongAnalyser::notify()
{
	// analyse channel data
	float fft[FREQUENCIES];
	BASS_ChannelGetData(chan, fft, BASS_DATA_FFT256); // get the FFT data
	int y = 0, b0 = 0;
	//DWORD val = BASS_ChannelGetLevel(chan);

	float value = fft[0];
	float freq[8] = {0, 0, 0, 0, 0, 0, 0, 0 };
	float avg[8] = {0, 0, 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < FREQUENCIES; i++) { 
		value = fft[i] <= 0.0 ? 0 : fft[i]; // make sure it's non-negative
		logFile << "[" << i << "]:\t" << fft[i]  << " = " << value << "\n";
		
		for (int j = 0; j < RANGES; j++) {
			if ( i >= ranges[j] && i < ranges[j+1] ) {
				freq[j] += value;
			}
		}
	}

	for(unsigned int i = 0; i < obs.size(); i++) {
		float value = freq[obs[i]->getFrequentcyRange()];
		obs[i]->update(value > 0 ? value : 0);
	}
}





