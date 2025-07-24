#include <LiquidCrystal.h>

// LCD (RS, E, D0-D7)
LiquidCrystal lcd(12, 11, 2, 3, 4, 5, 6, 7, 8, 9);

// Sensor & Output Pins
const int trigPin = A0;
const int echoPin = A1;
const int buzzerPin = A2;
const int redPin = A3;
const int bluePin = A4;
const int greenPin = A5;

long duration;
int distance;

const int tankHeight = 200;  // Tank height in cm

void setup() {
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  lcd.print("Water Level:");
}

void loop() {
  // Ultrasonic distance reading
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Convert distance to percentage: closer = more water
  int waterLevel = map(distance, tankHeight, 0, 0, 100);  // reverse scale
  if (waterLevel < 0) waterLevel = 0;
  if (waterLevel > 120) waterLevel = 120;

  // Show on LCD
  lcd.setCursor(0, 1);
  lcd.print("Level: ");
  lcd.print(waterLevel);
  lcd.print("%   ");  // clear extra digits

  // Overflow: distance <= 10 cm
  if (distance <= 10) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }
  // Sufficient (11–100 cm)
  else if (distance <= 100) {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
  }
  // Low level (101–200 cm)
  else if (distance <= 200) {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  }
  // Out of range (optional handling)
  else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }

  delay(1000);
}
