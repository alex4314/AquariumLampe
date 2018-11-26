/*
  Fading

  This example shows how to fade an LED using the pwmWrite() function.

  Created 1 Nov 2008
  By David A. Mellis
  Modified 17 June 2009
  By Tom Igoe

  Modified by LeafLabs for Maple

  http://arduino.cc/en/Tutorial/Fading

  For differences between Maple's pwmWrite() and Arduino's analogWrite():
  http://leaflabs.com/docs/lang/api/analogwrite.html#arduino-compatibility
*/

int ledPin = PA8; // Connect an LED to digital pin 9, or any other
// PWM-capable pin

//HardwareTimer timer(1);

void setup() {
  pwmWrite(ledPin, 0);
  pinMode(ledPin, PWM);  // setup the pin as PWM
  pwmWrite(ledPin, 0);
  //PWM_OPEN_DRAIN
  Serial.begin(9600);
  Timer1.setPrescaleFactor(16);
  Timer1.setOverflow(4096);
  delay(1000);
  Serial.println("Beginn...");

  //pinMode(PA0, PWM);
  myservo.attach(PA0);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);
  delay(5000);
  myservo.write(180);
  delay(5000);
  myservo.write(0);
  delay(5000);
  myservo.write(180);
  delay(5000);
  myservo.write(0);
  delay(5000);
}

void loop()  {
  //  // Fade in from min to max in increments of 1280 points:
  //  for (int fadeValue = 0; fadeValue <= 35; fadeValue++) {
  //    // Sets the value (range from 0 to 65535):
  //    pwmWrite(ledPin, fadeValue);
  //    // Wait for 30 milliseconds to see the dimming effect:
  //delay(1000);
  //  }
  //
  for (int fadeValue = 0 ; fadeValue < 4096; fadeValue += 1) {
    // Sets the value (range from 0 to 1280):
    pwmWrite(ledPin, fadeValue);
    // Wait for 30 milliseconds to see the dimming effect:

    Serial.print(" ...");
    Serial.println(fadeValue);
    delay(200);

  }
  //
  //pwmWrite(ledPin, 79);
  //  delay(100);
  //  pwmWrite(ledPin, 255);
  //  delay(100);

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }

}
