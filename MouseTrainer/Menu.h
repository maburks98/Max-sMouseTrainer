//// HEADER FILE FOR GAME MENU CLASS ////

#pragma once //Ensures the class is only included once when compiled

// Built ins
#include <iostream>

// Class header files
#include "FallingShapes.h"
#include "RandomCircles.h"
#include "PrecisionTargets.h"
#include "CpsTest.h"

// Libraries from Simple and Fast Multimedia Library (SFML) used to display media
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf; //SFML namespace (Simple Fast)

class Menu
{
private:

	// Menu variables
	RenderWindow* menuWindow;
	VideoMode videoMode;
	Event e;

	// Menu objects
	RectangleShape gameButton1;
	RectangleShape gameButton2;
	RectangleShape gameButton3;
	RectangleShape gameButton4;

	//Mouse positions
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	// Menu resources
	Music music;
	Font font;
	Texture titleScreenTexture;
	Texture bkgMenu;
	Sprite bkg;
	Sprite  titleScreen;

	// Menu text
	Text button1Text;
	Text button2Text;
	Text button3Text;
	Text button4Text;

	// Menu logic
	bool mouseHeld;

	// Private functions
	void initVariables();
	void initWindow();
	void initMenuButtons();
	void initFont();
	void initText();
	void initTexture();

public:

	/*
		Usage of Constructors and Destructors:

		Constructor
		- A constructor is a special function with a name that matches the class.
		- A constructor has no return not even a void.
		- The constructor is called whenever a new object is created.
		- The constructor allows the class to initialize varaiables

		Destructor
		- A destructor is a special function prefixed by a tilde (~) followed by the class name.
		- A destuctor has no return not even a void.
		- The destructor is called when an object is deleted or leaves the class scope.
		- The destructor destroys an object and deallocates dynamic memory.
		- Destructors are a preventative measure for data leaks and cleanup resources.
	*/
	Menu();  // Constructor
	virtual ~Menu(); // Destructor

	// Update game menu objects
	void updateObjects();

	// Render game menu objects 
	void renderObjects();

	// Render full game menu function
	int runMenu();
};

