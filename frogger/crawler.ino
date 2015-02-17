/*
 * Servo with Potentiometer control
 * Theory and Practice of Tangible User Interfaces
 * October 11 2007
 */

int servoPin = 7;      // Control pin for servo motor
int potPin   = 0;      // select the input pin for the potentiometer

int pulseWidth = 0;    // Amount to pulse the servo
long lastPulse = 0;    // the time in millisecs of the last pulse
int refreshTime = 20;  // the time in millisecs needed in between pulses
int val;               // variable used to store data from potentiometer

int minPulse = 500;   // minimum pulse width

void setup() {
  pinMode(servoPin, OUTPUT);  // Set servo pin as an output pin
  pulseWidth = minPulse;      // Set the motor position to the minimum
  Serial.begin(9600);         // connect to the serial port
  Serial.println("servo_serial_better ready");
}

void loop() {
  val = analogRead(potPin);    // read the value from the sensor, between 0 - 1024
  
  if (val > 0 && val <= 999 ) {
    pulseWidth = val*2 + minPulse;  // convert angle to microseconds
    
    Serial.print("moving servo to ");
    Serial.println(pulseWidth,DEC);
  
  }
  updateServo();   // update servo position
}

// called every loop(). 
void updateServo() {
  // pulse the servo again if the refresh time (20 ms) has passed:
  if (millis() - lastPulse >= refreshTime) {
    digitalWrite(servoPin, HIGH);   // Turn the motor on
    delayMicroseconds(pulseWidth);  // Length of the pulse sets the motor position
    digitalWrite(servoPin, LOW);    // Turn the motor off
    lastPulse = millis();           // save the time of the last pulse
  }
}

