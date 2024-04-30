//// IMPLEMENTATION FILE FOR GAME MENU CLASS ////

#include "Menu.h"

// Private functions

void Menu::initVariables()
{
    //Set menuWindow pointer to null
    menuWindow = nullptr;

    // Menu logic
    mouseHeld = false;
}

void Menu::initWindow()
{
    // Initialize variables for window dimensions
    videoMode.height = 700;
    videoMode.width = 1300;

    // Assign SFML RenderWindow to menuWindow pointer
    menuWindow = new RenderWindow(videoMode, "Mouse Training in Progress!", Style::Default);
    menuWindow->setFramerateLimit(60); // Set FPS to 60
}

void Menu::initMenuButtons()
{
    // Game button for falling shapes (game button 1)
    gameButton1.setPosition(65.f, 400.f);
    gameButton1.setSize(Vector2f(244.f, 250.f));
    gameButton1.setFillColor(Color(25, 25, 25));
    gameButton1.setOutlineThickness(-13.f);
    gameButton1.setOutlineColor(Color::Cyan);

    // Game button for random circles (game button 2)
    gameButton2.setPosition(374.f, 400.f);
    gameButton2.setSize(Vector2f(244.f, 250.f));
    gameButton2.setFillColor(Color(25, 25, 25));
    gameButton2.setOutlineThickness(-13.f);
    gameButton2.setOutlineColor(Color::Magenta);

    //Game button for CPS test (game button 3)
    gameButton3.setPosition(683.f, 400.f);
    gameButton3.setSize(Vector2f(244.f, 250.f));
    gameButton3.setFillColor(Color(25, 25, 25));
    gameButton3.setOutlineThickness(-13.f);
    gameButton3.setOutlineColor(Color::Green);

    //Game button for precision targets (game button 4)
    gameButton4.setPosition(992.f, 400.f);
    gameButton4.setSize(Vector2f(244.f, 250.f));
    gameButton4.setFillColor(Color(25, 25, 25));
    gameButton4.setOutlineThickness(-13.f);
    gameButton4.setOutlineColor(Color::Red);

}

void Menu::initFont()
{
    // Assign a font file to "font"
    if (!font.loadFromFile("Fonts/calibri.ttf"))
    {
        std::cerr << "ERROR::GAME::INITFONT::Failed to load font!" << "\n";
        // Output an error if font does not load
    }

    if (!music.openFromFile("Audio/menusong.mp3"))
        std::cerr << "ERROR::GAME::INITFONT::Failed to load music!" << "\n";
    // Output an error if music does not load
    music.play();
    music.setLoop(true);
}

void Menu::initText()
{
    // Text for button 1
    button1Text.setFont(font);
    button1Text.setCharacterSize(45);
    button1Text.setFillColor(Color::Cyan);
    button1Text.setString("Falling \nShapes");
    button1Text.setPosition(120.f, 470.f);

    // Text for button 2
    button2Text.setFont(font);
    button2Text.setCharacterSize(45);
    button2Text.setFillColor(Color::Magenta);
    button2Text.setString("Random \n Circles!");
    button2Text.setPosition(420.f, 470.f);

    // Text for button 3
    button3Text.setFont(font);
    button3Text.setCharacterSize(45);
    button3Text.setFillColor(Color::Green);
    button3Text.setString(" CPS \nTest!");
    button3Text.setPosition(758.f, 470.f);

    // Text for button 4
    button4Text.setFont(font);
    button4Text.setCharacterSize(45);
    button4Text.setFillColor(Color::Red);
    button4Text.setString("Precision \n Trainer!");
    button4Text.setPosition(1030.f, 470.f);
}

