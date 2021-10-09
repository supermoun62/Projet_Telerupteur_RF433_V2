//Exemple librairie simpleBouton.h
//Gestion d'un compteur avec un bouton + et un bouton -
#include "simpleBouton.h"

simpleBouton bouton_plus(7);
simpleBouton bouton_moins(8);
//Cablage : pin---BP---GND

int compteur = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(compteur);
}

void loop()
{
  bouton_plus.actualiser();
  bouton_moins.actualiser();

  if (bouton_plus.vientDEtreEnfonce())
  {
    compteur++;
	Serial.println(compteur);
  }
  
  if (bouton_moins.vientDEtreEnfonce())
  {
    compteur--;
	Serial.println(compteur);
  }
}
