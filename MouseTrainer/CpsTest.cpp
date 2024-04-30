//// IMPLEMENTATION FILE FOR CPSTEST GAME CLASS ////

#include "cpsTest.h"

// Private functions
void CpsTest::initVariables()
{
	// Set cpsWindow pointer to null
	cpsWindow = nullptr;

	// Game logic
	initialClick = false;
	settingsOpen = true;
	mouseHeld = true;
	timeUp = false;
	clickCounter = 0;
	clickTimer = 5.0f;
	cps = 0.f;
}

void CpsTest::initWindow()
{
	// Initialize variables for window dimensions
	videoMode.height = 800;
	videoMode.width = 800;

	// Assign SFML RenderWindow to cpsWindow pointer
	cpsWindow = new RenderWindow(videoMode, "Clicks Per Second Test!", Style::Titlebar | Style::Close);
	cpsWindow->setFramerateLimit(60); // Set FPS to 120
}

void CpsTest::initResources()
{
	// Assign a font file to "font"
	if (!font.loadFromFile("Fonts/calibri.ttf"))
	{
		std::cerr << "ERROR::GAME::INITRESOURCES::Failed to load font!" << "\n";
		// Output an error if font does not load
	}

	time = clock.getElapsedTime();

	// Assign a png file to "bkgTexture"
	if (!bkgTexture.loadFromFile("Images/clickerbkg.jpg"))
	{
		std::cout << "ERROR::GAME::INITRESOURCES::Failed to load texture!" << "\n";
		// Output error if image fails to load
	}
	bkgTexture.setSmooth(true);
	bkg.setTexture(bkgTexture); // Assign the texture to a sprite

	if (!popBuffer.loadFromFile("Audio/pop.flac"))
	{
		std::cerr << "ERROR::GAME::INITFILES::Failed to load audio!" << "\n";
		// Output an error if audio does not load
	}

	pop.setBuffer(popBuffer);

	if (!music.openFromFile("Audio/gamesong.wav"))
		std::cerr << "ERROR::GAME::INITRESOURCES::Failed to load music!" << "\n";
	// Output an error if music does not load
	music.play();
	music.setLoop(true);
}

void CpsTest::initText()
{
	uiText.setFont(font);
	uiText.setCharacterSize(40);
	uiText.setFillColor(Color::White);
	uiText.setString("NONE");

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
	easy.setString("     1 \nSecond \n Timer");
	easy.setPosition(80.f, 625.f);

	medium.setFont(font);
	medium.setCharacterSize(40);
	medium.setFillColor(Color::Yellow);
	medium.setString("     5 \nSecond \n Timer");
	medium.setPosition(((800.f - medium.getLocalBounds().width) / 2.f) + 5, 625.f);

	hard.setFont(font);
	hard.setCharacterSize(40);
	hard.setFillColor(Color::Red);
	hard.setString("    15 \nSecond \n Timer");
	hard.setPosition(600.f, 625.f);

	clickText.setFont(font);
	clickText.setCharacterSize(50);
	clickText.setFillColor(Color::White);
	clickText.setString("NONE");

	testOverText.setFont(font);
	testOverText.setCharacterSize(100);
	testOverText.setFillColor(Color::White);
	testOverText.setString("WELL DONE!");
	testOverText.setOutlineThickness(2);
	testOverText.setOutlineColor(Color::Black);
	testOverText.setPosition((800.f - testOverText.getLocalBounds().width) / 2.f, 200.f);

	testOverSubText.setFont(font);
	testOverSubText.setCharacterSize(40);
	testOverSubText.setFillColor(Color::White);
	testOverSubText.setOutlineThickness(2);
	testOverSubText.setOutlineColor(Color::Black);

	replay.setFont(font);
	replay.setCharacterSize(40);
	replay.setFillColor(Color::Green);
	replay.setString("  Play \nAgain?");
	replay.setPosition(45.f, 650.f);

	menu.setFont(font);
	menu.setCharacterSize(40);
	menu.setFillColor(Color::Yellow);
	menu.setString("   Return \nTo Menu?");
	menu.setPosition(620.f, 650.f);
}

