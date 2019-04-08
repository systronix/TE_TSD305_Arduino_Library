/*
Adapting the TSD305 demo program to work on the TE Weathershield

I2C lines go through a MUX on the Weathershield so a given sensor has to be 'selected' via the MUX.

Revisions
2019Apr03 bboyes  start

*/

#include <tsd305.h>

tsd305 m_tsd305;

void setup() {
  Serial.begin(115200);     // use max baud rate
  
  // Teensy3 doesn't reset with Serial Monitor as do Teensy2/++2, or wait for Serial Monitor window
  // Wait here for 10 seconds to see if we will use Serial Monitor, so output is not lost
  while((!Serial) && (millis()<10000));    // wait until serial monitor is open or timeout

  Serial.println("==== TE Connectivity ====");
  Serial.println("======== TSD305 =========");
  Serial.println("======== Measure ========");

  // WeatherShield MUX control pins
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  // MUX select TSD305
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);  

  m_tsd305.begin();
}

void loop() {
  tsd305_status status;
  float temperature;
  float object_temperature;
  boolean connected;

  connected = m_tsd305.is_connected();
  if (connected) {
    Serial.println(connected ? "Sensor Connected" : "Sensor Disconnected");

    status = m_tsd305.read_temperature_and_object_temperature(
        &temperature, &object_temperature);

    Serial.print("---Temperature = ");
    Serial.print(temperature, 1);
    // Serial.print((char)176); // should be degree symbol but doesn't work in TyCommander serial window
    Serial.println("C");

    Serial.print("---Object Temperature = ");
    Serial.print(object_temperature, 1);
    // Serial.print((char)176);
    Serial.println("C");
    Serial.println();
  } else {
    Serial.println(connected ? "Sensor Connected" : "Sensor Disconnected");
  }

  delay(1000);
}
