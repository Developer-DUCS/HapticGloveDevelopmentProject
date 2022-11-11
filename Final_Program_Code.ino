#include <MPU6050_tockn.h>
#include <Wire.h>
const byte flexPin1 = A0;
const byte flexPin2 = A1;
const byte flexPin3 = A2;
const byte flexPin4 = A3;
//const byte flexPin5 = A4;

int newAngle1, previousAngle1;
int newAngle2, previousAngle2;
int newAngle3, previousAngle3;
int newAngle4, previousAngle4;

MPU6050 mpu6050(Wire);

long timer = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
  mpu6050.update();

  if(millis() - timer > 1000){
    
    Serial.println("=======================================================");
    Serial.print("temp : ");Serial.println(mpu6050.getTemp());
    Serial.print("accX : ");Serial.print(mpu6050.getAccX());
    Serial.print("\taccY : ");Serial.print(mpu6050.getAccY());
    Serial.print("\taccZ : ");Serial.println(mpu6050.getAccZ());
  
    Serial.print("gyroX : ");Serial.print(mpu6050.getGyroX());
    Serial.print("\tgyroY : ");Serial.print(mpu6050.getGyroY());
    Serial.print("\tgyroZ : ");Serial.println(mpu6050.getGyroZ());
  
    Serial.print("accAngleX : ");Serial.print(mpu6050.getAccAngleX());
    Serial.print("\taccAngleY : ");Serial.println(mpu6050.getAccAngleY());
  
    Serial.print("gyroAngleX : ");Serial.print(mpu6050.getGyroAngleX());
    Serial.print("\tgyroAngleY : ");Serial.print(mpu6050.getGyroAngleY());
    Serial.print("\tgyroAngleZ : ");Serial.println(mpu6050.getGyroAngleZ());
    
    Serial.print("angleX : ");Serial.print(mpu6050.getAngleX());
    Serial.print("\tangleY : ");Serial.print(mpu6050.getAngleY());
    Serial.print("\tangleZ : ");Serial.println(mpu6050.getAngleZ());
    Serial.println("=======================================================\n");
    timer = millis();  
  }

  
  //THIS LINE BELOW IS WHAT MEASURES PURE OUTPUT
  //TAKE THE VALUES AND ASSIGN STRAIGHT VALUES TO 565 BELOW and BENT TO 689
  //Serial.print(analogRead(flexPin1));
  newAngle1 = map(analogRead(flexPin1), 565, 689, 0, 90);
  //newAngle1 = constrain(newAngle1, 0, 90); // optional
  //if (newAngle1 != previousAngle1) {
    //Serial.print("Bend: ");
    //Serial.print(newAngle1);
    //Serial.println(" degrees");
    //previousAngle1 = newAngle1;
  //}
  //THIS LINE BELOW IS WHAT MEASURES PURE OUTPUT
  //TAKE THE VALUES AND ASSIGN STRAIGHT VALUES TO 553 BELOW and BENT TO 668
  //Serial.print(analogRead(flexPin2));
  newAngle2 = map(analogRead(flexPin2), 553, 668, 0, 90);
  //newAngle2 = constrain(newAngle2, 0, 90); // optional
  //if (newAngle2 != previousAngle2) {
    //Serial.print("Bend: ");
    //Serial.print(newAngle2);
    //Serial.println(" degrees");
    //previousAngle2 = newAngle2;
  //}
  //THIS LINE BELOW IS WHAT MEASURES PURE OUTPUT
  //TAKE THE VALUES AND ASSIGN STRAIGHT VALUES TO 551 BELOW and BENT TO 676
  //Serial.print(analogRead(flexPin3));
  newAngle3 = map(analogRead(flexPin3), 551, 676, 0, 90);
  //newAngle3 = constrain(newAngle3, 0, 90); // optional
  //if (newAngle3 != previousAngle3) {
    //Serial.print("Bend: ");
    //Serial.print(newAngle3);
    //Serial.println(" degrees");
    //previousAngle3 = newAngle3;
  //}
  //THIS LINE BELOW IS WHAT MEASURES PURE OUTPUT
  //TAKE THE VALUES AND ASSIGN STRAIGHT VALUES TO 517 BELOW and BENT TO 702
  //Serial.print(analogRead(flexPin4));
  newAngle4 = map(analogRead(flexPin4), 517, 702, 0, 90);
  //newAngle4 = constrain(newAngle4, 0, 90); // optional
  //if (newAngle4 != previousAngle4) {
    //Serial.print("Bend: ");
    //Serial.print(newAngle4);
    //Serial.println(" degrees");
    //previousAngle4 = newAngle4;
  //}
  String output = " ";
  output = output + newAngle1;
  output = output + " " ;
  output = output + newAngle2;
  output = output + " ";
  output = output + newAngle3;
  output = output + " ";
  output = output + newAngle4;
  Serial.println(output);
  
  delay(500);
}
