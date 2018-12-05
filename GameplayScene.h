#pragma once

//Libraries
#include "cocos2d.h"

#include "Asteroids/Ship.h"
#include "Asteroids/Asteroid.h"
#include "Asteroids/Projectile.h"
#include "Asteroids/Enemy.h"

//Namespaces
using namespace cocos2d;

struct Mouse
{
	MyVector position;
};

struct Input
{
	bool pressed[256];
};

class GameplayScene : public Scene
{
public:
	//Engine Functions
	CREATE_FUNC(GameplayScene);
	static Scene* createScene();
	virtual void onExit();
	virtual void onEnter();

	////Init Functions
	virtual bool init();
	void initSprites();
	void initAsteroids();
	//void initProjectiles();
	void initEnemies();
	//void initShip();
	void initListeners();
	void initMouseListener();
	void initKeyboardListener();
	void initContactListener();
	void initPauseMenu();
	
	////Main Update Loop
	void update(float deltaTime);
	//void updateProjectiles();
	//void updateEnemies();
	//void updateAsteroids();
	
	//Callbacks
	void mouseDownCallback(Event* event);
	void mouseUpCallback(Event* event);
	void mouseMoveCallback(Event* event);
	void mouseScrollCallback(Event* event);
	void keyDownCallback(EventKeyboard::KeyCode keycode, Event* event);
	void keyUpCallback(EventKeyboard::KeyCode keycode, Event* event);
	bool onContactBeginCallback(PhysicsContact& contact);
	
	////Level creation funcitons
	void createAsteroid(MyVector position, MyVector size);
	//void createEnemy(MyVector position);
	//
	//
	////utility functions
	//void damageEnemy(MyVector position, int amount);
	//void damageAsteroid(Vec2 obstaclePosition, Vec2 birdPosition);
	//void toggleDebugDraw();
	void toggleMenu();
	void quitToMenu();
	//
	//
private:
	////Engine
	Director* director;
	
	//Event Listeners
	EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;
	bool mouseDown;
	MyVector mousePosition;
	
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
	//static Scene* sceneHandle;
	//float groundHeight;
	
	//bool drawDebug = false;
	
	Menu* pauseMenu;
	bool menuDisplayed = false;
	

	//Mouse Information
	Mouse mouse;
	Input input;
};
