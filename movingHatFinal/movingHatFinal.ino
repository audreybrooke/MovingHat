/*
 *  The final code base for final Project Group 6: movingHat. This code
 *  works with a variety of peripherals, such as photoresistors, the L2P3D chip,
 *  and a motor in order to create a "controlling" effect. It effectively allows
 *  the user to wave their hand in a circle over the photoresistors, and that controls
 *  the speed and direction o a motor, which is placed delicately below a hat, creating
 *  an image that the hat is moving via magic control.
 *  
 *  Authors: Audrey Brooke, Justin He, Maximilian Lee
 *  Group 6
 *  
 */

// Pin Configuration 
// Photoresistor controls
int numPins = 4;
int lightPins[] = {0, 1, 2, 3}; //the analog pin the photoresistor is 
int baseLevel = 160;
int lastSensed;

// Motor Controls
int motorDir = 0; // 0 is clockwise; 1 is counter clockwise
int motorPin = 9;  
int in1Pin = 10;
int in2Pin = 11;

void setup() {
  // open Serial printer
  Serial.begin(9600);
  baseLevel = test();
  // assign the index of the most recent sensor to lastSensed
  lastSensed = findSensor();
  // motor configuration
  pinMode(motorPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
}

void loop() {
  int covered = findSensor();
  Serial.print("Covered: ");
  Serial.println(covered);
  Serial.print("LastSensed: ");
  Serial.println(lastSensed);
  if (covered != -1 && covered != lastSensed) {
    if (covered > lastSensed) {
      if (covered == numPins - 1 && lastSensed == 0)
      {
        // turn clockwise
        Serial.println("clockwise");
        motorDir = 0;
      } else {
        // turn counter clockwise
        Serial.println("counter clockwise");
        motorDir = 1;
      }
    } else if (covered < lastSensed) {
      if (covered == 0 && lastSensed == numPins - 1) {
          // turn clockwise
          Serial.println("counter clockwise");
          motorDir = 1;
      } else {
        // turn clockwise
        Serial.println("clockwise");
        motorDir = 0;
      }
    }
    if (lastSensed != covered) {
      lastSensed = covered;
      if (motorDir == 0) {
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, HIGH);
      }
      else if (motorDir == 1) {
        digitalWrite(in1Pin, HIGH);
        digitalWrite(in2Pin, LOW);
      }
      activateMotor();
    }
  }
}

/*
 *  activateMotor() function, when called, rotates the motor in 1 go for a second.
 *  
 */
void activateMotor() {
  Serial.println("why");
  digitalWrite(motorPin, HIGH);
  delay(1500);
  digitalWrite(motorPin, LOW);
  delay(1000);
}

/*
 *  findSensor() determines which of the sensors is
 *  being covered (if any). Will return index of the sensor,
 *  and if no sensors are being covered, will return
 *  -1. 
 * 
 */
int findSensor () {
  for (int i = 0; i < numPins; i++) {
    if (analogRead(lightPins[i]) > baseLevel) {
      return i;
    }
  }
  return -1;
}

/*
 *  Test() allows us to determine the base level of light levels
 *  in the environment, so that way our measurements for our 
 *  photoresistors are of highest accuracy possible.
 *  
 */
int test () {
  delay(1000);
  int lightLevel;
  for (int i = 0; i < 4; i++) {
    lightLevel = analogRead(lightPins[i]); //Read the
    Serial.print(i);
    Serial.print(": ");
    Serial.println(lightLevel);
  }
  return lightLevel + 50;
}
