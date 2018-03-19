#include <wiringPi.h>
#include <softPwm.h>
#include "RGBLED.h"

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

#define ROW0 26
#define ROW1 27
#define ROW2 28
#define ROW3 29

#define bROW0 15
#define bROW1 16

#define bCOL0 12
#define bCOL1 13
#define bCOL2 14

#define A0 10
#define A1 11
#define A2 30
#define A3 31


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

	pinMode(ROW0, OUTPUT);
	pinMode(ROW1, OUTPUT);
	pinMode(ROW2, OUTPUT);
	pinMode(ROW3, OUTPUT);

	pinMode(bROW0, OUTPUT);
	pinMode(bROW1, OUTPUT);
	pinMode(bCOL0, INPUT);
	pinMode(bCOL1, INPUT);
	pinMode(bCOL2, INPUT);
	
	pinMode(A0, OUTPUT);
	pinMode(A1, OUTPUT);
	pinMode(A2, OUTPUT);
	pinMode(A3, OUTPUT);


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
	digitalWrite(ROW0, 1);
	digitalWrite(ROW1, 1);
	digitalWrite(ROW2, 1);
	digitalWrite(ROW3, 1);
}

void initPwm() {
	softPwmCreate(COL0R, 0, 10);
	softPwmCreate(COL1R, 0, 10);
	softPwmCreate(COL2R, 0, 10);
	softPwmCreate(COL3R, 0, 10);
	softPwmCreate(COL0G, 0, 10);
	softPwmCreate(COL1G, 0, 10);
	softPwmCreate(COL2G, 0, 10);
	softPwmCreate(COL3G, 0, 10);
	softPwmCreate(COL0B, 0, 10);
	softPwmCreate(COL1B, 0, 10);
	softPwmCreate(COL2B, 0, 10);
	softPwmCreate(COL3B, 0, 10);
}

void LED(int data[4][4], int row) {
	if(data[row][0] > 0) {
		digitalWrite(COL0R, 1);
	} else
		digitalWrite(COL0R, 0);

	if(data[row][1] > 0) {
		digitalWrite(COL1R, 1);
	} else
		digitalWrite(COL1R, 0);

	if(data[row][2] > 0) {
		digitalWrite(COL2R, 1);
	} else
		digitalWrite(COL2R, 0);

	if(data[row][3] > 0) {
		digitalWrite(COL3R, 1);
	} else
		digitalWrite(COL3R, 0);


	if(row == 0) {
		digitalWrite(ROW0, 0);
		digitalWrite(ROW1, 1);
		digitalWrite(ROW2, 1);
		digitalWrite(ROW3, 1);
	}
	else if(row == 1) {
		digitalWrite(ROW0, 1);
		digitalWrite(ROW1, 0);
		digitalWrite(ROW2, 1);
		digitalWrite(ROW3, 1);
	}
	else if(row == 2) {
		digitalWrite(ROW0, 1);
		digitalWrite(ROW1, 1);
		digitalWrite(ROW2, 0);
		digitalWrite(ROW3, 1);
	}
	else if(row == 3) {
		digitalWrite(ROW0, 1);
		digitalWrite(ROW1, 1);
		digitalWrite(ROW2, 1);
		digitalWrite(ROW3, 0);
	}
}

void rowOFF() {
	digitalWrite(ROW0, 0);
	digitalWrite(ROW1, 0);
	digitalWrite(ROW2, 0);
	digitalWrite(ROW3, 0);

	delay(1);
}

int ledblkCount;
ledblkCount = 0;

