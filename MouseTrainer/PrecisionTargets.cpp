//// IMPLEMENTATION FILE FOR PRECISION TARGETS GAME CLASS ////

#include "PrecisionTargets.h"

// Private functions

void PrecisionTargets::initVariables()
{
	// Set fallingShapesWindow pointer to null
	targetsWindow = nullptr;

	// Game logic
	mouseHeld = true;
	settingsOpen = true;
	points = 0;
	maxCircles = 15;
	clickCounter = 0.f;
	successfulClickCounter = 0.f;
	clickAccuracy = 0.f;
	timeUp = false;
	clickTimer = 15.0f;
	initialClick = false;
	numCircles = 0;
	gameWon = false;
}

void PrecisionTargets::initWindow()
{
	// Initialize variables for window dimensions
	videoMode.height = 800;
	videoMode.width = 800;

	// Assign SFML RenderWindow to targetsWindow pointer
	targetsWindow = new RenderWindow(videoMode, "Precision Targets Game!", Style::Titlebar | Style::Close);
	targetsWindow->setFramerateLimit(60); // Set FPS to 60
}

void PrecisionTargets::initResources()
{
	// Assign a font file to "font"
	if (!font.loadFromFile("Fonts/calibri.ttf"))
	{
		std::cerr << "ERROR::GAME::INITRESOURCES::Failed to load font!" << "\n";
		// Output an error if font does not load
	}

	if (!popBuffer.loadFromFile("Audio/zap.wav"))
	{
		std::cerr << "ERROR::GAME::INITRESOURCES::Failed to load audio!" << "\n";
		// Output an error if audio does not load
	}

	pop.setBuffer(popBuffer);

	time = clock.getElapsedTime();

	if (!music.openFromFile("Audio/gamesong.wav"))
		std::cerr << "ERROR::GAME::INITRESOURCES::Failed to load music!" << "\n";
	// Output an error if music does not load
	music.play();
	music.setLoop(true);
}

void PrecisionTargets::initText()
{
	uiText.setFont(font);
	uiText.setCharacterSize(30);
	uiText.setFillColor(Color::White);
	uiText.setString("NONE");
	uiText.setPosition(15, 718);

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

	timerText.setFont(font);
	timerText.setCharacterSize(40);
	timerText.setFillColor(Color::White);

	gameOverText.setFont(font);
	gameOverText.setCharacterSize(100);
	gameOverText.setOutlineThickness(2);
	gameOverText.setOutlineColor(Color::Black);

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
	replay.setFillColor(Color::Magenta);
	replay.setString("  Play \nAgain?");
	replay.setPosition(45.f, 650.f);

	menu.setFont(font);
	menu.setCharacterSize(40);
	menu.setFillColor(Color::Yellow);
	menu.setString("   Return \nTo Menu?");
	menu.setPosition(620.f, 650.f);
}

void PrecisionTargets::initCircles()
{
	circle.setPosition(10.f, 10.f);
	circle.setRadius(50.f);
}

void PrecisionTargets::initMenuButtons()
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
	replayButton.setOutlineColor(Color::Magenta);
}

