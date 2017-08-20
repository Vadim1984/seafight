#pragma once
#include "Board.h"

class View
{
public:
	View();
	void refresh(Board* ,int ,int );
	bool isStepPossible(int ,int );
	~View();
private:
	static const int  SIZE = 10;
	static const char HIT_SHIP = 'X';
	static const char BESIDE_SHIP = 250;
	char matrix_[SIZE][SIZE];
	void display();

};

