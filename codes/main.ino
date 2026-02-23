#include <Arduino.h>

// === Motor Pins (Exactly as in your working code) ===
#define motor_input1 26
#define motor_input2 25
#define motor_input3 33
#define motor_input4 32

// === Receiver Pins ===
// We only need 2 channels for basic driving
#define CH_STEERING_PIN 34 // Connected to Receiver Channel 1
#define CH_THROTTLE_PIN 35 // Connected to Receiver Channel 2

// === Helper Function (Exactly as in your working code) ===
void motorControl(int a, int b, int c, int d)
{
  digitalWrite(motor_input1, a);
  digitalWrite(motor_input2, b);
  digitalWrite(motor_input3, c);
  digitalWrite(motor_input4, d);
  //if ((a!=0)||(b!=0)||(c!=0)||(d!=0)) Serial.println(String(a)+" "+String(b)+" "+String(c)+" "+String(d));
}

void setup() {
  //Serial.begin(115200);

  // Motor Pins Setup
  pinMode(motor_input1, OUTPUT);
  pinMode(motor_input2, OUTPUT);
  pinMode(motor_input3, OUTPUT);
  pinMode(motor_input4, OUTPUT);

  // Receiver Pins Setup
  pinMode(CH_STEERING_PIN, INPUT);
  pinMode(CH_THROTTLE_PIN, INPUT);

  Serial.println("FlySky Drive Ready...");
}

void loop() {
  // Read the pulse width from the receiver (in microseconds)
  // Standard RC range is approx 1000 (Low) to 2000 (High), with 1500 as Center.
  int throttle = pulseIn(CH_STEERING_PIN, HIGH, 30000); 
  int steering = pulseIn(CH_THROTTLE_PIN, HIGH, 30000);

  if (steering > 1700) {
    motorControl(1, 0, 1, 0);
  }
  else if (steering < 1300 && steering > 1000) {
    motorControl(0, 1, 0, 1);
  }
  else if (throttle < 1300 && throttle > 1000) {
    motorControl(1, 0, 0, 1);
  }
  else if (throttle > 1700) {
    motorControl(0, 1, 1, 0);
  }
  else {
    motorControl(0, 0, 0, 0);
  }
  
  delay(10);
}
