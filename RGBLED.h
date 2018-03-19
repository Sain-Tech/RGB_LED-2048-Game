#ifndef RGB_LED_H
#define RGB_LED_H
	void init();
	void initPwm();
	void LED(int data[4][4], int row);
	void rowOFF();
	void LEDPwm(int data[4][4], int row);
	int buttonKey();
#endif