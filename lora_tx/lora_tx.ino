#include <dht.h>
#include <SPI.h>
#include <LoRa.h>

#define DHTPIN 6
#define smokeSensor A0
#define trigPin 5
#define echoPin 4
int m1=2;
int m2=3;
int m3=7;
int m4=8;
long duration;
int distance;
dht DHT;

void setup() {
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
  pinMode(m4,OUTPUT);
  pinMode(smokeSensor,INPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);
  while (!Serial);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa initialization failed. Check your connections!");
    while (1);
  }
}

void loop() {
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  distance=duration*0.034/2;
  if(distance>30){
    digitalWrite(m1,HIGH);
    digitalWrite(m2,HIGH);
  }else
  {
  digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);
}
  int s = analogRead(smokeSensor);
    int readData = DHT.read11(DHTPIN);

  float t = DHT.temperature;        // Read temperature
  float h = DHT.humidity;     

  // Convert temperature and humidity to byte arrays
  byte* temperatureBytes = reinterpret_cast<byte*>(&t);
  byte* humidityBytes = reinterpret_cast<byte*>(&h);
   Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" °C, Humidity: ");
    Serial.print(h);
    Serial.println(" %");
    Serial.print("Smoke Sensor Value ");
    Serial.println(s);
  

  // Transmit temperature and humidity data
  LoRa.beginPacket();
  LoRa.write(temperatureBytes, sizeof(float));
  LoRa.write(humidityBytes, sizeof(float));
  LoRa.write(s);
  LoRa.endPacket();

  delay(5000);
}
