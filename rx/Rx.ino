#include <ELECHOUSE_CC1101.h>

const int LEDPIN  =  A0;

void setup()
{
  pinMode(LEDPIN, OUTPUT);

  Serial.begin(9600);
  ELECHOUSE_cc1101.Init();
  ELECHOUSE_cc1101.SetReceive();

  for (int i = 0; i < 5; i++)
  {
    digitalWrite(LEDPIN, HIGH);
    delay(100);
    digitalWrite(LEDPIN, LOW);
    delay(100);
  }

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
  digitalWrite(LEDPIN, HIGH);

  size = ELECHOUSE_cc1101.ReceiveData(RX_buffer);

  Serial.print("@,");
  Serial.print(RX_buffer[0], DEC);
  Serial.print(",");
  Serial.print(RX_buffer[1], DEC);
  Serial.print(",");
  Serial.println("#");

  digitalWrite(LEDPIN, LOW);

  ELECHOUSE_cc1101.SetReceive();
}
