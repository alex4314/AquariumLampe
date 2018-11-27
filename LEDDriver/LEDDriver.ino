#include <Wire_slave.h>
#include <QueueArray.h>

struct animation {
  unsigned int startpoint;
  unsigned int duration;
  byte target;
};

animation channel[7];

int ledPin = PA8; // Connect an LED to digital pin 9, or any other
byte message[32];
byte modus = 0;

void setup() {
  //Serial.begin(9600);

  pinMode(ledPin, PWM);  // setup the pin as PWM
  pwmWrite(ledPin, 0);

  Timer1.setPrescaleFactor(16);
  Timer1.setOverflow(4096);

  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent);

  flushMessages();
  for (byte i = 0; i < 7; i++) 
    channel[i] = { 0 , 0 , 0 };
  
}

void loop()  {
  handleMessage();

  switch (modus) {
    case 10:

      break;
    case 20:

      break;
    case 30:

      break;
    case 40:

      break;
  }

  for (int fadeValue = 0 ; fadeValue < 4096; fadeValue += 1) {
    pwmWrite(ledPin, fadeValue);
  }
  int pos = 0;
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    //    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    //    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }

}

void receiveEvent(int howMany) {
  byte i = 0;
  while (Wire.available()) { // loop through all but the last
    message[i] = Wire.read(); // receive byte as a character
    i++;
  }
}

void handleMessage() {
  switch (message[0]) {
    case 0:
      break;

    case 21:     // new animation received
      channel[message[1]].startpoint = millis() + message[2];
      channel[message[1]].duration = combineByteToInt(message[3], message[4]);
      channel[message[1]].target = message[5];
      
      flushMessages();
      break;

    default:
      modus = message[0];
  }
}

int combineByteToInt(byte high, byte low) {
  int result= high << 8;
  result |= low;
  return result;
}

void flushMessages() {
  for (byte i = 0; i < 32; i++)
    message[i] = 0;
}