void Menu::initTexture()
{
    // Assign a png file to "titleScreenTexture"
    if (!titleScreenTexture.loadFromFile("Images/MaxsMouseTrainer1.png"))
    {
        std::cout << "ERROR::GAME::INITTEXTURE::Failed to load texture!" << "\n";
        // Output error if image fails to load
    }
    titleScreenTexture.setSmooth(true);
    titleScreen.setTexture(titleScreenTexture); // Assign the texture to a sprite
    titleScreen.setScale(Vector2f(1.1f, 1.1f)); // Adjust sprite scale
    titleScreen.setPosition(Vector2f(-1200.f, 40.f));

    // Assign a jpg file to "bkgMenu"
    if (!bkgMenu.loadFromFile("Images/menubkg.jpg"))
    {
        std::cout << "ERROR::GAME::INITTEXTURE::Failed to load texture!" << "\n";
        // Output error if image fails to load
    }
    bkgMenu.setSmooth(true);
    bkg.setTexture(bkgMenu); // Assign the texture to a sprite
    bkg.setScale(Vector2f(.7f, .65f)); // Adjust sprite scale
}

// Constructor // Destructor //
Menu::Menu()
{
    // Initialize private functions and objects
    initVariables();
    initWindow();
    initMenuButtons();
    initFont();
    initText();
    initTexture();
}

Menu::~Menu()
{
    // Destoy "menuWindow" ptr and deallocate its memory 
    delete menuWindow;
}

//Functions

// Update moving menu objects
void Menu::updateObjects()
{
    // Updates "titleScreen" position till centered
    if (titleScreen.getPosition().x <= 45.f)
    {
        titleScreen.move(Vector2f(30.f, 0.f));
    }

    // Updates mouse positions
    mousePosWindow = Mouse::getPosition(*menuWindow);
    mousePosView = menuWindow->mapPixelToCoords(mousePosWindow);
}

// Display menu objects to the window
void Menu::renderObjects()
{
    // Draw menu background
    menuWindow->draw(bkg);

    // Draw game buttons 
    menuWindow->draw(gameButton1);
    menuWindow->draw(gameButton2);
    menuWindow->draw(gameButton3);
    menuWindow->draw(gameButton4);

    // Draw game button text
    menuWindow->draw(button1Text);
    menuWindow->draw(button2Text);
    menuWindow->draw(button3Text);
    menuWindow->draw(button4Text);

    // Draw title screen icon
    menuWindow->draw(titleScreen);
}


///// PREFORMS ALL MENU FUNCTIONS /////

int Menu::runMenu()
{
    // Perform actions while menuWindow is open
    while (menuWindow->isOpen())
    {
        // Handle events or perform other actions
        while (menuWindow->pollEvent(e))
        {
            switch (e.type)
            {
            case Event::Closed:
                menuWindow->close(); // Closes the window when exit button is clicked
                break;
            case Event::KeyPressed: //Checks for a key press
                if (e.key.code == Keyboard::Escape) //Checks if key press is esc
                    menuWindow->close(); //Closes window when esc key is pressed
                break;
            }
        }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (mouseHeld == false)
            {
                mouseHeld = true;
                if (gameButton1.getGlobalBounds().contains(mousePosView))
                {
                    music.stop();
                    menuWindow->close();
                    FallingShapes fallingShapes;
                    fallingShapes.playFallingShapes();
                }
                else if (gameButton2.getGlobalBounds().contains(mousePosView))
                {
                    music.stop();
                    menuWindow->close();
                    RandomCircles randomCircles;
                    randomCircles.playRandomCircles();
                }
                else if (gameButton3.getGlobalBounds().contains(mousePosView))
                {
                    music.stop();
                    menuWindow->close();
                    CpsTest cpsTest;
                    cpsTest.playCpsTest();
                }
                else if (gameButton4.getGlobalBounds().contains(mousePosView))
                {
                    music.stop();
                    menuWindow->close();
                    PrecisionTargets precisionTargets;
                    precisionTargets.playPrecisionTargets();
                }
            }
        }
        else
        {
            mouseHeld = false;
        }
        // Clear the window
        menuWindow->clear();

        // Update menu objects
        updateObjects();

        // Render menu objects
        renderObjects();

        // Display the window
        menuWindow->display();
    }

    return 0;
}
