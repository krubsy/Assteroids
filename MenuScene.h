#pragma once
#include "cocos2d.h"

//Namespaces
using namespace cocos2d;

class MenuScene : public Scene 
{
public:
	//Engine Functions
	static Scene* createScene();
	void update(float deltaTime);

};
