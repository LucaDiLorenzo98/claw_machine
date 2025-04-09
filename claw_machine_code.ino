#include <Servo.h>

Servo servo_y1; 
Servo servo_y2;
Servo servo_x;

Servo servo_z;
Servo servo_gripper; 

const int VRx = A0;
const int VRy = A1;

const int SW = 2;
const int SW2 = 3;

void setup() {
  Serial.begin(9600);
  servo_y1.attach(6);
  servo_y2.attach(4);
  servo_x.attach(5);

  servo_z.attach(7);
  servo_gripper.attach(8);

  pinMode(SW, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);

  servo_gripper.write(0);
}

void loop() {

  int xValue = analogRead(VRx);
  int yValue = analogRead(VRy);

  int swState = digitalRead(SW);
  int swState2 = digitalRead(SW2);

  delay(200);

  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.print(yValue);
  Serial.print(" | SW: ");
  Serial.print(swState == LOW ? "PREMUTO" : "RILASCIATO");
  Serial.print(" | SW2: ");
  Serial.println(swState2 == LOW ? "PREMUTO" : "RILASCIATO");

  // handle joystick input anmd servo movement

  if(xValue > 600) {
    servo_x.write(0);
  } else if(xValue < 400) {
    servo_x.write(180);
  } else {
    servo_x.write(90);
  }

  if(yValue > 600) {
    servo_y1.write(0);
    servo_y2.write(180);
  } else if(yValue < 400) {
    servo_y1.write(180);
    servo_y2.write(0);
  } else {
    servo_y1.write(90);
    servo_y2.write(90);
  }

  // handle button press

  if(swState2 == LOW) {
    // open gripper
    servo_gripper.write(140);

    delay(500);

    // move down
    servo_z.write(0);

    delay(1400);

    // stop
    servo_z.write(90);

    delay(1000);

    // close gripper
    servo_gripper.write(0);

    delay(1000);

    // move up
    servo_z.write(180);

    delay(2300);
    
    // stop
    servo_z.write(90);
  }

  if(swState == LOW) {
    // open gripper
    servo_gripper.write(140);
  }

  /*
  if(swState == LOW) {
    servo_gripper.write(140);
    servo_z.write(0);
  } else if(swState2 == LOW) {
    servo_gripper.write(0);
    servo_z.write(180);
  } else {
    servo_z.write(90);
  }
  */

}
