 //// IMPLEMENTATION FILE FOR FALLING SHAPES GAME CLASS ////

#include "FallingShapes.h"

// Private functions
void FallingShapes::initVariables()
{
	// Set fallingShapesWindow pointer to null
	fallingShapesWindow = nullptr;

	// Game logic
	mouseHeld = true;
	settingsOpen = true;
	points = 0;
	shapeSpawnTimerMax = 10.f;
	shapeSpawnTimer = shapeSpawnTimerMax;
	health = 10;
	shapeSpeed = 3.f;
	maxShapes = 5;
	clickCounter = 0;
	successfulClickCounter = 0.f;
	clickAccuracy = 0.f;
	pointMultiplier = 1.f;
}

void FallingShapes::initWindow()
{
	// Initialize variables for window dimensions
	videoMode.height = 800;
	videoMode.width = 800;

	// Assign SFML RenderWindow to fallingShapesWindow pointer
	fallingShapesWindow = new RenderWindow(videoMode, "Falling Shapes Game!", Style::Titlebar | Style::Close);
	fallingShapesWindow->setFramerateLimit(60); // Set FPS to 60
}

void FallingShapes::initFiles()
{
	// Assign a font file to "font"
	if (!font.loadFromFile("Fonts/calibri.ttf"))
	{
		std::cerr << "ERROR::GAME::INITFILES::Failed to load font!" << "\n";
		// Output an error if font does not load
	}

	if (!popBuffer.loadFromFile("Audio/pop.flac"))
	{
		std::cerr << "ERROR::GAME::INITFILES::Failed to load audio!" << "\n";
		// Output an error if audio does not load
	}

	pop.setBuffer(popBuffer);

	if (!music.openFromFile("Audio/gamesong.wav"))
		std::cerr << "ERROR::GAME::INITFONT::Failed to load music!" << "\n";
	// Output an error if music does not load
	music.play();
	music.setLoop(true);
}

void FallingShapes::initText()
{
	uiText.setFont(font);
	uiText.setCharacterSize(30);
	uiText.setFillColor(Color::White);
	uiText.setString("NONE");
	uiText.setPosition(15, 5);

	settingsTitle.setFont(font);
	settingsTitle.setCharacterSize(100);
	settingsTitle.setFillColor(Color::White);
	settingsTitle.setString("Settings");
	settingsTitle.setOutlineThickness(2);
	settingsTitle.setOutlineColor(Color::Black);
	settingsTitle.setPosition((800.f - settingsTitle.getLocalBounds().width) / 2.f, 190.f);

	settingsSubTitle.setFont(font);
	settingsSubTitle.setCharacterSize(40);
	settingsSubTitle.setFillColor(Color::White);
	settingsSubTitle.setOutlineThickness(2);
	settingsSubTitle.setOutlineColor(Color::Black);

	easy.setFont(font);
	easy.setCharacterSize(40);
	easy.setFillColor(Color::Green);
	easy.setString("Beginner \n  Mode");
	easy.setPosition(68.f, 650.f);

	medium.setFont(font);
	medium.setCharacterSize(40);
	medium.setFillColor(Color::Yellow);
	medium.setString("Normal \n Mode");
	medium.setPosition(((800.f - medium.getLocalBounds().width) / 2.f) + 5, 650.f);

	hard.setFont(font);
	hard.setCharacterSize(40);
	hard.setFillColor(Color::Red);
	hard.setString("Insane \nMode");
	hard.setPosition(607.f, 650.f);

	gameOverText.setFont(font);
	gameOverText.setCharacterSize(100);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setString("GAME OVER!");
	gameOverText.setOutlineThickness(2);
	gameOverText.setOutlineColor(Color::Black);
	gameOverText.setPosition((800.f - gameOverText.getLocalBounds().width) / 2.f, 190.f);

	gameOverSubText.setFont(font);
	gameOverSubText.setCharacterSize(40);
	gameOverSubText.setFillColor(Color::White);
	gameOverSubText.setOutlineThickness(2);
	gameOverSubText.setOutlineColor(Color::Black);

	gameOverSubText1.setFont(font);
	gameOverSubText1.setCharacterSize(40);
	gameOverSubText1.setFillColor(Color::White);
	gameOverSubText1.setOutlineThickness(2);
	gameOverSubText1.setOutlineColor(Color::Black);

	replay.setFont(font);
	replay.setCharacterSize(40);
	replay.setFillColor(Color::Cyan);
	replay.setString("  Play \nAgain?");
	replay.setPosition(45.f, 650.f);

	menu.setFont(font);
	menu.setCharacterSize(40);
	menu.setFillColor(Color::Yellow);
	menu.setString("   Return \nTo Menu?");
	menu.setPosition(620.f, 650.f);
}

