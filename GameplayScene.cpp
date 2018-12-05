#include "GameplayScene.h"
#include "MenuScene.h"
#include <iostream>

//--- Engine Functions ---//
using namespace experimental;
Scene* GameplayScene::createScene()
{
	// 'scene' is an autorelease object
	Scene* scene = Scene::createWithPhysics();
	GameplayScene* layer = GameplayScene::create();

	scene->addChild(layer);

	//sceneHandle = scene;

	Vec2 winSize = Director::getInstance()->getWinSizeInPixels();

	return scene;
}

void GameplayScene::onExit()
{
	//Clearing all our vectors to make sure we're not leaking memory when we transition scenes!
	asteroids.clear();
	projectiles.clear();
	enemies.clear();
	Scene::onExit();

}

void GameplayScene::onEnter()
{
	Scene::onEnter();
}

//--- Init functions ---//

bool GameplayScene::init()
{
	//Ensure the parent init function was called first. If it wasn't, exit this one
	if (!Scene::init())
		return false;

	//Get the director from cocos so we can use it when needed
	director = Director::getInstance();

	//Init the event handlers
	initListeners();
	
	//Init the pause menu
	initPauseMenu();
	
	//Init the sprites
	initSprites();
	
	//Init the projectiles
	//initProjectiles();
	
	//Init the enemies
	initEnemies();
	
	//Init the asteroids
	initAsteroids();

	//Allow for the update() function to be called by cocos
	this->scheduleUpdate();

	//Let cocos know that the init function was successful
	return true;
}

void GameplayScene::initSprites()
{
	//Init the background sprites
	spr_Background = Sprite::create("images/Background.jpg"); //Load the handle
	spr_Background->setPosition(director->getWinSizeInPixels().width / 2.0f, director->getWinSizeInPixels().height / 2.0f); //Center the image in the window
	spr_Background->setAnchorPoint(Vec2(0.5f, 0.5f)); //Ensure the middle of the background is the anchor point

	spr_Background2 = Sprite::create("images/Background.jpg");
	spr_Background2->setPosition(director->getWinSizeInPixels().width * 1.5f, director->getWinSizeInPixels().height / 2.0f);
	spr_Background2->setAnchorPoint(Vec2(0.5f, 0.5f));

	//Add the physics body to the ground
	//PhysicsBody* body_Ground = PhysicsBody::createBox(Size(director->getWinSizeInPixels().width * 5, 15.0f)); //Create a box collider for the 
	//body_Ground->setDynamic(false); //We don't want the box collider to move around, we just want other stuff to hit
	//body_Ground->setPositionOffset(Vec2(0.0f, -215.0f)); //Move the collider to where the grass portion of the background sprite is
	//spr_Background->setPhysicsBody(body_Ground); //Attach the physics body to the background sprite
	this->addChild(spr_Background, -100); //Add the sprite, pushed way to the back
	this->addChild(spr_Background2, -100);

	ship = new Ship(MyVector(250.0f, 250.0f), "images/vector.jpg");
	ship->getBody()->setDynamic(true);
	this->addChild(ship->getSprite());

	//Init the camera target
	cameraTarget = Sprite::create();
	cameraTarget->setPositionX(ship->getSprite()->getPositionX());
	this->addChild(cameraTarget);
}

void GameplayScene::initListeners()
{
	//Init the mouse listener
	initMouseListener();

	//Init the keyboard listener
	initKeyboardListener();

	//Init the contact listener
	initContactListener();
}