void LEDPwm(int data[4][4], int row) {
	ledblkCount++;
	//printf("%d\n", ledblkCount);
	if(data[row][0] <= 0) { //led off
		softPwmWrite(COL0R, 0);
		softPwmWrite(COL0G, 0);
		softPwmWrite(COL0B, 0);
	}
	else if(data[row][0] == 2) { //lit up red
		softPwmWrite(COL0R, 1);
		softPwmWrite(COL0G, 0);
		softPwmWrite(COL0B, 0);
	}	
	else if(data[row][0] == 4) { //red (full)
		softPwmWrite(COL0R, 10);
		softPwmWrite(COL0G, 0);
		softPwmWrite(COL0B, 0);
	}
	else if(data[row][0] == 8) { //orange
		softPwmWrite(COL0R, 10);
		softPwmWrite(COL0G, 2);
		softPwmWrite(COL0B, 0);
	}
	else if(data[row][0] == 16) { //yellow
		softPwmWrite(COL0R, 10);
		softPwmWrite(COL0G, 10);
		softPwmWrite(COL0B, 0);
	}
	else if(data[row][0] == 32) { //green
		softPwmWrite(COL0R, 0);
		softPwmWrite(COL0G, 10);
		softPwmWrite(COL0B, 0);
	}
	else if(data[row][0] == 64) { //cyan
		softPwmWrite(COL0R, 0);
		softPwmWrite(COL0G, 10);
		softPwmWrite(COL0B, 3);
	}
	else if(data[row][0] == 128) { //bluesky
		softPwmWrite(COL0R, 0);
		softPwmWrite(COL0G, 9);
		softPwmWrite(COL0B, 10);
	}
	else if(data[row][0] == 256) { //blue
		softPwmWrite(COL0R, 0);
		softPwmWrite(COL0G, 0);
		softPwmWrite(COL0B, 10);
	}
	else if(data[row][0] == 512) { //purple
		softPwmWrite(COL0R, 2);
		softPwmWrite(COL0G, 0);
		softPwmWrite(COL0B, 10);
	}
	else if(data[row][0] == 1024) { //magenta
		softPwmWrite(COL0R, 10);
		softPwmWrite(COL0G, 0);
		softPwmWrite(COL0B, 10);
	}
	else if(data[row][0] == 2048) { //pink
		softPwmWrite(COL0R, 10);
		softPwmWrite(COL0G, 3);
		softPwmWrite(COL0B, 10);
	}
	else if(data[row][0] == 4096) { //1
		softPwmWrite(COL0R, 10);
		softPwmWrite(COL0G, 8);
		softPwmWrite(COL0B, 10);
	}
	else if(data[row][0] == 8192) { //2
		if(ledblkCount <= 240) {
			softPwmWrite(COL0R, 3);
			softPwmWrite(COL0G, 3);
			softPwmWrite(COL0B, 3);
		}
		else if(ledblkCount > 240 && ledblkCount <= 480){
			softPwmWrite(COL0R, 10);
			softPwmWrite(COL0G, 0);
			softPwmWrite(COL0B, 0);
		}
		else if(ledblkCount > 480) {
			ledblkCount = 0;
		}
	}
	else if(data[row][0] == 16384) { //3
		if(ledblkCount <= 240) {
			softPwmWrite(COL0R, 3);
			softPwmWrite(COL0G, 3);
			softPwmWrite(COL0B, 3);
		}
		else if(ledblkCount > 240 && ledblkCount <= 480){
			softPwmWrite(COL0R, 9);
			softPwmWrite(COL0G, 10);
			softPwmWrite(COL0B, 0);
		}
		else if(ledblkCount > 480) {
			ledblkCount = 0;
		}
	}
	else if(data[row][0] == 32768) { //4
		if(ledblkCount <= 240) {
			softPwmWrite(COL0R, 3);
			softPwmWrite(COL0G, 3);
			softPwmWrite(COL0B, 3);
		}
		else if(ledblkCount > 240 && ledblkCount <= 480){
			softPwmWrite(COL0R, 0);
			softPwmWrite(COL0G, 10);
			softPwmWrite(COL0B, 0);
		}
		else if(ledblkCount > 480) {
			ledblkCount = 0;
		}
	}
	else if(data[row][0] > 32768) { //5
		if(ledblkCount <= 240) {
			softPwmWrite(COL0R, 3);
			softPwmWrite(COL0G, 3);
			softPwmWrite(COL0B, 3);
		}
		else if(ledblkCount > 240 && ledblkCount <= 480){
			softPwmWrite(COL0R, 0);
			softPwmWrite(COL0G, 10);
			softPwmWrite(COL0B, 10);
		}
		else if(ledblkCount > 480) {
			ledblkCount = 0;
		}
	}
///////////////////////////////////////////////////////
	if(data[row][1] <= 0) { //led off
		softPwmWrite(COL1R, 0);
		softPwmWrite(COL1G, 0);
		softPwmWrite(COL1B, 0);
	}
	else if(data[row][1] == 2) { //lit up red
		softPwmWrite(COL1R, 1);
		softPwmWrite(COL1G, 0);
		softPwmWrite(COL1B, 0);
	}	
	else if(data[row][1] == 4) { //red (full)
		softPwmWrite(COL1R, 10);
		softPwmWrite(COL1G, 0);
		softPwmWrite(COL1B, 0);
	}
	else if(data[row][1] == 8) { //orange
		softPwmWrite(COL1R, 10);
		softPwmWrite(COL1G, 2);
		softPwmWrite(COL1B, 0);
	}
	else if(data[row][1] == 16) { //yellow
		softPwmWrite(COL1R, 10);
		softPwmWrite(COL1G, 10);
		softPwmWrite(COL1B, 0);
	}
	else if(data[row][1] == 32) { //green
		softPwmWrite(COL1R, 0);
		softPwmWrite(COL1G, 10);
		softPwmWrite(COL1B, 0);
	}
	else if(data[row][1] == 64) { //cyan
		softPwmWrite(COL1R, 0);
		softPwmWrite(COL1G, 10);
		softPwmWrite(COL1B, 3);
	}
	else if(data[row][1] == 128) { //bluesky
		softPwmWrite(COL1R, 0);
		softPwmWrite(COL1G, 9);
		softPwmWrite(COL1B, 10);
	}
	else if(data[row][1] == 256) { //blue
		softPwmWrite(COL1R, 0);
		softPwmWrite(COL1G, 0);
		softPwmWrite(COL1B, 10);
	}
	else if(data[row][1] == 512) { //purple
		softPwmWrite(COL1R, 2);
		softPwmWrite(COL1G, 0);
		softPwmWrite(COL1B, 10);
	}
	else if(data[row][1] == 1024) { //magenta
		softPwmWrite(COL1R, 10);
		softPwmWrite(COL1G, 0);
		softPwmWrite(COL1B, 10);
	}
	else if(data[row][1] == 2048) { //pink
		softPwmWrite(COL1R, 10);
		softPwmWrite(COL1G, 3);
		softPwmWrite(COL1B, 10);
	}
	else if(data[row][1] == 4096) { //1
		softPwmWrite(COL1R, 10);
		softPwmWrite(COL1G, 8);
		softPwmWrite(COL1B, 10);
	}
	else if(data[row][1] == 8192) { //2
		if(ledblkCount <= 240) {
			softPwmWrite(COL1R, 3);
			softPwmWrite(COL1G, 3);
			softPwmWrite(COL1B, 3);
		}
		else if(ledblkCount > 240 && ledblkCount <= 480){
			softPwmWrite(COL1R, 10);
			softPwmWrite(COL1G, 0);
			softPwmWrite(COL1B, 0);
		}
		else if(ledblkCount > 480) {
			ledblkCount = 0;
		}
	}
	else if(data[row][1] == 16384) { //3
		if(ledblkCount <= 240) {
			softPwmWrite(COL1R, 3);
			softPwmWrite(COL1G, 3);
			softPwmWrite(COL1B, 3);
		}
		else if(ledblkCount > 240 && ledblkCount <= 480){
			softPwmWrite(COL1R, 9);
			softPwmWrite(COL1G, 10);
			softPwmWrite(COL1B, 0);
		}
		else if(ledblkCount > 480) {
			ledblkCount = 0;
		}
	}
	else if(data[row][1] == 32768) { //4
		if(ledblkCount <= 240) {
			softPwmWrite(COL1R, 3);
			softPwmWrite(COL1G, 3);
			softPwmWrite(COL1B, 3);
		}
		else if(ledblkCount > 240 && ledblkCount <= 480){
			softPwmWrite(COL1R, 0);
			softPwmWrite(COL1G, 10);
			softPwmWrite(COL1B, 0);
		}
		else if(ledblkCount > 480) {
			ledblkCount = 0;
		}
	}
	else if(data[row][1] > 32768) { //5
		if(ledblkCount <= 240) {
			softPwmWrite(COL1R, 3);
			softPwmWrite(COL1G, 3);
			softPwmWrite(COL1B, 3);
		}
		else if(ledblkCount > 240 && ledblkCount <= 480){
			softPwmWrite(COL1R, 0);
			softPwmWrite(COL1G, 10);
			softPwmWrite(COL1B, 10);
		}
		else if(ledblkCount > 480) {
			ledblkCount = 0;
		}
	}
/////////////////////////////////////////////////
	if(data[row][2] <= 0) { //led off
		softPwmWrite(COL2R, 0);
		softPwmWrite(COL2G, 0);
		softPwmWrite(COL2B, 0);
	}
	else if(data[row][2] == 2) { //lit up red
		softPwmWrite(COL2R, 1);
		softPwmWrite(COL2G, 0);
		softPwmWrite(COL2B, 0);
	}	
	else if(data[row][2] == 4) { //red (full)
		softPwmWrite(COL2R, 10);
		softPwmWrite(COL2G, 0);
		softPwmWrite(COL2B, 0);
	}
	else if(data[row][2] == 8) { //orange
		softPwmWrite(COL2R, 10);
		softPwmWrite(COL2G, 2);
		softPwmWrite(COL2B, 0);
	}
	else if(data[row][2] == 16) { //yellow
		softPwmWrite(COL2R, 10);
		softPwmWrite(COL2G, 10);
		softPwmWrite(COL2B, 0);
	}
	else if(data[row][2] == 32) { //green
		softPwmWrite(COL2R, 0);
		softPwmWrite(COL2G, 10);
		softPwmWrite(COL2B, 0);
	}
	else if(data[row][2] == 64) { //cyan
		softPwmWrite(COL2R, 0);
		softPwmWrite(COL2G, 10);
		softPwmWrite(COL2B, 3);
	}
	else if(data[row][2] == 128) { //bluesky
		softPwmWrite(COL2R, 0);
		softPwmWrite(COL2G, 9);
		softPwmWrite(COL2B, 10);
	}
	else if(data[row][2] == 256) { //blue
		softPwmWrite(COL2R, 0);
		softPwmWrite(COL2G, 0);
		softPwmWrite(COL2B, 10);
	}
	else if(data[row][2] == 512) { //purple
		softPwmWrite(COL2R, 2);
		softPwmWrite(COL2G, 0);
		softPwmWrite(COL2B, 10);
	}
	else if(data[row][2] == 1024) { //magenta
		softPwmWrite(COL2R, 10);
		softPwmWrite(COL2G, 0);
		softPwmWrite(COL2B, 10);
	}
	else if(data[row][2] == 2048) { //pink
		softPwmWrite(COL2R, 10);
		softPwmWrite(COL2G, 3);
		softPwmWrite(COL2B, 10);
	}
	else if(data[row][2] == 4096) { //1
		softPwmWrite(COL2R, 10);
		softPwmWrite(COL2G, 8);
		softPwmWrite(COL2B, 10);
	}
	else if(data[row][2] == 8192) { //2
		if(ledblkCount <= 240) {
			softPwmWrite(COL2R, 3);
			softPwmWrite(COL2G, 3);
			softPwmWrite(COL2B, 3);
		}
		else if(ledblkCount > 240 && ledblkCount <= 480){
			softPwmWrite(COL2R, 10);
			softPwmWrite(COL2G, 0);
			softPwmWrite(COL2B, 0);
		}
		else if(ledblkCount > 480) {
			ledblkCount = 0;
		}
	}
	else if(data[row][2] == 16384) { //3
		if(ledblkCount <= 240) {
			softPwmWrite(COL2R, 3);
			softPwmWrite(COL2G, 3);
			softPwmWrite(COL2B, 3);
		}
		else if(ledblkCount > 240 && ledblkCount <= 480){
			softPwmWrite(COL2R, 9);
			softPwmWrite(COL2G, 10);
			softPwmWrite(COL2B, 0);
		}
		else if(ledblkCount > 480) {
			ledblkCount = 0;
		}
	}
	else if(data[row][2] == 32768) { //4
		if(ledblkCount <= 240) {
			softPwmWrite(COL2R, 3);
			softPwmWrite(COL2G, 3);
			softPwmWrite(COL2B, 3);
		}
		else if(ledblkCount > 240 && ledblkCount <= 480){
			softPwmWrite(COL2R, 0);
			softPwmWrite(COL2G, 10);
			softPwmWrite(COL2B, 0);
		}
		else if(ledblkCount > 480) {
			ledblkCount = 0;
		}
	}
	else if(data[row][2] > 32768) { //5
		if(ledblkCount <= 240) {
			softPwmWrite(COL2R, 3);
			softPwmWrite(COL2G, 3);
			softPwmWrite(COL2B, 3);
		}
		else if(ledblkCount > 240 && ledblkCount <= 480){
			softPwmWrite(COL2R, 0);
			softPwmWrite(COL2G, 10);
			softPwmWrite(COL2B, 10);
		}
		else if(ledblkCount > 480) {
			ledblkCount = 0;
		}
	}
//////////////////////////////////////////////////////////
	if(data[row][3] <= 0) { //led off
		softPwmWrite(COL3R, 0);
		softPwmWrite(COL3G, 0);
		softPwmWrite(COL3B, 0);
	}
	else if(data[row][3] == 2) { //lit up red
		softPwmWrite(COL3R, 1);
		softPwmWrite(COL3G, 0);
		softPwmWrite(COL3B, 0);
	}	
	else if(data[row][3] == 4) { //red (full)
		softPwmWrite(COL3R, 10);
		softPwmWrite(COL3G, 0);
		softPwmWrite(COL3B, 0);
	}
	else if(data[row][3] == 8) { //orange
		softPwmWrite(COL3R, 10);
		softPwmWrite(COL3G, 2);
		softPwmWrite(COL3B, 0);
	}
	else if(data[row][3] == 16) { //yellow
		softPwmWrite(COL3R, 10);
		softPwmWrite(COL3G, 10);
		softPwmWrite(COL3B, 0);
	}
	else if(data[row][3] == 32) { //green
		softPwmWrite(COL3R, 0);
		softPwmWrite(COL3G, 10);
		softPwmWrite(COL3B, 0);
	}
	else if(data[row][3] == 64) { //cyan
		softPwmWrite(COL3R, 0);
		softPwmWrite(COL3G, 10);
		softPwmWrite(COL3B, 3);
	}
	else if(data[row][3] == 128) { //bluesky
		softPwmWrite(COL3R, 0);
		softPwmWrite(COL3G, 9);
		softPwmWrite(COL3B, 10);
	}
	else if(data[row][3] == 256) { //blue
		softPwmWrite(COL3R, 0);
		softPwmWrite(COL3G, 0);
		softPwmWrite(COL3B, 10);
	}
	else if(data[row][3] == 512) { //purple
		softPwmWrite(COL3R, 2);
		softPwmWrite(COL3G, 0);
		softPwmWrite(COL3B, 10);
	}
	else if(data[row][3] == 1024) { //magenta
		softPwmWrite(COL3R, 10);
		softPwmWrite(COL3G, 0);
		softPwmWrite(COL3B, 10);
	}
	else if(data[row][3] == 2048) { //pink
		softPwmWrite(COL3R, 10);
		softPwmWrite(COL3G, 3);
		softPwmWrite(COL3B, 10);
	}
	else if(data[row][3] == 4096) { //1
		softPwmWrite(COL3R, 10);
		softPwmWrite(COL3G, 8);
		softPwmWrite(COL3B, 10);
	}
	else if(data[row][3] == 8192) { //2
		if(ledblkCount <= 240) {
			softPwmWrite(COL3R, 3);
			softPwmWrite(COL3G, 3);
			softPwmWrite(COL3B, 3);
		}
		else if(ledblkCount > 240 && ledblkCount <= 480){
			softPwmWrite(COL3R, 10);
			softPwmWrite(COL3G, 0);
			softPwmWrite(COL3B, 0);
		}
		else if(ledblkCount > 480) {
			ledblkCount = 0;
		}
	}
	else if(data[row][3] == 16384) { //3
		if(ledblkCount <= 240) {
			softPwmWrite(COL3R, 3);
			softPwmWrite(COL3G, 3);
			softPwmWrite(COL3B, 3);
		}
		else if(ledblkCount > 240 && ledblkCount <= 480){
			softPwmWrite(COL3R, 9);
			softPwmWrite(COL3G, 10);
			softPwmWrite(COL3B, 0);
		}
		else if(ledblkCount > 480) {
			ledblkCount = 0;
		}
	}
	else if(data[row][3] == 32768) { //4
		if(ledblkCount <= 240) {
			softPwmWrite(COL3R, 3);
			softPwmWrite(COL3G, 3);
			softPwmWrite(COL3B, 3);
		}
		else if(ledblkCount > 240 && ledblkCount <= 480){
			softPwmWrite(COL3R, 0);
			softPwmWrite(COL3G, 10);
			softPwmWrite(COL3B, 0);
		}
		else if(ledblkCount > 480) {
			ledblkCount = 0;
		}
	}
	else if(data[row][3] > 32768) { //5
		if(ledblkCount <= 240) {
			softPwmWrite(COL3R, 3);
			softPwmWrite(COL3G, 3);
			softPwmWrite(COL3B, 3);
		}
		else if(ledblkCount > 240 && ledblkCount <= 480){
			softPwmWrite(COL3R, 0);
			softPwmWrite(COL3G, 10);
			softPwmWrite(COL3B, 10);
		}
		else if(ledblkCount > 480) {
			ledblkCount = 0;
		}
	}
//////////////////////////////////////////////////////////////////

	if(row == 0) {
		rowOFF();
		digitalWrite(ROW0, 1);
		digitalWrite(ROW1, 0);
		digitalWrite(ROW2, 0);
		digitalWrite(ROW3, 0);
	}
	else if(row == 1) {
		rowOFF();
		digitalWrite(ROW0, 0);
		digitalWrite(ROW1, 1);
		digitalWrite(ROW2, 0);
		digitalWrite(ROW3, 0);
	}
	else if(row == 2) {
		rowOFF();
		digitalWrite(ROW0, 0);
		digitalWrite(ROW1, 0);
		digitalWrite(ROW2, 1);
		digitalWrite(ROW3, 0);
	}
	else if(row == 3) {
		rowOFF();
		digitalWrite(ROW0, 0);
		digitalWrite(ROW1, 0);
		digitalWrite(ROW2, 0);
		digitalWrite(ROW3, 1);
	}
}

int bROW[2] = {15, 16};
int bCOL[3] = {12, 13, 14};

int buttonKey() {
	
	int i, j, key;
	
	key = -1;
	for(i = 0; i < 3; i++) {
		digitalWrite(bROW[i], 1);
		for(j = 0; j < 3; j++) {
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