void FallingShapes::initShapes()
{
	shape.setPosition(10.f, 10.f);
	shape.setRadius(50.f);
	shape.setPointCount(4);
	shape.setFillColor(Color::Green);
}

void FallingShapes::initMenuButtons()
{
	// Settings button for easy mode
	easyButton.setPosition(40.f, 600.f);
	easyButton.setSize(Vector2f(200.f, 200.f));
	easyButton.setFillColor(Color(25, 25, 25));
	easyButton.setOutlineThickness(-13.f);
	easyButton.setOutlineColor(Color::Green);

	// Settings button for medium mode
	mediumButton.setPosition(300.f, 600.f);
	mediumButton.setSize(Vector2f(200.f, 200.f));
	mediumButton.setFillColor(Color(25, 25, 25));
	mediumButton.setOutlineThickness(-13.f);
	mediumButton.setOutlineColor(Color::Yellow);

	// Settings button for hard mode
	hardButton.setPosition(560.f, 600.f);
	hardButton.setSize(Vector2f(200.f, 200.f));
	hardButton.setFillColor(Color(25, 25, 25));
	hardButton.setOutlineThickness(-13.f);
	hardButton.setOutlineColor(Color::Red);

	// Gameover button for menu return
	menuButton.setPosition(600.f, 600.f);
	menuButton.setSize(Vector2f(200.f, 200.f));
	menuButton.setFillColor(Color(25, 25, 25));
	menuButton.setOutlineThickness(-13.f);
	menuButton.setOutlineColor(Color::Yellow);

	// Gameover button to replay
	replayButton.setPosition(0.f, 600.f);
	replayButton.setSize(Vector2f(200.f, 200.f));
	replayButton.setFillColor(Color(25, 25, 25));
	replayButton.setOutlineThickness(-13.f);
	replayButton.setOutlineColor(Color::Cyan);
}

void FallingShapes::initTexture()
{
	// Assign a png file to "titleScreenTexture"
	if (!bkgTexture.loadFromFile("Images/neonbkg.jpg"))
	{
		std::cout << "ERROR::GAME::INITTEXTURE::Failed to load texture!" << "\n";
		// Output error if image fails to load
	}
	bkgTexture.setSmooth(true);
	bkg.setTexture(bkgTexture); // Assign the texture to a sprite
	bkg.setScale(Vector2f(1.35f, 1.35f)); // Adjust sprite scale

	if (!settingsTexture.loadFromFile("Images/settingsbkg.jpg"))
	{
		std::cout << "ERROR::GAME::INITTEXTURE::Failed to load texture!" << "\n";
		// Output error if image fails to load
	}
	settingsTexture.setSmooth(true);
	settingsBkg.setTexture(settingsTexture); // Assign the texture to a sprite
	settingsBkg.setScale(Vector2f(1.35f, 1.35f)); // Adjust sprite scale
}

// Constructor // Destructor //
FallingShapes::FallingShapes()
{
	// Initialize private functions and objects
	initVariables();
	initWindow();
	initFiles();
	initText();
	initShapes();
	initMenuButtons();
	initTexture();
}

FallingShapes::~FallingShapes()
{
	// Destoy "fallingShapesWindow" ptr and deallocate its memory 
	delete fallingShapesWindow;
}

// Functions

