#include "stdafx.h"
#include "LineBeat.h"


LineBeat::LineBeat(Ogre::SceneManager* sceneManager,  
			   std::string name, 
			   std::string meshName,
			   int frequentcyRange) : Observer(frequentcyRange)
{
	_points.push_back(Ogre::Vector3(0.0f, 0.0f, 0.0f ));
	_points.push_back(Ogre::Vector3(0.0f, 10.0f, 0.0f ));
	_points.push_back(Ogre::Vector3(0.0f, 10.0f, 5.0f));
	_points.push_back(Ogre::Vector3(0.0f, 0.0f, 5.0f ));
	_points.push_back(Ogre::Vector3(0.0f, 10.0f, 0.0f ));
	_points.push_back(Ogre::Vector3(0.0f, 10.0f, 5.0f));
	

	_lines = new DynamicLines(Ogre::RenderOperation::OT_LINE_LIST);
	for (int i=0; i<_points.size(); i++) {
	  _lines->addPoint(_points[i]);
	}
	_lines->update();
	_node = sceneManager->getRootSceneNode()->createChildSceneNode();
	_node->attachObject(_lines);

	logFile.open("linebeat.log");
}



LineBeat::~LineBeat(void)
{
	logFile.close();
}

void LineBeat::update(float value)
{
	logFile << getFrequentcyRange() << " :\t " << value << "\n";
	Ogre::Vector3 currentScale = getScale();
	this->setThreashold(0.97*this->getThreashold()+0.03*value);
	if ( value > this->getThreashold() ) {
		if(_points[1].y < 30){
			_points[1].y += 3;
			_points[4].y += 3;
			_points[2].y += 3;
			_points[5].y += 3;
		}
			
		
	} else {
		if(_points[1].y > 10){
			_points[1].y -= 3;
			_points[4].y -= 3;
			_points[2].y -= 3;
			_points[5].y -= 3;
		}
		
	}
	
	for (int i=0; i<_points.size(); ++i) {
		_lines->setPoint(i,_points[i]);
	}
		
		
		
	_lines->update();
}

Ogre::SceneNode* LineBeat::getNode()
{
	return _node;
}

void LineBeat::setPosition(Ogre::Vector3 position)
{
	_node->setPosition(position);
}

Ogre::Vector3 LineBeat::getScale()
{
	return _node->getScale();
}

void LineBeat::setScale(Ogre::Vector3 scale)
{

}

void LineBeat::setMaxSize(double maxSize)
{
	
}

void LineBeat::setMinSize(double minSize)
{

}

void LineBeat::setScaling(Ogre::Vector3 scaling)
{
	
}