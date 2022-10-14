//Thumb Sensor Set to A0 pin
const int FLEX_PIN0 = A0;
//Pointer Finger Sensor Set to A1 pin
const int FLEX_PIN1 = A1;
//Middle Finger Sensor Set to A2 pin
const int FLEX_PIN2 = A2;
//Ring Finger Sensor Set to A3 Pin
const int FLEX_PIN3 = A3;
//Pinkie Finger Sensor Set to A4
const int FLEX_PIN4 = A4;
//Voltage given by Arudino
const float VCC = 5;
//Array of resistors values that are Affecting the Sensor
const float FingerResistors[5]={9970.0,10010.0,10060.0,10020.0,10000.0};
//Array of resistance measurements when Sensors are straight
const float FingerStraightResistance[5] = {12644.0,12645.0, 12759.0, 12341.68, 00000.0};
//Array of resistance measurments when Sensors are bent at 90 degrees
const float FingerBentResistance[5] = {24141.67,23345.8,20930.81,21346.0,00000.0};

void setup() {
  Serial.begin(9600);
  // set thumb as input
  pinMode(FLEX_PIN0, INPUT);
  // set pointer finger as input
  pinMode(FLEX_PIN1, INPUT);
  // set middle finger as input
  pinMode(FLEX_PIN2, INPUT);
  // set ring finger as input
  pinMode(FLEX_PIN3, INPUT);
  // set pinkie as input
  pinMode(FLEX_PIN4, INPUT);
}

void loop() {
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC0 = analogRead(FLEX_PIN0);
  int flexADC1 = analogRead(FLEX_PIN1);
  int flexADC2 = analogRead(FLEX_PIN2);
  int flexADC3 = analogRead(FLEX_PIN3);
  int flexADC4 = analogRead(FLEX_PIN4);
  //Calculate the resistance being read by the Arduino
  float flexV0 = flexADC0 * VCC / 1023.0;
  float flexV1 = flexADC1 * VCC / 1023.0;
  float flexV2 = flexADC2 * VCC / 1023.0;
  float flexV3 = flexADC3 * VCC / 1023.0;
  float flexV4 = flexADC4 * VCC / 1023.0;
  float flexR0 = FingerResistors[0] * (VCC / flexV0 - 1.0);
  float flexR1 = FingerResistors[1] * (VCC / flexV1 - 1.0);
  float flexR2 = FingerResistors[2] * (VCC / flexV2 - 1.0);
  float flexR3 = FingerResistors[3] * (VCC / flexV3 - 1.0);
  float flexR4 = FingerResistors[4] * (VCC / flexV4 - 1.0);
  //print out resistance of fingers
  Serial.println("Resistance of finger 0 circuit: " + String(flexR0) + " ohms");
  Serial.println("Resistance of finger 1 circuit: " + String(flexR1) + " ohms");
  Serial.println("Resistance of finger 2 circuit: " + String(flexR2) + " ohms");
  Serial.println("Resistance of finger 3 circuit: " + String(flexR3) + " ohms");
  Serial.println("Resistance of finger 4 circuit: " + String(flexR4) + " ohms");
  //Map out the angles that various resistances mean
  float Finger0Angle = map(flexR0, FingerStraightResistance[0], FingerBentResistance[0], 0, 90.0);
  float Finger1Angle = map(flexR1, FingerStraightResistance[1], FingerBentResistance[1], 0, 90.0);
  float Finger2Angle = map(flexR2, FingerStraightResistance[2], FingerBentResistance[2], 0, 90.0);
  float Finger3Angle = map(flexR3, FingerStraightResistance[3], FingerBentResistance[3], 0, 90.0);
  float Finger4Angle = map(flexR4, FingerStraightResistance[4], FingerBentResistance[4], 0, 90.0);
  //print out each finger angle
  Serial.println("Bend of finger 0: " + String(Finger0Angle) + " degrees");
  Serial.println("Bend of finger 1: " + String(Finger1Angle) + " degrees");
  Serial.println("Bend of finger 2: " + String(Finger2Angle) + " degrees");
  Serial.println("Bend of finger 3: " + String(Finger3Angle) + " degrees");
  Serial.println("Bend of finger 4: " + String(Finger4Angle) + " degrees");
  Serial.println();

  delay(500);
}
