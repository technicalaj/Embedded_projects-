#include <RF24.h>
#include <SPI.h>
#include <RF24Audio.h>
#include "printf.h"    // General includes for radio and audio lib

RF24 radio(7,8);    // Set radio up using pins 7 (CE) 8 (CS)
RF24Audio rfAudio(radio,0); // Set up the audio using the radio, and set to radio number 0

int TALKBUTTON = 3;

void setup() {      
  Serial.begin(115200);
  
  printf_begin();
  radio.begin();
  radio.printDetails();
  rfAudio.begin();

  pinMode(TALKBUTTON, INPUT);

  //sets interrupt to check for button talk abutton press
  attachInterrupt(digitalPinToInterrupt(TALKBUTTON), talk, CHANGE);
  
  //sets the default state for each module to recevie
  rfAudio.receive();
}

void talk()
{
  if (digitalRead(TALKBUTTON)) rfAudio.transmit();
  else rfAudio.receive();
}


void loop()
{
}
