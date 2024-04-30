#include "RandomCircles.h"
//// IMPLEMENTATION FILE FOR RANDOM CIRCLES GAME CLASS ////

#include "RandomCircles.h"

// Private functions
void RandomCircles::initVariables()
{
	// Set fallingShapesWindow pointer to null
	randCirclesWindow = nullptr;

	// Game logic
	mouseHeld = true;
	settingsOpen = true;
	points = 0;
	circleSpawnTimerMax = 15.f;
	circleSpawnTimer = circleSpawnTimerMax;
	maxCircles = 4;
	clickCounter = 0.f;
	successfulClickCounter = 0.f;
	clickAccuracy = 0.f;
	timeUp = false;
	clickTimer = 45.0f;
	initialClick = false;
	radius = 40.f;
}

void RandomCircles::initWindow()
{
	// Initialize variables for window dimensions
	videoMode.height = 800;
	videoMode.width = 800;

	// Assign SFML RenderWindow to randCirclesWindow pointer
	randCirclesWindow = new RenderWindow(videoMode, "Random Circles Game!", Style::Titlebar | Style::Close);
	randCirclesWindow->setFramerateLimit(60); // Set FPS to 60
}

void RandomCircles::initResources()
{
	// Assign a font file to "font"
	if (!font.loadFromFile("Fonts/calibri.ttf"))
	{
		std::cerr << "ERROR::GAME::INITRESOURCES::Failed to load font!" << "\n";
		// Output an error if font does not load
	}

	if (!popBuffer.loadFromFile("Audio/pop.flac"))
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

void RandomCircles::initText()
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
	gameOverText.setFillColor(Color::Green);
	gameOverText.setString("WELL DONE!");
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
	replay.setFillColor(Color::Magenta);
	replay.setString("  Play \nAgain?");
	replay.setPosition(45.f, 650.f);

	menu.setFont(font);
	menu.setCharacterSize(40);
	menu.setFillColor(Color::Yellow);
	menu.setString("   Return \nTo Menu?");
	menu.setPosition(620.f, 650.f);
}

void RandomCircles::initCircles()
{
	circle.setPosition(10.f, 10.f);
	circle.setRadius(50.f);
}

void RandomCircles::initMenuButtons()
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

void RandomCircles::initTextures()
{
	// Assign a png file to "titleScreenTexture"
	if (!bkgTexture.loadFromFile("Images/randomcirclesbkg.png"))
	{
		std::cout << "ERROR::GAME::INITTEXTURES::Failed to load texture!" << "\n";
		// Output error if image fails to load
	}
	bkgTexture.setSmooth(true);
	bkg.setTexture(bkgTexture); // Assign the texture to a sprite
	bkg.setScale(Vector2f(1.35f, 1.35f)); // Adjust sprite scale

	if (!redTarget.loadFromFile("Images/redtarget.png"))
	{
		std::cout << "ERROR::GAME::INITTEXTURES::Failed to load texture!" << "\n";
	}
	if (!purpleTarget.loadFromFile("Images/purpletarget.png"))
	{
		std::cout << "ERROR::GAME::INITTEXTURES::Failed to load texture!" << "\n";
	}
	if (!blueTarget.loadFromFile("Images/bluetarget.png"))
	{
		std::cout << "ERROR::GAME::INITTEXTURES::Failed to load texture!" << "\n";
	}
	if (!greenTarget.loadFromFile("Images/greentarget.png"))
	{
		std::cout << "ERROR::GAME::INITTEXTURES::Failed to load texture!" << "\n";
	}
	if (!yellowTarget.loadFromFile("Images/yellowtarget.png"))
	{
		std::cout << "ERROR::GAME::INITTEXTURES::Failed to load texture!" << "\n";
	}
	redTarget.setSmooth(true);
	purpleTarget.setSmooth(true);
	blueTarget.setSmooth(true);
	greenTarget.setSmooth(true);
	yellowTarget.setSmooth(true);

	if (!settingsTexture.loadFromFile("Images/settingsbkg.jpg"))
	{
		std::cout << "ERROR::GAME::INITTEXTURES::Failed to load texture!" << "\n";
		// Output error if image fails to load
	}
	settingsTexture.setSmooth(true);
	settingsBkg.setTexture(settingsTexture); // Assign the texture to a sprite
	settingsBkg.setScale(Vector2f(1.35f, 1.35f)); // Adjust sprite scale
}

// Constructor // Destructor //
RandomCircles::RandomCircles()
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

RandomCircles::~RandomCircles()
{
	// Destoy "fallingShapesWindow" ptr and deallocate its memory 
	delete randCirclesWindow;
}

// Functions

// Spawn a circle at a random location
void RandomCircles::spawnCircles()
{
	circle.setPosition(
		static_cast<float>(rand() % static_cast<int>(randCirclesWindow->
			getSize().x - circle.getRadius())), static_cast<float>(rand() % static_cast<int>(randCirclesWindow->
				getSize().y - circle.getRadius())));
	// "static_cast<float>" safely turns the following variable into a float.

	circle.setRadius(radius);
	circle.setPointCount(100);

	int type = rand() % 5;

	switch (type)
	{
	case 0:
		circle.setTexture(&redTarget);
		break;
	case 1:
		circle.setTexture(&purpleTarget);
		break;
	case 2:
		circle.setTexture(&blueTarget);
		break;
	case 3:
		circle.setTexture(&greenTarget);
		break;
	case 4:
		circle.setTexture(&yellowTarget);
		break;
	default: // For debug usage
		circle.setRadius(100.f);
		circle.setPointCount(3);
		circle.setFillColor(Color::White);
		break;
	}

	circles.push_back(circle);
}

