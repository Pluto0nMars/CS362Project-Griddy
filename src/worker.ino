#include <Wire.h>

void setup() {
//   Wire.begin(9); // join I2C bus with address 8
  Wire.begin(8); // join I2C bus with address 8
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  // nothing needed here
}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();
}