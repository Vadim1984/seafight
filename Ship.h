/************************
 * will be used in Model
 ************************/

#pragma once

class Ship
{
public:
	Ship(int, int, int, int, int);
	~Ship();

	inline int Ship::getShipSize() const
	{
		return this->size_;
	}
	inline int Ship::getShipStartX() const
	{
		return this->startX_;
	}
	inline int Ship::getShipEndX() const
	{
		return this->endX_;
	}
	inline int Ship::getShipStartY() const
	{
		return this->startY_;
	}
	inline int Ship::getShipEndY() const
	{
		return this->endY_;
	}

	inline bool Ship::isShipLive() const
	{
		return this->isLive_;
	}

	bool damage(int, int);
	void displayShipInfo();

private:
	int size_;
	int startX_;
	int endX_;
	int startY_;
	int endY_;
	int nHits_;
	bool isLive_;
};

