#include "stdafx.h"
#include "MySceneManager.h"


MySceneManager::MySceneManager(void)
{
	_sceneManager = NULL;
	_root = NULL;
	_listener = NULL;
}


MySceneManager::~MySceneManager(void)
{
	delete _root;
	delete _listener;
}

void MySceneManager::loadResources()
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

int MySceneManager::startup()
{
	_root = new Ogre::Root("../LabFiles/OgreConfig/plugins_d.cfg");
	if ( !_root->showConfigDialog() ) {
		return -1;
	}
	// Create the RenderWindow and MySceneManager
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
	_listener = new MyFrameListener(window, camera, viewport, _SinbadNode, _SinbadEnt);
	_root->addFrameListener(_listener);
	
	loadResources();
	createScene();

	return 0;
}

void MySceneManager::createScene()
{
	//Ogre::Entity* ent = _MySceneManager->createEntity("Sinbad", "Sinbad.mesh");
	_SinbadEnt = _sceneManager->createEntity("Sinbad.mesh");
	printf("%s\n", _sceneManager->getName());
	//_MySceneManager->getRootSceneNode()->attachObject(ent);
	_sceneManager->setAmbientLight(Ogre::ColourValue(.5f,.5f,.5f));

	// Define plane
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -5);
	Ogre::MeshManager::getSingleton().createPlane("plane", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
		1500, 1500, 200, 200, true, 1, 5, 6, Ogre::Vector3::UNIT_Z);

	// Create plane and add it to the scene and also change the material
	Ogre::Entity* ground = _sceneManager->createEntity("LightPlaneEntity", "plane");
	_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ground);
	ground->setMaterialName("shader/texture");
	
	//// Add one directional light
	Ogre::Light* light = _sceneManager->createLight( "Light1" );
	light->setType( Ogre::Light::LT_DIRECTIONAL );
	light->setDiffuseColour(1,1,0.7);
	light->setDirection( Ogre::Vector3(1, -1, -0.3) );

	//// Add one directional light
	Ogre::Light* light2 = _sceneManager->createLight( "Light2" );
	light2->setType( Ogre::Light::LT_DIRECTIONAL );
	light2->setDiffuseColour(0.5, 1, 0.5);
	light2->setSpecularColour(1,1,1);
	light2->setDirection( Ogre::Vector3(-1, -1, 0.5) );
	

	// add shadows 
	_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	_SinbadNode = _sceneManager->getRootSceneNode()->createChildSceneNode();
	_SinbadNode->attachObject(_SinbadEnt);
	_listener->setAniState(_SinbadEnt->getAnimationState("RunBase"));
	_listener->setAniStateTop(_SinbadEnt->getAnimationState("RunTop"));
	_listener->setNode(_SinbadNode);
	// make the showroom
	makeRoom();
	// Create a particle system
	//Ogre::ParticleSystem* partSystem = _sceneManager->createParticleSystem("smoke", "MySmoke1");
	// Attach the particle system to Sinbad
	//_SinbadNode->attachObject(partSystem); 

	_songAnalyser = new SongAnalyser(_sceneManager);
	_listener->setSongAnalyser(_songAnalyser);
	
	_songAnalyser->addObserver(new MyLight(_sceneManager->createLight( "Light3" ), 1, 0.5));

	for(int i = 1; i <= 8; i++) {
		Mesh * newMesh = new Mesh(_sceneManager, "donutShowcase" + i, "Donut.mesh", i-1, 1.5/pow(10, i));
		newMesh->setPosition(Ogre::Vector3(170, i*10, -142.5));
		newMesh->setMaxSize( 30/i+5 );
		newMesh->setMinSize( 10/i );
		newMesh->setScaling(Ogre::Vector3(2.0, 2.0, 2.0));
		_songAnalyser->addObserver(newMesh);
	}

	Replicator* rep = new Replicator(_sceneManager, "rep", "sphere.mesh", 7, 0.3);
	rep->setPosition(Ogre::Vector3(170, 20, 42.5));
	rep->setScale(Ogre::Vector3(0.05, 0.05, 0.05));
	rep->setMaterial("Material.blue");
	_songAnalyser->addObserver(rep);

	Replicator* repp = new Replicator(_sceneManager, "rep2", "sphere.mesh", 4, 0.3);
	repp->setPosition(Ogre::Vector3(170, 20, 42.5));
	repp->setScale(Ogre::Vector3(0.05, 0.05, 0.05));
	repp->setMaterial("Material.red");
	_songAnalyser->addObserver(repp);

	Replicator* reppp = new Replicator(_sceneManager, "reppp", "sphere.mesh", 1, 0.3);
	reppp->setPosition(Ogre::Vector3(170, 20, 42.5));
	reppp->setScale(Ogre::Vector3(0.05, 0.05, 0.05));
	reppp->setMaterial("Material.green");
	_songAnalyser->addObserver(reppp);

	LineBeat * lb;

	float linePos = 115;
	for(int i = 1; i <= 8; i++) {
		 lb = new LineBeat(_sceneManager, "willbeunnamed", "Donut.mesh", i-1, 1.5);
		lb->setMaxSize(4);
		lb->setMinSize(1);
		lb->setPosition(Ogre::Vector3(170, 0, linePos));
		_songAnalyser->addObserver(lb);
		linePos+=7;
	}

	Ogre::SceneNode* particleShowcase1 = _sceneManager->getRootSceneNode()->createChildSceneNode();
	particleShowcase1->setPosition(190, 0, -20);
	_songAnalyser->addObserver( new ParticleBeat(_sceneManager->createParticleSystem("smoke1", "MySmokeRed"), particleShowcase1, 2, 0.1));

	Ogre::SceneNode* particleShowcase2 = _sceneManager->getRootSceneNode()->createChildSceneNode();
	particleShowcase2->setPosition(190, 0, -65);
	_songAnalyser->addObserver( new ParticleBeat(_sceneManager->createParticleSystem("smoke2", "MySmokeGreen"), particleShowcase2, 3, 0.1));

	Ogre::SceneNode* particleShowcase3 = _sceneManager->getRootSceneNode()->createChildSceneNode();
	particleShowcase3->setPosition(140, 0, -20);
	_songAnalyser->addObserver( new ParticleBeat(_sceneManager->createParticleSystem("smoke3", "MySmokeBlue"), particleShowcase3, 5, 0.1));

	Ogre::SceneNode* particleShowcase4 = _sceneManager->getRootSceneNode()->createChildSceneNode();
	particleShowcase4->setPosition(140, 0, -65);
	_songAnalyser->addObserver( new ParticleBeat(_sceneManager->createParticleSystem("smoke4", "MySmokeWhite"), particleShowcase4, 7, 0.1));

	Ogre::SceneNode* particleShowcase5 = _sceneManager->getRootSceneNode()->createChildSceneNode();
	particleShowcase5->setPosition(170, 0, -42.5);
	_songAnalyser->addObserver( new ParticleBeat(_sceneManager->createParticleSystem("smoke5", "MySmoke1"), particleShowcase5, 0, 0.1));

	//Light showcase
	Ogre::Entity* topSphere;
	Ogre::SceneNode* topSphereNode;
	topSphere = _sceneManager->createEntity("topSphere", "sphere.mesh");
	topSphereNode = _sceneManager->getRootSceneNode()->createChildSceneNode();
	topSphereNode->setPosition(-162.5,25,142.5);
	topSphereNode->setScale(0.6,0.01,0.6);
	topSphereNode->attachObject(topSphere);

	Ogre::Entity* sphere;
	Ogre::SceneNode* sphereNode;
	MyLight* spotlight;
	for(int i = 0; i < 9; i++){
		//Sphere
		sphere = _sceneManager->createEntity("WhiteCube" + std::to_string(i), "sphere.mesh");
		sphereNode = _sceneManager->getRootSceneNode()->createChildSceneNode();
		sphereNode->setPosition(-172.5, 0, 122.5 + (i*6));
		sphereNode->setScale(0.01,0.01,0.01);
		sphereNode->attachObject(sphere);
		//Light
		spotlight = new MyLight(_sceneManager->createLight("spotlight" + std::to_string(i)), i % 8, 1);
		spotlight->getLight()->setType( Ogre::Light::LT_SPOTLIGHT);
		/*if(i < 3){
			spotlight->getLight()->setDiffuseColour(1,0,0);
			spotlight->getLight()->setSpecularColour(1,0,0);
		} else if(i < 6){
			spotlight->getLight()->setDiffuseColour(0,1,0);
			spotlight->getLight()->setSpecularColour(0,1,0);
		} else {
			spotlight->getLight()->setDiffuseColour(0,0,1);
			spotlight->getLight()->setSpecularColour(0,0,1);
		}*/
		spotlight->getLight()->setDiffuseColour(1,1,1);
		spotlight->getLight()->setSpecularColour(1,1,1);
		spotlight->getLight()->setDirection(0, -1, 0);
		spotlight->getLight()->setPosition(Ogre::Vector3(-172.5, 20, 122.5 + (i*6)));
		spotlight->getLight()->setSpotlightRange(Ogre::Degree(10), Ogre::Degree(20));
		_songAnalyser->addObserver(spotlight);
	}
}