void PrecisionTargets::initTextures()
{
	// Assign a png file to "titleScreenTexture"
	if (!bkgTexture.loadFromFile("Images/precisionbkg.jpg"))
	{
		std::cout << "ERROR::GAME::INITTEXTURES::Failed to load texture!" << "\n";
		// Output error if image fails to load
	}
	bkgTexture.setSmooth(true);
	bkg.setTexture(bkgTexture); // Assign the texture to a sprite
	bkg.setScale(Vector2f(.816f, .816f)); // Adjust sprite scale

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
PrecisionTargets::PrecisionTargets()
{
	// Initialize private functions and objects
	initVariables();
	initWindow();
	initResources();
	initText();
	initCircles();
	initMenuButtons();
	initTextures();
}

PrecisionTargets::~PrecisionTargets()
{
	// Destoy "fallingShapesWindow" ptr and deallocate its memory 
	delete targetsWindow;
}

// Functions

// Spawn a circle at a random location
void PrecisionTargets::spawnCircles()
{
	circle.setPosition(
		static_cast<float>(rand() % static_cast<int>(targetsWindow->
			getSize().x - circle.getRadius())), static_cast<float>(rand() % static_cast<int>(targetsWindow->
				getSize().y - circle.getRadius())));
	// "static_cast<float>" safely turns the following variable into a float.

	circle.setRadius(5.f);
	circle.setPointCount(100);
	circle.setOutlineThickness(2.f);
	circle.setOutlineColor(Color::Black);

	int type = rand() % 5;

	switch (type)
	{
	case 0:
		circle.setFillColor(Color::Red);
		break;
	case 1:
		circle.setFillColor(Color::Green);
		break;
	case 2:
		circle.setFillColor(Color::Cyan);
		break;
	case 3:
		circle.setFillColor(Color::Magenta);
		break;
	case 4:
		circle.setFillColor(Color::Yellow);
		break;
	default: // For debug usage
		circle.setRadius(100.f);
		circle.setPointCount(3);
		circle.setFillColor(Color::White);
		break;
	}

	circles.push_back(circle);
}

void PrecisionTargets::updateMouse()
{
	//Updates mouse positions
	mousePosWindow = Mouse::getPosition(*targetsWindow);
	mousePosView = targetsWindow->mapPixelToCoords(mousePosWindow);
}

// Update and render objects when the game concludes
void PrecisionTargets::handleGameOver()
{
	targetsWindow->clear();
	updateMouse();
	targetsWindow->draw(bkg);

	if (gameWon == true)
	{
		gameOverText.setFillColor(Color::Green);
		gameOverText.setString("SUCCESS!");
	}
	else if (!gameWon)
	{
		gameOverText.setFillColor(Color::Red);
		gameOverText.setString("GAME OVER!");
	}
	gameOverText.setPosition((800.f - gameOverText.getLocalBounds().width) / 2.f, 190.f);
	targetsWindow->draw(gameOverText);

	if (clickCounter > 0)
		clickAccuracy = (successfulClickCounter / clickCounter) * 100;

	std::stringstream gameOverString;
	gameOverString << "Targets Clicked: " << points << " of " << maxCircles;

	std::stringstream gameOverString1;
	gameOverString1 << "Accuracy: " << clickAccuracy << "%";

	gameOverSubText.setString(gameOverString.str());
	gameOverSubText.setPosition((800.f - gameOverSubText.getLocalBounds().width) / 2.f, 320.f);
	gameOverSubText1.setString(gameOverString1.str());
	gameOverSubText1.setPosition((800.f - gameOverSubText1.getLocalBounds().width) / 2.f, 370.f);
	targetsWindow->draw(gameOverSubText);
	targetsWindow->draw(gameOverSubText1);

	targetsWindow->draw(menuButton);
	targetsWindow->draw(replayButton);
	targetsWindow->draw(menu);
	targetsWindow->draw(replay);
}

void PrecisionTargets::handleSettings()
{
	targetsWindow->clear();
	updateMouse();
	targetsWindow->draw(settingsBkg);
	targetsWindow->draw(settingsTitle);

	std::stringstream settingsString;
	settingsString << "         Precision Targets Game!\n     When the game starts click\n  all the targets in the time limit!\n     Choose your difficulty setting:";

	settingsSubTitle.setString(settingsString.str());
	settingsSubTitle.setPosition((800.f - settingsSubTitle.getLocalBounds().width) / 2.f, 340.f);
	targetsWindow->draw(settingsSubTitle);

	targetsWindow->draw(easyButton);
	targetsWindow->draw(mediumButton);
	targetsWindow->draw(hardButton);
	targetsWindow->draw(easy);
	targetsWindow->draw(medium);
	targetsWindow->draw(hard);
}

void PrecisionTargets::updateCircles()
{
	if (initialClick)
	{
		if (numCircles < maxCircles)
		{
			spawnCircles();
			numCircles += 1;
		}
	}
	// Check if shape is clicked
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (mouseHeld == false)
		{
			mouseHeld = true;
			clickCounter += 1.f;

			for (size_t i = 0; i < circles.size(); i++)
			{
				if (circles[i].getGlobalBounds().contains(mousePosView))
				{
					points += 1;
					pop.play();

					// Delete the shape
					circles.erase(circles.begin() + i);
					successfulClickCounter += 1.f;
					if (points >= maxCircles)
						gameWon = true;
				}
			}
		}
	}
	else
	{
		mouseHeld = false;
	}
}

