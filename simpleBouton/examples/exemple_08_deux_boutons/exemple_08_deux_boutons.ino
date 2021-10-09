//Exemple librairie simpleBouton.h
//Affichage de l'état de deux boutons
#include "simpleBouton.h"

simpleBouton bouton1(7);
simpleBouton bouton2(8);
//Cablage : pin---BP---GND

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  bouton1.actualiser();
  bouton2.actualiser();

  if (bouton1.vientDEtreEnfonce()) Serial.println("Bouton 1 Enfonce");
  if (bouton1.vientDEtreRelache()) Serial.println("Bouton 1 Relache");
  if (bouton2.vientDEtreEnfonce()) Serial.println("Bouton 2 Enfonce");
  if (bouton2.vientDEtreRelache()) Serial.println("Bouton 2 Relache");
}
