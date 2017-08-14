#include <iostream>
#include <ctime>
#include <map>

using namespace std;

class Board
{
private:
	static const int SIZE = 10;
	static const char SHIP = 'X';
	char matrix[SIZE][SIZE];
	map <string, int> shipsMap;


public:
	Board();
	~Board();
	void setShip(int);
	void display();
	bool setShipVertical(char[SIZE][SIZE], int, int, int);
	bool setShipHorizontal(char[SIZE][SIZE], int, int, int);
};

Board::Board()
{
	shipsMap = { 
		           { "fourDecks", 1 },
	               { "threeDecks", 2 },
	               { "twoDecks", 3 },
	               { "oneDecks", 4 } 
	};

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			matrix[i][j] = ' ';

	srand(time(NULL));
}

Board::~Board()
{
}

void Board::setShip(int shipSize)
{
	/*
      1 корабль Ч р€д из 4 клеток (ЂчетырЄхпалубныеї)
      2 корабл€ Ч р€д из 3 клеток (ЂтрЄхпалубныеї)
      3 корабл€ Ч р€д из 2 клеток (Ђдвухпалубныеї)
      4 корабл€ Ч 1 клетка (Ђоднопалубныеї)
	*/
	cout << "shipSize: " << shipSize << endl;

	const int UP = 0;
	const int DOWN = 2;
	const int LEFT = 3;
	const int RIGHT = 1;

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

	// set ship!!!!
	if (startX == endX && startY < endY) {
		for (int i = startY; i <= endY; i++)
			matrix[i][startX] = SHIP;
	}
	else if (startX == endX && startY > endY) {
		for (int i = endY; i <= startY; i++)
			matrix[i][startX] = SHIP;
	}
	else if(startY == endY && startX < endX) {
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

	cout << "=> startX: " << startX << endl;
	cout << "=> endX: " << endX << endl;
	cout << "=> startY: " << startY << endl;
	cout << "=> endY: " << endY << endl;
	cout << "=> shipSize: " << shipSize << endl;
	cout << "********************************************************************************* " << endl;
}

bool Board::setShipVertical(char matrix[SIZE][SIZE], int startX, int startY, int endY)
{
	bool shipSetted = true;

	if (endY >= SIZE || endY < 0)
		return false;

	int begin, end;

	if (startY < endY) {
		begin = startY;
		end = endY;
	}
	else if (startY > endY) {
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


bool Board::setShipHorizontal(char matrix[SIZE][SIZE], int startX, int startY, int endX)
{
	bool shipSetted = true;

	if (endX >= SIZE || endX < 0)
		return false;

	int begin, end;

	if (startX < endX) {
		begin = startX;
		end = endX;
	}
	else if (startX > endX) {
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


int main()
{
	
	Board* b = new Board();
	b->setShip(4);
	b->setShip(3);
	b->setShip(3);
	b->setShip(2);
	b->setShip(2);
	b->setShip(2);
	b->setShip(1);
	b->setShip(1);
	b->setShip(1);
	b->setShip(1);
	b->display();
	delete b;

	system("pause"); 
	return 0;
}



