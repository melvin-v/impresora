// Definición de los pines para los motores
#include <Servo.h>
Servo myservo;  // crea el objeto servo
int pos = 0;    // posicion del servo

const int motorXPin1 = 2;    // 28BYJ48 In1
const int motorXPin2 = 3;    // 28BYJ48 In2
const int motorXPin3 = 4;    // 28BYJ48 In3
const int motorXPin4 = 5;    // 28BYJ48 In4

const int motorYPin1 = 6;    // 28BYJ48 In1
const int motorYPin2 = 7;    // 28BYJ48 In2
const int motorYPin3 = 8;    // 28BYJ48 In3
const int motorYPin4 = 9;    // 28BYJ48 In4


const int motorZPin1 = 31;    // 28BYJ48 In1
const int motorZPin2 = 32;    // 28BYJ48 In2
const int motorZPin3 = 33;    // 28BYJ48 In3
const int motorZPin4 = 34;    // 28BYJ48 In4

int motorSpeed = 1500;       // Velocidad del motor
int stepsPerRev = 4076;      // Pasos para una vuelta completa

const int numSteps = 8;
const int stepsLookup[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };

void setup() {
  myservo.attach(10);

  pinMode(motorXPin1, OUTPUT);
  pinMode(motorXPin2, OUTPUT);
  pinMode(motorXPin3, OUTPUT);
  pinMode(motorXPin4, OUTPUT);

  pinMode(motorYPin1, OUTPUT);
  pinMode(motorYPin2, OUTPUT);
  pinMode(motorYPin3, OUTPUT);
  pinMode(motorYPin4, OUTPUT);

  pinMode(motorZPin1, OUTPUT);
  pinMode(motorZPin2, OUTPUT);
  pinMode(motorZPin3, OUTPUT);
  pinMode(motorZPin4, OUTPUT);

}

void loop() {
  myservo.write(0);
  moverB2();

  delay(50000);
}

void moveStepper(String motor, float revolutions, String direction) {
  int totalSteps = revolutions * stepsPerRev; // Calcula el total de pasos a dar
  bool clockwise = (direction == "CW");

  for (int i = 0; i < totalSteps; i++) {
    if (motor == "X") {
      updateStepper(motorXPin1, motorXPin2, motorXPin3, motorXPin4, clockwise);
    } else if (motor == "Y") {
      updateStepper(motorYPin1, motorYPin2, motorYPin3, motorYPin4, clockwise);
    } else if (motor == "Z") {
      updateStepper(motorZPin1, motorZPin2, motorZPin3, motorZPin4, clockwise);
    }
    delayMicroseconds(motorSpeed);
  }
}

void updateStepper(int pin1, int pin2, int pin3, int pin4, bool clockwise) {
  static int stepCounterX = 0;
  static int stepCounterY = 0;
  int* stepCounter = &stepCounterX; // Por defecto apunta al contador del EJE X

  if (pin1 == motorYPin1) { // Cambia a usar el contador del EJE Y si los pines coinciden
    stepCounter = &stepCounterY;
  }

  if (clockwise) {
    *stepCounter = (*stepCounter + 1) % numSteps;
  } else {
    *stepCounter = (*stepCounter - 1 + numSteps) % numSteps;
  }
  setOutput(pin1, pin2, pin3, pin4, *stepCounter);
}

void setOutput(int pin1, int pin2, int pin3, int pin4, int step) {
  digitalWrite(pin1, bitRead(stepsLookup[step], 0));
  digitalWrite(pin2, bitRead(stepsLookup[step], 1));
  digitalWrite(pin3, bitRead(stepsLookup[step], 2));
  digitalWrite(pin4, bitRead(stepsLookup[step], 3));
}

void moverA1(){
  moveStepper("Y",3, "CW");
  moverZ();
  moveStepper("Y",3, "CCW");
}

void moverA2(){
  moveStepper("Y", 1.5, "CW");
  moverZ();
  moveStepper("Y", 1.5, "CCW");
}

void moverA3(){
  moverZ();
}

void moverB1(){
  moveStepper("X", 1.5, "CCW");
  moveStepper("Y", 3, "CW");
  moverZ();
  moveStepper("X", 1.5, "CW");
  moveStepper("Y", 3, "CCW");
}

void moverB2(){
  moveStepper("X", 1.5, "CCW");
  moveStepper("Y", 1.5, "CW");
  moverZ();
  moveStepper("X", 1.5, "CW");
  moveStepper("Y", 1.5, "CCW");
}

void moverB3(){
  moveStepper("X", 1.5, "CCW");
  moverZ();
  moveStepper("X", 1.5, "CW");
}

void moverC1(){
  moveStepper("X", 3, "CCW");
  moveStepper("Y", 3, "CW");
  moverZ();
  moveStepper("X", 3, "CW");
  moveStepper("Y", 3, "CCW");
}

void moverC2(){
  moveStepper("X", 3, "CCW");
  moveStepper("Y", 1.5, "CW");
  moverZ();
  moveStepper("X", 3, "CW");
  moveStepper("Y", 1.5, "CCW");
}

void moverC3(){
  moveStepper("X", 3, "CCW");
  moverZ();
  moveStepper("X", 3, "CW");
}

void moverZ(){
  moveStepper("Z", 1, "CW");
  
  
}

