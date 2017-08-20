#include "Ship.h"
#include <iostream>

using namespace std;

/********************************************
 * Constructor set ship size and coordinates
 ********************************************/
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
 * This func check if: 
 * 1) is current ship is damaged 
 * 2) is ship fully or partial damaged and set apropriate indicator
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
 * Display ship related information 
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



