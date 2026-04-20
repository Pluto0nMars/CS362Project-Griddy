#include <Wire.h>

void setup() {
  Wire.begin(); // join I2C bus as master
  Serial.begin(9600);
}

void loop() {
  // Send to slave 1 (address 8)
  Wire.beginTransmission(8);
  Wire.write("Hello 8");
  Wire.endTransmission();

  delay(500);

  // Send to slave 2 (address 9)
  Wire.beginTransmission(9);
  Wire.write("Hello 9");
  Wire.endTransmission();

  delay(1000);
}