// Spawn a random shape type at a random location on the x-axis
void FallingShapes::spawnShapes()
{
	shape.setPosition(
		static_cast<float>(rand() % static_cast<int>(fallingShapesWindow->
			getSize().x - shape.getRadius())), 0.f);
	// "static_cast<float>" safely turns the following variable into a float.

	// Generate a random shape type
	int type = rand() % 5;

	switch (type)
	{
	case 0:
		shape.setRadius(15.f);
		shape.setPointCount(5);
		shape.setFillColor(Color::Magenta);
		break;
	case 1:
		shape.setRadius(20.f);
		shape.setPointCount(6);
		shape.setFillColor(Color::Red);
		break;
	case 2:
		shape.setRadius(25.f);
		shape.setPointCount(3);
		shape.setFillColor(Color::Yellow);
		break;
	case 3:
		shape.setRadius(30.f);
		shape.setPointCount(100);
		shape.setFillColor(Color::Blue);
		break;
	case 4:
		shape.setRadius(35.f);
		shape.setPointCount(4);
		shape.setFillColor(Color::Green);
		shape.rotate(45.f);
		break;
	default: // For debug usage
		shape.setRadius(100.f);
		shape.setPointCount(3);
		shape.setFillColor(Color::White);
		break;
	}

	//Spawn the shape
	shapes.push_back(shape);
}

void FallingShapes::updateMouse()
{
	//Updates mouse positions
	mousePosWindow = Mouse::getPosition(*fallingShapesWindow);
	mousePosView = fallingShapesWindow->mapPixelToCoords(mousePosWindow);
}

// Update and render object when game concludes
void FallingShapes::handleGameOver()
{
	fallingShapesWindow->clear();
	updateMouse();
	fallingShapesWindow->draw(bkg);
	fallingShapesWindow->draw(gameOverText);

	if (clickCounter > 0)
		clickAccuracy = (successfulClickCounter / clickCounter) * 100;

	std::stringstream gameOverString;
	gameOverString << "Final Score : " << points << "\n";

	std::stringstream gameOverString1;
	gameOverString1 << "Accuracy: " << clickAccuracy << "%\n";

	gameOverSubText.setString(gameOverString.str());
	gameOverSubText.setPosition((800.f - gameOverSubText.getLocalBounds().width) / 2.f, 320.f);
	gameOverSubText1.setString(gameOverString1.str());
	gameOverSubText1.setPosition((800.f - gameOverSubText1.getLocalBounds().width) / 2.f, 370.f);
	fallingShapesWindow->draw(gameOverSubText);
	fallingShapesWindow->draw(gameOverSubText1);

	fallingShapesWindow->draw(menuButton);
	fallingShapesWindow->draw(replayButton);
	fallingShapesWindow->draw(menu);
	fallingShapesWindow->draw(replay);
}

void FallingShapes::handleSettings()
{
	fallingShapesWindow->clear();
	updateMouse();
	fallingShapesWindow->draw(settingsBkg);
	fallingShapesWindow->draw(settingsTitle);

	std::stringstream settingsString;
	settingsString << "             FALLING SHAPES GAME!\n           When the game starts click\nthe shapes before they go off screen!\n         Choose your difficulty setting:";

	settingsSubTitle.setString(settingsString.str());
	settingsSubTitle.setPosition((800.f - settingsSubTitle.getLocalBounds().width) / 2.f, 340.f);
	fallingShapesWindow->draw(settingsSubTitle);

	fallingShapesWindow->draw(easyButton);
	fallingShapesWindow->draw(mediumButton);
	fallingShapesWindow->draw(hardButton);
	fallingShapesWindow->draw(easy);
	fallingShapesWindow->draw(medium);
	fallingShapesWindow->draw(hard);
}

