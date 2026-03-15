#include <Wire.h>
#include<LiquidCrystal_I2C_Hangul.h>
#include <DHT.h>

LiquidCrystal_I2C_Hangul lcd(0x27,16,2); //LCD

#define DHTPIN 2           // DHT22 signal pin
#define DHTTYPE DHT22      // DHT 22 (AM2302)

#define BUZZER_PIN 7       // Buzzer pin
#define RELAY_PIN 8        // Relay connected to NC terminal
#define LED_PIN 9          // LED pin

// Thresholds
#define TEMP_MIN 15.0
#define TEMP_MAX 35.0
#define HUMIDITY_MIN 30.0
#define HUMIDITY_MAX 75.0

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  // I2C LCD Initialization
  lcd.init();
  lcd.backlight();

  // Pin Modes
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);  // Relay closed (fan ON)
  digitalWrite(LED_PIN, LOW);

  // Initial LCD messages
  lcd.setCursor(0, 0);
  lcd.print("   Welcome   ");
  delay(2500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Climate");
  lcd.setCursor(0, 1);
  lcd.print(" Monitoring  ");
  delay(2500);
  lcd.clear();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    delay(2000);
    return;
  }

  // Temperature alert status
  String tempAlert;
  if (temperature < TEMP_MIN) {
    tempAlert = "LOW";
  } else if (temperature > TEMP_MAX) {
    tempAlert = "HIGH";
  } else {
    tempAlert = "STABLE";
  }

  // Determine humidity alert status
  String humAlert;
  if (humidity < HUMIDITY_MIN) {
    humAlert = "LOW";
  } else if (humidity > HUMIDITY_MAX) {
    humAlert = "HIGH";
  } else {
    humAlert = "STABLE";
  }

  // Serial output for debugging
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" °C (");
  Serial.print(tempAlert);
  Serial.print(")\tHumidity: ");
  Serial.print(humidity);
  Serial.print(" % (");
  Serial.print(humAlert);
  Serial.println(")");

  // LCD Display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print("C ");
  lcd.print(tempAlert);

  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(humidity, 1);
  lcd.print("% ");
  lcd.print(humAlert);

  // Alarm/Control Logic
  bool tempOutOfRange = (temperature < TEMP_MIN || temperature > TEMP_MAX);
  bool humidityOutOfRange = (humidity < HUMIDITY_MIN || humidity > HUMIDITY_MAX);

  if (tempOutOfRange || humidityOutOfRange) {
    digitalWrite(RELAY_PIN, LOW);  // Fan OFF
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
    delay(300);

    digitalWrite(LED_PIN, LOW);
    tone(BUZZER_PIN, 500);
    delay(300);

    noTone(BUZZER_PIN);
    delay(1400);
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Fan ON
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    delay(2000);
  }
}
