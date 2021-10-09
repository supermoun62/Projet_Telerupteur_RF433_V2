//Exemple librairie simpleBouton.h
//Programme minimal : plus simple y a pas !
#include "simpleBouton.h"

simpleBouton boutonTest(7);//Cablage : pin---BP---GND

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  if (boutonTest) Serial.println("Detection appui bouton");
}
