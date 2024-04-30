//// HEADER FILE FOR RANDOM CIRCLES GAME CLASS ////

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

class RandomCircles
{
private:

	// Falling shapes variables
	RenderWindow* randCirclesWindow;
	VideoMode videoMode;
	Event e;

	//Mouse positions
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	// Random circles resources
	Music music;
	Font font;

	Texture settingsTexture;
	Sprite settingsBkg;

	Texture redTarget;
	Texture purpleTarget;
	Texture blueTarget;
	Texture greenTarget;
	Texture yellowTarget;
	Texture bkgTexture;

	Sprite bkg;

	SoundBuffer popBuffer;
	Sound pop;

	Clock clock;
	Time time;

	// Random circles ui text
	Text uiText;
	Text settingsTitle;
	Text settingsSubTitle;
	Text easy;
	Text medium;
	Text hard;
	Text timerText;
	Text gameOverText;
	Text gameOverSubText;
	Text gameOverSubText1;
	Text replay;
	Text menu;

	// Game logic
	bool settingsOpen;
	bool mouseHeld;
	bool initialClick;
	float clickCounter;
	float successfulClickCounter;
	float clickAccuracy;

	bool timeUp;
	float clickTimer;

	unsigned points;

	float circleSpawnTimer;
	float circleSpawnTimerMax;
	int maxCircles;
	float radius;

	// Game objects
	std::vector<sf::CircleShape> circles;
	sf::CircleShape circle;

	RectangleShape easyButton;
	RectangleShape mediumButton;
	RectangleShape hardButton;
	RectangleShape menuButton;
	RectangleShape replayButton;

	// Private functions
	void initVariables();
	void initWindow();
	void initResources();
	void initText();
	void initCircles();
	void initMenuButtons();
	void initTextures();

public:
	// Constructor // Destructor //
	RandomCircles();
	virtual ~RandomCircles();

	// Handle cricle spawn locations
	void spawnCircles();

	// Update mouse positions
	void updateMouse();

	// Handle a game over screen
	void handleGameOver();

	// Handle a settings screen
	void handleSettings();

	// Handle circle and mouse collision
	void updateCircles();

	// Get time passed
	void updateTime();

	// Update game objects
	void updateObjects();

	// Render game objects 
	void renderObjects();

	// Random circle game loop
	int playRandomCircles();
};



