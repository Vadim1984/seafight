/*
* will be used as Model
*/

#pragma once

class Ship
{
private:
	int size;
	int startX;
	int endX;
	int startY;
	int endY;
public:
	Ship(int, int, int, int, int);
	~Ship();
	int getShipSize();
	int getShipStartX() const;
	int getShipEndX() const;
	int getShipStartY() const;
	int getShipEndY() const;
	void displayShipInfo();
};

