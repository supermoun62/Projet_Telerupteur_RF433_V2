//Exemple librairie simpleBouton.h
//Gestion d'un compteur avec un bouton + et un bouton -
//et répétition progressive en cas d'appui long
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

uint32_t delai;
bool blocage = false;

void loop()
{
  bouton_plus.actualiser();
  bouton_moins.actualiser();
  
  if (bouton_plus.vientDEtreEnfonce() || bouton_moins.vientDEtreEnfonce()) delai = 0;

  //Gestion du petit malin qui appuie sur les deux boutons en même temps
  if (bouton_plus.estEnfonce() && bouton_moins.estEnfonce()) blocage = true;
  if (bouton_plus.estRelache() && bouton_moins.estRelache()) blocage = false;
  if (blocage) return;
   
  if (bouton_plus.estEnfonceDepuisAuMoins(delai))
  {
    compteur++;
	Serial.println(compteur);
    delai = delai + delaiRepetition(bouton_plus.dureeEtatActuel());
  }

  if (bouton_moins.estEnfonceDepuisAuMoins(delai))
  {
    compteur--;
	Serial.println(compteur);
    delai = delai + delaiRepetition(bouton_moins.dureeEtatActuel());
  }
}

uint32_t delaiRepetition(uint32_t duree)
{ //Exemple de cadence progressive
  if (duree <  1000) return 1000;
  if (duree <  3000) return 500;
  if (duree <  7000) return 250;
  return 100;
}
