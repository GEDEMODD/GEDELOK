#include "SceneManager.h"


SceneManager::SceneManager(void)
{
	_sceneManager = NULL;
	_root = NULL;
	_listener = NULL;
}


SceneManager::~SceneManager(void)
{
	delete _root;
	delete _listener;
}

void SceneManager::loadResources()
{
	Ogre::ConfigFile cf;
	cf.load("../LabFiles/OgreConfig/resources_d.cfg");
	Ogre::ConfigFile::SectionIterator sectionIter = cf.getSectionIterator();
	Ogre::String sectionName, typeName, dataName;
	while ( sectionIter.hasMoreElements() ) {
		sectionName = sectionIter.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = sectionIter.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		// Iterate over the settings and add each resource:
		for (i = settings->begin(); i != settings->end(); i++) {
			typeName = i->first;
			dataName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(dataName, typeName, sectionName);
		}
	}

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

int SceneManager::startup()
{
	_root = new Ogre::Root("../LabFiles/OgreConfig/plugins_d.cfg");
	if ( !_root->showConfigDialog() ) {
		return -1;
	}
	// Create the RenderWindow and sceneManager
	Ogre::RenderWindow* window = _root->initialise(true, "Ogre3D Beginner Guide");
	_sceneManager = _root->createSceneManager(Ogre::ST_GENERIC);

	// Create a camaera and a viewport
	Ogre::Camera* camera = _sceneManager->createCamera("Camera");
	camera->setPosition(Ogre::Vector3(0, 0, 50));
	camera->lookAt(Ogre::Vector3(0, 0, 0));
	camera->setNearClipDistance(5);
	
	Ogre::Viewport* viewport = window->addViewport(camera);
	viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.,0));
	camera->setAspectRatio(Ogre::Real( viewport->getActualWidth() / Ogre::Real(viewport->getActualHeight() )));
	
	// Add Frame Listener
	_listener = new FrameListener(window, camera, viewport, _SinbadNode, _SinbadEnt);
	_root->addFrameListener(_listener);
	
	loadResources();
	createScene();

	return 0;
}

void SceneManager::createScene()
{
	//Ogre::Entity* ent = _sceneManager->createEntity("Sinbad", "Sinbad.mesh");
	_SinbadEnt = _sceneManager->createEntity("Sinbad.mesh");
	//_sceneManager->getRootSceneNode()->attachObject(ent);
	_sceneManager->setAmbientLight(Ogre::ColourValue(.5f,.5f,.5f));

	// Define plane
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -5);
	Ogre::MeshManager::getSingleton().createPlane("plane", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
		1500, 1500, 200, 200, true, 1, 5, 6, Ogre::Vector3::UNIT_Z);

	// Create plane and add it to the scene and also change the material
	Ogre::Entity* ground = _sceneManager->createEntity("LinghtPlaneEntity", "plane");
	_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ground);
	ground->setMaterialName("Examples/BeachStones");

	// Add one directional light
	Ogre::Light* light = _sceneManager->createLight( "Light1" );
	light->setType( Ogre::Light::LT_DIRECTIONAL );
	light->setDirection( Ogre::Vector3(1, -1, 0) );

	// add shadows 
	_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	_SinbadNode = _sceneManager->getRootSceneNode()->createChildSceneNode();
	_SinbadNode->attachObject(_SinbadEnt);
	_listener->setAniState(_SinbadEnt->getAnimationState("RunBase"));
	_listener->setAniStateTop(_SinbadEnt->getAnimationState("RunTop"));
	_listener->setNode(_SinbadNode);
}

void SceneManager::renderOneFrame()
{
	Ogre::WindowEventUtilities::messagePump();
	_keepRunning = _root->renderOneFrame();
}	

bool SceneManager::keepRunning()
{
	return _keepRunning;	
}