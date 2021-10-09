/* Synopsis: Emission Telerupteur RF433 avec memorisation de l'etat 
   Carte   : Arduino Nano
   Capteur : Emetteur 433.   
             
   Biblio  : VirtualWire 1.3 
             simpleBouton.h 1.4.2 
             Wire
             
   Source  : http://www.airspayce.com/mikem/arduino/VirtualWire/index.html
             https://forum.arduino.cc/index.php?topic=375232.0 
             https://lesiteferroviaire.pagesperso-orange.fr/Memoire%2024LC512.htm
             http://electroniqueamateur.blogspot.com/2020/01/utiliser-une-memoire-eeprom-i2c-arduino.html 

   C.Mercier  62128 Boiry-Becquerelle  
*/
//-------------------------------------------------
#include <Wire.h>
#define adresse_EEPROM 0x50 //Addresse i2c de l'EEPROM
  int adresseK1 = 10;
  int donneeK1 = 0;
  int adresseK2 = 20;
  int donneeK2 = 0;
//-------------------------------------------------
//librairie simpleBouton.h
//Cablage : pin---BP---GND
#include "simpleBouton.h"
  const uint8_t PINBP1 = 2;//Pin Nano 5
  const uint8_t PINBP2 = 5;//Pin Nano 8
  simpleBouton bouton1(PINBP1);
  simpleBouton bouton2(PINBP2);
//-------------------------------------------------
#include <VirtualWire.h>
//const int PINPTT = 10; // Pin Nano 13 
//const int PINDATAINPUT = 11; // Pin Nano 14 
//const int PINDATAOUT = 12; // Pin Nano 15
int pin_led = 13;//copie PINPTT
//-------------------------------------------------
  int ledK1=3;//Pin Nano 6
  bool memK1 = 0;//memoire K1
  bool envoiMessK1ON = 0;//memoire message K1 ON
  bool envoiMessK1OFF = 1;//memoire message K1 ON
  unsigned long tpsCourantK1ON = 0;
  unsigned long tpsEnvoiMessK1ON = 220;//A modifier si nécessaire;
  unsigned long tpsCourantK1OFF = 1;
  unsigned long tpsEnvoiMessK1OFF = 220;//A modifier si nécessaire;
//-------------------------------------------------
  int ledK2=6;//Pin Nano 9
  bool memK2;//memoire K2
  bool envoiMessK2ON = 0;//memoire message K2 ON
  bool envoiMessK2OFF = 1;//memoire message K2 ON
  unsigned long tpsCourantK2ON = 0;
  unsigned long tpsEnvoiMessK2ON = 220;//A modifier si nécessaire;
  unsigned long tpsCourantK2OFF = 1;
  unsigned long tpsEnvoiMessK2OFF = 220;//A modifier si nécessaire;
//-------------------------------------------------
  bool bitDemarrage = 1;
  int valeurTest = 0;
//*************************************************
void setup()
  { 
    Wire.begin();//déclare maitre sur le bus i2c
//-------------------------------------------------  
    //vw_set_ptt_pin(PINPTT);
    //vw_set_rx_pin(PINDATAINPUT);
    //vw_set_tx_pin(PINDATAOUT);// On peut changer les pins rx,tx,ptt AVANT vw_setup() si util.
    vw_setup(2000);// Bits par seconde  
    vw_rx_start();// Démarre la partie réception de la librairie VirtualWire.
    pinMode(pin_led,OUTPUT);
    digitalWrite(pin_led,LOW);
//-------------------------------------------------
    pinMode (PINBP1,INPUT);
    pinMode(ledK1,OUTPUT);
    digitalWrite(ledK1,HIGH);
    pinMode (PINBP2,INPUT);
    pinMode(ledK2,OUTPUT);
    digitalWrite(ledK2,HIGH);           
//-------------------------------------------------    
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
          memK1 =1; 
          envoiMessK1OFF = 0;    
        } 
    else
        {
          memK1 = 0;
          envoiMessK1ON = 0;      
        } 
lectureAdresseK2();               
    if(donneeK2 == 1)    
        {
          memK2 =1;
          envoiMessK2OFF = 0;     
        } 
    else
        {
          memK2 = 0;
          envoiMessK2ON = 0;      
        }                    
  }
bouton1.actualiser();  
if (bouton1.vientDEtreEnfonce() )
  { 
    memK1 =! memK1;    
    ecritureAdresseK1();              
    if (memK1 == 1 && envoiMessK1ON == 0)
      {
        tpsCourantK1ON = millis();
      }
        if (memK1 == 0 && envoiMessK1OFF == 0)
          {
            tpsCourantK1OFF = millis();
          }                  
  }
//*************************************************
bouton2.actualiser();  
if (bouton2.vientDEtreEnfonce() )
  { 
    memK2 =! memK2;
    ecritureAdresseK2();    
    if (memK2 == 1 && envoiMessK2ON == 0)
      {
        tpsCourantK2ON = millis();
      }
        if (memK2 == 0 && envoiMessK2OFF == 0)
          {
            tpsCourantK2OFF = millis();
          }        
  }  
//*************************************************  
envoiMessageK1ON(); 
envoiMessageK1OFF(); 
envoiMessageK2ON(); 
envoiMessageK2OFF(); 
//*************************************************
if(memK1 == 1)
  {
    digitalWrite(ledK1, LOW);    
  }
else
  {
    digitalWrite(ledK1, HIGH);    
  }
if(memK2 == 1)
  {
    digitalWrite(ledK2, LOW);
  }
else
  {
    digitalWrite(ledK2, HIGH);  
  }
//*************************************************
//Serial.println(memK1); 
//Serial.print("\t");
//Serial.println(envoiMessK1OFF);
bitDemarrage = 0;  
}//FIN LOOP
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
void envoiMessageK1ON()
{
if(( millis()-tpsCourantK1ON < tpsEnvoiMessK1ON) && memK1 == 1)
  {
    const char *msg="Relais1ON";
    vw_send((uint8_t *)msg, strlen(msg)); //Envoi du message
    vw_wait_tx();//Attend la fin de la transmission en cours
    envoiMessK1ON = 1;
    envoiMessK1OFF = 0;     
  }  
}
//*************************************************
void envoiMessageK1OFF()
{
if(( millis()-tpsCourantK1OFF < tpsEnvoiMessK1OFF) && memK1 == 0)
  {
    const char *msg="Relais1OFF";
    vw_send((uint8_t *)msg, strlen(msg)); //Envoi du message
    vw_wait_tx();//Attend la fin de la transmission en cours
    envoiMessK1OFF = 1;
    envoiMessK1ON = 0;
  } 
}
//*************************************************
void envoiMessageK2ON()
{
if(( millis()-tpsCourantK2ON < tpsEnvoiMessK2ON) && memK2 == 1)
  {
    const char *msg="Relais2ON";
    vw_send((uint8_t *)msg, strlen(msg)); //Envoi du message
    vw_wait_tx();//Attend la fin de la transmission en cours
    envoiMessK2ON = 1;
    envoiMessK2OFF = 0;
  }
}  
//*************************************************  
void envoiMessageK2OFF()
{
if(( millis()-tpsCourantK2OFF < tpsEnvoiMessK2OFF) && memK2 == 0)
  {
    const char *msg="Relais2OFF";
    vw_send((uint8_t *)msg, strlen(msg)); //Envoi du message
    vw_wait_tx();//Attend la fin de la transmission en cours
    envoiMessK2OFF = 1;
    envoiMessK2ON = 0;
  }
}
