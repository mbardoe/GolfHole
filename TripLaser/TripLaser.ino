/* light beam trigger based on SWEEP by Scott Fitzgerald & Barragan and the adafruit photocell
<<<<<<< HEAD
    test

		A laser pointer is used to create a tripwire across a box. When the beam is 
		broken the servo is activated and a flag is raised. Then two rows of leds light up
		in an alternating pattern. A delay of 2 seconds happens and then the whole thing resets. 
		Added a siren sound with a piezo.
=======
    test and siren sketch that Ben Small provided.
		A laser pointer is used to create a tripwire across a box. When the beam is 
		broken the servo is activated and a flag is raised. Then two rows of leds light up
		in an alternating pattern. A delay of 2 seconds happens and then the whole thing resets. 
		Added a siren through a piezo.
>>>>>>> origin/master

		by Matthew K. Bardoe
		July 15, 2016


*/

#include <Servo.h>

// LED info
int blueLED = 3;  // the pin for one string of LEDs
int yellowLED = 4; // the pin for the other string of LED's

<<<<<<< HEAD
// twelve servo objects can be created on most boards
int laserPin = 2;
int blueLED = 3;
int yellowLED = 4;
=======
>>>>>>> origin/master
// Siren info
int speakerpin = 8; // the pin to which the Piezo will be attached  (other Piezo wire is grounded)
int lowpitch = 500;
int highpitch = 3000;

<<<<<<< HEAD
int servoPosition = 90;
=======
//laser info
int laserPin = 2; // the pin for the laser pointer
int tripValue =950; // the reading of the beam for no laser.

//Servo info
Servo myservo;  // create servo object to control a servo
int servoPosition = 90; // lower position for the flag. 
>>>>>>> origin/master
int pos = 90;    // variable to store the servo position

//Photocell info
int photocellPin = A0;     // the cell and 10K pulldown are connected to a0
<<<<<<< HEAD
int photocellReading = 0;
int photocellInit = 0;
=======
int photocellReading = 0;  // the current reading of the photocell. Generally with a laser the reading is close to 1000. 
int photocellInit = 0; // This is used in the startup to make sure that the beam is aligned with the photocell


>>>>>>> origin/master
void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  // Set the pins
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  // test lights
  lightLights();
  // Test laser
  digitalWrite(2, HIGH); //Turn on Laser
  while (photocellInit < 900)
  {
    photocellReading = analogRead(photocellPin);
    photocellInit = 0.1 * photocellReading + .9 * photocellInit;
    Serial.println(photocellReading);
  }
  Serial.println("BEGIN");
  myservo.write(servoPosition);
}

void loop() {
  photocellReading = analogRead(photocellPin);
  if (photocellReading < 950) {
    //Raise
    digitalWrite(laserPin, LOW);
    Serial.println("Raise the flag");
    for (pos = 90; pos <= 172; pos += 10) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (int i = 0; i < 3; i++)
    {
      lightLights();
    }
    servoPosition = 172;
    delay(2000);
    digitalWrite(laserPin, HIGH);
    delay(200);
  }
  else if (servoPosition != 90 ) {
    Serial.println("Lower the flag");
    for (pos = 172; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    servoPosition = 90;

  }
}

void lightLights() {
  Serial.println("Light Blue lights");
  digitalWrite(3, HIGH);
<<<<<<< HEAD
  
    for (int pitch = lowpitch; pitch < highpitch; pitch++) { // cycles the pitch up from lowpitch to high pitch (Hz)
=======
  //Activate Siren
  for (int pitch = lowpitch; pitch < highpitch; pitch++) { // cycles the pitch up from lowpitch to high pitch (Hz)
>>>>>>> origin/master
      tone(speakerpin, pitch, 3);  //plays a given tone for 2ms

    }
    for (int pitch = highpitch; pitch > lowpitch; pitch--) { // cycles the pitch down from higpitch to lowpitch
      // play the tone for 20 ms on pin 8
      tone(speakerpin, pitch, 3);

    }
  
<<<<<<< HEAD
  //delay(500);
  Serial.println("Light Yellow lights");

  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  
    for (int pitch = lowpitch; pitch < highpitch; pitch++) { // cycles the pitch up from lowpitch to high pitch (Hz)
=======
  //Serial.println("Light Yellow lights");
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  //activate siren
  for (int pitch = lowpitch; pitch < highpitch; pitch++) { // cycles the pitch up from lowpitch to high pitch (Hz)
>>>>>>> origin/master
      tone(speakerpin, pitch, 3);  //plays a given tone for 2ms

    }
    for (int pitch = highpitch; pitch > lowpitch; pitch--) { // cycles the pitch down from higpitch to lowpitch
      // play the tone for 20 ms on pin 8
      tone(speakerpin, pitch, 3);

    }
  
<<<<<<< HEAD

  //delay(500);
=======
>>>>>>> origin/master
  digitalWrite(4, LOW);

}

