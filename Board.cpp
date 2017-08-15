#include "Board.h" 
#include "Ship.h"

using namespace std;

/**************
 * Constructor
 **************/
Board::Board()
{
	shipsMap = { 
		           { "fourDecks",  1 },
	               { "threeDecks", 2 },
	               { "twoDecks",   3 },
	               { "oneDecks",   4 } 
	};

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			matrix[i][j] = ' ';

	srand(time(NULL));
}

Board::~Board()
{
}



/********************************************************************************
 * In loop create random coordinates and random direction for the setting ship.
 * Analyze if no ship near current ship.
 ********************************************************************************/
const Ship Board::calcShipCoordinates(int shipSize)
{
	cout << "shipSize: " << shipSize << endl;

	const int UP = 0;
	const int RIGHT = 1;
	const int DOWN = 2;
	const int LEFT = 3;
	

	int startX, startY, endX, endY;
	bool wasUP, wasDOWN, wasLEFT, wasRIGHT;
	bool shipSetted = false;

	while (!shipSetted) {

		startX = rand() % 10;
		startY = rand() % 10;
		cout << "  startX: " << startX << endl;
		cout << "  startY: " << startY << endl;
		wasUP = false;
		wasDOWN = false;
		wasLEFT = false;
		wasRIGHT = false;

			while ((!wasUP || !wasDOWN || !wasLEFT || !wasRIGHT) && !shipSetted ) {
				int direction = rand() % 4;
				int range;

				cout << "     direction: " << direction << endl;

				switch (direction) {
				case UP: 
					wasUP = true;
					range = startY - shipSize + 1;
					shipSetted = setShipVertical(matrix, startX, startY, range);
					if (shipSetted) {
						endY = range;
						endX = startX;
					}
					break;       
				case DOWN: 
					wasDOWN = true;
					range = startY + shipSize - 1;
					shipSetted = setShipVertical(matrix, startX, startY, range);
					if (shipSetted) {
						endY = range;
						endX = startX;
					}
					break;
				case LEFT: 
					wasLEFT = true;
					range = startX - shipSize + 1;
					shipSetted = setShipHorizontal(matrix, startX, startY, range);
					if (shipSetted) {
						endX = range;
						endY = startY;
					}
					break;
				case RIGHT: 
					wasRIGHT = true;
					range = startX + shipSize - 1;
					shipSetted = setShipHorizontal(matrix, startX, startY, range);
					if (shipSetted) {
						endX = range;
						endY = startY;
					}
					break;
				}


				cout << "     shipSetted: " << shipSetted << endl;
				cout << "     wasUP: " << wasUP << endl;
				cout << "     wasDOWN: " << wasDOWN << endl;
				cout << "     wasLEFT: " << wasLEFT << endl;
				cout << "     wasRIGHT: " << wasRIGHT << endl;
				cout << "     *********************** " << endl;
		}

	}

	cout << "  *********************** " << endl;



	cout << "=> startX: " << startX << endl;
	cout << "=> endX: " << endX << endl;
	cout << "=> startY: " << startY << endl;
	cout << "=> endY: " << endY << endl;
	cout << "=> shipSize: " << shipSize << endl;
	cout << "********************************************************************************* " << endl;

	return Ship(shipSize, startX, endX, startY, endY);
}


/**********************************************
 * Set ship to play board by it's coorninates
 **********************************************/
void Board::setShip(const Ship& ship) {
	// set ship!!!!
	int startX = ship.getShipStartX();
	int endX = ship.getShipEndX();
	int startY = ship.getShipStartY();
	int endY = ship.getShipEndY();

	if (startX == endX && startY < endY) {
		for (int i = startY; i <= endY; i++)
			matrix[i][startX] = SHIP;
	}
	else if (startX == endX && startY > endY) {
		for (int i = endY; i <= startY; i++)
			matrix[i][startX] = SHIP;
	}
	else if (startY == endY && startX < endX) {
		for (int j = startX; j <= endX; j++)
			matrix[startY][j] = SHIP;
	}
	else if (startY == endY && startX > endX) {
		for (int j = endX; j <= startX; j++)
			matrix[startY][j] = SHIP;
	}
	else if (startY == endY && startX == endX) {
		matrix[startY][startX] = SHIP;
	}
}

/******************************************
 * Check possibility of set ship vertical
 ******************************************/
