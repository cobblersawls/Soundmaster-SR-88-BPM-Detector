#include "SevSeg.h"
SevSeg sevseg; //Initiates a seven segment controller object
int analogInput = 0; // define analog OUT signal pin
int analog;
float counter = 0;
float calculation;
int previousVal=0;
int screenDisplay = 0000;
int buffArray[] = {0,0,0,0}

unsigned long previousMillis = 0;
const long interval = 4000; // interval for recording data for the bpm
void setup() {
  pinMode(analogInput, INPUT); // set the OUT signal pin as an input
  Serial.begin(9600); // launch the serial monitor

byte numDigits = 4;  
    byte digitPins[] = {2, 5, 6, 7};// https://www.instructables.com/Using-a-4-digit-7-segment-display-with-arduino/
    byte segmentPins[] = {3, 4, 8, 9, 10, 11, 12, 13}; // With the above, the display can be set up.
    bool resistorsOnSegments = 0; 
    // variable above indicates that 4 resistors were placed on the digit pins.
    // set variable to 1 if you want to use 8 resistors on the segment pins.
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(90);

}
 
void loop() {
 
analog = analogRead(analogInput);  // read the voltage level on the A0
sevseg.setNumber(screenDisplay,1); // keeps the screen on, initialised with 0000.
   sevseg.refreshDisplay(); // Must run repeatedly
   
  if(analog > 700){ // if there is a pulse, it's counted, it makes sure it doesn't count one pulse as 2.
     counter++;
     if (previousVal > 700){
      counter--;
      previousVal=analog;
     }
      else{
        previousVal=analog;
      }
  }
   else{
   previousVal=analog;
   }


   
 unsigned long currentMillis = millis(); // The interval where the counts are taken
  if (currentMillis - previousMillis >= interval){
    // save the last time you took a reading
  previousMillis = currentMillis;
  calculation = (counter/4)*30; // works out the bpm
  if (calculation > 100){
    calculation = calculation/2; // if the bpm goes over 100, it divides it by 2.
  }
  screenDisplay = calculation*10; // Gets around the floating point issue on the display
  Serial.println(calculation,1);

  calculation = 0; // Resets the values back for the next count.
  counter = 0;
    }
  } 
  
