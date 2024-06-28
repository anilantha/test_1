#include <LowPower.h>
#include <IRremote.h>
#define sensor A0
#define storage A1
//int sensor = A0;
float VOLTS;
//float TMP;
float TEMP;
float voltage;
const int interruptPin = 2;
const int Receiver = 9;
int VAL = 0;
int ADD = 0;

void setup() {

  pinMode(Receiver, OUTPUT);
  digitalWrite(Receiver, HIGH);
  pinMode(3, OUTPUT);
  pinMode(7, OUTPUT); //Cap sense on
  pinMode(10, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10);
  Sense_storage();
  delay(10);
     Sense();

      for (int i = 0; i < 4; i++) { //20 for primary nodes
        LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
      
      }

}

float Sense_storage() {
  digitalWrite(7, HIGH);   // Cap sense on (HIGH is the voltage level)
  delay(2);
  int sensorValue = analogRead(storage);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * 2 * (3.3 / 1023.0);

  delay(2);
  digitalWrite(7, LOW);
  delay(2);

  return voltage; // Return the voltage value
}

void Sense() {

{
  delay(5);
  IRsend irsend;
  delay(200);
  int reading = analogRead(sensor);
  VOLTS = reading * (3100 / 1024.0);
  TEMP = ((VOLTS - 500) / 10);
  Serial.print("Temperature (C): ");
  delay(5);
  Serial.println(TEMP);
  int PV = 0;  // Example temperature value
  int cap = 10 * (Sense_storage()); // Example capacity value
  int nodeID = 0;          // Example node ID value
  int Temp = TEMP;             // Example PV value
  // Concatenate the values into a 28-bit hexadecimal value
  unsigned long payload = ((unsigned long)(PV & 0xFF) << 24) | ((unsigned long)(cap & 0xFF) << 16) | ((unsigned long)(nodeID & 0xFF) << 8) | (Temp & 0xFF);
  delay(2);
  digitalWrite(Receiver, HIGH);
  delay(10);
  for (int i = 0; i < 1; i++) {
    // irsend.sendPanasonic(0x4004, 0xABCDEF1);
    //    irsend.sendRC5(TEMP, 8);
    irsend.sendRC5(payload, 28);
    // irsend.sendNEC(payload, 8);
    delay(40); //keep 40ms for sony !!!
  }
  delay(5);

  digitalWrite(Receiver, LOW);
  delay(10);
 
  delay(2);

}

}
