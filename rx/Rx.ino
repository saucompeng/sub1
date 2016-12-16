#include <ELECHOUSE_CC1101.h>
#include <SoftwareSerial.h>

const int LEDPIN  =  A0;

SoftwareSerial mySerial(10, 7); // RX, TX

int packetCount=1;


void setup()
{
  pinMode(LEDPIN, OUTPUT);

  Serial.begin(9600);
  mySerial.begin(9600);
  
  ELECHOUSE_cc1101.Init();
  ELECHOUSE_cc1101.SetReceive();

  for (int i = 0; i < 5; i++)
  {
    digitalWrite(LEDPIN, HIGH);
    delay(100);
    digitalWrite(LEDPIN, LOW);
    delay(100);
  }

  Serial.println("Hi");

  attachInterrupt(digitalPinToInterrupt(3), ELECHOUSE_CC1101_RevData, FALLING);
}

byte RX_buffer[61] = {0};
byte size, i, flag;

void loop()
{
  while (1);
}

void ELECHOUSE_CC1101_RevData()
{
  

  size = ELECHOUSE_cc1101.ReceiveData(RX_buffer);

  if(size>0)
  {
    Serial.println("Receive Size: ");
    Serial.println((int)size);
    Serial.println((int)RX_buffer[2]);
  }

  

  if(size==3)
  {
    digitalWrite(LEDPIN, HIGH);

    if(packetCount!=(int)RX_buffer[2])
    {
      mySerial.print("@,");
      mySerial.print(RX_buffer[0], DEC);
      mySerial.print(",");
      mySerial.print(RX_buffer[1], DEC);
      mySerial.print(",");
      mySerial.println("#");

      

      packetCount=RX_buffer[2];
    }
    
    
  
    digitalWrite(LEDPIN, LOW);
  }

  ELECHOUSE_cc1101.SetReceive();
}