void FallingShapes::updateShapes()
{
	if (shapes.size() < maxShapes)
	{
		// Spawn shape and update timer
		if (shapeSpawnTimer >= shapeSpawnTimerMax)
		{
			spawnShapes();
			shapeSpawnTimer = 0.f;
		}
		else
			shapeSpawnTimer += 1.f;
	}

	// Move and update the shapes
	for (int i = 0; i < shapes.size(); i++)
	{
		// Shape moves down
		shapes[i].move(0.f, shapeSpeed);

		// Check if the shape moves below the screen
		if (shapes[i].getPosition().y > fallingShapesWindow->getSize().y)
		{
			shapes.erase(shapes.begin() + i);
			health -= 1;
		}
	}

	// Check if shape is clicked
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (mouseHeld == false)
		{
			mouseHeld = true;
			clickCounter += 1.f;

			for (size_t i = 0; i < shapes.size(); i++)
			{
				if (shapes[i].getGlobalBounds().contains(mousePosView))
				{
					// Gain points
					if (shapes[i].getFillColor() == Color::Magenta)
						points += (9 * pointMultiplier);
					else if (shapes[i].getFillColor() == Color::Red)
						points += (7 * pointMultiplier);
					else if (shapes[i].getFillColor() == Color::Yellow)
						points += (5 * pointMultiplier);
					else if (shapes[i].getFillColor() == Color::Blue)
						points += (3 * pointMultiplier);
					else if (shapes[i].getFillColor() == Color::Green)
						points += (1 * pointMultiplier);

					pop.play();

					// Delete the shape
					shapes.erase(shapes.begin() + i);
					shapeSpeed += .01;
					successfulClickCounter += 1.f;
				}
			}
		}
	}
	else
	{
		mouseHeld = false;
	}
}

// Update moving game objects
void FallingShapes::updateObjects()
{
	updateMouse();
	updateShapes();

	if (clickCounter > 0)
		clickAccuracy = (successfulClickCounter / clickCounter) * 100;

	std::stringstream uiString;
	uiString << "Points: " << points << "\n"
		<< "Health: " << health << "\n"
		<< "Accuracy: " << clickAccuracy << "%\n";

	uiText.setString(uiString.str());
}

// Render game objects to window
void FallingShapes::renderObjects()
{
	fallingShapesWindow->draw(bkg);

	for (auto& s : shapes)
		fallingShapesWindow->draw(s);

	fallingShapesWindow->draw(uiText);
}

// Game loop
int FallingShapes::playFallingShapes()
{
	// Perform actions while fallingShapesWindow is open
	while (fallingShapesWindow->isOpen())
	{
		// Handle events or perform other actions
		while (fallingShapesWindow->pollEvent(e))
		{
			switch (e.type)
			{
			case Event::Closed:
				fallingShapesWindow->close(); // Closes the window when exit button is clicked
				break;
			case Event::KeyPressed: //Checks for a key press
				if (e.key.code == Keyboard::Escape) //Checks if key press is esc
					fallingShapesWindow->close(); //Closes window when esc key is pressed
				break;
			}
		}
		// Clear the window
		fallingShapesWindow->clear();

		if (settingsOpen == true)
		{
			handleSettings();
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (mouseHeld == false)
				{
					mouseHeld = true;
					if (easyButton.getGlobalBounds().contains(mousePosView))
					{
						settingsOpen = false;
					}
					else if (mediumButton.getGlobalBounds().contains(mousePosView))
					{
						shapeSpeed = 4.f;
						maxShapes = 7;
						shapeSpawnTimerMax = 8.f;
						pointMultiplier = 2.f;
						settingsOpen = false;
					}
					else if (hardButton.getGlobalBounds().contains(mousePosView))
					{
						shapeSpeed = 4.5f;
						maxShapes = 9;
						shapeSpawnTimerMax = 5.f;
						pointMultiplier = 4.f;
						settingsOpen = false;
					}
				}
			}
			else
			{
				mouseHeld = false;
			}
		}
		if (health > 0 && !settingsOpen)
		{
			// Update game objects
			updateObjects();

			// Render game objects
			renderObjects();
		}
		else if (health <= 0 && !settingsOpen)
		{
			handleGameOver();
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (mouseHeld == false)
				{
					mouseHeld = true;
					if (replayButton.getGlobalBounds().contains(mousePosView))
					{
						fallingShapesWindow->close();
						FallingShapes playAgain;
						playAgain.playFallingShapes();
					}
					else if (menuButton.getGlobalBounds().contains(mousePosView))
					{
						music.stop();
						fallingShapesWindow->close();
						Menu menuReturn;
						menuReturn.runMenu();
					}
				}
			}
			else
			{
				mouseHeld = false;
			}
		}


		// Display the window
		fallingShapesWindow->display();
	}
	return 0;
}
