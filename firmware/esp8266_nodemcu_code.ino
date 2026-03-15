#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT.h>

// Wi-Fi credentials
#define WIFI_SSID "Galaxy"
#define WIFI_PASSWORD "222444$$$"

// Firebase credentials
#define FIREBASE_HOST "https://matlab-app-connection-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "dvsJPrSlf9e4jcf7zemq3XrAOLStZMl7fw7DOvrb"

// DHT sensor config
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Firebase objects
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// Thresholds
#define TEMP_MIN 15.0
#define TEMP_MAX 30.0
#define HUM_MIN 30.0
#define HUM_MAX 60.0

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Firebase setup
  config.database_url = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (!isnan(temp) && !isnan(hum)) {
    Serial.print("Temp: "); Serial.print(temp);
    Serial.print(" °C, Hum: "); Serial.println(hum);

    // Send actual sensor readings
    Firebase.setFloat(firebaseData, "/data/temperature", temp);
    Firebase.setFloat(firebaseData, "/data/humidity", hum);

    // Determine temperature alert status
    String tempAlert;
    if (temp < TEMP_MIN) {
      tempAlert = "LOW";
    } else if (temp > TEMP_MAX) {
      tempAlert = "HIGH";
    } else {
      tempAlert = "STABLE";
    }

    // Determine humidity alert status
    String humAlert;
    if (hum < HUM_MIN) {
      humAlert = "LOW";
    } else if (hum > HUM_MAX) {
      humAlert = "HIGH";
    } else {
      humAlert = "STABLE";
    }

    // Send alerts to Firebase
   Firebase.setFloat(firebaseData, "/data/temperature", temp);
   Firebase.setFloat(firebaseData, "/data/humidity", hum);
   Firebase.setString(firebaseData, "/data/TempAlert", tempAlert);
   Firebase.setString(firebaseData, "/data/HumidityAlert", humAlert);

    Serial.print("Temp Alert: "); Serial.println(tempAlert);
    Serial.print("Humidity Alert: "); Serial.println(humAlert);

  } else {
    Serial.println("Failed to read from DHT sensor!");
  }

  delay(5000); // Send updates every 5 seconds
}
