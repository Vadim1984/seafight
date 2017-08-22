/*************************
 * will be used as Model
 *************************/

#pragma once
#include <iostream>
#include <ctime>
#include <map>
#include <vector>
#include "Ship.h"

using namespace std;

class Board
{

public:
	Board();
	~Board();
	bool isAllShipCrashed();
	void display();
	bool isHit(int, int);
	inline int getCreashedShips() const
	{
		return this->nCrashedShips_;
	}

private:
	static const int  SIZE = 10;
	static const char SHIP = 254;
	static const char HIT_SHIP = 'X';
	char matrix_[SIZE][SIZE];
	map <string, int> shipTypeCountMap_;
	map <string, int> shipsTypeSizeMap_;
	vector<Ship> ships_;
	int nCrashedShips_;

	bool isSetShipV(char[SIZE][SIZE], int, int, int);
	bool isSetShipH(char[SIZE][SIZE], int, int, int);
	const Ship computeShipCoord(int);
	void setShip(const Ship&);
	void notifyShip(int x, int y);


};