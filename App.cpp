#include <iostream>
#include "Controller.h"

int main()
{

	Controller* c = new Controller();
	c->startGame();

	delete c;

	system("pause");
	return 0;
}