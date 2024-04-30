//// HEADER FILE FOR CPSTEST GAME CLASS ////

#pragma once //Ensures the class is only included once when compiled

// Built ins
#include <iostream>
#include <iomanip>
#include <vector>

// Class header files
#include "Menu.h"

// Libraries from Simple and Fast Multimedia Library (SFML) used to display media
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf; //SFML namespace (Simple Fast)

class CpsTest
{
private:

	// CPS variables
	RenderWindow* cpsWindow;
	VideoMode videoMode;
	Event e;

	//Mouse positions
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	// CPS resources
	Music music;
	Font font;
	Clock clock;
	Time time;
	Texture settingsTexture;
	Sprite settingsBkg;
	Texture bkgTexture;
	Sprite bkg;
	SoundBuffer popBuffer;
	Sound pop;

	// CPS ui text
	Text uiText;
	Text settingsTitle;
	Text settingsSubTitle;
	Text easy;
	Text medium;
	Text hard;
	Text clickText;
	Text testOverText;
	Text testOverSubText;
	Text replay;
	Text menu;

	// Game logic
	bool initialClick;
	bool mouseHeld;
	bool timeUp;
	int clickCounter;
	float clickTimer;
	float cps;
	bool settingsOpen;

	// Game objects
	CircleShape circle;
	std::vector<CircleShape> flashingCircles;
	CircleShape flashingCircle;

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
	void initGameObjects();

public:
	// Constructor // Destructor //
	CpsTest();
	virtual ~CpsTest();

	// Update mouse positions
	void updateMouse();

	// Handle actions after the test
	void handleTestOver();

	// Handle a settings screen
	void handleSettings();

	// Create flashing center circles
	void spawnCircles();

	// Update flashing center circles
	void updateCircles();

	// Update game time
	void updateTime();

	// Update game objects
	void updateObjects();

	// Render game objects 
	void renderObjects();

	// CPS test game loop
	int playCpsTest();
};

