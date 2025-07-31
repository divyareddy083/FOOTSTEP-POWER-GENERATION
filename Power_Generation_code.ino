#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Constants
int prev = 0, stepCount = 0;
unsigned long previousMillis = 0;
const long interval = 1000;  
unsigned long currentMillis;

float v, vout, vin;  // Variables for voltage calculation

// Initialize the LCD (16x2) with I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize serial communication and pin for LED
  Serial.begin(9600);
  pinMode(8, OUTPUT); // LED indication

  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  // Welcome message
  lcd.print("FOOT STEP POWER");
  lcd.setCursor(0, 1);
  lcd.print("   GENERATOR");
  delay(2000);
  lcd.clear();

  // Static display labels
  lcd.setCursor(0, 0);
  lcd.print("STEP COUNT:");
  lcd.setCursor(0, 1);
  lcd.print("VOLTAGE:");
}

void loop() {
  v = analogRead(A0);
  currentMillis = millis(); // Get current time

  // Step detection
  if (v != 0 && prev == 0) {
    stepCount += 1;
    digitalWrite(8, HIGH); // Turn on LED
    lcd.setCursor(12, 0);
    lcd.print("    "); // Clear previous value
    lcd.setCursor(12, 0);
    lcd.print(stepCount);
  } else {
    if (currentMillis - previousMillis >= 100) {
      previousMillis = currentMillis;
      digitalWrite(8, LOW); // Turn off LED after short delay
    }
  }

  prev = v;

  // Voltage calculation
  vout = (v * 5.00) / 1024.00;       // ADC to volts
  vin = (vout / 0.040909) * 100;     // Convert to millivolts based on scaling

  // Display voltage in mV, only 3 digits (integer)
  lcd.setCursor(9, 1);
  lcd.print("      ");              // Clear old digits
  lcd.setCursor(9, 1);
  lcd.print((int)vin);              // Show as integer
  lcd.print("mV ");

  delay(200);
}
