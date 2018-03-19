/*References for 2048 Game: https://m.blog.naver.com/PostView.nhn?blogId=azure0777&logNo=220290664944&proxyReferer=https%3A%2F%2Fwww.google.co.kr%2F */

#include "RGBLED.h"
#include "SEVENSEG.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <conio.h>

/*#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define UD 26
#define RES 114*/

#define val 4096 //Testing Color

int score, moved, tmpScore, cpScore;

void checkGameOver(int data[4][4], int cpData[4][4]); //Check game over.
void printBoard(int data[4][4]); //Print board on screen.
void addData(int data[4][4]); //Add new number random location.
void copyState(int data[4][4], int cpData[4][4]); //Copy current game state for undo.
void moveLeft(int data[4][4], int cpData[4][4]); //Move left.
void moveRight(int data[4][4], int cpData[4][4]); //Move right.
void moveUp(int data[4][4], int cpData[4][4]); //Move up.
void moveDown(int data[4][4], int cpData[4][4]); //Move down.
void Undo(int data[4][4], int cpData[4][4]); //Undo
void Reset(int data[4][4], int cpData[4][4]); //Reset the game.
void ledTest() //Test for DotMatrix.

void checkGameOver(int data[4][4], int cpData[4][4]) { //Checking game over
	int i, j;
	int printGO[4][4] = {{4, 0, 0, 4}, {0, 4, 4, 0}, {0, 4, 4, 0}, {4, 0, 0, 4}}; //Game over message on DotMatrix.

	for (i = 0; i<4; i++) for (j = 0; j<4; j++) if (data[i][j] == 0) return; //Check all location is "empty"(0).
	for (i = 0; i<3; i++) for (j = 0; j<3; j++) if (data[i][j] == data[i + 1][j] || data[i][j] == data[i][j + 1]) return; //Check combinable number on middle.
	for (i = 0; i<3; i++) if (data[i][3] == data[i + 1][3]) return; //Check combinable number on edge of row.
	for (j = 0; j<3; j++) if (data[3][j] == data[3][j + 1]) return; //Check combinable number on edge of column.
	/*If not problem, just exit.*/

	printf("Game Over..\n"); 

	while(1) {
		if(buttonKey() == 0) { //Key 'A'
			Reset(data, cpData);
			break;
		}
		else if(buttonKey() == 2) { //Key 'B'
			score = cpScore;
			Undo(data, cpData);
			break;
		}
		for(i = 0; i < 4; i++) {
			LEDPwm(printGO, i);
			setDigit(score, i);
			delay(1);
		}
	}
}

void printBoard(int data[4][4]) {
	system("clear");
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (data[i][j] == 0)
				printf(".	");
			else
				printf("%d	", data[i][j]);
		}
		printf("\n\n\n");
	}
	printf("SCORE: %d\n", score);
}

void addData(int data[4][4]) {
	int i, j, cnt;
	int* p0[16] = { 0 };

	for (i = 0, cnt = 0; i < 4; i++) { //Add number on random location
		for (j = 0; j < 4; j++)
			if (data[i][j] == 0) { //Check is location empty.
				p0[cnt] = &data[i][j]; //Added only addresses having "0"
				cnt++;
			}
	}
	srand(time(NULL)); //For various seed.
	*p0[rand() % cnt] = (rand() % 100 < 95) ? 2 : 4; //95% is "2" and 5% is "4", and added one of the empty locations.
}

void copyState(int data[4][4], int cpData[4][4]) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			cpData[i][j] = data[i][j];
		}
	}
}

void moveLeft(int data[4][4], int cpData[4][4]) {
	int i, j, r, act;
	for (i = 0, act = 0; i < 4; i++) { //Check all row.
		for (j = 1; j <= 3; j++) { //Check column 1 to 3
			for (r = j; r > 0; r--) { //Move value to first colume.
				if (data[i][r] == 0 || data[i][r] > 100000)
					break;
				if (data[i][r - 1] != 0 && data[i][r - 1] != data[i][r])
					break;
				if (data[i][r - 1] == 0)
					data[i][r - 1] = data[i][r];
				else if (data[i][r] == data[i][r - 1]) {
					data[i][r - 1] = data[i][r - 1] + data[i][r];
					data[i][r - 1] += 100000;
					score += 2 * (data[i][r]);
				}
				data[i][r] = 0;
				act++;
			}
		}
	}
	moved = act;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (data[i][j] > 100000)
				data[i][j] -= 100000;
		}
	}
	if (act > 0) { //If block was moved.
		addData(data); //Add new number.
		printBoard(data); //Refresh board.
		checkGameOver(data, cpData);
	}
}

void moveRight(int data[4][4], int cpData[4][4]) {
	int i, j, r, act;
	for (i = 0, act = 0; i < 4; i++) {
		for (j = 2; j >= 0; j--) {
			for (r = j; r < 3; r++) {
				if (data[i][r] == 0 || data[i][r] > 100000)
					break;
				if (data[i][r + 1] != 0 && data[i][r + 1] != data[i][r])
					break;
				if (data[i][r + 1] == 0)
					data[i][r + 1] = data[i][r];
				else if (data[i][r] == data[i][r + 1]) {
					data[i][r + 1] = data[i][r + 1] + data[i][r];
					data[i][r + 1] += 100000;
					score += 2 * (data[i][r]);
				}
				data[i][r] = 0;
				act++;
			}
		}
	}
	moved = act;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (data[i][j] > 100000)
				data[i][j] -= 100000; //임시로 더한 10000을 감소 
		}
	}
	if (act > 0) {
		addData(data);
		printBoard(data);
		checkGameOver(data, cpData);
	}
}

