/*
 * will be used as View
 */

#pragma once
#include <iostream>
#include <ctime>
#include <map>
#include "Ship.h"

using namespace std;

class Board
{
private:
	static const int SIZE = 10;
	static const char SHIP = 'X';
	char matrix[SIZE][SIZE];
	map <string, int> shipsMap;
	bool setShipVertical(char[SIZE][SIZE], int, int, int);
	bool setShipHorizontal(char[SIZE][SIZE], int, int, int);

public:
	Board();
	~Board();
	const Ship calcShipCoordinates(int);
	void setShip(const Ship&);
	void display();
	bool isHit(int, int);

};