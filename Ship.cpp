#include "Ship.h"
#include <iostream>

using namespace std;

/******************************************************
 * 'Ship' - Constructor set ship size and coordinates
 * @param size   - size of Ship
 * @param startX - X coordinate of start ship
 * @param endX   - X coordinate of end ship
 * @param startY - Y coordinate of start ship
 * @param endY   - Y coordinate of end ship
 ******************************************************/
Ship::Ship(int size, int startX, int endX, int startY, int endY)
{
	this->size_ = size;
	this->startX_ = startX;
	this->endX_ = endX;
	this->startY_ = startY;
	this->endY_ = endY;
	this->isLive_ = true;
	this->nHits_ = 0;
}


Ship::~Ship()
{
}


/***********************************************************************
 * 'damage' - check if: 
 *            1) is current ship is damaged 
 *            2) is ship fully or partial damaged and set apropriate indicator
 *
 * @param y     - Y coordinate of player step
 * @param x     - X coordinate of player step
 * @return bool - true if player hit the ship, else false
 ***********************************************************************/
bool Ship::damage(int y, int x) {

	bool shipDamaged = false;

	if (x >= startX_ && x <= endX_ && y >= startY_ && y <= endY_) {
		shipDamaged = true;
		++nHits_;
	}

	if (nHits_ == size_) {
		isLive_ = false;
	}

	return shipDamaged;
}

/***********************************************************************
 * 'displayShipInfo' - Display ship related information 
 ***********************************************************************/
void Ship::displayShipInfo() {
	cout << "*******  Ship info: **********" << endl;
	cout << "*     size   = " << this->size_ << endl;
	cout << "*     startX = " << this->startX_ << endl;
	cout << "*     endX   = " << this->endX_ << endl;
	cout << "*     startY = " << this->startY_ << endl;
	cout << "*     endY   = " << this->endY_ << endl;
	cout << "******************************" << endl;
}



