/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
//  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
//  Serial.println("Enabled IRin");
}

void loop() {
  if (irrecv.decode(&results)) {

    int receivedTemp = results.value;
    Serial.println(receivedTemp,BIN);
    Serial.println(results.value, HEX);
    Serial.println(results.bits);
    Serial.println(results.address, HEX);

    long payload = results.value;  // Example payload value without "0x" prefix
     Serial.println(payload);

int temp = (payload >> 16) & 0xFF;    // Extract temperature value
int extractedCap = (payload >> 8) & 0xFF;      // Extract capacity value
int extractedNodeID = payload & 0xFF;          // Extract node ID value

// Print the extracted values
Serial.print("Temperature: ");
Serial.println(temp);
Serial.print("Capacity: ");
Serial.println(extractedCap);
Serial.print("Node ID: ");
Serial.println(extractedNodeID);
    irrecv.resume(); // Receive the next value
  }
  delay(100);

  
}

//#include <IRremote.h>
//
//const int RECEIVE_PIN = 11;  // Pin connected to the IR receiver
//const int DATA_BITS = 8;     // Number of bits in the received payload
//
//IRrecv irrecv(RECEIVE_PIN);
//decode_results results;
//
//void setup() {
//  Serial.begin(9600);
//  irrecv.enableIRIn();
//}
//
//void loop() {
//  if (irrecv.decode(&results)) {
//    if (results.bits == DATA_BITS) {
//      // Extract the temperature and node number from the received payload
//      int receivedTemp = results.value / 10;  // Extract the temperature (two digits)
//      int receivedNode = results.value % 10;  // Extract the node number (one digit)
//
//      // Print the received values
//      Serial.print("Received Temperature: ");
//      Serial.println(receivedTemp);
//      Serial.print("Received Node: ");
//      Serial.println(receivedNode);
//    }
//    irrecv.resume();
//  }
//}
