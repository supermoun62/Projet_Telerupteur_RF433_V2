/*  
  Synopsis: Lecture totale mémoire EEPROM 24LC256
   
  Source: https://lesiteferroviaire.pagesperso-orange.fr/Memoire%2024LC512.htm
          http://electroniqueamateur.blogspot.com/2020/01/utiliser-une-memoire-eeprom-i2c-arduino.html 

  C.Mercier  62128 Boiry-Becquerelle             
*/
#include <Wire.h>  // bibliothèque i2c
#define adresse_EEPROM 0x50    //Addresse i2c de l'EEPROM
int compteur = 0;
int donnee = 0;
int valMax = 4096;
bool bitStop = 0;
//************************************
void setup(void)
{
Serial.begin(9600);
Wire.begin();//On declare Arduino en tant que maitre
delay(1000); 
}//FIN SETUP
//************************************
void loop() 
{  
if( (compteur <= valMax && bitStop == 0) )
    for(compteur=0 ; compteur<=valMax ; compteur++)
      {
        lecturedonnee();
        delay(10);
      }
if ( compteur > valMax )
{
  bitStop = 1;          
}
//Serial.print(bitStop);
}//FIN LOOP
//************************************
void lecturedonnee()
{
  Wire.beginTransmission(adresse_EEPROM);  // adresse i2c du 24LC256
  Wire.write((int)(compteur>>8));//position adresse 24LC256- Octet le plus significatif
  Wire.write((int)(compteur & 0xFF));//position adresse 24LC256- Octet le moins significatif
  Wire.endTransmission();
  Wire.requestFrom(adresse_EEPROM, 1); // on demande au 24LC256 d'envoyer l'info
  delay(5);
  donnee = Wire.read();
  Serial.print(compteur);
  Serial.print(" : ");
  Serial.print(donnee, BIN);
  Serial.print(" ");
  Serial.print("--");
  Serial.print(" ");
  Serial.print(donnee, HEX);
  Serial.println("");   
} 
//************************************ 
