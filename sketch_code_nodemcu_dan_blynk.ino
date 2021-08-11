//ASYONI ELEKTRONIK


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "TOKEN";  //Masukan Auth Token yang dikirim ke email
char ssid[] = "ssid "; //Masukan nama wifi kamu
char pass[] = "password"; //  // Masukan Password wifi kamu
 
#define DHTPIN 0          // pin data DHT11 hubungkan ke GPIO Pin D3 pada nodeMCU
 
#define DHTTYPE DHT11     

 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
 

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca dari sensor DHT!");
    return;
  }

  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
}
 
void setup()
{
  
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}
 
void loop()
{
  Blynk.run();
  timer.run();
}
