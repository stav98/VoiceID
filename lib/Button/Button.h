/*
||
|| @file Button.h
|| @version 1.6
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide an easy way of making buttons
|| #
||
|| @license
|| | Copyright (c) 2009 Alexander Brevig. All rights reserved.
|| | This code is subject to AlphaLicence.txt
|| | alphabeta.alexanderbrevig.com/AlphaLicense.txt
|| #
||
*/

#ifndef BUTTON_H
#define BUTTON_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define PULLUP HIGH
#define PULLDOWN LOW

#define CURRENT  0
#define PREVIOUS 1
#define CHANGED  2
#define D_LOCK   3
#define S_LOCK   4

#define DEBOUNCE_TIME  25
#define LONG_CLICK_DURATION  2000
#define LONG_CLICK      2
#define CLICK		    1
#define NO_CLICK		0

class Button{
  public:
    Button(uint8_t buttonPin, uint8_t buttonMode=PULLDOWN);
    void pullup();
    void pulldown();
    bool isPressed();
    bool wasPressed();
    bool stateChanged();
	bool uniquePress();
	uint8_t chkButtonState();
  private: 
    uint8_t pin;
    uint8_t mode;
    uint8_t state;
	uint8_t but_lock;
	unsigned long start;
};

#endif

/*
|| @changelog
|| | 1.6 2009-05-05 - Alexander Brevig : Added uniquePress, it returns true if the state has changed AND the button is pressed
|| | 1.5 2009-04-24 - Alexander Brevig : Added stateChanged, @contribution http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?action=viewprofile;username=klickadiklick
|| | 1.4 2009-04-24 - Alexander Brevig : Added wasPressed, @contribution http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?action=viewprofile;username=klickadiklick
|| | 1.3 2009-04-12 - Alexander Brevig : Added constructor with one parameter Button(uint8_t buttonPin)
|| | 1.2 2009-04-10 - Alexander Brevig : Namechange from Switch to Button
|| | 1.1 2009-04-07 - Alexander Brevig : Altered API
|| | 1.0 2008-10-23 - Alexander Brevig : Initial Release
|| #
*/


