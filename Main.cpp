#include "TextWindow.h"
#include "Timer.h"
#include <windows.h>
#include <ctime>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>#include <cwchar>

using namespace std;


int pX = 0;
int pY = 0;
int vX = 1;
int vY = 0;

int score = 0;

const int sArrW = 25;
const int sArrL = 50;

char sArr[sArrW * sArrL] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
							' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
							' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
							' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
							' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
							' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
							' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
							' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
							' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
							' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', };

char scoreArr[10] = { '0','0','0','0','0','0','0','0','0','0' };

vector<COORD> snake;

bool Continue = TRUE;

string stage = "menu";

void alterScore() {

	score++;

	string strArr[10] = { "1","2","3","4","5","6","7","8","9","0" };
	char chaArr[10] = { '1','2','3','4','5','6','7','8','9','0' };

	string str = to_string(score);

	for (int x = str.size() - 1; x >= 0; x--) {
		for (int y = 0; y < 10; y++) {
			if (str.substr(str.size() - x - 1, 1) == strArr[y]) {
				scoreArr[9 - x] = chaArr[y];
			}
		}
	}
}

int randNum(int top, int bottom) {
	return ((rand() /*- bottom*/) % top) + bottom;
}

void addSnake() {
	int len = snake.size();
	COORD c;
	if (len == 0) {
		c.X = pX;
		c.Y = pY;
	}
	else {
		 c.X = snake[len - 1].X; 
		 c.Y = snake[len - 1].Y;
	}
	snake.push_back(c);
}

void moveSnake() {
	
	COORD temp1;
	COORD temp2;

	if (sArr[(pX + vX) + (pY + vY) * sArrL] == '-' || sArr[(pX + vX) + (pY + vY) * sArrL] == '+' || sArr[(pX + vX) + (pY + vY) * sArrL] == '=') {
		if (sArr[(pX + vX) + (pY + vY) * sArrL] == '-') {
			addSnake();
			alterScore();
		}else if (sArr[(pX + vX) + (pY + vY) * sArrL] == '+') {
			for (int x = 0; x < sArrL * sArrW; x++) {
				sArr[x] = '#';
			}
			addSnake();
			addSnake();
			addSnake();
			alterScore();
			alterScore();
			alterScore();
		}
		else if (sArr[(pX + vX) + (pY + vY) * sArrL] == '=') {
			for (int x = 0; x < 10; x++) {
				addSnake();
				alterScore();
			}
		}

		int rInt = randNum(100, 0);
		int num = randNum(sArrL * sArrW - 1, 0);
		while (sArr[num] == '0') {
			num = randNum(sArrL * sArrW - 1, 0);
		}

		if (rInt < 80) {
			sArr[num] = '-';
		}else if( rInt < 98 ){
			while(num > sArrW * sArrL - sArrL || num % sArrL == sArrL - 1 || sArr[num] == '*' || sArr[num + 1] == '*' || sArr[num + sArrL] == '*' || sArr[num + 1 + sArrL] == '*') {
				num = randNum(sArrL * sArrW - 1, 0);
			}

			sArr[num] = '+';
			sArr[num + 1] = '+';
			sArr[num + sArrL] = '+';
			sArr[num + 1 + sArrL] = '+';
		}else {
			sArr[num] = '=';
		}

	}
	if (pX + vX < 0 || pY + vY < 0 || pX + vX >= sArrL || pY + vY >= sArrW || sArr[(pX + vX) + (pY + vY) * sArrL] == '*') {
		stage = "gameover";
	}
	else if (snake.empty() ) {
		pX += vX;
		pY += vY;
	}else{
		for (int x = 0; x < snake.size(); x++) {
			if (x == 0) {
				temp1.X = snake[0].X; temp1.Y = snake[0].Y;
				snake[0].X = pX; snake[0].Y = pY;
				pX += vX;
				pY += vY;
				temp2.X = temp1.X; temp2.Y = temp1.Y;
			}else {
				temp1.X = snake[x].X; temp1.Y = snake[x].Y;
				snake[x].X = temp2.X; snake[x].Y = temp2.Y;
				temp2.X = temp1.X; temp2.Y = temp1.Y;
			}
		}
	}

	for (int x = 0; x < sArrL * sArrW; x++) {
		if(sArr[x] != '-' && sArr[x] != '+' && sArr[x] != '=') sArr[x] = '#';
	}

	sArr[pX + pY * sArrL] = '*';
	for (int x = 0; x < snake.size(); x++) {
		sArr[snake[x].X + snake[x].Y * sArrL] = '*';
	}
}