void RandomCircles::updateMouse()
{
	//Updates mouse positions
	mousePosWindow = Mouse::getPosition(*randCirclesWindow);
	mousePosView = randCirclesWindow->mapPixelToCoords(mousePosWindow);
}

// Update and render objects when the game concludes
void RandomCircles::handleGameOver()
{
	randCirclesWindow->clear();
	updateMouse();
	randCirclesWindow->draw(bkg);
	randCirclesWindow->draw(gameOverText);

	if (clickCounter > 0)
		clickAccuracy = (successfulClickCounter / clickCounter) * 100;

	std::stringstream gameOverString;
	gameOverString << "Targets Clicked: " << points << "\n";

	std::stringstream gameOverString1;
	gameOverString1 << "Accuracy: " << clickAccuracy << "%\n";

	gameOverSubText.setString(gameOverString.str());
	gameOverSubText.setPosition((800.f - gameOverSubText.getLocalBounds().width) / 2.f, 320.f);
	gameOverSubText1.setString(gameOverString1.str());
	gameOverSubText1.setPosition((800.f - gameOverSubText1.getLocalBounds().width) / 2.f, 370.f);
	randCirclesWindow->draw(gameOverSubText);
	randCirclesWindow->draw(gameOverSubText1);

	randCirclesWindow->draw(menuButton);
	randCirclesWindow->draw(replayButton);
	randCirclesWindow->draw(menu);
	randCirclesWindow->draw(replay);
}

void RandomCircles::handleSettings()
{
	randCirclesWindow->clear();
	updateMouse();
	randCirclesWindow->draw(settingsBkg);
	randCirclesWindow->draw(settingsTitle);

	std::stringstream settingsString;
	settingsString << "       RANDOM CIRCLES GAME!\n      When the game starts click\nclick as many targets as possible!\n    Choose your difficulty setting:";

	settingsSubTitle.setString(settingsString.str());
	settingsSubTitle.setPosition((800.f - settingsSubTitle.getLocalBounds().width) / 2.f, 340.f);
	randCirclesWindow->draw(settingsSubTitle);

	randCirclesWindow->draw(easyButton);
	randCirclesWindow->draw(mediumButton);
	randCirclesWindow->draw(hardButton);
	randCirclesWindow->draw(easy);
	randCirclesWindow->draw(medium);
	randCirclesWindow->draw(hard);
}

void RandomCircles::updateCircles()
{
	if (initialClick)
	{
		if (circles.size() < maxCircles)
		{
			// Spawn shape and update timer
			if (circleSpawnTimer >= circleSpawnTimerMax)
			{
				spawnCircles();
				circleSpawnTimer = 0.f;
			}
			else
				circleSpawnTimer += 1.f;
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
				}
			}
		}
	}
	else
	{
		mouseHeld = false;
	}
}

void RandomCircles::updateTime()
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
void RandomCircles::updateObjects()
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
void RandomCircles::renderObjects()
{
	randCirclesWindow->draw(bkg);

	for (auto& s : circles)
		randCirclesWindow->draw(s);

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

	randCirclesWindow->draw(timerText);
	randCirclesWindow->draw(uiText);
}

// Game loop
int RandomCircles::playRandomCircles()
{
	// Perform actions while randCirclesWindow is open
	while (randCirclesWindow->isOpen())
	{
		// Handle events or perform other actions
		while (randCirclesWindow->pollEvent(e))
		{
			switch (e.type)
			{
			case Event::Closed:
				randCirclesWindow->close(); // Closes the window when exit button is clicked
				break;
			case Event::KeyPressed: //Checks for a key press
				if (e.key.code == Keyboard::Escape) //Checks if key press is esc
					randCirclesWindow->close(); //Closes window when esc key is pressed
				break;
			}
		}
		// Clear the window
		randCirclesWindow->clear();

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
						circleSpawnTimerMax = 9.f;
						maxCircles = 3;
						clickTimer = 30.0f;
						radius = 30.f;
						settingsOpen = false;
					}
					else if (hardButton.getGlobalBounds().contains(mousePosView))
					{
						circleSpawnTimerMax = 3.f;
						maxCircles = 2;
						clickTimer = 15.0f;
						radius = 20.f;
						settingsOpen = false;
					}
				}
			}
			else
			{
				mouseHeld = false;
			}
		}


		if (!timeUp && !settingsOpen)
		{
			// Update game objects
			updateObjects();

			// Render game objects
			renderObjects();
		}
		else if (timeUp && !settingsOpen)
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
						randCirclesWindow->close();
						RandomCircles playAgain;
						playAgain.playRandomCircles();
					}
					else if (menuButton.getGlobalBounds().contains(mousePosView))
					{
						music.stop();
						randCirclesWindow->close();
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
		randCirclesWindow->display();
	}
	return 0;
}
