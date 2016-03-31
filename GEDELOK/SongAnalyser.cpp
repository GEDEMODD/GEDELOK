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

SongAnalyser::SongAnalyser(SceneManager* sceneManager)
{
	mSceneMgr = sceneManager;
	for (int i = 0; i < BANDS; i++) {
		Entity* ent = mSceneMgr->createEntity("mycube" + StringConverter::toString(i),"cube.mesh");
		cubes[i] = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		cubes[i]->attachObject(ent);
		cubes[i]->setScale(Vector3(0.3,0.3,0.3));
		cubes[i]->setPosition(Vector3(0,0,i*50));
	}

	// play a song
	if (!BASS_Init(-1,44100,0,NULL,NULL)) {
		Ogre::LogManager::getSingleton().logMessage("can't initialize BASS");
	}
	else {
		char file[MAX_PATH]="../dab.mp3";
		if (!(chan = BASS_StreamCreateFile(FALSE, file, 0, 0, BASS_SAMPLE_LOOP))
			&& !(chan = BASS_MusicLoad(FALSE, file, 0, 0, BASS_MUSIC_RAMP | BASS_SAMPLE_LOOP, 0))) {
				Ogre::LogManager::getSingleton().logMessage("can't play music file");
		}
		BASS_ChannelPlay(chan,FALSE);
	}
	// Open the Log file
	logFile.open("log.txt");

	accelerator = 1;
}

SongAnalyser::~SongAnalyser()
{
	BASS_Free(); // free up BASS
	logFile.close();
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
		Vector3 currentpos = cubes[x]->getPosition();
		cubes[x]->setScale(0.3, (float)y / 50.0, 0.3);
		cubes[x]->setPosition(currentpos.x, 0.5 * 106.08 * (float)y / 50.0 , currentpos.z);
	}
}

void SongAnalyser::addObserver(Object* newObserver)
{
	observers.push_back(newObserver);
}

void SongAnalyser::notify()
{
	// analyse channel data
	float fft[FREQUENCIES];
	BASS_ChannelGetData(chan, fft, BASS_DATA_FFT256); // get the FFT data
	int y = 0, b0 = 0;
	//DWORD val = BASS_ChannelGetLevel(chan);

	double makeSmallerBy = 0.1,
		   makeBiggerBy = 0.3,
		   threashold = 0.35;

	float value = fft[0];
	bool low = false, mid = false, high = false;
	for (int i = 0; i < FREQUENCIES; i++) {
		value = fft[i] <= 0.0 ? 0 : fft[i];
		logFile << "[" << i << "]:\t" << fft[i]  << " = " << value << "\n";
		
		if ( i <= 20) {
			// low freq
			if ( !low ) {
				low = value > threashold;
			}
		} else if ( (i > 20) && (i < (FREQUENCIES/3) * 2)) {
			// mid freq
			if ( !mid ) {
				mid = value > threashold;
			}
		} else {
			// high
			if ( !high ) {
				high = value > threashold;
			}
		}
	}

	for(unsigned int x = 0; x < observers.size(); x++) {
		Object *curr = observers[x];
		if ( low ) {
			curr->increase();
		} else {
			curr->decrease();
		}
	}
}

