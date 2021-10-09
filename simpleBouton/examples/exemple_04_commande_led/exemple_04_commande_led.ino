//Exemple librairie simpleBouton.h
//Commande d'une led par un bouton
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

bool led_allumee = false;

void loop()
{
  bouton.actualiser();
  if (bouton.vientDEtreEnfonce())
  {
    led_allumee = !led_allumee; //inversion du bouléen
	digitalWrite(pin_led, led_allumee ? HIGH : LOW);
	/*Si pas à l'aise avec l'opérateur ternaire, code équivalent :
	if (led_allumee)
	{
	  digitalWrite(pin_led, HIGH);
	}
	else
	{
	  digitalWrite(pin_led, LOW);
	}*/
  }
}
