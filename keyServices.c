#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

#define bROW0 15
#define bROW1 16

#define bCOL0 12
#define bCOL1 13
#define bCOL2 14

#define ROW0 26
#define ROW1 27
#define ROW2 28
#define ROW3 29

#define COL0R 0
#define COL1R 1
#define COL2R 2
#define COL3R 3

#define COL0G 4
#define COL1G 5
#define COL2G 6
#define COL3G 21

#define COL0B 22
#define COL1B 23
#define COL2B 24
#define COL3B 25

#define A0 10 //data pin 0
#define A1 11 //data pin 1
#define A2 30 //data pin 2
#define A3 31 //data pin 3

void init() {
	if(wiringPiSetup() == -1)
		return 1;

	pinMode(COL0R, OUTPUT);
	pinMode(COL1R, OUTPUT);
	pinMode(COL2R, OUTPUT);
	pinMode(COL3R, OUTPUT);
	pinMode(COL0G, OUTPUT);
	pinMode(COL1G, OUTPUT);
	pinMode(COL2G, OUTPUT);
	pinMode(COL3G, OUTPUT);
	pinMode(COL0B, OUTPUT);
	pinMode(COL1B, OUTPUT);
	pinMode(COL2B, OUTPUT);
	pinMode(COL3B, OUTPUT);

	pinMode(bROW0, OUTPUT);
	pinMode(bROW1, OUTPUT);
	pinMode(bCOL0, INPUT);
	pinMode(bCOL1, INPUT);
	pinMode(bCOL2, INPUT);

	pinMode(ROW0, OUTPUT);
	pinMode(ROW1, OUTPUT);
	pinMode(ROW2, OUTPUT);
	pinMode(ROW3, OUTPUT);

	digitalWrite(COL0R, 0);
	digitalWrite(COL1R, 0);
	digitalWrite(COL2R, 0);
	digitalWrite(COL3R, 0);
	digitalWrite(COL0G, 0);
	digitalWrite(COL1G, 0);
	digitalWrite(COL2G, 0);
	digitalWrite(COL3G, 0);
	digitalWrite(COL0B, 0);
	digitalWrite(COL1B, 0);
	digitalWrite(COL2B, 0);
	digitalWrite(COL3B, 0);
}

int bROW[2] = {15, 16};
int bCOL[3] = {12, 13, 14};

void initSeg() {
	pinMode(A0, OUTPUT);
	pinMode(A1, OUTPUT);
	pinMode(A2, OUTPUT);
	pinMode(A3, OUTPUT);
	
	digitalWrite(A0, 0);
	digitalWrite(A1, 0);
	digitalWrite(A2, 0);
	digitalWrite(A3, 1);
	
	digitalWrite(ROW0, 0);
	digitalWrite(ROW1, 0);
	digitalWrite(ROW2, 0);
	digitalWrite(ROW3, 0);
}

int buttonKey() { // Return the number of pressed key.
	
	int i, j, key;
	
	key = -1;
	for(i = 0; i < 3; i++) { // Select the row.
		digitalWrite(bROW[i], 1);
		for(j = 0; j < 3; j++) { // Read the column.
			if(digitalRead(bCOL[j]) == 1)
				if(i == 0 && j == 0)
					key = 0;
				else if(i == 0 && j == 1)
					key = 1;
				else if(i == 0 && j == 2)
					key = 2;
				else if(i == 1 && j == 0)
					key = 3;
				else if(i == 1 && j == 1)
					key = 4;
				else if(i == 1 && j == 2)
					key = 5;


				else
					key = -1;
		}
		digitalWrite(bROW[i], 0);
	}

	return key;
}

int main() {
	init();
	initSeg();

	int cnt = 0;

	while(1) {
		// Display "0000" when raspberry pi booted up.
		if(cnt == 0) {
			digitalWrite(ROW0, 1);
			digitalWrite(ROW1, 0);
			digitalWrite(ROW2, 0);
			digitalWrite(ROW3, 0);
		}
		else if(cnt == 1) {
			digitalWrite(ROW0, 0);
			digitalWrite(ROW1, 1);
			digitalWrite(ROW2, 0);
			digitalWrite(ROW3, 0);
		}
		else if(cnt == 2) {
			digitalWrite(ROW0, 0);
			digitalWrite(ROW1, 0);
			digitalWrite(ROW2, 1);
			digitalWrite(ROW3, 0);
		}
		else if(cnt == 3) {
			digitalWrite(ROW0, 0);
			digitalWrite(ROW1, 0);
			digitalWrite(ROW2, 0);
			digitalWrite(ROW3, 1);
		}
		if(buttonKey() == 0) {
			// Press key 'A': reboot raspberry pi.
			init();
			initSeg();
			system("shutdown -r now");
			return 0;
		}
		else if(buttonKey() == 2) {
			// Press key 'D': shutdown raspberry pi.
			init();
			initSeg();
			system("shutdown -h now");
			return 0;
		}
		else if(buttonKey() != -1) {
			// Press any arrow key: start game - calling the program "LED2048".
			system("/home/pi/Desktop/LED2048");
			return 0;
		}
		cnt++;

		if(cnt == 4)
			cnt = 0;

		delay(500);
	}
}