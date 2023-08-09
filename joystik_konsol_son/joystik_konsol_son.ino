/*
Geliştirici = Emirhan Özçelik

Proje Amacı = Seri haberleşme kullanarak oluşturulan kumanda ile işlevsel veri iletimi

--------------------Bağlantılar----------------------------
joy-x = A0
joy-y = A1
buton1 = 2
buton2 = 4
buton3 = 7
buton4 = 8

emirhanozcelik339@gmail.com adresinden sorularınızı iletebilirsiniz iyi çalışmalar :)
*/





#include <EEPROM.h>
byte sayac = 0;
unsigned long gecen_zaman = 0;
unsigned long aralik = 100; // milisaniye cinsinden paket gönderim aralığı (250 den büyük olamaz)
const byte aralik_adr = 1;
String paket[9];

void setup() 
{
  Serial.begin(115200);
  pinMode(2,INPUT_PULLUP);
    pinMode(4,INPUT_PULLUP);
      pinMode(7,INPUT_PULLUP);
        pinMode(8,INPUT_PULLUP);

       /*
        if(Serial.available())
        {
          if(Serial.read() == 'T')
          {
            int a = Serial.parseInt();
            if(a <= 250)
            {
            EEPROM.write(aralik_adr,a);
            aralik = a;
            }
            else
            {
              aralik = 100;
              EEPROM.write(aralik_adr,aralik);
            }
          }
        }
        aralik = EEPROM.read(aralik_adr);
        */
}

