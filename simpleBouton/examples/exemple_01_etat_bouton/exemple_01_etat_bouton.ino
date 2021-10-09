//Exemple librairie simpleBouton.h
//Affichage de l'état du bouton
#include "simpleBouton.h"

simpleBouton bouton(7);
//Cablage : pin---BP---GND

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  bouton.actualiser();
  if (bouton.vientDEtreEnfonce()) Serial.println("Enfonce");
  if (bouton.vientDEtreRelache()) Serial.println("Relache");
}