int main()
{

	//Sets window size------
	//HWND console = GetConsoleWindow();
	//RECT r;
	//GetWindowRect(console, &r); //stores the console's current dimensions
	//
	//int screenX = GetSystemMetrics(0);
	//int screenY = GetSystemMetrics(1);
	//
	//MoveWindow(console, r.left, r.top, screenX+10, screenY+20, TRUE); // 1600 width, 800 height
	//----------------------

	//A note on how to set cursor position, if it is ever useful again.
	//SetConsoleCursorPosition(hOut,
	//	MouseWhere);


	//SetConsoleDisplayMode(out,CONSOLE_FULLSCREEN_MODE,0);

	TextWindow tw(1600, 800);
	
	Timer::InitializeDeltaTime();

	HANDLE hIn;
	HANDLE hOut;

	INPUT_RECORD InRec;
	DWORD NumRead;

	//-------------------

	Sprite scoreSprite(scoreArr, 10, 1);
	scoreSprite.SetPosition(60, 4);

	char mArr[22] = "Press space to start.";
	Sprite menuSprite(mArr, 22, 1);
	menuSprite.SetPosition(50, 20);

	char rArr[119] = "Welcome to snake.   Blue fruits    give one point  and snake length.   Red give 3.    Purple give 10.     Have fun.   ";
	Sprite rulesSprite(rArr, 17, 7);
	rulesSprite.SetPosition(50, 10);
	
	sArr[ (sArrW * sArrL) / 2] = '-';

	Sprite arrSprite(sArr, sArrW, sArrL);
	arrSprite.SetPosition(0, 0);

	for (int x = 0; x < sArrW * sArrL; x++) {
		if (sArr[x] != '-' && sArr[x] != '=') sArr[x] = '#';
	}

	int count = 0;

	//SetConsoleMode(hIn, E);
	while (Continue) {

		Timer::CalculateDeltaTime();
		tw.SwapBackBuffers();
		float check = Timer::GetDeltaTime();

		if (stage == "menu") {
			tw.RenderSprite(menuSprite);
			tw.RenderSprite(rulesSprite);
		}
		else if (stage == "game") {
			if (count % 10 == 0) {
				count = 0;
				moveSnake();
			}

			count++;

			scoreSprite.SetSprite(scoreArr, 10, 1);
			tw.RenderSprite(scoreSprite);

			arrSprite.SetSprite(sArr, sArrL, sArrW);
			tw.RenderSprite(arrSprite);
			
		}
		else if (stage == "gameover") {
			char goArr[17] = "Your score was: ";
			Sprite goSprite(goArr, 17, 1);
			goSprite.SetPosition(40, 15);
			scoreSprite.SetPosition(56, 15);
			tw.RenderSprite(goSprite);
			tw.RenderSprite(scoreSprite);
		}
		else {
			tw.RenderSprite(menuSprite);
		}
		
		if(GetAsyncKeyState(27)){
			Continue = FALSE;
		}
		if(stage == "menu"){
			if (GetAsyncKeyState(32)) {
				stage = "game";
			}
		}else if (stage == "game") {
			if (GetAsyncKeyState(37)) {
				if (snake.size() == 0 || vX != 1) {
					vX = -1; vY = 0;
				}
			}if (GetAsyncKeyState(38)) {
				if (snake.size() == 0 || vY != 1) {
					vY = -1; vX = 0;
				}
			}if (GetAsyncKeyState(39)) {
				if (snake.size() == 0 || vX != -1) {
					vX = 1; vY = 0;
				}
			}if (GetAsyncKeyState(40)) {
				if (snake.size() == 0 || vY != -1) {
					vY = 1; vX = 0;
				}
			}
		}
		else if (stage == "gameover") {
			if (GetAsyncKeyState(13)) {
				snake.clear();
				score = 0;
				for (int x = 0; x < sArrW * sArrL; x++) {
					sArr[x] = '#';
					if (x < 10) {
						scoreArr[x] = '0';
					}
				}
				sArr[(sArrW * sArrL) / 2] = '-';
				sArr[0] = '*';
				pX = 0; pY = 0; vX = 1; vY = 0;
				scoreSprite.SetPosition(60, 4);
				stage = "menu";
			}
		}

	}

	return 0;
}