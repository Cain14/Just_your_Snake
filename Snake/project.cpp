#include <windows.h>
#include <iostream>
#include <ctime>
#include <conio.h>

using namespace std;

class Snake
{
private:
    const int width { 20 };
    const int height { 20 };
    int x{}, y{}, fruitX{},  fruitY{}, score{};
    int tailX[100]{}, tailY[100]{};
    int nTail{};

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

public:
    bool gameOver{};

    enum class eDirection{ STOP = 0, LEFT, RIGHT, UP, DOWN };
    eDirection dir;

    void setup();
    void draw();
    void input();
    void logic();
};

void Snake::setup()
{
    gameOver = false;
    dir = eDirection::STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
}

void Snake::draw()
{
    system("cls"); // Clear screen

	// Draw top wall
	for (int i = 0; i < width + 2; i++) {
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) {
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "#";
			}
			if (i == y && j == x) {
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "O";
			}
			else if (i == fruitY && j == fruitX) {
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "F";
			}
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
						cout << "o";
						print = true;
					}
				}
				if (!print) {
					cout << " ";
				}
			}

			if (j == width - 1) {
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "#";
			}
		}
		cout << endl;
	}

	// Draw bottom wall
	for (int i = 0; i < width + 2; i++) {
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "#";
	}
	cout << endl;

	// Reset text color to default
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "SCORE = " << score;
	Sleep(300);
}

void Snake::input()
{
    if (_kbhit())
	{
		switch (_getch()) {
            case 'a': dir = eDirection::LEFT; break;
            case 's': dir = eDirection::DOWN; break;
            case 'w': dir = eDirection::UP; break;
            case 'd': dir = eDirection::RIGHT; break;
			case 'x': gameOver = true; break;
		}
	}
}

void Snake::logic()
{
    int prevX = tailX[0];
	int prevY = tailY[0];
	int  prev2x, prev2y;
	if (nTail > 0) {
		tailX[0] = x;
		tailY[0] = y;
		for (int i = 1; i < nTail; i++) {
			prev2x = tailX[i];
			prev2y = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = prev2x;
			prevY = prev2y;
		}
	}

	switch (dir)
	{
        case eDirection::LEFT:  x--; break;
        case eDirection::RIGHT: x++; break;
        case eDirection::UP:    y--; break;
        case eDirection::DOWN:  y++; break;
        default:    break;
	}
	if (x > width || x < 0|| y > height || y < 0) {
		gameOver = true;
		for (int i = 0; i < nTail; i++)
		{
			if (tailX[i] == x && tailY[i] == y) {
				gameOver = true;
				break;
			}
		}
	}
	if (x == fruitX && y == fruitY) {
		score += 10;

		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;

	}
}

int main()
{
    Snake sn;

    srand(static_cast<unsigned int>(time(nullptr)));
	sn.setup();
	while (!sn.gameOver) {

		sn.draw();
		sn.input();
		sn.logic();

	}

    return 0;
}
