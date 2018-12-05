#pragma once
//3rd Party Libraries
#include "cocos2d.h"
#include "Math/Vector.h"
#include <ctime>
//Namespaces
using namespace cocos2d;

class MenuScene : public cocos2d::Scene
{
public:
	//Engine Functions
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onExit();
	virtual void onEnter();
	void update(float deltaTime);
	CREATE_FUNC(MenuScene);
	void initMenu();
	void initListeners();
	void initMouseListener();
	void initKeyboardListener();
	void spawnRandomEntity();
	MyVector getRandomPointOnRect();
	bool getRandomBool();
	MyVector getRandomPointInWindow();
	std::vector<Sprite*> entities;
	void killOffscreenEntities();
private:
	//Engine
	Director* director;
	EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;
	MyVector mousePosition;
	Sprite* spr_Background;
	Label* titleLabel;
	clock_t timeOfLastSpawn;
	int rectWidth;
	int rectHeight;
	int totalRect;
	Vec2 winCenter;
	Menu* menu;
};