void loop() 
{
  kontrol5();
}
void kontrol1() /* direk gönderir, paketleme yok*/
{  
  int a = map(analogRead(A0),0,1023,1,10);
  int b = map(analogRead(A1),0,1023,1,10);
 
    if(a < 3 && sayac < 4){Serial.println("W"); sayac++;}
  else if(a > 7 && sayac < 4){Serial.println("A"); sayac++;}
    if(b < 3 && sayac < 4){Serial.println("S"); sayac++;}
  else if(b > 7 && sayac < 4){Serial.println("D"); sayac++;}
   if(digitalRead(2) == 0 && sayac < 4){Serial.println("F"); sayac++;}
  else if(digitalRead(4) == 0 && sayac < 4){Serial.println("G"); sayac++;}
  else if(digitalRead(7) == 0 && sayac < 4){Serial.println("E"); sayac++;}
  else if(digitalRead(8) == 0 && sayac < 4){Serial.println("H"); sayac++;}
  if(sayac >= 4)
  {
    sayac = 0;
  }
}
void kontrol2() /* paketleyerek gönderir,her satıra bir karakter*/
{
  int a = map(analogRead(A0),0,1023,1,10);
  int b = map(analogRead(A1),0,1023,1,10);

  if(millis()  - 50 >= gecen_zaman)
  {
    gecen_zaman = millis();
    if(sayac > 0)
    {
      sayac = 0;
      for(int a=0;a<9;a++)
      {
        if(paket[a] != "")
        {
          Serial.println(paket[a]);
          paket[a] = "";
        }
      }
    }
  }
  else
  {
     if(a < 3 && sayac < 4){paket[0] = "W"; sayac++;}
  else if(a > 7 && sayac < 4){paket[1] = "A"; sayac++;}
     if(b < 3 && sayac < 4){paket[2] = "S"; sayac++;}
  else if(b > 7 && sayac < 4){paket[3] = "D"; sayac++;}
     if(digitalRead(2) == 0 && sayac < 4){paket[4] = "F"; sayac++;}
  else if(digitalRead(4) == 0 && sayac < 4){paket[5] = "G"; sayac++;}
  else if(digitalRead(7) == 0 && sayac < 4){paket[6] = "E"; sayac++;}
  else if(digitalRead(8) == 0 && sayac < 4){paket[7] = "H"; sayac++;}
  }
}
void kontrol3() /*paketleyerek gönderir, tüm paket bir satırda*/
{
  int a = map(analogRead(A0),0,1023,1,10);
  int b = map(analogRead(A1),0,1023,1,10);

  if(millis()  - 50 >= gecen_zaman)
  {
    gecen_zaman = millis();
    if(sayac > 0)
    {
      sayac = 0;
      for(int a=0;a<9;a++)
      {
        if(paket[a] != "")
        {
          Serial.print(paket[a]);
          paket[a] = "";
        }
      }
      Serial.println("");
    }
  }
  else
  {
     if(a < 3 && sayac < 4){paket[0] = "W"; sayac++;}
  else if(a > 7 && sayac < 4){paket[1] = "A"; sayac++;}
     if(b < 3 && sayac < 4){paket[2] = "S"; sayac++;}
  else if(b > 7 && sayac < 4){paket[3] = "D"; sayac++;}
     if(digitalRead(2) == 0 && sayac < 4){paket[4] = "F"; sayac++;}
  else if(digitalRead(4) == 0 && sayac < 4){paket[5] = "G"; sayac++;}
  else if(digitalRead(7) == 0 && sayac < 4){paket[6] = "E"; sayac++;}
  else if(digitalRead(8) == 0 && sayac < 4){paket[7] = "H"; sayac++;}
  }
}
void kontrol4() /*paketleyerek gönderir, tüm paket bir satırda, + ek kontroller*/
{
  int a = map(analogRead(A0),0,1023,1,10);
  int b = map(analogRead(A1),0,1023,1,10);

  if(millis()  - 50 >= gecen_zaman)
  {
    gecen_zaman = millis();
    if(sayac > 0)
    {
      sayac = 0;
      for(int a=0;a<9;a++)
      {
        if(paket[a] != "")
        {
          Serial.print(paket[a]);
          paket[a] = "";
        }
      }
      Serial.println("");
    }
  }
  else
  {
      if(a < 3 && b < 3 && sayac < 6){paket[0] = "U"; paket[2] = ""; sayac++;} // WS
    else if(a < 3 && b > 7 && sayac < 6){paket[0] = "O"; paket[3] = ""; sayac++;} // WD

     if(a > 7 && b > 7 && sayac < 6){paket[1] = "P"; paket[3] = ""; sayac++;} // AD
    else if(a > 7 && b < 3 && sayac < 6){paket[1] = "Z"; paket[2] = ""; sayac++;} // AS

     if(a < 3 && sayac < 5){paket[0] = "W"; sayac++;}
  else if(a > 7 && sayac < 5){paket[1] = "A"; sayac++;}

     if(b < 3 && sayac < 5){paket[2] = "S"; sayac++;}
  else if(b > 7 && sayac < 5){paket[3] = "D"; sayac++;}

     if(digitalRead(2) == 0 && sayac < 5){paket[4] = "F"; sayac++;}
  else if(digitalRead(4) == 0 && sayac < 5){paket[5] = "G"; sayac++;}
  else if(digitalRead(7) == 0 && sayac < 5){paket[6] = "E"; sayac++;}
  else if(digitalRead(8) == 0 && sayac < 5){paket[7] = "H"; sayac++;}
  }
}
void kontrol5() /*paketleyerek gönderir, her satıra bir karakter, + ek kontroller*/
{
  int a = map(analogRead(A0),0,1023,1,10);
  int b = map(analogRead(A1),0,1023,1,10);

  if(millis()  - aralik >= gecen_zaman)
  {
    gecen_zaman = millis();
    if(sayac > 0)
    {
      sayac = 0;
      for(int a=0;a<9;a++)
      {
        if(paket[a] != "")
        {
          Serial.println(paket[a]);
          paket[a] = "";
        }
      }
    }
  }
  else
  {
      if(a < 3 && b < 3 && sayac < 6){paket[0] = "U"; paket[2] = ""; sayac++;} // WS
    else if(a < 3 && b > 7 && sayac < 6){paket[0] = "O"; paket[3] = ""; sayac++;} // WD

     if(a > 7 && b > 7 && sayac < 6){paket[1] = "P"; paket[3] = ""; sayac++;} // AD
    else if(a > 7 && b < 3 && sayac < 6){paket[1] = "Z"; paket[2] = ""; sayac++;} // AS

     if(a < 3 && sayac < 5){paket[0] = "W"; sayac++;}
  else if(a > 7 && sayac < 5){paket[1] = "A"; sayac++;}

     if(b < 3 && sayac < 5){paket[2] = "S"; sayac++;}
  else if(b > 7 && sayac < 5){paket[3] = "D"; sayac++;}

     if(digitalRead(2) == 0 && sayac < 5){paket[4] = "F"; sayac++;}
  else if(digitalRead(4) == 0 && sayac < 5){paket[5] = "G"; sayac++;}
  else if(digitalRead(7) == 0 && sayac < 5){paket[6] = "E"; sayac++;}
  else if(digitalRead(8) == 0 && sayac < 5){paket[7] = "H"; sayac++;}
  }
}