bool Board::setShipVertical(char matrix[SIZE][SIZE], int startX, int startY, int endY)
{
	bool shipSetted = true;

	if (endY >= SIZE || endY < 0)
		return false;

	int begin, end;

	if (startY < endY) {               /* case when ship is setted DOWN */
		begin = startY;
		end = endY;
	}
	else if (startY > endY) {          /* case when ship is setted UP */
		begin = endY;
		end = startY;
	}
	else {
		begin = end = startY;
	}

	if (startY > 0 && endY < SIZE - 1 && startX > 0 && startX < SIZE - 1) {
		for (int i = begin - 1; i <= end + 1; i++) {
			if (matrix[i][startX] == SHIP || matrix[i][startX - 1] == SHIP || matrix[i][startX + 1] == SHIP) {
				return false;
			}
		}
	}
	else if (startY == 0 && startX > 0 && startX < SIZE - 1) {
		for (int i = begin; i <= end + 1; i++) {
			if (matrix[i][startX] == SHIP || matrix[i][startX - 1] == SHIP || matrix[i][startX + 1] == SHIP) {
				return false;
			}
		}

	}
	else if (startY == 0 && startX == 0) {
		for (int i = begin; i <= end + 1; i++) {
			if (matrix[i][startX] == SHIP || matrix[i][startX + 1] == SHIP) {
				return false;
			}
		}

	}
	else if (startY == 0 && startX == SIZE - 1) {
		for (int i = begin; i <= end + 1; i++) {
			if (matrix[i][startX] == SHIP || matrix[i][startX - 1] == SHIP) {
				return false;
			}
		}

	}
	else if (endY == SIZE - 1 && startX > 0 && startX < SIZE - 1) {
		for (int i = begin - 1; i <= end; i++) {
			if (matrix[i][startX] == SHIP || matrix[i][startX - 1] == SHIP || matrix[i][startX + 1] == SHIP) {
				return false;
			}
		}

	}
	else if (endY == SIZE - 1 && startX == 0) {
		for (int i = begin - 1; i <= end; i++) {
			if (matrix[i][startX] == SHIP || matrix[i][startX + 1] == SHIP) {
				return false;
			}
		}

	}
	else if (endY == SIZE - 1 && startX == SIZE - 1) {
		for (int i = begin - 1; i <= end; i++) {
			if (matrix[i][startX] == SHIP || matrix[i][startX - 1] == SHIP) {
				return false;
			}
		}

	}
	else if (startY > 0 && endY < SIZE - 1 && startX == 0) {
		for (int i = begin - 1; i <= end + 1; i++) {
			if (matrix[i][startX] == SHIP || matrix[i][startX + 1] == SHIP) {
				return false;
			}
		}

	}
	else if (startY > 0 && endY < SIZE - 1 && startX == SIZE - 1) {
		for (int i = begin - 1; i <= end + 1; i++) {
			if (matrix[i][startX] == SHIP || matrix[i][startX - 1] == SHIP) {
				return false;
			}
		}

	}

	return shipSetted;
}

/***********************************************
 * Check possibility of set ship horisontal
 **********************************************/
bool Board::setShipHorizontal(char matrix[SIZE][SIZE], int startX, int startY, int endX)
{
	bool shipSetted = true;

	if (endX >= SIZE || endX < 0)
		return false;

	int begin, end;

	if (startX < endX) {           /* case when ship is setted LEFT */
		begin = startX;
		end = endX;
	}
	else if (startX > endX) {      /* case when ship is setted RIGHT */
		begin = endX;
		end = startX;
	}
	else {
		begin = end = startX;
	}

	if (startX > 0 && endX < SIZE - 1 && startY > 0 && startY < SIZE - 1) {
		for (int j = begin - 1; j <= end + 1; j++) {
			if (matrix[startY][j] == SHIP || matrix[startY - 1][j] == SHIP || matrix[startY + 1][j] == SHIP) {
				return false;
			}
		}
	}
	else if (startY == 0 && startX > 0 && startX < SIZE - 1) {
		for (int j = begin - 1; j <= end + 1; j++) {
			if (matrix[startY][j] == SHIP || matrix[startY + 1][j] == SHIP) {
				return false;
			}
		}

	}
	else if (startY == 0 && startX == 0) {
		for (int j = begin; j <= end + 1; j++) {
			if (matrix[startY][j] == SHIP || matrix[startY + 1][j] == SHIP) {
				return false;
			}
		}

	}
	else if (endX == SIZE - 1 && startY == 0) {
		for (int j = begin - 1; j <= end; j++) {
			if (matrix[startY][j] == SHIP || matrix[startY + 1][j] == SHIP) {
				return false;
			}
		}

	}
	else if (startX > 0 && endX < SIZE - 1 && startY == SIZE - 1) {
		for (int j = begin - 1; j <= end + 1; j++) {
			if (matrix[startY][j] == SHIP || matrix[startY - 1][j] == SHIP) {
				return false;
			}
		}

	}
	else if (startX == 0 && startY == SIZE - 1) {
		for (int j = begin; j <= end + 1; j++) {
			if (matrix[startY][j] == SHIP || matrix[startY - 1][j] == SHIP) {
				return false;
			}
		}

	}
	else if (endX == SIZE - 1 && startY == SIZE - 1) {
		for (int j = begin - 1; j <= end; j++) {
			if (matrix[startY][j] == SHIP || matrix[startY - 1][j] == SHIP) {
				return false;
			}
		}

	}
	else if (startX == 0 && startY > 0 && startY < SIZE - 1) {
		for (int j = begin; j <= end + 1; j++) {
			if (matrix[startY][j] == SHIP || matrix[startY - 1][j] == SHIP || matrix[startY + 1][j] == SHIP) {
				return false;
			}
		}

	}
	else if (endX == SIZE - 1 && startY > 0 && startY < SIZE - 1) {
		for (int j = begin - 1; j <= end; j++) {
			if (matrix[startY][j] == SHIP || matrix[startY - 1][j] == SHIP || matrix[startY + 1][j] == SHIP) {
				return false;
			}
		}

	}

	return shipSetted;
}


/************************
 * Display play board
 ***********************/
void Board::display()
{
	cout << "----------------------------------------" <<  endl;
	cout << "    A B C D E F G H I J" << endl << endl;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (j == 0) {
				cout << i << "   ";
			}
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	cout << "----------------------------------------" << endl;
}

/*******************************
 * Check if player hit the ship
 *******************************/
bool Board::isHit(int x, int y) {

	bool hit;

	if (matrix[y][x] == SHIP) {
		hit = true;
	}
	else {
		hit = false;
	}

	return hit;
}





