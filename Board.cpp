#include "Board.h" 
#include "Ship.h"

using namespace std;

/*************************
 * 'Board' - Constructor
 *************************/
Board::Board()
{
	shipTypeCountMap_ = {
		{ "fourDecks",  1 },
	    { "threeDecks", 2 },
	    { "twoDecks",   3 },
	    { "oneDecks",   4 } 
	};

	shipsTypeSizeMap_ = {
		{ "fourDecks",  4 },
		{ "threeDecks", 3 },
		{ "twoDecks",   2 },
		{ "oneDecks",   1 }
	};

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			matrix_[i][j] = ' ';

	srand(time(NULL));

	nCrashedShips_ = 0;

	ships_.reserve(10);

	// set ships coordinates according to ship count and ship size, setted in maps: shipsCountMap_, shipsSizeMap_
	for each(pair<string, int> countShips in shipTypeCountMap_) {
		for (int i = 0; i < countShips.second; i++) {
			ships_.push_back(computeShipCoord(shipsTypeSizeMap_[countShips.first]));
		}
	}

	display();
}

Board::~Board()
{
}



/****************************************************************************************************
 * 'computeShipCoord' - In loop create random coordinates and random direction for the setting ship.
 *                      Analyze if no ship near current ship.
 * @param shipSize    - size of ship for which will be computed coordinates
 * @return const Ship - return Ship object
 ****************************************************************************************************/
const Ship Board::computeShipCoord(int shipSize)
{
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

        wasUP = false;
        wasDOWN = false;
		wasLEFT = false;
		wasRIGHT = false;

		while ((!wasUP || !wasDOWN || !wasLEFT || !wasRIGHT) && !shipSetted ) {
			int direction = rand() % 4;
			int range;

			switch (direction) {
			  case UP: 
				wasUP = true;
				range = startY - shipSize + 1;
				shipSetted = isSetShipV(matrix_, startX, startY, range);
				if (shipSetted) {
					endY = range;
					endX = startX;
				}
				break;       
			  case DOWN: 
				wasDOWN = true;
				range = startY + shipSize - 1;
				shipSetted = isSetShipV(matrix_, startX, startY, range);
				if (shipSetted) {
					endY = range;
					endX = startX;
				}
				break;
			  case LEFT: 
				wasLEFT = true;
				range = startX - shipSize + 1;
				shipSetted = isSetShipH(matrix_, startX, startY, range);
				if (shipSetted) {
					endX = range;
					endY = startY;
				}
				break;
			  case RIGHT: 
				wasRIGHT = true;
				range = startX + shipSize - 1;
				shipSetted = isSetShipH(matrix_, startX, startY, range);
				if (shipSetted) {
					endX = range;
					endY = startY;
				}
				break;
			}
		}
	}

	Ship ship = Ship(shipSize, startX, endX, startY, endY);

	setShip(ship);

	return ship;
}


/**********************************************************
 * 'setShip' - Set ship to play board by it's coorninates
 * @param Ship& reference to the Ship object
 **********************************************************/
void Board::setShip(const Ship& CurrentShip) {

	int startX = CurrentShip.getShipStartX();
	int endX = CurrentShip.getShipEndX();
	int startY = CurrentShip.getShipStartY();
	int endY = CurrentShip.getShipEndY();

	if (startX == endX && startY < endY) {
		for (int i = startY; i <= endY; i++)
			matrix_[i][startX] = SHIP;
	}
	else if (startX == endX && startY > endY) {
		for (int i = endY; i <= startY; i++)
			matrix_[i][startX] = SHIP;
	}
	else if (startY == endY && startX < endX) {
		for (int j = startX; j <= endX; j++)
			matrix_[startY][j] = SHIP;
	}
	else if (startY == endY && startX > endX) {
		for (int j = endX; j <= startX; j++)
			matrix_[startY][j] = SHIP;
	}
	else if (startY == endY && startX == endX) {
		matrix_[startY][startX] = SHIP;
	}
}

/**************************************************************************************
 * 'isSetShipV' - Check possibility of set ship vertical
 * @param matrix[SIZE][SIZE] - matrix which used for analize posibility of set ship
 * @param startX             - X coordinate of start ship
 * @param startY             - Y coordinate of start ship
 * @param endY               - Y coordinate of end ship
 * @return bool              - true if set ship possible otherwise false
 **************************************************************************************/
bool Board::isSetShipV(char matrix[SIZE][SIZE], int startX, int startY, int endY)
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

/**************************************************************************************
 * 'isSetShipH' - Check possibility of set ship horisontal
 * @param matrix[SIZE][SIZE] - matrix which used for analize posibility of set ship
 * @param startX             - X coordinate of start ship
 * @param startY             - Y coordinate of start ship
 * @param endX               - X coordinate of end ship
 * @return bool              - true if set ship possible otherwise false
 **************************************************************************************/
bool Board::isSetShipH(char matrix[SIZE][SIZE], int startX, int startY, int endX)
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


/**********************************
 * 'display' - Display play board
 **********************************/
void Board::display()
{
	cout << "----------------------------------------" <<  endl;
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

/**********************************************************
 * 'isHit' - Check if player hit the ship
 * @param y     - Y coordinate of player step
 * @param x     - X coordinate of player step
 * @return bool - true if player hit the ship, else false
 **********************************************************/
bool Board::isHit(int y, int x) {

	bool hit;

	if (matrix_[y][x] == SHIP) {
		hit = true;
		matrix_[y][x] = HIT_SHIP;
		notifyShip(y, x);
	}
	else {
		hit = false;
	}

	return hit;
}


/*******************************************************************
 * 'notifyShip' - Find and notify damaged ship to update ship state
 *                If whole ship is crashed then increment counter
 * @param y - Y coordinate of player step
 * @param x - X coordinate of player step
 *******************************************************************/
void Board::notifyShip(int y, int x) {

	for (int i = 0; i < ships_.size(); i++)
	{
		if (ships_[i].isShipLive()) {
			ships_[i].damage(y, x);
			
			if (!ships_[i].isShipLive()) {
				++nCrashedShips_;
			}
		}
	}
}

/******************************************************************************************
 * 'isAllShipCrashed' - Check if All ships are crashed
 * @return bool - true if All ships some of player are already crashed, else return false
 ******************************************************************************************/
bool Board::isAllShipCrashed() {

	if (nCrashedShips_ == ships_.size()) {
		return true;
	}
	else{
		return false;
	}

}





