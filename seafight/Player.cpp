#include <iostream>
#include <ctime>
#include <map>

using namespace std;

class Board
{
public:
	Board();
	~Board();
	void setShip(int);
	void display();
	bool setShipVertical(char**, int, int, int);
	bool setShipHorizontal(char**, int, int, int);

private:
	static const int SIZE = 10;
	static const char SHIP = 'X';
	char matrix[SIZE][SIZE];
	map <string, int> shipsMap;
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
		/*cout << "startX: " << startX << endl;
		cout << "startY: " << startY << endl;*/
		wasUP = false;
		wasDOWN = false;
		wasLEFT = false;
		wasRIGHT = false;

			while (!shipSetted && (!wasUP || !wasDOWN || !wasLEFT || !wasRIGHT)) {
				int direction = rand() % 4;
				int range;

				//cout << "direction: " << direction << endl;

				switch (direction) {
				case UP: 
					wasUP = true;
					range = startY + shipSize;
					if (range < SIZE) {
						if ((startY > 0 && matrix[startY-1][startX] != SHIP) || (range < SIZE - 1 && matrix[range + 1][startX] != SHIP)) {
							for (int i = startY; i <= range; i++) {
								if (matrix[i][startX] == SHIP) {
									shipSetted = false;
									break;
								}
								else if (startX > 0 && startX < SIZE - 1) {
									if (matrix[i][startX - 1] == SHIP || matrix[i][startX + 1] == SHIP) {
										shipSetted = false;
										break;
									}
								}
								else {
									shipSetted = true;
								}
							}
						}
						if (shipSetted) {
							endY = range;
							endX = startX;
						}
					}
					break;       
				case DOWN: 
					wasDOWN = true;
					range = startY - shipSize;
					if (range < SIZE) {
						if ((startY > 0 && matrix[startY - 1][startX] != SHIP) || (range < SIZE - 1 && matrix[range + 1][startX] != SHIP)) {
							for (int i = startY; i <= range; i++) {
								if (matrix[i][startX] == SHIP) {
									shipSetted = false;
									break;
								}
								else if (startX > 0 && startX < SIZE - 1) {
									if (matrix[i][startX - 1] == SHIP || matrix[i][startX + 1] == SHIP) {
										shipSetted = false;
										break;
									}
								}
								else {
									shipSetted = true;
								}
							}
						}
						if (shipSetted) {
							endY = range;
							endX = startX;
						}
					}
					break;
				case LEFT: 
					wasLEFT = true;
					range = startX - shipSize;
					if (range < SIZE) {
						if ((startX > 0 && matrix[startY][startX - 1] != SHIP) || (range < SIZE - 1 && matrix[startY][range + 1] != SHIP)) {
							for (int j = startX; j <= range; j++) {
								if (matrix[startY][j] == SHIP) {
									shipSetted = false;
									break;
								}
								else if (startY > 0 && startY < SIZE - 1) {
									if (matrix[startY - 1][j] == SHIP || matrix[startY + 1][j] == SHIP) {
										shipSetted = false;
										break;
									}
								}
								else {
									shipSetted = true;
								}
							}
						}
						if (shipSetted) {
							endX = range;
							endY = startY;
						}
					}
					break;
				case RIGHT: 
					wasRIGHT = true;
					range = startX + shipSize;
					if ( range < SIZE) {
						if ((startX > 0 && matrix[startY][startX - 1] != SHIP) || (range < SIZE - 1 && matrix[startY][range + 1] != SHIP)) {
							for (int j = startX; j <= range; j++) {
								if (matrix[startY][j] == SHIP) {
									shipSetted = false;
									break;
								}
								else if (startY > 0 && startY < SIZE - 1) {
									if (matrix[startY - 1][j] == SHIP || matrix[startY + 1][j] == SHIP) {
										shipSetted = false;
										break;
									}
								}
								else {
									shipSetted = true;
								}
							}
						}
						if (shipSetted) {
							endX = range;
							endY = startY;
						}
					}
					break;
				}
		}

	}
	/*cout << "wasUP: " << wasUP << endl;
	cout << "wasDOWN: " << wasDOWN << endl;
	cout << "wasLEFT: " << wasLEFT << endl;
	cout << "wasRIGHT: " << wasRIGHT << endl;*/

	// set ship!!!!
	if (startX == endX) {
		for (int i = startY; i < endY; i++)
			matrix[i][startX] = SHIP;
	}else if(startY == endY) {
		for (int j = startX; j < endX; j++)
			matrix[startY][j] = SHIP;
	}

	/*cout << "startX: " << startX << endl;
	cout << "endX: " << endX << endl;
	cout << "startY: " << startY << endl;
	cout << "endY: " << endY << endl;
	cout << "shipSize: " << shipSize << endl;*/
}

bool Board::setShipVertical(char** matrix, int startX, int startY, int range)
{
	bool shipSetted;

	if (range < SIZE) {
		if ((startY > 0 && matrix[startY - 1][startX] != SHIP) || (range < SIZE - 1 && matrix[range + 1][startX] != SHIP)) {
			for (int i = startY; i <= range; i++) {
				if (matrix[i][startX] == SHIP) {
					shipSetted = false;
					break;
				}
				else if (startX > 0 && startX < SIZE - 1) {
					if (matrix[i][startX - 1] == SHIP || matrix[i][startX + 1] == SHIP) {
						shipSetted = false;
						break;
					}
				}
				else {
					shipSetted = true;
				}
			}
		}
	}

	return shipSetted;
}

bool Board::setShipHorizontal(char** matrix, int startX, int startY, int range)
{
	bool shipSetted;

    for (int j = startX; j < range; j++) {
		if (matrix[startY][j] == SHIP) {
			shipSetted = false;
			break;
		}
		else if (startY > 0 && startY < SIZE - 1) {
			if (matrix[startY - 1][j] == SHIP || matrix[startY + 1][j] == SHIP) {
				shipSetted = false;
				break;
			}
		}
		else {
			shipSetted = true;
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
				cout << i + 1 << "   ";
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
	//b->setShip(1);
	//b->setShip(1);
	//b->setShip(1);
	//b->setShip(1);
	b->display();
	b->~Board();

	system("pause"); 
	return 0;
}



