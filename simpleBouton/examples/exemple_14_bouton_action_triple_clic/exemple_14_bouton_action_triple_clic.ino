#include "simpleBouton.h"

const uint8_t pin_bouton = 3;//cablage pin---BP---GND

boutonAction bouton(pin_bouton);

void simpleClic() {Serial.println("simple clic");}
void doubleClic() {Serial.println("double clic");}
void tripleClic() {Serial.println("triple clic");}

void setup()
{
  Serial.begin(115200);
  bouton.attacher(simpleClic, doubleClic, tripleClic);
}

void loop()
{
  bouton.actualiser();
}