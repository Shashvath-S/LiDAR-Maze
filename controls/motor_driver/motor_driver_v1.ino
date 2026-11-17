/* Omnidirectional (mecanum) car: forward, backward, strafe left, and strafe right */
#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Motor positions (change the numbers if your wiring is different)
Adafruit_DCMotor *frontRight = AFMS.getMotor(2);
Adafruit_DCMotor *backRight  = AFMS.getMotor(4);
Adafruit_DCMotor *frontLeft  = AFMS.getMotor(1);
Adafruit_DCMotor *backLeft   = AFMS.getMotor(3);

int speed = 160; // Increased from 80 to overcome mecanum wheel friction
int led_Pin = 13;

void wheel(Adafruit_DCMotor *m, uint8_t dir) {
  m->setSpeed(dir == RELEASE ? 0 : speed);
  m->run(dir);
}

void drive(uint8_t fl, uint8_t fr, uint8_t bl, uint8_t br) {
  wheel(frontLeft,  fl);
  wheel(frontRight, fr);
  wheel(backLeft,   bl);
  wheel(backRight,  br);
}

void stopCar() { drive(RELEASE, RELEASE, RELEASE, RELEASE); }

//                        FL        FR        BL        BR
void moveForward()  { drive(FORWARD,  FORWARD,  FORWARD,  FORWARD);  }
void moveBackward() { drive(BACKWARD, BACKWARD, BACKWARD, BACKWARD); }
void strafeLeft()   { drive(BACKWARD, FORWARD,  FORWARD,  BACKWARD); }
void strafeRight()  { drive(FORWARD,  BACKWARD, BACKWARD, FORWARD);  }

void setup() {
  Serial.begin(115200);
  AFMS.begin();
  pinMode(led_Pin, OUTPUT);

  // Blink for ~4 seconds before moving
  for (int i = 0; i < 20; i++) {
    digitalWrite(led_Pin, HIGH);
    delay(100);
    digitalWrite(led_Pin, LOW);
    delay(100);
  }
}

void loop() {
  Serial.println("Forward");
  moveForward();
  delay(2000);
  stopCar();
  delay(1000);

  Serial.println("Backward");
  moveBackward();
  delay(2000);
  stopCar();
  delay(1000);

  Serial.println("Left");
  strafeLeft();
  delay(2000);
  stopCar();
  delay(1000);

  Serial.println("Right");
  strafeRight();
  delay(2000);
  stopCar();
  delay(3000);
}