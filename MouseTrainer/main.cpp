//// MAIN FILE FOR PROGRAM EXECUTION ////

#include "Menu.h"

//SFML libraries for graphical display

int main()
{
	// Init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	// Init game menus
	Menu menu;
	menu.runMenu();


	return 0;
}