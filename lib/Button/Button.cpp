/*
||
|| @file Button.cpp
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

//include the class definition
#include "Button.h"

/*
|| <<constructor>>
|| @parameter buttonPin sets the pin that this switch is connected to
|| @parameter buttonMode indicates PULLUP or PULLDOWN resistor
*/
Button::Button(uint8_t buttonPin, uint8_t buttonMode){
	this->pin=buttonPin;
    pinMode(pin,INPUT);
	buttonMode==PULLDOWN ? pulldown() : pullup();
    state = 0;
    bitWrite(state,CURRENT,!mode);
	but_lock = 0;
}

/*
|| Set pin HIGH as default
*/
void Button::pullup(void){
	mode=PULLUP;
	digitalWrite(pin,HIGH);
}

/*
|| Set pin LOW as default
*/
void Button::pulldown(void){
	mode=PULLDOWN;
	//digitalWrite(pin,LOW);
}

/*
|| Return the bitWrite(state,CURRENT, of the switch
*/
bool Button::isPressed(void){
    bitWrite(state,PREVIOUS,bitRead(state,CURRENT));
    if (digitalRead(pin) == mode){
        bitWrite(state,CURRENT,false);
    } else {
	    delay(DEBOUNCE_TIME);
		if (digitalRead(pin) != mode)
            bitWrite(state,CURRENT,true);
    }
    if (bitRead(state,CURRENT) != bitRead(state,PREVIOUS)){
        bitWrite(state,CHANGED,true);
    }else{
        bitWrite(state,CHANGED,false);
    }
	int start = millis();   
	return bitRead(state,CURRENT);
}

/*
|| Return true if the button has been pressed
*/
bool Button::wasPressed(void){
    if (bitRead(state,CURRENT)){
        return true;
    } else {
        return false;
    }
}

/*
|| Return true if state has been changed
*/
bool Button::stateChanged(void){
    return bitRead(state,CHANGED);
}

/*
|| Return true if the button is pressed, and was not pressed before
*/
bool Button::uniquePress(void){
    return (isPressed() && stateChanged());
}


uint8_t Button::chkButtonState(void)
{
 if (uniquePress())
    {
	 bitWrite(state, S_LOCK, false);
	 bitWrite(state, D_LOCK, false);
	 start = millis();
     //Serial.println(start);
	}
 else if (isPressed())
    {
     //Serial.println(millis() - start);
	 if (((millis() - start) > LONG_CLICK_DURATION) && (!(bitRead(state, D_LOCK))))
	    {
		 bitWrite(state, D_LOCK, true);
         return LONG_CLICK;
		}
     else if (!(bitRead(state, S_LOCK)))
	    {
		 bitWrite(state, S_LOCK, true);
		 return CLICK;	   
		}
	} 
 else 
    return NO_CLICK; 
}

/*
|| @changelog
|| | 2009-05-05 - Alexander Brevig : Added uniquePress()
|| | 2009-04-24 - Alexander Brevig : Added wasPressed()
|| | 2009-04-12 - Alexander Brevig : Added constructor
|| |                                 Shortened logic
|| | 2009-04-10 - Alexander Brevig : Namechange from Switch
|| | 2009-04-07 - Alexander Brevig : Altered API
|| | 2008-10-23 - Alexander Brevig : Initial Release
|| | 2008-10-22 - Alexander Brevig : Class implemented
|| # 
*/






