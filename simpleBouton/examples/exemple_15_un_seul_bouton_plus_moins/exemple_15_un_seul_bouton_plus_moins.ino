#include "simpleBouton.h"

//1) cliquer et maintenir enfonce pendant plus de 20 secondes
//2) double-cliquer et maintenir enfonce pendant plus de 20 secondes

const uint8_t pin_bouton = 3;//cablage pin---BP---GND

boutonAction bouton(pin_bouton);

int nombre = 0;
void augmenter() {Serial.println(++nombre);}
void diminuer()  {Serial.println(--nombre);}

void setup()
{
  Serial.begin(115200);
  Serial.println(nombre);
  bouton.attacher(augmenter, diminuer);
  bouton.activerRepetition();
}

void loop()
{
  bouton.actualiser();
}