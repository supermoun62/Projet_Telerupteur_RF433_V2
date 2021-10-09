//Exemple librairie simpleBouton.h
//Affichage des durées d'appui
#include "simpleBouton.h"

simpleBouton bouton(7);
//Cablage : pin---BP---GND

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  //Lecture de la durée d'appui AVANT d'actualiser
  uint32_t duree = bouton.dureeEnfonce();
 
  bouton.actualiser();
  
  if (bouton.vientDEtreEnfonce())
  {
	Serial.print("Bouton enfonce");
  }

  if (bouton.vientDEtreRelache())
  {
    Serial.print(" pendant ");
	Serial.print(duree);
	Serial.println(" ms");
  } 
}
