#include "FrameListener.h"


FrameListener::FrameListener(void)
{
}


FrameListener::~FrameListener(void)
{
	_InputManager->destroyInputObject(_Keyboard);
	_InputManager->destroyInputObject(_Mouse);
	OIS::InputManager::destroyInputSystem(_InputManager);
}

FrameListener::FrameListener(Ogre::RenderWindow* win, Ogre::Camera* cam, Ogre::Viewport* viewport, Ogre::SceneNode* node, Ogre::Entity* ent)
{
	OIS::ParamList parameters;
	unsigned int windowHandle = 0;
	std::ostringstream windowHandleString;

	win->getCustomAttribute("WINDOW", &windowHandle);
	windowHandleString << windowHandle;

	parameters.insert(std::make_pair("WINDOW", windowHandleString.str()));
	_InputManager = OIS::InputManager::createInputSystem(parameters);

	_Keyboard = static_cast<OIS::Keyboard*>(_InputManager->createInputObject( OIS::OISKeyboard, false ));

	_Cam = cam;
	_movementSpeed = 50.0f;
	_WalkingSpeed = 50.0f;
	setNode(node);

	_Mouse = static_cast<OIS::Mouse*>(_InputManager->createInputObject( OIS::OISMouse, false ));
}

bool FrameListener::frameStarted(const Ogre::FrameEvent& evt)
{
	_Keyboard->capture();
	if( _Keyboard->isKeyDown( OIS::KC_ESCAPE ) ){ 
		return false;
	}
		
	// Move the camera with W S A D
	Ogre::Vector3 translate(0, 0, 0);
	if ( _Keyboard->isKeyDown(OIS::KC_W) ) {
		translate += Ogre::Vector3(0, 0, -1);
	}
	if ( _Keyboard->isKeyDown(OIS::KC_S) ) {
		translate += Ogre::Vector3(0, 0, 1);
	}
	if ( _Keyboard->isKeyDown(OIS::KC_A) ) {
		translate += Ogre::Vector3(-1, 0, 0);
	}
	if ( _Keyboard->isKeyDown(OIS::KC_D) ) {
		translate += Ogre::Vector3(1, 0, 0);
	}
	_Cam->moveRelative(translate * evt.timeSinceLastFrame * _movementSpeed);

	// Control the camera with the mouse
	_Mouse->capture();
	float rotX = _Mouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1;
	float rotY = _Mouse->getMouseState().Y.rel * evt.timeSinceLastFrame* -1;
	_Cam->yaw( Ogre::Radian(rotX) );
	_Cam->pitch( Ogre::Radian(rotY) );

	Ogre::Vector3 SinbandTranslate(0, 0, 0);
	float _rotation = 0.0f;

	// Move sinbad with arrow keys
	bool walked = false;
	if ( _Keyboard->isKeyDown(OIS::KC_UP) ) {
		SinbandTranslate += Ogre::Vector3(0, 0, -1);
		_rotation = 3.14f;
		walked = true;
	}
	if ( _Keyboard->isKeyDown(OIS::KC_DOWN) ){
		SinbandTranslate += Ogre::Vector3(0, 0, 1);
		_rotation = 0.0f;
		walked = true;
	}
	if ( _Keyboard->isKeyDown(OIS::KC_LEFT) ){
		SinbandTranslate += Ogre::Vector3(-1, 0, 0);
		_rotation = -1.57f;
		walked = true;
	}
	if ( _Keyboard->isKeyDown(OIS::KC_RIGHT) ){
		SinbandTranslate += Ogre::Vector3(1, 0, 0);
		_rotation = +1.57f;
		walked = true;
	}

	if ( walked ) {
		_aniState->setEnabled(true);
		_aniStateTop->setEnabled(true);
		if ( _aniState->hasEnded() ) {
			_aniState->setTimePosition(0.0f);
		}
		if ( _aniStateTop->hasEnded() ) {
			_aniStateTop->setTimePosition(0.0f);
		}
	} else {
		_aniState->setTimePosition(0.0f);
		_aniState->setEnabled(false);
		_aniStateTop->setTimePosition(0.0f);
		_aniStateTop->setEnabled(false);
	}	

	_aniState->addTime(evt.timeSinceLastFrame);
	_aniStateTop->addTime(evt.timeSinceLastFrame);

	_node->translate(SinbandTranslate * evt.timeSinceLastFrame * _WalkingSpeed);
	_node->resetOrientation();
	_node->yaw( Ogre::Radian(_rotation) );
	return true;
}

void FrameListener::setNode(Ogre::SceneNode* node)
{
	_node = node;
}

void FrameListener::setAniState(Ogre::AnimationState* state)
{
	_aniState = state;
	_aniState->setLoop(false);
}

void FrameListener::setAniStateTop(Ogre::AnimationState* state)
{
	_aniStateTop = state;
	_aniStateTop->setLoop(false);
}