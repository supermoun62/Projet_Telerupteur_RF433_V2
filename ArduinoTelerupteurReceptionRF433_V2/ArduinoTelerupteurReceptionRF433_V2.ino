/*
   Synopsis: Reception Telerupteur RF433 avec memorisation de l'etat
   Carte   : Arduino nano
   Capteur : Recepteur 433
      
   Biblio  : VirtualWire 1.3
             Wire 

   Source  : http://www.airspayce.com/mikem/arduino/VirtualWire/index.html
             https://forum.arduino.cc/index.php?topic=375232.0 

             https://github.com/m0/Updated-Arduino-VirtualWire-Library
             https://www.carnetdumaker.net/articles/communiquer-sans-fil-en-433mhz-avec-la-bibliotheque-virtualwire-et-une-carte-arduino-genuino/ 
             
             http://www.lucea.fr/spip.php?article4
             
             https://lesiteferroviaire.pagesperso-orange.fr/Memoire%2024LC512.htm
             http://electroniqueamateur.blogspot.com/2020/01/utiliser-une-memoire-eeprom-i2c-arduino.html 
    
   C. Mercier 62128 Boiry-Becquerelle
*/
//-----------------------------------
  #include <Wire.h>
  #define adresse_EEPROM 0x50 //Addresse i2c de l'EEPROM
  int adresseK1 = 10;
  int donneeK1 = 0;
  int adresseK2 = 20;
  int donneeK2 = 0;
//-------------------------------------------------
  #include <VirtualWire.h>
//const int PINPTT = 10; // Pin Nano 13 
//const int PINDATAINPUT = 11; // Pin Nano 14 
//const int PINDATAOUT = 12; // Pin Nano 15
//-----------------------------------
  const int PINLEDK1 = 2;// Pin Nano 5
  const int PINK1 = 3;// Pin Nano 6
  const int PINLEDK2 = 6;// Pin Nano 9
  const int PINK2 = 7;// Pin Nano 10
  bool K1;
  bool memK1;
  bool bitK1;
  bool K2;
  bool memK2;
  bool bitK2;
  bool bitDemarrage;
//*************************************************
void setup()
{
Wire.begin();//déclare maitre sur le bus i2c  
//-----------------------------------  
/* On peut changer les pins rx,tx,ptt AVANT vw_setup() si util.     
   vw_set_ptt_pin(PINPTT);
   vw_set_rx_pin(PINDATAINPUT);
   vw_set_tx_pin(PINDATAOUT);// 
*/   
vw_setup(2000);// Bits par seconde  
vw_rx_start();// Démarre la partie réception de la librairie VirtualWire.
//-----------------------------------
    pinMode(PINLEDK1, OUTPUT); 
    pinMode(PINK1, OUTPUT);
    digitalWrite(PINLEDK1, HIGH);
    digitalWrite(PINK1, HIGH);
    pinMode(PINLEDK2, OUTPUT);
    pinMode(PINK2, OUTPUT);
    digitalWrite(PINLEDK2, HIGH); 
    digitalWrite(PINK2, HIGH);
//-----------------------------------    
  K1 = 0; 
  memK1 = 0;
  bitK1 = 0;
  K2 = 0;
  memK2 = 0;
  bitK2 = 0;
  bitDemarrage = 1;
  Serial.begin(9600);
  delay(2000); 
}//FIN SETUP
//*************************************************
void loop()
{
if(bitDemarrage==1)
  {  
lectureAdresseK1();
    if(donneeK1 == 1)
        {
          K1 = 1; 
        } 
    else
        {
          K1 = 0;
        } 
lectureAdresseK2();               
    if(donneeK2 == 1)    
        {
          K2 = 1;
        } 
    else
        {
          K2 = 0;
        }                    
  }  
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;      
if ( vw_get_message(buf, &buflen) ) // Lit le dernier message reçu
  { 
    if ((buflen==9) && (strncmp((char*)buf,"Relais1ON",9)) == 0) 
      {        
        K1 = 1;    
      }      
    if ((buflen==10) && (strncmp((char*)buf,"Relais1OFF",10)) == 0) 
      {        
        K1 = 0;  
      }
    if ((buflen==9) && (strncmp((char*)buf,"Relais2ON",9)) == 0) 
      {
        K2 = 1;    
      }      
    if ((buflen==10) && (strncmp((char*)buf,"Relais2OFF",10)) == 0) 
      {
        K2 = 0;  
      } 
  }//FIN GET 

if((K1 == 1) )
  {
    digitalWrite(PINLEDK1, LOW); 
    digitalWrite(PINK1, LOW);     
  }
else
  {
    digitalWrite(PINLEDK1, HIGH);
    digitalWrite(PINK1, HIGH);
  }
if(K2 == 1)
  {
    digitalWrite(PINLEDK2, LOW);
    digitalWrite(PINK2, LOW);      
  }
else
  {
    digitalWrite(PINLEDK2, HIGH);
    digitalWrite(PINK2, HIGH);
  }
if(K1==1 && bitK1 ==0)
  {
    memK1 = 1;
    ecritureAdresseK1();
    bitK1 = 1;    
  }
if(K1==0 && bitK1 ==1)
  {
    memK1 = 0;
    ecritureAdresseK1();
    bitK1 = 0;   
  }
if(K2==1 && bitK2 ==0)
  {
    memK2 = 1;
    ecritureAdresseK2();
    bitK2 = 1;    
  }
if(K2==0 && bitK2 ==1)
  {
    memK2 = 0;
    ecritureAdresseK2();
    bitK2 = 0;   
  }
  
//Serial.println(memK1);
bitDemarrage = 0;
} //FIN LOOP
//*************************************************
void lectureAdresseK1()
{
  Wire.beginTransmission(adresse_EEPROM); //adresse 24LC256
  Wire.write(adresseK1>>8);//position adresse 24LC256- Octet le plus significatif
  Wire.write(adresseK1 & 0xFF);//position adresse 24LC256- Octet le moins significatif
  Wire.endTransmission();
  Wire.requestFrom(adresse_EEPROM,1);//adresse et quantite 1 octet 
  delay(5); 
  donneeK1 = Wire.read();  
}
//*************************************************
void ecritureAdresseK1()
{  
  Wire.beginTransmission(adresse_EEPROM);
  Wire.write(adresseK1>>8);//position adresse 24LC256- Octet le plus significatif
  Wire.write(adresseK1 & 0xFF);//position adresse 24LC256- Octet le moins significatif
  Wire.write(memK1);
  Wire.endTransmission();
  delay(5); 
}
//*************************************************
void lectureAdresseK2()
{
  Wire.beginTransmission(adresse_EEPROM); //adresse 24LC256
  Wire.write(adresseK2>>8);//position adresse 24LC256- Octet le plus significatif
  Wire.write(adresseK2 & 0xFF);//position adresse 24LC256- Octet le moins significatif
  Wire.endTransmission();
  Wire.requestFrom(adresse_EEPROM,1);//adresse et quantite 1 octet
  delay(5); 
  donneeK2 = Wire.read();   
}
//*************************************************
void ecritureAdresseK2()
{  
  Wire.beginTransmission(adresse_EEPROM);
  Wire.write(adresseK2>>8);//position adresse 24LC256- Octet le plus significatif
  Wire.write(adresseK2 & 0xFF);//position adresse 24LC256- Octet le moins significatif
  Wire.write(memK2);
  Wire.endTransmission();
  delay(5); 
}
//*************************************************
