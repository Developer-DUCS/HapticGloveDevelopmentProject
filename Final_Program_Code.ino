#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SoftwareSerial.h>


SoftwareSerial BT(10,11); // TX to pin_10. RX to pin_11 of Arduino.
const byte flexPin1 = A0;
const byte flexPin2 = A1;
const byte flexPin3 = A2;
//Mux control pins
int s0 = 8;
//Mux in "SIG" pin
int SIG_pin = A3;
int newAngle1, previousAngle1;
int newAngle2, previousAngle2;
int newAngle3, previousAngle3;
int newAngle4, previousAngle4;
MPU6050 mpu6050(Wire);
long timer = 0;

void setup() {
  pinMode(s0, OUTPUT);  
  digitalWrite(s0, LOW);
  Serial.begin(115200);
  BT.begin(115200);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(false); 
}

void loop() {

  mpu6050.update();
  //THIS LINE BELOW IS WHAT MEASURES PURE OUTPUT
  //TAKE THE VALUES AND ASSIGN STRAIGHT VALUES TO 565 BELOW and BENT TO 689
  //Serial.print(analogRead(flexPin1));
  newAngle1 = map(analogRead(flexPin1), 565, 689, 0, 90);
  //THIS LINE BELOW IS WHAT MEASURES PURE OUTPUT
  //TAKE THE VALUES AND ASSIGN STRAIGHT VALUES TO 553 BELOW and BENT TO 668
  //Serial.print(analogRead(flexPin2));
  newAngle2 = map(analogRead(flexPin2), 553, 668, 0, 90);
  //THIS LINE BELOW IS WHAT MEASURES PURE OUTPUT
  //TAKE THE VALUES AND ASSIGN STRAIGHT VALUES TO 551 BELOW and BENT TO 676
  //Serial.print(analogRead(flexPin3));
  newAngle3 = map(analogRead(flexPin3), 551, 676, 0, 90);

  

  String output = " ";


  for(int i = 0; i < 2; i ++){
    output = output + readMux(i);
    output = output + " " ;
  }
  output = output + newAngle1;
  output = output + " " ;
  output = output + newAngle2;
  output = output + " ";
  output = output + newAngle3;
  output = output + " ";
  output = output + mpu6050.getAccX();
  output = output + " ";
  output = output + mpu6050.getAccY();
  output = output + " ";
  output = output + mpu6050.getAccZ();
  output = output + " ";
  output = output + mpu6050.getGyroX();
  output = output + " ";
  output = output + mpu6050.getGyroY();
  output = output + " ";
  output = output + mpu6050.getGyroZ();
  output = output + " ";
  output = output + mpu6050.getAccAngleX();
  output = output + " ";
  output = output + mpu6050.getAccAngleY();
  output = output + " ";
  output = output + mpu6050.getGyroAngleX();
  output = output + " ";
  output = output + mpu6050.getGyroAngleY();
  output = output + " ";
  output = output + mpu6050.getGyroAngleZ();
  output = output + " ";
  output = output + mpu6050.getAngleX();
  output = output + " ";
  output = output + mpu6050.getAngleY();
  output = output + " ";
  output = output + mpu6050.getAngleZ();
  output = output + " ";
  output = output + "end";
  
  Serial.println(output);
  BT.println(output);
  delay(100);
}

float readMux(int channel){
  int controlPin[] = {s0};

  int muxChannel[2][1]={
    {0}, //channel 0
    {1}, //channel 1
  };

  //loop through the 1 sig
  for(int i = 0; i < 1; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  //read the value at the SIG pin
  float val = map(analogRead(SIG_pin), 450, 220, 0, 90);

  //return the value
  return val;
}
