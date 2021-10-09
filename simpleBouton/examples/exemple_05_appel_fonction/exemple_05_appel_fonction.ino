//Exemple librairie simpleBouton.h
//Appel d'une fonction à chaque appui bouton
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
  if (bouton.vientDEtreEnfonce())
  {
    actionAssociee();
  }
}

void actionAssociee()
{
  Serial.println("Action");
}
