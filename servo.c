

#include <Servo.h>

// Creates a servo object to control a servo
Servo myServo;

// Initialise the pins
const int buttonPin = 2;
const int ledPin = 13;
const int servoPin = 9;

// Initialise variables
int servoDirection = 1; // Oscillates between 1 & -1 for direction
int servoPos = 0;       // Stores the position of the servo arm
int buttonState = 0;    // Stores the value of the button state
int dirChange = 0;

// Begin program
void setup() {
   // Init the LED pin as OUTPUT
   pinMode(ledPin, OUTPUT);
   // Init the push button as input
   pinMode(buttonPin, INPUT);
   // 'Attach' the servo to the pin
   myServo.attach(servoPin);
   // Reset servo position to 0
   myServo.write(servoPos);
}

void loop() {
   // Get state of button
   buttonState = digitalRead(buttonPin);

   while (buttonState == HIGH) {
      if (servoDirection == 1 && servoPos != 180) {
         // Moving from 0 to 180
         digitalWrite(ledPin, HIGH);   // Sets led to on
         servoPos++;    // Increments the desired position
         myServo.write(servoPos);   // Sets the desired position
         delay(15);     // Provides time for the servo to adjust
      } else if (servoDirection == -1 && servoPos != 0) {
         // Moving from 180 to 0
         digitalWrite(ledPin, HIGH);   // Sets led to on
         servoPos--;    // Decrements the desired position
         myServo.write(servoPos);   // Sets the desired position
         delay(15);     // Provides time for the servo to adjust
      }
      dirChange = 1;
      buttonState = digitalRead(buttonPin);
   }

   if (dirChange == 1) {
      servoDirection = servoDirection * -1;
      dirChange = 0;
   }

   digitalWrite(ledPin, LOW);
}