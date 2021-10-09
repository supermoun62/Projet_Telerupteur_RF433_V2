//Exemple librairie simpleBouton.h
//Led témoin d'appui bouton
#include "simpleBouton.h"

const uint8_t pin_led = 13;
const uint8_t pin_bouton = 7;
//Cablage : pin---BP---GND

simpleBouton bouton(pin_bouton);

void setup()
{
  //Initialisation de la led
  pinMode(pin_led, OUTPUT);
  digitalWrite(pin_led, LOW);
}

void loop()
{
  bouton.actualiser();
  if (bouton.vientDEtreEnfonce())
  {
	digitalWrite(pin_led, HIGH); //allumer la led
  }
  if (bouton.vientDEtreRelache())
  {
	digitalWrite(pin_led, LOW); //éteindre la led
  }
}
/*NB : les fonctions booléennes sont pratiques d'utilisation avec l'opérateur ternaire.
//Par exemple, équivalent condensé :
void loop()
{
  if (bouton.actualiser()) //Changement d'état du bouton
  {
    digitalWrite(pin_led, bouton.estEnfonce() ? HIGH : LOW);
  }
}
*/