void PrecisionTargets::updateTime()
{
	if (!initialClick)
	{
		if (clickCounter > 0)
		{
			clock.restart(); // Restart the clock when the first click occurs
			initialClick = true;
		}
	}

	if (initialClick)
	{
		time = clock.getElapsedTime();
	}
}

// Update moving game objects
void PrecisionTargets::updateObjects()
{
	updateTime();
	updateMouse();

	updateCircles();

	if (clickCounter > 0)
		clickAccuracy = (successfulClickCounter / clickCounter) * 100;

	std::stringstream uiString;
	uiString << "Targets Clicked: " << points << "\n"
		<< "Accuracy: " << clickAccuracy << "%\n";

	uiText.setString(uiString.str());
}

// Render game objects to window
void PrecisionTargets::renderObjects()
{
	targetsWindow->draw(bkg);

	for (auto& s : circles)
		targetsWindow->draw(s);

	if (initialClick)
	{
		float elapsedTime = time.asSeconds();
		std::stringstream timeString;
		timeString << "Time Elapsed: \n" << "  " << std::fixed << std::setprecision(1) << elapsedTime << " Seconds";

		timerText.setString(timeString.str());
		timerText.setCharacterSize(30);
		timerText.setPosition((800.f - timerText.getLocalBounds().width) / 2.f, 0.f);

		if (elapsedTime >= clickTimer)
			timeUp = true;
	}
	else
	{
		std::stringstream startString;
		startString << "      Click to start!\nTest time: " << clickTimer << " seconds";
		timerText.setString(startString.str());
		timerText.setPosition(150.f, 330.f);
		timerText.setCharacterSize(60);
		timerText.setOutlineThickness(2.f);
		timerText.setOutlineColor(Color::Black);
	}

	targetsWindow->draw(timerText);
	targetsWindow->draw(uiText);
}

// Game loop
int PrecisionTargets::playPrecisionTargets()
{
	// Perform actions while randCirclesWindow is open
	while (targetsWindow->isOpen())
	{
		// Handle events or perform other actions
		while (targetsWindow->pollEvent(e))
		{
			switch (e.type)
			{
			case Event::Closed:
				targetsWindow->close(); // Closes the window when exit button is clicked
				break;
			case Event::KeyPressed: //Checks for a key press
				if (e.key.code == Keyboard::Escape) //Checks if key press is esc
					targetsWindow->close(); //Closes window when esc key is pressed
				break;
			}
		}
		// Clear the window
		targetsWindow->clear();

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
						clickTimer = 13.0f;
						maxCircles = 17;
						settingsOpen = false;
					}
					else if (hardButton.getGlobalBounds().contains(mousePosView))
					{
						clickTimer = 10.0f;
						maxCircles = 20;
						settingsOpen = false;
					}
				}
			}
			else
			{
				mouseHeld = false;
			}
		}

		if (!timeUp && !gameWon && !settingsOpen)
		{
			// Update game objects
			updateObjects();

			// Render game objects
			renderObjects();
		}
		else if (!settingsOpen)
		{
			// Perform tasks when game ends
			handleGameOver();
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (mouseHeld == false)
				{
					mouseHeld = true;
					if (replayButton.getGlobalBounds().contains(mousePosView))
					{
						targetsWindow->close();
						PrecisionTargets playAgain;
						playAgain.playPrecisionTargets();
					}
					else if (menuButton.getGlobalBounds().contains(mousePosView))
					{
						music.stop();
						targetsWindow->close();
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
		targetsWindow->display();
	}
	return 0;
}
