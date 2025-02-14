#include <Stepper.h>

// Define the number of steps per revolution for your stepper motor
const int stepsPerRevolution = 200;

// Initialize the stepper library on the pins connected to the L298 driver
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

// Define the pin for reading the PWM signal
const int pwmPin = 2;

// Define variables for pulse width measurement
unsigned long pulseWidth;
unsigned long period;
int motorPosition;

void setup() {
  // Set the PWM pin as input
  pinMode(pwmPin, INPUT);

  // Set the speed of the stepper motor
  myStepper.setSpeed(60); // You can adjust the speed as needed

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Measure the length of the high and low pulses
  unsigned long highTime = pulseIn(pwmPin, HIGH);
  unsigned long lowTime = pulseIn(pwmPin, LOW);

  // Calculate the total period of the PWM signal
  period = highTime + lowTime;

  // Calculate the duty cycle (percentage of high time)
  float dutyCycle = (float)highTime / period;

  // Map the duty cycle to a motor position (0-255)
  motorPosition = map(dutyCycle * 100, 0, 100, 0, 255);

  // Print the duty cycle and motor position for debugging
  Serial.print("Duty Cycle: ");
  Serial.print(dutyCycle * 100);
  Serial.print("%, Motor Position: ");
  Serial.println(motorPosition);

  // Move the stepper motor to the new position
  int stepsToMove = map(motorPosition, 0, 255, 0, stepsPerRevolution);
  myStepper.step(stepsToMove);

  // Add a small delay to avoid rapid changes
  delay(100);
}
