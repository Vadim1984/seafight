#include "Ship.h"
#include <iostream>

using namespace std;

/********************************************
 * Constructor set ship size and coordinates
 ********************************************/
Ship::Ship(int size, int startX, int endX, int startY, int endY)
{
	this->size = size;
	this->startX = startX;
	this->endX = endX;
	this->startY = startY;
	this->endY = endY;
}


Ship::~Ship()
{
}

/************************************
 * Getters ship size and coordinates
 ************************************/

int Ship::getShipSize()
{
	return this->size;
}
int Ship::getShipStartX() const
{
	return this->startX;
}
int Ship::getShipEndX() const
{
	return this->endX;
}
int Ship::getShipStartY() const
{
	return this->startY;
}
int Ship::getShipEndY() const
{
	return this->endY;
}

void Ship::displayShipInfo() {
	cout << "*******  Ship info: **********"  << endl;
	cout << "*     size   = " << this->size   << endl;
	cout << "*     startX = " << this->startX << endl;
	cout << "*     endX   = " << this->endX   << endl;
	cout << "*     startY = " << this->startY << endl;
	cout << "*     endY   = " << this->endY   << endl;
	cout << "******************************"  << endl;
}



