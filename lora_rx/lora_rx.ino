#include <SPI.h>
#include <LoRa.h>

int Relay1=3;
int Relay2=4;
int Relay3=5;
float s;
void setup() {
  Serial.begin(9600);
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  pinMode(Relay3,OUTPUT);
  while (!Serial);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa initialization failed. Check your connections!");
    while (1);
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    byte temperatureBytes[sizeof(float)];
    byte humidityBytes[sizeof(float)];
    
    // Read temperature and humidity data from packet
    for (int i = 0; i < sizeof(float); i++) {
      temperatureBytes[i] = LoRa.read();
    }
    for (int i = 0; i < sizeof(float); i++) {
      humidityBytes[i] = LoRa.read();
    }
    // Convert byte arrays to temperature and humidity values
    float t = *reinterpret_cast<float*>(temperatureBytes);
    float h = *reinterpret_cast<float*>(humidityBytes);
    int s = LoRa.read();
    // Print temperature and humidity values
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" °C, Humidity: ");
    Serial.print(h);
    Serial.println(" %");
    Serial.print("smoke Sensor Value ");
    Serial.println(s);
    if(t>27)
    {
      digitalWrite(Relay1,HIGH);
    }
    else{
      digitalWrite(Relay1,LOW);
    }
    if(h<95){
      digitalWrite(Relay2,HIGH);
    }
    else{
      digitalWrite(Relay2,LOW);
    }
    if(s<13){
      digitalWrite(Relay3,HIGH);
    }
    else{
      digitalWrite(Relay3,LOW);
    }
  }
}
