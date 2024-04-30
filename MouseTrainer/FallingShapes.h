//// HEADER FILE FOR FALLING SHAPES GAME CLASS ////

#pragma once //Ensures the class is only included once when compiled

// Built ins
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

// Class header files
#include "Menu.h"

//Libraries from Simple and Fast Multimedia Library (SFML) used to display media
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf; //SFML namespace (Simple Fast)

class FallingShapes
{
private:

	// Falling shapes variables
	RenderWindow* fallingShapesWindow;
	VideoMode videoMode;
	Event e;

	//Mouse positions
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	// Falling shapes resources
	Font font;
	Texture settingsTexture;
	Sprite settingsBkg;
	Texture bkgTexture;
	Sprite bkg;
	SoundBuffer popBuffer;
	Sound pop;
	Music music;

	// Falling shapes ui text
	Text uiText;
	Text settingsTitle;
	Text settingsSubTitle;
	Text easy;
	Text medium;
	Text hard;
	Text gameOverText;
	Text gameOverSubText;
	Text gameOverSubText1;
	Text replay;
	Text menu;

	// Game logic
	bool mouseHeld;
	bool settingsOpen;
	unsigned points;
	int health;
	float shapeSpawnTimer;
	float shapeSpawnTimerMax;
	float shapeSpeed;
	int maxShapes;
	float clickCounter;
	float successfulClickCounter;
	float clickAccuracy;
	float pointMultiplier;

	// Game objects
	std::vector<sf::CircleShape> shapes;
	sf::CircleShape shape;

	RectangleShape easyButton;
	RectangleShape mediumButton;
	RectangleShape hardButton;
	RectangleShape menuButton;
	RectangleShape replayButton;

	// Private functions
	void initVariables();
	void initWindow();
	void initFiles();
	void initText();
	void initShapes();
	void initMenuButtons();
	void initTexture();

public:
	// Constructor // Destructor //
	FallingShapes();
	virtual ~FallingShapes();

	// Handle shape choices and spawn location
	void spawnShapes();

	// Update mouse positions
	void updateMouse();

	// Handle a game over screen
	void handleGameOver();

	// Handle a settings screen
	void handleSettings();

	// Handle shape movement and mouse collision
	void updateShapes();

	// Update game objects
	void updateObjects();

	// Render game objects 
	void renderObjects();

	// Falling shapes game loop
	int playFallingShapes();
};

