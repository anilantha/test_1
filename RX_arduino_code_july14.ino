

#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);

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
