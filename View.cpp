#include "View.h"



View::View()
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			matrix_[i][j] = ' ';
}

/************************************************************
 * 'refresh' - Refresh Board and View after player make step
 * @param board - pointer to board which will be shodew for players
 * @param y - Y coordinate of player step
 * @param x - X coordinate of player step
 ************************************************************/
void View::refresh(Board* board, int y, int x) {
	if (board->isHit(y, x)) {
		matrix_[y][x] = HIT_SHIP;
	}
	else {
		matrix_[y][x] = BESIDE_SHIP;
	}

	display();
}

/*************************************************
 * 'isStepPossible' - check if step was already done
 * @param y - Y coordinate of player step
 * @param x - X coordinate of player step
 *************************************************/
bool View::isStepPossible(int y, int x) {
	if (matrix_[y][x] == HIT_SHIP || matrix_[y][x] == BESIDE_SHIP) {
		return false;
	}
	else {
		return true;
	}
}

/*********************************
 * 'display' - Display play board
 *********************************/
void View::display()
{
	cout << "----------------------------------------" << endl;
	cout << "    A B C D E F G H I J" << endl << endl;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (j == 0) {
				cout << i << "   ";
			}
			cout << matrix_[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	cout << "----------------------------------------" << endl;
}

View::~View()
{
}
