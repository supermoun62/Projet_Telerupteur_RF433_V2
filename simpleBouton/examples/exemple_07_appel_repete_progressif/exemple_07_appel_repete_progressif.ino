//Exemple librairie simpleBouton.h
//Appel de fonction sur appui bouton + gestion de répétition sur appui long
//avec cadence de répétition progressive
#include "simpleBouton.h"

simpleBouton bouton(7);
//Cablage : pin---BP---GND

void setup()
{
  Serial.begin(115200);
}

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
    delai = delai + delaiRepetition(bouton.dureeEnfonce());
  }
}

uint32_t delaiRepetition(uint32_t duree)
{ //Exemple de cadence progressive
  if (duree <  1000) return 1000;
  if (duree <  3000) return 500;
  if (duree <  7000) return 250;
  return 100;
}

void actionAssociee()
{
  Serial.println("Action");
}
