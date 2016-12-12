 #include <ELECHOUSE_CC1101.h>
 
 void setup()
{
  Serial.begin(9600);
  ELECHOUSE_cc1101.Init();
  ELECHOUSE_cc1101.SetReceive();
    
  attachInterrupt(digitalPinToInterrupt(3),ELECHOUSE_CC1101_RevData,FALLING);
}

byte RX_buffer[61]={0};
byte size,i,flag;

void loop()
{
   while(1);
}

void ELECHOUSE_CC1101_RevData()
{
  size=ELECHOUSE_cc1101.ReceiveData(RX_buffer);
  
    Serial.print("@,");
    Serial.print(RX_buffer[0],DEC);
    Serial.print(",");
    Serial.print(RX_buffer[1],DEC);
    Serial.print(",");
    Serial.println("#");

  ELECHOUSE_cc1101.SetReceive();
}
