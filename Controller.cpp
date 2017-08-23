#include "Controller.h"

Controller::Controller()
{
	computerBoard_ = new Board();
	playerBoard_ = new Board();
	computerView_ = new View();
	playerView_ = new View();
	srand(time(NULL));
}


/*****************************************
 * 'startGame' - func that start the game
 *****************************************/
void Controller::startGame() {

	while (!computerBoard_->isAllShipCrashed()) {

		playerStep();

		cout << "_____________________________________________________" << endl;
	}

	cout << "Congratulation! Tou are win! " << endl;
	cout << "Crashed ships count: " << computerBoard_->getCreashedShips() << endl;
	computerBoard_->display();
}

/*********************************************************
 * 'playerStep' - func that allow to make step for player
 *********************************************************/
void Controller::playerStep() {

	int x, y;

	cout << "Player, please make your step" << endl;
	cout << "input X from 0 to 9: ";
	cin >> x;
	cout << "input Y from 0 to 9: ";
	cin >> y;

	bool isXCorrect = x >= 0 && x <= 9;
	bool isYCorrect = y >= 0 && y <= 9;

	if (isXCorrect && isYCorrect) {
		computerView_->refresh(computerBoard_, y, x);
	}
	else if (!isXCorrect && !isYCorrect) {
		cout << "You've typed wrong X: " << x << ", and wrong Y: " << y << endl;
	}
	else if (!isXCorrect) {
		cout << "You've typed wrong X:" << x << endl;
	}
	else if (!isYCorrect) {
		cout << "You've typed wrong Y: " << y << endl;
	}
}

/************************************************
 * 'computerStep' - func that emulate step for pc
 ************************************************/
void Controller::computerStep() {                                          //TODO: finish this func

	int x, y;

	while (!playerBoard_->isAllShipCrashed()) {

		x = rand() % 10;
		y = rand() % 10;

		if (x >= 0 && x <= 9 && y >= 0 && y <= 9) {

			if (playerView_->isStepPossible(y, x)) {
				playerView_->refresh(playerBoard_, y, x);
			}
		}
	}
}

Controller::~Controller()
{
	delete computerBoard_;
	delete playerBoard_;
	delete computerView_;
	delete playerView_;
}
