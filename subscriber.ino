#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "owais";
const char* password = "Owais@2412";

// MQTT Broker details
const char* mqtt_server = "e5f352a0.ala.eu-central-1.emqxsl.com";
const int mqtt_port = 8883;
const char* topic = "hotel/room/temp_Data";

// Secure MQTT Client
WiFiClientSecure espClient;
PubSubClient client(espClient);

// Buzzer pin
const int buzzerPin = 5; // Adjust according to your ESP32 wiring

float temperature_threshold = 28.0;  // Threshold for alarm
int threshold_breached_count = 0;    // Track threshold breaches

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  float temperature = message.substring(12).toFloat(); // Extract temperature
  Serial.print("Received temperature: ");
  Serial.println(temperature);

  // Check if temperature crosses threshold
  if (temperature > temperature_threshold) {
    threshold_breached_count++;
  } else {
    threshold_breached_count = 0;  // Reset count if temperature drops below threshold
  }

  if (threshold_breached_count >= 5) {
    Serial.println("ALARM: Temperature threshold exceeded for 5 minutes!");
    digitalWrite(buzzerPin, HIGH);  // Turn the buzzer on
  } else {
    digitalWrite(buzzerPin, LOW);   // Turn the buzzer off if threshold is not exceeded
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      client.subscribe(topic);
    }
    delay(5000);
  }
}

void setup() {
  Serial.begin(115200);

  // Initialize buzzer pin
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); // Initially turn the buzzer off

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  espClient.setInsecure();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  reconnect();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
