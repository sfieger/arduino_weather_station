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
char deg = 0;

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
char therm = 1;

byte feuchtigkeit[8] = {
  B00000,
  B00100,
  B01110,
  B01110,
  B11111,
  B11111,
  B01110,
  B00000
};
char feuchte = 2;

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
  lcd.createChar(deg, degree);
  lcd.createChar(therm, thermometer);
  lcd.createChar(feuchte, feuchtigkeit);
  
  lcd.begin(16, 2);
}

void loop() {
  float t = 0;
  float h = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(therm);
  lcd.print(" ");
  lcd.print(t, 1);
  lcd.print(deg);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print(feuchte);
  lcd.print(" ");
  lcd.print(h, 1);
  lcd.print("%");

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