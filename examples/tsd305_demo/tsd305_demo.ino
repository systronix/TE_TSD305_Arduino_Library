/*
Adapting the TSD305 demo program to work on the TE Weathershield

I2C lines go through a MUX on the Weathershield so a given sensor has to be 'selected' via the MUX.

----- Revisions -----
2019Apr03 bboyes  start, based on TE example

----- TODO -----
Add better time detection so time output is always a multiple of the desired interval

*/

#include <tsd305.h>

tsd305 m_tsd305;

void setup() {
  Serial.begin(115200);     // use max baud rate
  
  // Teensy3 doesn't reset with Serial Monitor as do Teensy2/++2, or wait for Serial Monitor window
  // Wait here for 10 seconds to see if we will use Serial Monitor, so output is not lost
  while((!Serial) && (millis()<10000));    // wait until serial monitor is open or timeout

  Serial.println("==== TE Connectivity TSD305 ====");
  Serial.printf("Seconds, Sensor\xC2\xB0\x43, Object\xC2\xB0\x43\n");

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

void loop() 
{
  tsd305_status status;
  float temperature;
  float object_temperature;
  boolean connected;

  connected = m_tsd305.is_connected();
  if (connected) 
  {
    status = m_tsd305.read_temperature_and_object_temperature(
        &temperature, &object_temperature);

    // Serial.printf("Sensor Temp= %3.1f \xC2\xB0\x43, ", temperature);   // UTF-8 degree symbol and C
    // Serial.printf("Object Temp= %3.1f \xC2\xB0\x43\n", object_temperature);   // UTF-8 degree symbol and C

    Serial.printf("%4u,  %3.1f,  %3.1f\n", millis()/1000, temperature, object_temperature);   // for CSV file use

  } 
  else 
  {
    Serial.println("Sensor Disconnected");
  }

  delay(5000);
}

    // Serial.printf("Temp= %4.2f \xC2\xB0\x43,", temperature);   // UTF-8 degree symbol and C
    // Serial.printf(" Press= %5.2f hPa,", pressure);
    // Serial.printf(" Hum= %4.2f %%RH\n", humidity);