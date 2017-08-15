#include <iostream>
#include "Ship.h"
#include "Board.h"


int main()
{

	Board* b = new Board();

	Ship fourDecksShip = b->calcShipCoordinates(4);
	b->setShip(fourDecksShip);
	Ship threeDecksShipfirst = b->calcShipCoordinates(3);
	b->setShip(threeDecksShipfirst);
	Ship threeDecksShipSecond = b->calcShipCoordinates(3);
	b->setShip(threeDecksShipSecond);
	Ship twoDecksShipfirts = b->calcShipCoordinates(2);
	b->setShip(twoDecksShipfirts);
	Ship twoDecksShipSecond = b->calcShipCoordinates(2);
	b->setShip(twoDecksShipSecond);
	Ship twoDecksShipThird = b->calcShipCoordinates(2);
	b->setShip(twoDecksShipThird);
	Ship oneDecksShipfirts = b->calcShipCoordinates(1);
	b->setShip(oneDecksShipfirts);
	Ship oneDecksShipSecond = b->calcShipCoordinates(1);
	b->setShip(oneDecksShipSecond);
	Ship oneDecksShipThird = b->calcShipCoordinates(1);
	b->setShip(oneDecksShipThird);
	Ship oneDecksShipFourth = b->calcShipCoordinates(1);
	b->setShip(oneDecksShipFourth);

	b->display();

	delete b;

	system("pause");
	return 0;
}