void GameplayScene::initMouseListener()
{
	//Init the mouse listener
	mouseListener = EventListenerMouse::create();

	//On Mouse Down
	mouseListener->onMouseDown = CC_CALLBACK_1(GameplayScene::mouseDownCallback, this);

	//On Mouse Up
	mouseListener->onMouseUp = CC_CALLBACK_1(GameplayScene::mouseUpCallback, this);

	//On Mouse Move
	mouseListener->onMouseMove = CC_CALLBACK_1(GameplayScene::mouseMoveCallback, this);

	//On Mouse Scroll
	mouseListener->onMouseScroll = CC_CALLBACK_1(GameplayScene::mouseScrollCallback, this);

	//Add the mouse listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void GameplayScene::initKeyboardListener()
{
	//Create the keyboard listener
	keyboardListener = EventListenerKeyboard::create();

	//Setting up callbacks
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameplayScene::keyDownCallback, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameplayScene::keyUpCallback, this);

	//Add the keyboard listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void GameplayScene::initContactListener()
{
	//Create the contact listener
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	//Assign callbacks
	contactListener->onContactBegin = CC_CALLBACK_1(GameplayScene::onContactBeginCallback, this);

	//Add the listener to the event dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameplayScene::initAsteroids()
{

	//Creating the wood structure our pigs are going to sit on
	//First Layer
	//Supports
	createAsteroid(MyVector(667.5, 150), MyVector(20, 100));

}

void GameplayScene::initEnemies()
{
	//Creating the pigs
	//createPig(Vec2(712.5, groundHeight + 20));
	//createPig(Vec2(812.5, groundHeight + 20));
	//createPig(Vec2(762.5, groundHeight + 130));
}

void GameplayScene::initPauseMenu()
{
	//Creating our pause menu!
	//A menu is built of menu items
	//A menu item is built out of a label or a sprite

	Label* pausedLabel = Label::create("PAUSED", "fonts/arial.ttf", 50.0f, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	pausedLabel->enableShadow();
	MenuItem* pausedItem = MenuItemLabel::create(pausedLabel, NULL);
	pausedItem->setPosition(0, 50);

	Label* resumeLabel = Label::create("Resume", "fonts/arial.ttf", 50.0f, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::BOTTOM);
	resumeLabel->enableShadow();
	MenuItem* resumeItem = MenuItemLabel::create(resumeLabel, CC_CALLBACK_0(GameplayScene::toggleMenu, this));

	resumeItem->setPosition(0, 0);

	Label* quitLabel = Label::create("Quit", "fonts/arial.ttf", 50.0f, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::BOTTOM);
	quitLabel->enableShadow();
	MenuItem* quitItem = MenuItemLabel::create(quitLabel, CC_CALLBACK_0(GameplayScene::quitToMenu, this));
	quitItem->setPosition(0, -50);

	//Creating the actual pause menu, note the null on the end! this is imporant when creating cocos objects that take a list of things, not putting NULL at the end of the list will crash!
	pauseMenu = Menu::create(pausedItem, resumeItem, quitItem, NULL);

	//Adding the pause menu to the world and then making it not visible, we don't want to start the game paused!
	this->addChild(pauseMenu, 99);
	pauseMenu->setVisible(false);
}


//--- Main update loop ---//

void GameplayScene::update(float deltaTime)
{
	
	if (input.pressed[EventKeyboard::KeyCode::KEY_W]) {
		vec4 force = ship->rotation * vec4(0.0f, 2.0f, 0.0f, 0.0f);
		ship->addForce(MyVector(0.0f, 10.0f));
	}
	ship->update(deltaTime);

	//If the active bird is on the slingshot, it shouldn't be affected by gravity & other physics forces
	//if (activeBird->getState() == onSlingshot)
	//{
	//	activeBird->getBody()->setDynamic(false);
	//}
	////If the active bird is off the slingshot, it should be affected by physics
	//else if (activeBird->getState() == airborne)
	//{
	//	activeBird->getBody()->setDynamic(true);
	//	//Moving the camera target to follow the current active bird
	//	cameraTarget->setPositionX(-activeBird->getSprite()->getPositionX() + (director->getWinSizeInPixels().width / 2));
	//}


	//Getting rid of birds & pigs if they should die
	//updateProjectiles();
	//updateEnemies();
}

/*
//void GameplayScene::spawnBird()
//{
//	//Creating a new bird, and setting it as the active bird
//	activeBird = new Bird(slingshotPosition);
//
//	//Pushing this new bird to our vector of birds
//	birds.push_back(activeBird);
//
//	//Adding the new bird to the world
//	this->addChild(activeBird->getSprite(), 1);
//}

void GameplayScene::updateProjectiles()
{
	//For every projectle in our vector of projectile
	for (int i = 0; i < projectiles.size(); i++)
	{
		//Get the velocity of the projectile
		//float projVel = projectiles[i]->getBody()->getVelocity().getLength();
		
		//If the projectile is moving slowly and it's not on the slingshot
		//if (projVel < 20.0f && [i]->getState() != onSlingshot)
		//{
		//	//Spawn a new bird if the slow bird is the active bird
		//	if (birds[i] == activeBird) {
		//		spawnBird();
		//	}
		//	//If the bird has pretty much stopped
		//	if (birdVel < 5.0f)
		//	{
		//		//Kill the bird in 3 seconds
		//		birds[i]->kill(3.0f);
		//
		//
		//
		//		//Erase it from the vector, and decrement the iterator
		//		birds.erase(birds.begin() + i);
		//		i--;
		//	}
		//}
	}
}

void GameplayScene::updateEnemies()
{
	//For all the pigs in our vector
	for (int i = 0; i < enemies.size(); i++)
	{
		//If the pig should die
		//if (enemies[i]->shouldDie())
		//{
		//	//Create a sweet particle system to show that the pig died
		//	CCParticleSystemQuad* emitter;
		//	emitter = CCParticleExplosion::createWithTotalParticles(10);
		//	emitter->setGravity(Vec2(0, 98.1));
		//	emitter->setStartColor(Color4F::WHITE);
		//	emitter->setStartColorVar(Color4F(0, 0, 0, 0));
		//	emitter->setEndColor(Color4F(0, 0, 0, 0));
		//	emitter->setEndColorVar(Color4F(0, 0, 0, 0));
		//	emitter->setPosition(pigs[i]->getPosition());
		//	emitter->runAction(Sequence::create(DelayTime::create(5.0f), RemoveSelf::create(), NULL));
		//	this->addChild(emitter);
		//
		//	//Play the poof sound effect
		//
		//	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/poof.wav");
		//	experimental::AudioEngine::play2d("audio/poof.mp3");
		//
		//	//Erase the pig from the vector, and decrement the iterator
		//	pigs.erase(pigs.begin() + i);
		//	i--;
		//}
	}
}
*/
//--- Callbacks ---//

void GameplayScene::mouseDownCallback(Event* event)
{
	//Cast the event as a mouse event
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

	//Get the position of the mouse button press
	auto mouseClickPosition = mouseEvent->getLocationInView();
	mouseClickPosition.y += 540;

	//Get the mouse button from the event handler
	auto mouseButton = mouseEvent->getMouseButton();

	//Perform different logic depending on which button was pressed
	if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
		std::cout << "Left Mouse Button Pressed!" << std::endl;
	else if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
		std::cout << "Right Mouse Button Pressed!" << std::endl;

	std::cout << "Attempting to grab bird!" << std::endl;
	//std::cout << "Distance was: " << (mouseClickPosition - slingshotPosition).length() << std::endl;
	//if ((mouseClickPosition - slingshotPosition).length() < 50.0f)
	//{
	//	//Bird grabbed!
	//	birdHeld = true;
	//	std::cout << "Bird Grabbed!!!" << std::endl;
	//}

	mouseDown = true;
}

void GameplayScene::mouseUpCallback(Event* event)
{
	//Cast the event as a mouse event
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

	//Get the position of the mouse button press
	auto mouseUpPosition = mouseEvent->getLocation();

	//Init the message to be output in the message box
	std::stringstream message;

	//Get the mouse button from the event handler
	auto mouseButton = mouseEvent->getMouseButton();

	//Perform different logic depending on which button was released
	if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
		std::cout << "Left Mouse Button Released!" << std::endl;
	else if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
		std::cout << "Right Mouse Button Released!" << std::endl;
	mouseDown = false;
	//if (birdHeld)
	//{
	//	activeBird->getSprite()->getPhysicsBody()->setDynamic(true);
	//	activeBird->getSprite()->getPhysicsBody()->setVelocity((slingshotPosition - activeBird->getSprite()->getPosition()) * 5.0f);
	//	activeBird->setState(birdState::airborne);
	//	//sceneHandle->runAction(MoveTo::create(1.0f, Vec2(150, 0)));
	//	birdHeld = false;
	//}
}

void GameplayScene::mouseMoveCallback(Event* event)
{
	//Cast the event as a mouse event
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

	//Get the position of the mouse from the event handler
	auto mouseEventPos = mouseEvent->getLocationInView();

	//Store the position into the mouse struct
	this->mouse.position = MyVector(mouseEventPos.x, 540 + mouseEventPos.y);

	//Output the position to the console
	//std::cout << this->mouse.position.x << ", " << this->mouse.position.y << std::endl;

	mousePosition = mouse.position;
}

void GameplayScene::mouseScrollCallback(Event* event)
{

}

void GameplayScene::keyDownCallback(EventKeyboard::KeyCode keyCode, Event* event)
{
	input.pressed[(int)keyCode] = true;

	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		std::cout << "Space Bar Was Pressed!" << std::endl;
		for (int i = 0; i < enemies.size(); i++)
		{
			//enemies[i]->damage(50);
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		ship->setTheta(ship->getTheta() - 10);
	}



}

void GameplayScene::keyUpCallback(EventKeyboard::KeyCode keyCode, Event* event)
{
	input.pressed[(int)keyCode] = false;

	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		std::cout << "Space Bar Was Released!" << std::endl;
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_R)
	{
		//std::cout << "Resetting Bird!" << std::endl;
		//if (activeBird->getState() != onSlingshot) {
		//	spawnBird();
		//}
	}

	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {}
		//toggleDebugDraw();

	else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		//exit(0);
		toggleMenu();
}

bool GameplayScene::onContactBeginCallback(PhysicsContact& contact)
{
	//Getting the two nodes from the collision
	//Nodes contain position, physics bodies, etc.
	//Superclass of scene/layer
	//In this context, they represent the information we can get about colliding bodies from the collision itself
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();

	//We get the tags from the physics bodies, which we set in the object's constructor. Pig, bird, obstacle. Lets us know what the object type is, so we can respond to specific collisions
	int tagA = contact.getShapeA()->getBody()->getTag();
	int tagB = contact.getShapeB()->getBody()->getTag();

	//We make sure both nodes exist, just to be safe.
	//if (nodeA && nodeB)
	//{
	//	//A pig colliding with a pig, a bird colliding with a bird, an obstacle colliding with an obstacle should just collide, and nothing special should happen
	//	if (tagA == tagB)
	//		return true;	//Returning true lets cocos know that we want these obstacles to collide with eachother, if you return false to a collision the objects will phase through eachother as if they never collided
	//
	//	//If a pig collides with an obstacle, or an obstacle collides with a pig, we just want them to collide and nothing else.
	//	if ((tagA == obstacle && tagB == pig) || (tagA == pig && tagB == obstacle))
	//	{
	//		return true;
	//	}
	//
	//	if (tagA == tags::bird)
	//	{
	//		if (tagB == tags::pig)
	//		{
	//			//If a bird hits a pig, we want to damage the pig & collide
	//			damagePig(nodeB->getPosition(), nodeA->getPosition());
	//			return true;
	//		}
	//		else if (tagB == tags::obstacle)
	//		{
	//			//Destroy the obstacle if it's going fast enough
	//			damageObstacle(nodeB->getPosition(), nodeA->getPosition());
	//			return true;
	//		}
	//	}
	//	else if (tagB == tags::bird)
	//	{
	//		if (tagA == tags::pig)
	//		{
	//			//If a bird hits a pig, we want to damage the pig & collide
	//			damagePig(nodeA->getPosition(), nodeB->getPosition());
	//			return true;
	//		}
	//		else if (tagA == tags::obstacle)
	//		{
	//			//Destroy the obstacle if it's going fast enough
	//			damageObstacle(nodeA->getPosition(), nodeB->getPosition());
	//			return true;
	//		}
	//	}
	//}
	return true;
}

//--- Level creation functions ---//

void GameplayScene::createAsteroid(MyVector position, MyVector size)
{
	//Create the obstacle with the given parameters
	Asteroid* newAsteroid = new Asteroid(position, size);
	//Add the obstacle to the world, on the same layer as the birds & pigs
	//this->addChild(newObstacle->getSprite(), 1);
	//Put it in our vector of obstacles
	//obstacles.push_back(newObstacle);
}
/*
void GameplayScene::createEnemy(MyVector position)
{
	////Create the new pig
	//Pig* newPig = new Pig(position);
	//Add the new pig to the world
	//this->addChild(newPig->getSprite(), 1);
	//Add the pig to our vector of pigs
	//pigs.push_back(newPig);
}


//--- Utility functions ---//

void GameplayScene::damageEnemy(MyVector position, int amount)
{
	//From a collision we can't get the game objects that collided, since the games' physics don't know or care about what a pig, or a bird is!
	//The physics engine's job is just to make things move & collide, it doesn't know that we're playing Upset Avians(tm)
	//Because of this, we're just going to look for the pig based on its position

	//If the amount of damage we need to do to the pig is zero, we're done here!
	//if (amount == 0)
	//	return;
	//
	////For all pigs in the vector
	//for (int i = 0; i < enemies.size(); i++)
	//{
	//	//If the pig we found is *really* close to the given position
	//	if (abs(enemies[i]->getPosition().length() - position.length()) < 2.5f)
	//	{
	//		//Set its sprite to the damaged texture
	//		pigs[i]->getSprite()->setTexture("UA/Enemies/spr_Pig_Hurt.png");
	//		//Damage the pig by the given amount
	//		pigs[i]->damage(amount);
	//		//we're done here, return to what we were doing before!
	//		return;
	//	}
	//}
	////if the code reaches this point, we looped through all the pigs and couldn't find one that matched the position, so we print an error.
	//std::cout << "Couldn't find pig to damage!" << std::endl;
}

void GameplayScene::damageAsteroid(Vec2 obstaclePosition, Vec2 birdPosition)
{
	//float birdVelocity = 0;
	//
	////For all the birds in our vector
	//for (int i = 0; i < birds.size(); i++)
	//{
	//	//if the bird we found is *really* close to the given position
	//	if (abs(birds[i]->getPosition().length() - birdPosition.length()) < 2.5f)
	//	{
	//		//get that bird's velocity, its the one we want to use to damage the obstacle!
	//		birdVelocity = birds[i]->getBody()->getVelocity().length();
	//	}
	//}
	//
	////for all the obstacles in our vector
	//for (int i = 0; i < obstacles.size(); i++)
	//{
	//	//if the obstacle we found is *really* close to the given position
	//	if (abs(obstacles[i]->getPosition().length() - obstaclePosition.length()) < 2.5f)
	//	{
	//		//if the bird's velocity is > 400		(that's a fast bird!)
	//		if (birdVelocity > 400)
	//		{
	//			//get rid of the obstacle, the bird smashed it!
	//			obstacles[i]->getSprite()->runAction(RemoveSelf::create());
	//			obstacles.erase(obstacles.begin() + i);
	//			i--;
	//
	//			//Create a particle system of wood fragments where the obstacle broke
	//			CCParticleSystemQuad* emitter;
	//			Color4F brown = Color4F(0.55f, 0.27f, 0.07f, 1.0f);
	//			emitter = CCParticleExplosion::createWithTotalParticles(10);
	//			emitter->setGravity(Vec2(0, -98.1));
	//			emitter->setStartColor(brown);
	//			emitter->setStartColorVar(Color4F(0, 0, 0, 0));
	//			emitter->setEndColor(Color4F(0, 0, 0, 0));
	//			emitter->setEndColorVar(Color4F(0, 0, 0, 0));
	//			emitter->setPosition(obstaclePosition);
	//			emitter->runAction(Sequence::create(DelayTime::create(5.0f), RemoveSelf::create(), NULL));
	//			this->addChild(emitter);
	//		}
	//		return;
	//	}
	//}
}

void GameplayScene::toggleDebugDraw()
{
	//toggles the debug draw
	drawDebug = !drawDebug;

	sceneHandle->getPhysicsWorld()->setDebugDrawMask(drawDebug == true ? PhysicsWorld::DEBUGDRAW_ALL : PhysicsWorld::DEBUGDRAW_NONE);
}
*/
void GameplayScene::toggleMenu()
{
	//Toggles the pause menu, and the pause!

	//If the game isn't already paused
	if (menuDisplayed == false)
	{
		//We're now displaying the pause menu!
		menuDisplayed = true;
		//Make the menu visible
		pauseMenu->setVisible(true);
		//Set the world's speed to 0, pausing the world (hmmm, what kind of cool effects could you do by setting the world speed?)
		//sceneHandle->getPhysicsWorld()->setSpeed(0.0f);
	}
	else
	{
		//We were already displaying the menu, so let's hide it!
		menuDisplayed = false;
		//make the menu not visible
		pauseMenu->setVisible(false);
		//set the world's speed back to normal
		//sceneHandle->getPhysicsWorld()->setSpeed(1.0f);
	}
}

void GameplayScene::quitToMenu()
{
	//Quits to menu!
	//First we make a new scene
	Scene* menuScene = MenuScene::createScene();
	//and then we transition into that scene using a sweet effect
	director->replaceScene(TransitionPageTurn::create(2.0f, menuScene, true));
}


//Scene* GameplayScene::sceneHandle = nullptr;