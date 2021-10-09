#include "simpleBouton.h"

const uint8_t pin_bouton = 3;//cablage pin---BP---GND

boutonAction bouton(pin_bouton);

void clic() {Serial.println("clic");}

void setup()
{
  Serial.begin(115200);
  bouton.attacher(clic);
}

void loop()
{
  bouton.actualiser();
}