#include <ELECHOUSE_CC1101.h>

#include "DHT.h"

const int LEDPIN  =  A0;

#define DHTPIN 5
#define DHTTYPE DHT21
DHT dht(DHTPIN, DHTTYPE);

#define size 3

int counter = 0;

byte TX_buffer[size] = {0};
byte i;

void setup()
{
  Serial.begin(9600);

  Serial.println("Tx");

  pinMode(LEDPIN, OUTPUT);  

  

  Serial.println("TxOk");

  dht.begin();

  ELECHOUSE_cc1101.Init();
  
  for(int i=0;i<5;i++)
  {
     digitalWrite(LEDPIN, HIGH); 
    delay(100);
    digitalWrite(LEDPIN, LOW); 
    delay(100);
  }
  
}

void loop()
{
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else
  {
    digitalWrite(LEDPIN, HIGH); 
    
    Serial.println((byte)t);
    Serial.println((byte)h);
    TX_buffer[0] = (byte)t;
    TX_buffer[1] = (byte)h;
    ELECHOUSE_cc1101.SendData(TX_buffer, 2);
    digitalWrite(LEDPIN, LOW); 
    
    Serial.println("Send ok");
  }

  


}
