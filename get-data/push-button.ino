#include <Wire.h>
#include "Adafruit_AS726x.h"

// Create the object
Adafruit_AS726x ams;

// Buffer to hold raw values
uint16_t sensorValues[AS726x_NUM_CHANNELS];

// Pin definitions
const int buttonPin = 3;  // Pin connected to the pushbutton
const int ledPin = 12;  // Pin connected to the built-in LED

// Variable to hold the button state
int buttonState = 0;

void setup() {
  Serial.begin(9600);
  while(!Serial);

  // Initialize digital pin LED_BUILTIN as an output
  pinMode(ledPin, OUTPUT);

  // Set the button pin as input with internal pull-up
  pinMode(buttonPin, INPUT_PULLUP);

  // Begin and make sure we can talk to the sensor
  if (!ams.begin()) {
    Serial.println("could not connect to sensor! Please check your wiring.");
    while (1);
  }
}

void loop() {
  // Read the state of the pushbutton (inverted logic due to pull-up)
  buttonState = digitalRead(buttonPin);

  // Check if the pushbutton is pressed (LOW means pressed due to pull-up)
  if (buttonState == LOW) {
    // Turn the LED off
    digitalWrite(ledPin, LOW);
    
    // Wait for 3 seconds
    delay(1000);
    
    // Turn the LED on
    digitalWrite(ledPin, HIGH);
    
    // Wait for 2 seconds
    delay(2000);

    // Read the sensor data
    readSensorData();
  } 
  else{
    digitalWrite(ledPin, LOW);
  }
}

void readSensorData() {
  // Read the device temperature
  uint8_t temp = ams.readTemperature();
  
  // ams.drvOn(); // Uncomment this if you want to use the driver LED for readings
  ams.startMeasurement(); // Begin a measurement
  
  // Wait till data is available
  bool rdy = false;
  while (!rdy) {
    delay(5);
    rdy = ams.dataReady();
  }
  // ams.drvOff(); // Uncomment this if you want to use the driver LED for readings

  // Read the values!
  ams.readRawValues(sensorValues);
  // ams.readCalibratedValues(calibratedValues);

  // Print the sensor values
  Serial.print("Violet: "); Serial.print(sensorValues[AS726x_VIOLET]);
  Serial.print(" Blue: "); Serial.print(sensorValues[AS726x_BLUE]);
  Serial.print(" Green: "); Serial.print(sensorValues[AS726x_GREEN]);
  Serial.print(" Yellow: "); Serial.print(sensorValues[AS726x_YELLOW]);
  Serial.print(" Orange: "); Serial.print(sensorValues[AS726x_ORANGE]);
  Serial.print(" Red: "); Serial.print(sensorValues[AS726x_RED]);
  Serial.println();
}
