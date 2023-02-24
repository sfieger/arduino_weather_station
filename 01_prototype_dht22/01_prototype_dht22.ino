#include <dhtnew.h>

DHTNEW dht(13);

void setup() {
  Serial.begin(9600);
}

void loop() {
  dht.read();
  float t = dht.getTemperature();
  float h = dht.getHumidity();

  Serial.print("TMP: ");
  Serial.print(t, 1);
  Serial.println("°C");

  Serial.print("HMD: ");
  Serial.print(h, 1);
  Serial.println("%");

  delay(2000);
}