void CpsTest::initGameObjects()
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

	// Test over button for menu return
	menuButton.setPosition(600.f, 600.f);
	menuButton.setSize(Vector2f(200.f, 200.f));
	menuButton.setFillColor(Color(25, 25, 25));
	menuButton.setOutlineThickness(-13.f);
	menuButton.setOutlineColor(Color::Yellow);

	// Test over button to replay
	replayButton.setPosition(0.f, 600.f);
	replayButton.setSize(Vector2f(200.f, 200.f));
	replayButton.setFillColor(Color(25, 25, 25));
	replayButton.setOutlineThickness(-13.f);
	replayButton.setOutlineColor(Color::Green);

	// Middle screen circle
	circle.setRadius(350.f);
	circle.setFillColor(Color(0, 0, 0, 230));
	circle.setOutlineThickness(-15.f);
	circle.setOutlineColor(Color::Black);
	circle.setPosition(50, 50);

	// Flashing circles
	flashingCircle.setRadius(50.f);
	flashingCircle.setFillColor(Color(25, 25, 25));
	flashingCircle.setPosition(10.f, 10.f);
}

// Constructor // Destructor //
CpsTest::CpsTest()
{
	// Initialize private functions and objects
	initVariables();
	initWindow();
	initResources();
	initText();
	initGameObjects();
}

CpsTest::~CpsTest()
{
	// Destoy "cpsWindow" ptr and deallocate its memory 
	delete cpsWindow;
}

// Functions

// Update mouse positions
void CpsTest::updateMouse()
{
	mousePosWindow = Mouse::getPosition(*cpsWindow);
	mousePosView = cpsWindow->mapPixelToCoords(mousePosWindow);
}

// Update and render object when test concludes
void CpsTest::handleTestOver()
{
	cpsWindow->clear();
	cpsWindow->draw(bkg);
	updateMouse();
	cpsWindow->draw(testOverText);

	if (clickCounter > 0)
		cps = (clickCounter / clickTimer);

	std::stringstream testOverString;
	testOverString << "Clicks Per Second: " << cps << "\n";

	testOverSubText.setString(testOverString.str());
	testOverSubText.setPosition((800.f - testOverSubText.getLocalBounds().width) / 2.f, 320.f);
	cpsWindow->draw(testOverSubText);

	cpsWindow->draw(menuButton);
	cpsWindow->draw(replayButton);
	cpsWindow->draw(menu);
	cpsWindow->draw(replay);
}

void CpsTest::handleSettings()
{
	cpsWindow->clear();
	updateMouse();
	cpsWindow->draw(settingsBkg);
	cpsWindow->draw(settingsTitle);

	std::stringstream settingsString;
	settingsString << "                         CPS TEST!\n      When the test starts click as you\n    can to test your clicks per second!\n           Choose your timer value:";

	settingsSubTitle.setString(settingsString.str());
	settingsSubTitle.setPosition((800.f - settingsSubTitle.getLocalBounds().width) / 2.f, 340.f);
	cpsWindow->draw(settingsSubTitle);

	cpsWindow->draw(easyButton);
	cpsWindow->draw(mediumButton);
	cpsWindow->draw(hardButton);
	cpsWindow->draw(easy);
	cpsWindow->draw(medium);
	cpsWindow->draw(hard);
}

void CpsTest::spawnCircles()
{
	// Set inital circle parameters
	flashingCircle.setPosition(392.5, 392.5);

	// Add circle to a vector
	flashingCircles.push_back(flashingCircle);
}



