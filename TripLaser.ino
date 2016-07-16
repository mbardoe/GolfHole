/* light beam trigger based on SWEEP by Scott Fitzgerald & Barragan and the adafruit photocell
    test
		A laser pointer is used to create a tripwire across a box. When the beam is 
		broken the servo is activated and a flag is raised. Then two rows of leds light up
		in an alternating pattern. A delay of 2 seconds happens and then the whole thing resets. 

		by Matthew K. Bardoe
		July 15, 2016


*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo


int laserPin = 2; // the pin for the laser pointer
int blueLED = 3;  // the pin for one string of LEDs
int yellowLED = 4; // the pin for the other string of LED's
int tripValue =950; // the reading of the beam for no laser.
int servoPosition = 90; // lower position for the flag. 
int pos = 90;    // variable to store the servo position
int photocellPin = A0;     // the cell and 10K pulldown are connected to a0
int photocellReading = 0;  // the current reading of the photocell. Generally with a laser the reading is close to 1000. 
int photocellInit = 0; // This is used in the startup to make sure that the beam is aligned with the photocell
void setup() {
  Serial.begin(9600);  // begin serial
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  // Set the pins
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  // test lights
  lightLights(); // Each strip should light up.
  // Test laser
  digitalWrite(2, HIGH); //Turn on Laser
	
  while (photocellInit < 900)
  {
    photocellReading=analogRead(photocellPin);
    photocellInit = 0.1 * photocellReading + .9 * photocellInit;
    Serial.println(photocellReading);
  }
  Serial.println("BEGIN");
	
  myservo.write(servoPosition);// move servo to the start position.
}

void loop() {
  photocellReading = analogRead(photocellPin); // get a reading on the beam
  if (photocellReading < tripValue) {
    //Raise
    digitalWrite(laserPin, LOW);	// turn off the laser for now.
    //Serial.println("Raise the flag");
    for (pos = 90; pos <= 172; pos += 10) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (int i=0; i<8; i++) // flash lights
    {
      lightLights();
    }
    servoPosition = 172; // set the current position. When I set it to 180 it felt like the servo was trying to go beyond itself.
    delay(2000); // wait 2 seconds before reset.
    digitalWrite(laserPin,HIGH); // restart the beam.
    delay(200); // let the beam get to the sensor.
  }
  else if (servoPosition != 90 ) {
    //Serial.println("Lower the flag");
    for (pos = 172; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    servoPosition = 90;
    
  }
}

void lightLights() { // little script to flash each strip.
  //Serial.println("Light Blue lights");
  digitalWrite(3, HIGH);
  delay(500);
  //Serial.println("Light Yellow lights");
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW);

}

