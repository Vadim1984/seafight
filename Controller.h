#pragma once

#include <ctime>
#include "Board.h"
#include "Ship.h"
#include "View.h"

class Controller
{
public:
	Controller();
	void startGame();
	~Controller();

private:
	Board* computerBoard_;
	Board* playerBoard_;
	View* computerView_;
	View* playerView_;
	void computerStep();
	void playerStep();
};