void MySceneManager::renderOneFrame()
{
	Ogre::WindowEventUtilities::messagePump();
	_keepRunning = _root->renderOneFrame();
	//_songAnalyser->update();
	_songAnalyser->notify();
}	

bool MySceneManager::keepRunning()
{
	return _keepRunning;	
}

void MySceneManager::makeRoom(){
	// Define a floor plane mesh
        Ogre::Plane p;
        p.normal = Ogre::Vector3::UNIT_Y;
        p.d = 200;

        Ogre::MeshManager::getSingleton().createPlane("FloorPlane",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
         p,2000,2000,1,1,true,1,5,5,Ogre::Vector3::UNIT_Z);

        p.normal = Ogre::Vector3::UNIT_Z;
        p.d = 200;
        Ogre::MeshManager::getSingleton().createPlane("FirstWallPlane", 
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			p,2000,2000,1,1,true,1,5,5,Ogre::Vector3::UNIT_Y);

		p.normal = Ogre::Vector3::NEGATIVE_UNIT_Z;
        p.d = 200;
		Ogre::MeshManager::getSingleton().createPlane("SecondWallPlane",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			p,2000,2000,1,1,true,1,5,5,Ogre::Vector3::UNIT_Y);

		p.normal = Ogre::Vector3::UNIT_X;
        p.d = 200;
		Ogre::MeshManager::getSingleton().createPlane("ThirdWallPlane",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			p,2000,2000,1,1,true,1,5,5,Ogre::Vector3::UNIT_Y);

		p.normal = Ogre::Vector3::NEGATIVE_UNIT_X;
        p.d = 200;
		Ogre::MeshManager::getSingleton().createPlane("FourthWallPlane",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		 p,2000,2000,1,1,true,1,5,5,Ogre::Vector3::UNIT_Y);

		p.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
        p.d = 200;
		Ogre::MeshManager::getSingleton().createPlane("Roof",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			p,2000,2000,1,1,true,1,5,5,Ogre::Vector3::UNIT_Z);

        // Create an entity (the floor)
       Ogre::Entity* ent = _sceneManager->createEntity("floor", "FloorPlane");
        ent->setMaterialName("Core/StatsBlockBorder/Up");

        _sceneManager->getRootSceneNode()->attachObject(ent);

        ent = _sceneManager->createEntity("firstWall", "FirstWallPlane");
        ent->setMaterialName("Material.003");

        _sceneManager->getRootSceneNode()->attachObject(ent);

		ent = _sceneManager->createEntity("secondWall", "SecondWallPlane");
        ent->setMaterialName("Material.003");

        _sceneManager->getRootSceneNode()->attachObject(ent);

		ent = _sceneManager->createEntity("thirdWall", "ThirdWallPlane");
        ent->setMaterialName("Material.003");

        _sceneManager->getRootSceneNode()->attachObject(ent);

		ent = _sceneManager->createEntity("fourthWall", "FourthWallPlane");
        ent->setMaterialName("Material.003");

        _sceneManager->getRootSceneNode()->attachObject(ent);

		ent = _sceneManager->createEntity("roofWall", "Roof");
        ent->setMaterialName("Material.003");

        _sceneManager->getRootSceneNode()->attachObject(ent);

		std::string boxMatName = "Material.002";
		double boxW = 0.75, boxL = 0.75, boxH = 0.05;
		double distToWall = 170.0;

		// Platforms for showcase 

		Ogre::Entity* box;
		Ogre::SceneNode * boxNode;
		unsigned int count = 0;
		for(int i = -1; i < 2; i=i+2){
				for(int j = -142.5; j <= 190; j = j+95){
					box = _sceneManager->createEntity("Box" + std::to_string(count++) , "Cube.mesh");
					boxNode = _sceneManager->getRootSceneNode()->createChildSceneNode();
					box->setMaterialName(boxMatName);
					boxNode->setPosition(i*distToWall,-5,j);
					boxNode->setScale(boxW, boxH, boxL);
					boxNode->attachObject(box);
				}
		}	
}