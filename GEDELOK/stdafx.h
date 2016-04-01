// stdafx.h
 
// Ogre headers you need
#include "OgreCamera.h"
#include "OgreEntity.h"
#include "OgreFrameListener.h"
#include "OgreLogManager.h"
#include "OgreMeshManager.h"
#include "OgreMovableObject.h"
#include "OgreParticleSystem.h"
#include "OgreRenderWindow.h"
#include "OgreSceneNode.h"
#include "OgreSceneManager.h"
#include "OgreSingleton.h"
#include "OgreStringConverter.h"
#include "OgreWindowEventUtilities.h"

#include "OIS\OIS.h"

#include "bass.h"
 
// any other header can be included, as usual
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif