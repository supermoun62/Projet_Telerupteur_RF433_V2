/*
   Lecture d'une adresse d'une mémoire EEPROM 24LC256
   Chargement d'un octet d'une mémoire EEPROM 24LC256
   C.Mercier  62128 Boiry-Becquerelle
   
   Source:  https://lesiteferroviaire.pagesperso-orange.fr/Memoire%2024LC512.htm
            http://electroniqueamateur.blogspot.com/2020/01/utiliser-une-memoire-eeprom-i2c-arduino.html  
   
*/
//------------------------------------
#include <Wire.h>  // bibliothèque i2c
#define adresse_EEPROM 0x50    //Addresse i2c de l'EEPROM
//#define adresseMax 30 // taille de l'EEPROM (nombre d'octets)
int adress = 10;
int val = 0;
int donnee = 0;
//------------------------------------
//librairie simpleBouton.h
//Cablage : pin---BP---GND
#include "simpleBouton.h"
  const uint8_t PINBP1 = 2;//Pin Nano 5
  const uint8_t PINBP2 = 5;//Pin Nano 8
  simpleBouton bouton1(PINBP1);
  simpleBouton bouton2(PINBP2);
//------------------------------------
int ledK1=3;//Pin Nano 6
int ledK2=6;//Pin Nano 9
//************************************
void setup(void)
{
pinMode (PINBP1,INPUT);
pinMode(ledK1,OUTPUT);
digitalWrite(ledK1,HIGH);
pinMode (PINBP2,INPUT);
pinMode(ledK2,OUTPUT);
digitalWrite(ledK2,HIGH); 
Serial.begin(9600);
Wire.begin();
delay(1000);  
//************************************
}//FIN SETUP
void loop() 
{
//------------------------------------  
bouton1.actualiser();  
if (bouton1.vientDEtreEnfonce() )
  { 
    digitalWrite(ledK1,LOW);
    lecturedonnee(); 
    digitalWrite(ledK1,HIGH);          
  }
//------------------------------------ 
bouton2.actualiser();  
if (bouton2.vientDEtreEnfonce() )
  { 
    digitalWrite(ledK2,LOW);
    ecrituredonnee(); 
    digitalWrite(ledK2,HIGH);          
  }
//------------------------------------  
}//FIN LOOP
//************************************
void lecturedonnee()
{
  Wire.beginTransmission(adresse_EEPROM);  // adresse i2c du 24LC256
  Wire.write((int)(adress>>8));//position adresse 24LC256- Octet le plus significatif
  Wire.write((int)(adress & 0xFF));//position adresse 24LC256- Octet le moins significatif
  Wire.endTransmission();
  Wire.requestFrom(adresse_EEPROM, 1); // on demande au 24LC256 d'envoyer l'info
  delay(5);
  donnee = Wire.read();
  Serial.print(adress);
  Serial.print(" : ");
  Serial.print(donnee);   
} 
//************************************ 
void ecrituredonnee()
{  
  Wire.beginTransmission(adresse_EEPROM);
  Wire.write((int)(adress>>8));//position adresse 24LC256- Octet le plus significatif
  Wire.write((int)(adress & 0xFF));//position adresse 24LC256- Octet le moins significatif
  Wire.write(val);
  Wire.endTransmission();
  delay(5); 
}
//************************************
