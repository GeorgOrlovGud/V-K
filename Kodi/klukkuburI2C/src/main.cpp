#include <Wire.h>
#include <Adafruit_BME280.h>
#include <WiFi.h>

#include "WiFiSpeak.h"
#include "vedur.h"

//Þetta er I2C tenging, ef þú fattaðir það ekki á nafninu á folderinum, farðu að sofa.
//SPI tenging er of mikið vesen og breytir engu fyrir þetta verkefni.
#define BME280_I2C_ADDRESS 0x76
#define MIC_PIN 34              //Sleppi pin.h kjaftæðinu
//Mældi með því að hafa Interstellar tónlist nálægt lol
const int MIC_THRESHOLD = 700; //Beyta þessu frekar en að stilla potentiometerinn með skrúfjárni eins og fáviti

Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  delay(1000);

  int setupTime = 45; //sekúndur

  //(GPIO21 = SDA, GPIO22 = SCL):

  Wire.begin();

  if (!bme.begin(BME280_I2C_ADDRESS)) {
    Serial.println("(I2C) BME280 Vitlaust tengt");
    while (1);
  } else {
    Serial.println("(I2C) BME280 Virkar!");
  }

  pinMode(MIC_PIN, INPUT); //Init mic pinann

  THINGSPEAK::SetupWiFi(setupTime);
  THINGSPEAK::setup_ThingSpeak();
}

void loop() {
  //Ég nora þessar breytur oftar en einu sinni þanng skilgreini þær í stað þess að kalla alltaf á bme klass
  float temperature = bme.readTemperature();       // °C
  float humidity    = bme.readHumidity();          // %
  float pressure    = bme.readPressure() / 100.0F; // hPa
  bool rain         = VEDUR::rignir();

  int soundLevel = analogRead(MIC_PIN);
  bool isLoud = soundLevel > MIC_THRESHOLD;

  Serial.print("Hávaðastig: " + soundLevel); //Á eina skalanum sem skiptir máli, tilfinning

  Serial.print("Hitastig: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Rakastig: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Loftpressa: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Rignir?: ");
  Serial.println(rain ? "Já" : "Nei");

  Serial.print("Hávaði: ");
  Serial.println(soundLevel);

  Serial.print("Er þetta of hátt?? ");
  Serial.println(isLoud ? "Já" : "Nei");

  Serial.println("Thingspeak writeAll loop fall");
  THINGSPEAK::writeAll(temperature, humidity, pressure, rain, isLoud);

  Serial.println();
  delay(20000);
}
