#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"

// =========================
// DHT11
// =========================
#define DHTPIN 15
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// =========================
// DS18B20
// =========================
#define DS18B20_PIN 4

OneWire oneWire(DS18B20_PIN);
DallasTemperature ds18b20(&oneWire);

// =========================
// SENSOR MAGNÉTICO
// =========================
#define SENSOR_PUERTA 27

void setup() {
  Serial.begin(115200);

  // Iniciar DHT11
  dht.begin();

  // Iniciar DS18B20
  ds18b20.begin();

  // Iniciar sensor magnetico
  pinMode(SENSOR_PUERTA, INPUT);

  Serial.println("================================");
  Serial.println("   SISTEMA DE MONITOREO IoT");
  Serial.println("================================");
}

void loop() {

  // -------------------------
  // Leer DHT11
  // -------------------------
  float humedad = dht.readHumidity();
  float temperaturaDHT = dht.readTemperature();

  // -------------------------
  // Leer DS18B20
  // -------------------------
  ds18b20.requestTemperatures();
  float temperaturaDS = ds18b20.getTempCByIndex(0);

  // -------------------------
  // Leer sensor magnetico
  // -------------------------
  int estadoPuerta = digitalRead(SENSOR_PUERTA);

  Serial.println("-------------------------");

  // DHT11
  if (isnan(humedad) || isnan(temperaturaDHT)) {
    Serial.println("DHT11: Error de lectura");
  } else {
    Serial.print("DHT11 - Temperatura: ");
    Serial.print(temperaturaDHT);
    Serial.println(" °C");

    Serial.print("DHT11 - Humedad: ");
    Serial.print(humedad);
    Serial.println(" %");
  }

  // DS18B20
  Serial.print("DS18B20 - Temperatura: ");
  Serial.print(temperaturaDS);
  Serial.println(" °C");

  // Sensor magnetico
  Serial.print("Puerta: ");

  if (estadoPuerta == LOW) {
    Serial.println("CERRADA");
  } else {
    Serial.println("ABIERTA");
  }

  delay(2000);
}