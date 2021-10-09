//Exemple librairie simpleBouton.h
//Appel de fonction sur appui bouton + gestion de répétition sur appui long
#include "simpleBouton.h"

simpleBouton bouton(7);
//Cablage : pin---BP---GND

void setup()
{
  Serial.begin(115200);
}

const uint32_t tempo = 1000;
uint32_t delai;

void loop()
{
  bouton.actualiser();
  if (bouton.vientDEtreEnfonce())
  {
    delai = 0;
  }
  if (bouton.estEnfonceDepuisAuMoins(delai))
  {
    actionAssociee();
    delai = delai + tempo;
  }
}

void actionAssociee()
{
  Serial.println("Action");
}
