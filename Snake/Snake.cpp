#include <iostream>
#include<conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int nWidth = 20;
const int nHeight = 20;
int x, y, fruitx, fruity ,score ;
int tailx[100];
int taily[100];
int ntail;	
enum eDirection{STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;
HANDLE  h = GetStdHandle(STD_OUTPUT_HANDLE);
void Setup() {
	gameOver = false;
	dir = STOP;
	x = nWidth / 2;
	y = nHeight / 2;
	fruitx = rand() % nWidth;
	fruity = rand() % nHeight;
	score = 0;
	ntail = 0;
}
void Draw() {
	system("cls"); // Clear screen

	// Draw top wall
	for (int i = 0; i < nWidth + 2; i++) {
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < nHeight; i++) {
		for (int j = 0; j < nWidth; j++) {
			if (j == 0) {
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "#";
			}
			if (i == y && j == x) {
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "O";
			}
			else if (i == fruity && j == fruitx) {
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "F";
			}
			else {
				bool print = false;
				for (int k = 0; k < ntail; k++) {
					if (tailx[k] == j && taily[k] == i) {
						SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
						cout << "o";
						print = true;
					}
				}
				if (!print) {
					cout << " ";
				}
			}

			if (j == nWidth - 1) {
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "#";
			}
		}
		cout << endl;
	}

	// Draw bottom wall
	for (int i = 0; i < nWidth + 2; i++) {
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "#";
	}
	cout << endl;

	// Reset text color to default
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "SCORE = " << score;
	Sleep(100);
}


void Input() {
	if (_kbhit())
	{
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'w':
			dir = UP;
			break;
		case 'd':
			dir = RIGHT;
			break;
			case 'x':
				gameOver = true;
				break;
		}
	}

}

void Logic() {
	int prevX = tailx[0];
	int prevY = taily[0];
	int  prev2x, prev2y;
	if (ntail > 0) {
		tailx[0] = x;
		taily[0] = y;
		for (int i = 1; i < ntail; i++) {
			prev2x = tailx[i];
			prev2y = taily[i];
			tailx[i] = prevX;
			taily[i] = prevY;
			prevX = prev2x;
			prevY = prev2y;
		}
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
		
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > nWidth || x < 0|| y > nHeight || y < 0) {
		gameOver = true;
		for (int i = 0; i < ntail; i++)
		{
			if (tailx[i] == x && taily[i] == y) {
				gameOver = true;
				break;
			}
		}
	}
	if (x == fruitx && y == fruity) {
		score += 10;
		
		fruitx = rand() % nWidth;
		fruity = rand() % nHeight;
		ntail++;

	}
}

int main() {
	srand(time(NULL));
	Setup();
	while (!gameOver) {
		
		Draw();
		Input();
		Logic();
		
	}
}

//Game made by hand from Cain ;)
