#include <wiringPi.h>
#include "SEVENSEG.h"

#define A0 10 //data pin 0
#define A1 11 //data pin 1
#define A2 30 //data pin 2
#define A3 31 //data pin 3

int tmpnum;

int num[10][4] = {
	{0, 0, 0, 0},
	{0, 0, 0, 1}, 
	{0, 0, 1, 0}, 
	{0, 0, 1, 1}, 
	{0, 1, 0, 0}, 
	{0, 1, 0, 1}, 
	{0, 1, 1, 0}, 
	{0, 1, 1, 1},
	{1, 0, 0, 0},
	{1, 0, 0, 1}, 
	{1, 0, 1, 0}, 
	{1, 0, 1, 1},
	{1, 1, 0, 0}, 
	{1, 1, 0, 1}, 
	{1, 1, 1, 0}, 
	{1, 1, 1, 1}};

void setSegment(int value) {
	digitalWrite(A0, num[value][3]);
	digitalWrite(A1, num[value][2]);
	digitalWrite(A2, num[value][1]);
	digitalWrite(A3, num[value][0]);
}

void initSeg() {
	pinMode(A0, OUTPUT);
	pinMode(A1, OUTPUT);
	pinMode(A2, OUTPUT);
	pinMode(A3, OUTPUT);
}

void setDigit(int value, int col) {
	if(col == 0) {
		setSegment(value / 1000);
		tmpnum = value % 1000;
	}
	else if(col == 1) {
		setSegment(tmpnum / 100);
		tmpnum = tmpnum % 100;
	}
	else if(col == 2) {
		setSegment(tmpnum / 10);
		tmpnum = tmpnum % 10;
	}
	else if(col == 3) {
		setSegment(tmpnum % 10);
	}
}