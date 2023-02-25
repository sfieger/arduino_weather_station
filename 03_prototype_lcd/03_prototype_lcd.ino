#include <LiquidCrystal.h>

LiquidCrystal lcd(3, 4, 5, 6, 7, 8, 9);

byte degree[8] = {
  B00010,
  B00101,
  B00010,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
char degree_sign = 0;

byte thermometer[8] = {
  B00100,
  B01010,
  B01010,
  B01010,
  B01010,
  B10001,
  B10001,
  B01110
};
char temp_sign = 1;

byte humidity[8] = {
  B00000,
  B00100,
  B01110,
  B01110,
  B11111,
  B11111,
  B01110,
  B00000
};
char hum_sign = 2;

byte pressure[8] = {
  B00100,
  B00100,
  B00100,
  B01110,
  B00101,
  B11111,
  B00000,
  B11111
};
char pres_sign = 3;

const byte ledPin = 10;
const byte interruptPin = 2;
volatile byte backgroundState = LOW;

void setup() {

  for (int i = 3; i < 11; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), backgroundLight, LOW);
  
  // init LCD
  lcd.createChar(degree_sign, degree);
  lcd.createChar(temp_sign, thermometer);
  lcd.createChar(hum_sign, humidity);
  lcd.createChar(pres_sign, pressure);
  
  lcd.begin(16, 4);
}

void loop() {
  String time = "2023-02-25 11:22";
  float t = 22.5;
  float h = 60.1;
  float p = 1015;

  Serial.println(time);
  Serial.print("TEMP: ");
  Serial.println(t);
  Serial.print("HUM:  ");
  Serial.println(h);
  Serial.print("PRES:");
  Serial.println(p);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(time);

  lcd.setCursor(0, 1);
  lcd.print(temp_sign);
  lcd.print(" ");
  lcd.print(t, 1);
  lcd.print(" ");
  lcd.print(degree_sign);
  lcd.print("C");

  lcd.setCursor(0, 2);
  lcd.print(hum_sign);
  lcd.print(" ");
  lcd.print(h, 1);
  lcd.print(" %");

  lcd.setCursor(0, 3);
  lcd.print(pres_sign);
  lcd.print(" ");
  lcd.print(p, 0);
  lcd.print(" hPa");


  if (backgroundState == HIGH) {
    digitalWrite(ledPin, backgroundState);
    delay(10000);
    backgroundState = LOW;
    digitalWrite(ledPin, backgroundState);
  }
}

void backgroundLight() {
  backgroundState = HIGH;
}