/*
  RGB fading
  Modified from the following example.
  http://arduino.cc/en/Tutorial/Fading
 */

int rPin = 11; // red
int gPin = 9;  // green
int bPin = 10; // blue

void setup() {
  //Serial.begin(9600);
}

void loop() {
  
  fading(rPin); // red
  fading(gPin); // green
  fading(bPin); // blue
}

void fading(int ledPin)
{
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {
    analogWrite(ledPin, fadeValue); // sets the value (range from 0 to 255):
    delay(10);                      // wait for 10 milliseconds to see the dimming effect
  }
    
  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {
    analogWrite(ledPin, fadeValue); // sets the value (range from 0 to 255):
    delay(10);                      // wait for 10 milliseconds to see the dimming effect
  }
}

