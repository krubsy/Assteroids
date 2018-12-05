#pragma once

//Libraries
#include "cocos2d.h"

#include "Asteroids/Ship.h"
#include "Asteroids/Asteroid.h"
#include "Asteroids/Projectile.h"
#include "Asteroids/Enemy.h"

//Namespaces
using namespace cocos2d;

class GameplayScene : public Scene
{
public:
	//Engine Functions
	CREATE_FUNC(GameplayScene);
	static Scene* createScene();
	virtual void onExit();
	virtual void onEnter();
	//Init Functions
	virtual bool init();
	void initSprites();
	void initAsteroids();
	void initProjectiles();
	void initEnemies();
	void initShip();
	void initListeners();
	void initMouseListener();
	void initKeyboardListener();
	void initContactListener();
	void initPauseMenu();

	//Main Update Loop
	void update(float deltaTime);

	

private:
	//Engine
	Director* director;

	//Event Listeners
	EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;
	bool mouseDown;
	vec2 mousePosition;

	//Background Sprites
	Sprite* spr_Background;
	Sprite* spr_Background2;

	Ship* ship;

	//Vectors of asteroids, projectiles, and enemies on the screen.
	std::vector<Asteroid> asteroids;
	std::vector<Projectile> projectiles;
	std::vector<Enemy> enemies;

	//Sprites

	//Camera Target
	Sprite* cameraTarget;
	static Scene* sceneHandle;
	float groundHeight;

	bool drawDebug = false;

	Menu* pauseMenu;
	bool menuDispayed = false;

};
