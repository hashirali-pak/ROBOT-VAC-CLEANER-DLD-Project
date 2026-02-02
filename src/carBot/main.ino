/*
 * Project: B5 Vac Bomber (DLD Semester Project)
 * Created by: Hamza Mir & Team 
 * Context: 3rd Semester Digital Logic Design Final
 * * What this code does:
 * This is the brain of our robot. It reads character commands from the 
 * Android Bluetooth app (via HC-05) and translates them into motor movements 
 * using the L293D shield. We added some custom moves like "Victory Dance" too!
 */

#include <AFMotor.h>

// --- MOTOR SETUP ---
// We are using the Adafruit Motor Shield library.
// 1KHz frequency gave us the smoothest torque for the gear motors.
AF_DCMotor motor1(1, MOTOR12_1KHZ); // Front Left
AF_DCMotor motor2(2, MOTOR12_1KHZ); // Front Right
AF_DCMotor motor3(3, MOTOR34_1KHZ); // Rear Left
AF_DCMotor motor4(4, MOTOR34_1KHZ); // Rear Right

char val;         // Variable to store the command coming from Bluetooth
int Speeed = 255; // Default start speed (Max Power!)

void setup() {
  Serial.begin(9600); // Start serial comms to talk to the HC-05 module
}

void loop() {
  // Check if the phone sent a command
  if (Serial.available() > 0) {
    val = Serial.read(); // Store the incoming character

    // ---------------------------------------------------------
    // SPEED CONTROL
    // The app sends numbers '0' to '9' to set speed.
    // 'q' is our turbo button (Max speed).
    // ---------------------------------------------------------
    if (val == '0') Speeed = 0;
    else if (val == '1') Speeed = 100;
    else if (val == '2') Speeed = 120;
    else if (val == '3') Speeed = 140;
    else if (val == '4') Speeed = 160;
    else if (val == '5') Speeed = 180;
    else if (val == '6') Speeed = 200;
    else if (val == '7') Speeed = 220;
    else if (val == '8') Speeed = 240;
    else if (val == '9') Speeed = 245;
    else if (val == 'q') Speeed = 255; 

    // ---------------------------------------------------------
    // MOVEMENT LOGIC
    // Mapping the characters sent by the controller app
    // to our custom functions below.
    // ---------------------------------------------------------
    if (val == 'F') forward();
    else if (val == 'B') back();
    else if (val == 'L') left();
    else if (val == 'R') right();
    
    // Diagonal Moves:
    // This was tricky! We slow down one side to make it curve.
    else if (val == 'G') topleft();     
    else if (val == 'I') topright();    
    else if (val == 'H') bottomleft();  
    else if (val == 'J') bottomright(); 
    
    else if (val == 'S' || val == 'T') Stop(); 

    // ---------------------------------------------------------
    // COOL CUSTOM MOVES
    // We mapped the extra function buttons (F1, F2, F3) 
    // to do special tricks.
    // ---------------------------------------------------------
    else if (val == 'K') victoryDance(); // Button F1: Wiggles the robot
    else if (val == 'P') circleMove();   // Button F2: Does a 360 drift
    else if (val == 'N') zigZag();       // Button F3: Runs a Z-pattern
  }
}

// =========================================================
// OUR CUSTOM FUNCTIONS
// =========================================================

// A little celebration move - wiggles left and right
void victoryDance() {
  for (int i = 0; i < 4; i++) {
    left(); delay(150);
    right(); delay(150);
  }
  Stop();
}

// Drifts in a circle by powering only the front motors
void circleMove() {
  motor1.setSpeed(Speeed); motor1.run(FORWARD);
  motor2.setSpeed(Speeed); motor2.run(FORWARD);
  motor3.run(RELEASE); // Let the back wheels drag
  motor4.run(RELEASE);
  delay(2000); 
  Stop();
}

// A pre-programmed evasion pattern
void zigZag() {
  forward(); delay(400);
  left();    delay(200);
  forward(); delay(400);
  right();   delay(200);
  Stop();
}

// =========================================================
// BASIC MOVEMENT (L293D DRIVER LOGIC)
// =========================================================

void forward() {
  motor1.setSpeed(Speeed); motor1.run(FORWARD);
  motor2.setSpeed(Speeed); motor2.run(FORWARD);
  motor3.setSpeed(Speeed); motor3.run(FORWARD);
  motor4.setSpeed(Speeed); motor4.run(FORWARD);
}

void back() {
  motor1.setSpeed(Speeed); motor1.run(BACKWARD);
  motor2.setSpeed(Speeed); motor2.run(BACKWARD);
  motor3.setSpeed(Speeed); motor3.run(BACKWARD);
  motor4.setSpeed(Speeed); motor4.run(BACKWARD);
}

void left() {
  // Tank turn logic: Left wheels forward, Right wheels back
  motor1.setSpeed(Speeed); motor1.run(FORWARD);
  motor2.setSpeed(Speeed); motor2.run(FORWARD);
  motor3.setSpeed(Speeed); motor3.run(BACKWARD);
  motor4.setSpeed(Speeed); motor4.run(BACKWARD);
}

void right() {
  // Tank turn logic: Left wheels back, Right wheels forward
  motor1.setSpeed(Speeed); motor1.run(BACKWARD);
  motor2.setSpeed(Speeed); motor2.run(BACKWARD);
  motor3.setSpeed(Speeed); motor3.run(FORWARD);
  motor4.setSpeed(Speeed); motor4.run(FORWARD);
}

void topleft() {
  // To curve left, we keep right motors at full speed
  // and drop left motors to 1/3 speed.
  motor1.setSpeed(Speeed); motor1.run(FORWARD);
  motor2.setSpeed(Speeed); motor2.run(FORWARD);
  motor3.setSpeed(Speeed / 3); motor3.run(FORWARD);
  motor4.setSpeed(Speeed / 3); motor4.run(FORWARD);
}

void topright() {
  motor1.setSpeed(Speeed / 3); motor1.run(FORWARD);
  motor2.setSpeed(Speeed / 3); motor2.run(FORWARD);
  motor3.setSpeed(Speeed); motor3.run(FORWARD);
  motor4.setSpeed(Speeed); motor4.run(FORWARD);
}

void bottomleft() {
  motor1.setSpeed(Speeed); motor1.run(BACKWARD);
  motor2.setSpeed(Speeed); motor2.run(BACKWARD);
  motor3.setSpeed(Speeed / 3); motor3.run(BACKWARD);
  motor4.setSpeed(Speeed / 3); motor4.run(BACKWARD);
}

void bottomright() {
  motor1.setSpeed(Speeed / 3); motor1.run(BACKWARD);
  motor2.setSpeed(Speeed / 3); motor2.run(BACKWARD);
  motor3.setSpeed(Speeed); motor3.run(BACKWARD);
  motor4.setSpeed(Speeed); motor4.run(BACKWARD);
}

void Stop() {
  // RELEASE cuts power completely so it coasts to a stop
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}