// Update moving game objects
void CpsTest::updateTime()
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (!mouseHeld)
		{
			mouseHeld = true;
			clickCounter += 1;
			pop.play();
			spawnCircles();
			if (!initialClick)
			{
				if (clickCounter > 0)
				{
					clock.restart(); // Restart the clock when the first click occurs
					initialClick = true;
				}
			}
		}
	}
	else
	{
		mouseHeld = false;
	}

	if (initialClick)
	{
		time = clock.getElapsedTime();
	}

}

void CpsTest::updateCircles()
{
	for (int i = 0; i < flashingCircles.size(); i++)
	{
		int a = flashingCircles[i].getFillColor().a;
		float radius = flashingCircles[i].getRadius();

		a -= 3; // Decrease alpha
		radius += 3.9f; // Increase radius

		flashingCircles[i].setRadius(radius);
		flashingCircles[i].setFillColor(Color(3, 181, 0, a));

		float centerX = 400.0f;
		float centerY = 400.0f;
		Vector2f circlePosition(centerX - radius, centerY - radius); // Center of the circle

		flashingCircles[i].setPosition(circlePosition);

		if (a <= 0 || radius >= 350.f)
		{
			// Erase the circle from the vector
			flashingCircles.erase(flashingCircles.begin() + i);
			i--; // Decrement i to account for the erased element
		}
	}
}

void CpsTest::updateObjects()
{
	updateTime();
	updateCircles();
}

// Render game objects to window
void CpsTest::renderObjects()
{
	cpsWindow->draw(bkg);

	if (initialClick)
	{
		float elapsedTime = time.asSeconds();
		std::stringstream timeString;
		timeString << "Time Elapsed: \n" << std::fixed << std::setprecision(1) << elapsedTime << " Seconds";

		uiText.setString(timeString.str());
		uiText.setPosition(15, 5);
		cpsWindow->draw(uiText);

		if (elapsedTime >= clickTimer)
			timeUp = true;
	}

	cpsWindow->draw(circle);

	for (auto& s : flashingCircles)
	{
		cpsWindow->draw(s);
	}

	if (clickCounter <= 0)
	{
		std::stringstream startString;
		startString << "      Click to start!\nTest time: " << clickTimer << " seconds";
		clickText.setString(startString.str());
		clickText.setPosition(200, 330);
	}
	else if (clickCounter > 0)
	{
		std::stringstream clickString;
		clickString << clickCounter;
		clickText.setString(clickString.str());
		clickText.setPosition(370, 370);
		clickText.setCharacterSize(70);
	}
	cpsWindow->draw(clickText);
}

// Game loop
int CpsTest::playCpsTest()
{
	// Perform actions while fallingShapesWindow is open
	while (cpsWindow->isOpen())
	{
		// Handle events or perform other actions
		while (cpsWindow->pollEvent(e))
		{
			switch (e.type)
			{
			case Event::Closed:
				cpsWindow->close(); // Closes the window when exit button is clicked
				break;
			case Event::KeyPressed: //Checks for a key press
				if (e.key.code == Keyboard::Escape) //Checks if key press is esc
					cpsWindow->close(); //Closes window when esc key is pressed
				break;
			}
		}
		// Clear the window
		cpsWindow->clear();

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
						clickTimer = 1.0f;
						settingsOpen = false;
					}
					else if (mediumButton.getGlobalBounds().contains(mousePosView))
					{
						clickTimer = 5.0f;
						settingsOpen = false;
					}
					else if (hardButton.getGlobalBounds().contains(mousePosView))
					{
						clickTimer = 15.0f;
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
			// Perform tasks when CPS test ends
			handleTestOver();
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (mouseHeld == false)
				{
					mouseHeld = true;
					if (replayButton.getGlobalBounds().contains(mousePosView))
					{
						cpsWindow->close();
						CpsTest playAgain;
						playAgain.playCpsTest();
					}
					else if (menuButton.getGlobalBounds().contains(mousePosView))
					{
						music.stop();
						cpsWindow->close();
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
		cpsWindow->display();
	}
	return 0;
}


