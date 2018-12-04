/*
 * A simple programme that will change the intensity of
 * an LED based  * on the amount of light incident on 
 * the photo resistor.
 * 
 */

//PhotoResistor Pin
int numPins = 4;
int lightPins[] = {0, 1, 2, 3}; //the analog pin the photoresistor is 
int lastSensed;
int baseLevel = 160;

int findSensor ();
void setup()
{
  // pinMode(ledPin, OUTPUT); //sets the led pin to output
  Serial.begin(9600);
  lastSensed = findSensor();
}
 /*
 * loop() - this function will start after setup 
 * finishes and then repeat
 */
void loop()
{
  delay(1000);
  // find covered sensor
  int covered = findSensor();
  Serial.println(covered);
  if (covered != -1 && covered != lastSensed) {
    Serial.print("Covered: ");
    Serial.println(covered);
    Serial.print("LastSensed: ");
    Serial.println(lastSensed);
    
    if (covered > lastSensed) {
      if (covered == numPins - 1 && lastSensed == 0)
      {
        // turn clockwise
        Serial.println("clockwise");
      } else {
        // turn counter clockwise
        Serial.println("counter clockwise");
      }
    } else if (covered < lastSensed) {
      if (covered == 0 && lastSensed == numPins - 1) {
          // turn clockwise
          Serial.println("counter clockwise");
      } else {
        // turn clockwise
        Serial.println("clockwise");
      }
    }
    if (lastSensed != covered)
      lastSensed = covered;
  }
  
}



int findSensor () {
  for (int i = 0; i < numPins; i++) {
    if (analogRead(lightPins[i]) > baseLevel) {
      return i;
    }
  }
  return -1;
}

void test () {
  delay(1000);
  int lightLevel;
  for (int i = 0; i < 4; i++) {
    lightLevel = analogRead(lightPins[i]); //Read the
    Serial.print(i);
    Serial.print(": ");
    Serial.println(lightLevel);
  }
}