void moveUp(int data[4][4], int cpData[4][4]) {
	int i, j, r, act;
	for (j = 0, act = 0; j < 4; j++) {
		for (i = 1; i <= 3; i++) {
			for (r = i; r > 0; r--) {
				if (data[r][j] == 0 || data[r][j] > 100000)
					break;
				if (data[r - 1][j] != 0 && data[r - 1][j] != data[r][j])
					break;
				if (data[r - 1][j] == 0)
					data[r - 1][j] = data[r][j];
				else if (data[r][j] == data[r - 1][j]) {
					data[r - 1][j] = data[r - 1][j] + data[r][j];
					data[r - 1][j] += 100000;
					score += 2 * (data[r][j]);
				}
				data[r][j] = 0;
				act++;
			}
		}
	}
	moved = act;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (data[i][j] > 100000)
				data[i][j] -= 100000; //임시로 더한 10000을 감소 
		}
	}
	if (act > 0) {
		addData(data);
		printBoard(data);
		checkGameOver(data, cpData);
	}
}

void moveDown(int data[4][4], int cpData[4][4]) {
	int i, j, r, act;
	for (j = 0, act = 0; j < 4; j++) {
		for (i = 2; i >= 0; i--) {
			for (r = i; r < 3; r++) {
				if (data[r][j] == 0 || data[r][j] > 100000)
					break;
				if (data[r + 1][j] != 0 && data[r + 1][j] != data[r][j])
					break;
				if (data[r + 1][j] == 0)
					data[r + 1][j] = data[r][j];
				else if (data[r][j] == data[r + 1][j]) {
					data[r + 1][j] = data[r + 1][j] + data[r][j];
					data[r + 1][j] += 100000;
					score += 2 * (data[r][j]);
				}
				data[r][j] = 0;
				act++;
			}
		}
	}
	moved = act;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (data[i][j] > 100000)
				data[i][j] -= 100000; //임시로 더한 10000을 감소 
		}
	}
	if (act > 0) {
		addData(data);
		printBoard(data);
		checkGameOver(data, cpData);
	}
}

void Undo(int data[4][4], int cpData[4][4]) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			data[i][j] = cpData[i][j];
		}
	}
	printBoard(data);
}

void Reset(int data[4][4], int cpData[4][4]) {
	
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			data[i][j] = 0;
			cpData[i][j] = 0;
		}
	}
	tmpScore = 0;
	cpScore = 0;
	score = 0;

	addData(data);
	addData(data);
	printBoard(data);
}

void ledTest() {
	int i;
	//int data[4][4] = {{2,4,8,16}, {32,64,128,256}, {512,1024,2048,4096}, {8192,16384,32768,32800}}; //put data with color in for test
	int data[4][4] = {{val,val,val,val}, {val,val,val,val}, {val,val,val,val}, {val,val,val,val}};
	
	while(1) {
		for(i = 0; i < 4; i++) { //select next line
			LEDPwm(data, i); //print one line
			delay(1);
		}
	}
}

int main() {

	init();
	initPwm();
	initSeg();

	//ledTest(); //Un-comment if you want to test DotMatrix.

	int data[4][4] = { 0 };
	int tmpData[4][4] = { 0 };
	int cpData[4][4] = { 0 };
	
	int key, i;
	char cKey;
	int isKeyReleased, isfkey, isfkeyPDelay;

	score = 0;
	tmpScore = 0;
	cpScore = 0;
	moved = 0;
	isKeyReleased = 1;
	isfkey = 0;
	isfkeyPDelay = 0;
	

	addData(data);
	addData(data);
	printBoard(data);

	while(1) {
		for(i = 0; i < 4; i++) { //Display on DotMatrix.
			LEDPwm(data, i);
			setDigit(score, i);
			delay(1);
		}
		if(buttonKey() == 0) {
			isfkey = 1;
			isfkeyPDelay = 10;
		}
		else
			if(isfkeyPDelay >= 0) {
				isfkeyPDelay--;
				if(isfkey == 1 && buttonKey() == 2) {
					init();
					initPwm();
					initSeg();
					system("shutdown -h now");
					return 0;
				}
					
				if(isfkeyPDelay < 1) {
					isfkey = 0;
				}
			}

		if(isKeyReleased == 1) {
			switch(buttonKey()) {
				case 2: //Undo
					score = cpScore;
					Undo(data, cpData);
					break;
				case 0: //Reset
					Reset(data, cpData);
					break;
				case 1: //UP
					tmpScore = score;
					copyState(data, tmpData);
					moveUp(data, cpData);
					if(moved > 0) {
						cpScore = tmpScore;
						copyState(tmpData, cpData);
					}
					break;
				case 4: //DOWN
					tmpScore = score;
					copyState(data, tmpData);
					moveDown(data, cpData);
					if(moved > 0) {
						cpScore = tmpScore;
						copyState(tmpData, cpData);
					}
					break;
				case 3: //LEFT
					tmpScore = score;
					copyState(data, tmpData);
					moveLeft(data, cpData);
					if(moved > 0) {
						cpScore = tmpScore;
						copyState(tmpData, cpData);
					}
					break;
				case 5: //RIGHT
					tmpScore = score;
					copyState(data, tmpData);
					moveRight(data, cpData);
					if(moved > 0) {
						cpScore = tmpScore;
						copyState(tmpData, cpData);
					}
					break;
			
			}
		}
		if(buttonKey() == -1)
			isKeyReleased = 1;
		else
			isKeyReleased = 0;
	}
	return 0;
}