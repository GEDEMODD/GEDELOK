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
	for (int i=0; i<BANDS; i++)
	{
		Entity* ent = mSceneMgr->createEntity("mycube" + StringConverter::toString(i),"cube.mesh");
		cubes[i] = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		cubes[i]->attachObject(ent);
		cubes[i]->setScale(Vector3(0.3,0.3,0.3));
		cubes[i]->setPosition(Vector3(0,0,i*50));
	}

	// play a song
	if (!BASS_Init(-1,44100,0,NULL,NULL)) Ogre::LogManager::getSingleton().logMessage("can't initialize BASS");
	else
	{
		char file[MAX_PATH]="../wave.mp3";
		if (!(chan=BASS_StreamCreateFile(FALSE,file,0,0,BASS_SAMPLE_LOOP))
			&& !(chan=BASS_MusicLoad(FALSE,file,0,0,BASS_MUSIC_RAMP|BASS_SAMPLE_LOOP,0))) 
			Ogre::LogManager::getSingleton().logMessage("can't play music file");
		BASS_ChannelPlay(chan,FALSE);
	}

	logFile.open("log.txt");
}

SongAnalyser::~SongAnalyser()
{
	BASS_Free(); // free up BASS
	logFile.close();
}

void SongAnalyser::update()
{
	// analyse channel data
	float fft[128];
	BASS_ChannelGetData(chan,fft,BASS_DATA_FFT256); // get the FFT data
	int y=0, b0=0;

	for (int i = 0; i < 128; i++) {
		logFile << fft[i];
		logFile << "; ";
	}
	logFile << "\n";

	for (int x = 0; x < BANDS; x++) {
		float sum = 0;
		int b1 = pow(2, x * 10.0 / (BANDS-1));
		
		if (b1 > 127) {
			b1 = 127;
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
		cubes[x]->setScale(0.1, (float)y / 50.0, 0.1);
		cubes[x]->setPosition(currentpos.x, 53.04 * (float)y / 50.0 , currentpos.z);
	}
}

void SongAnalyser::addObserver(SceneNode* newObserver)
{
	observers.push_back(newObserver);
}

void SongAnalyser::notify()
{
	// analyse channel data
	float fft[1024];
	BASS_ChannelGetData(chan, fft, BASS_DATA_FFT2048); // get the FFT data
	int y = 0, b0 = 0;
	DWORD val = BASS_ChannelGetLevel(chan);

	for(unsigned int x = 0; x < observers.size(); x++) {
		SceneNode *curr = observers[x];

		//logFile << val;
		//logFile << "\n";
		long value = fft[90];
		if ( curr->getScale().x > value) {
			curr->setPosition(curr->getPosition().x, value,  curr->getPosition().z);
			curr->setScale(curr->getScale().x - 0.1, curr->getScale().y - 0.1,  curr->getScale().z - 0.1);
		} else {
			curr->setPosition(curr->getPosition().x, value,  curr->getPosition().z);
			curr->setScale(curr->getScale().x + 0.1, curr->getScale().y + 0.1,  curr->getScale().z + 0.1);
		}

		if ( value > 2 ) 
		{

		}
	}
	/*for (int i = 0; fft[i] != '\0'; i++) {
		for(unsigned int x = 0; x < observers.size(); x++) {
			SceneNode *curr = observers[x];
			float value = fft[i] * 0.01;
			if ( curr->getScale().x < value) {
				curr->setScale(value, value, value);			
			}
		}
	}*/
}

