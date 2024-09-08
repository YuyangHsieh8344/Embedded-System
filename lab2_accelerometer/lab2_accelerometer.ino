// Core library for code-sense
#include "Energia.h"

// Following includes for Energia only
#include "SPI.h"

// Include the library for the LCD screen
#include "Screen_HX8353E.h" 

Screen_HX8353E myScreen;

const int xpin = 23; // x-axis of the accelerometer
const int ypin = 24; // y-axis
const int zpin = 25; // z-axis (only on 3-axis models)

void setup() {
  // put your setup code here, to run once:

  // initialize for sending diagnostic info to computer
  Serial.begin(9600); 

  //Initialize the LCD Screen
  myScreen.begin();
  myScreen.clear(blackColour);

  // Set the analog pins as inputs
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(zpin, INPUT);
}

void loop() {
  // Read the analog values from the accelerometer
  int x = analogRead(xpin);
  int y = analogRead(ypin);
  int z = analogRead(zpin);


  int xAccel = x;
  int yAccel = y;
  int zAccel = z;



  // Display the XYZ values on the LCD screen using myScreen.gText()
  myScreen.gText(10, 10, "X-Axis: " + String(xAccel) , greenColour);
    
  myScreen.gText(10, 55, "Y-Axis: " + String(yAccel) , greenColour); 
     
  myScreen.gText(10, 100, "Z-Axis: " + String(zAccel) , greenColour); 
    

  // Also send the values to the Serial monitor
  Serial.print(xAccel);
  Serial.print(" ");
  
  Serial.print(yAccel);
  Serial.print(" ");
  Serial.println(zAccel);
  
  delay(200); 
}
