/* Capteur de température numérique à 1 fil DS18B20 avec exemple de code Arduino. Plus d'infos : https://www.makerguides.com */

// Incluez les bibliothèques Arduino requises :
#include <OneWire.h>
#include <DallasTemperature.h>

// Définir à quelle broche de l'Arduino le bus 1-Wire est connecté :
#define ONE_WIRE_BUS 2

// Crée une nouvelle instance de la classe oneWire pour communiquer avec n'importe quel appareil OneWire :
Un fil un fil(ONE_WIRE_BUS);

// Passez la référence oneWire à la bibliothèque DallasTemperature :
Capteurs de température Dallas(&oneWire);

void setup() {
  // Commencer la communication série à un débit en bauds de 9 600 :
  Série.begin(9600);
  // Démarrez la bibliothèque :
  capteurs.begin();
}

boucle vide() {
  // Envoie la commande à tous les appareils sur le bus pour effectuer une conversion de température :
  capteurs.requestTemperatures();

  // Récupère la température en degrés Celsius pour l'index de l'appareil :
  float tempC = capteurs.getTempCByIndex(0); // l'index 0 fait référence au premier appareil
  // Récupère la température en degrés Fahrenheit pour l'index de l'appareil :
  flotteur tempF = capteurs.getTempFByIndex(0);

  // Imprime la température en Celsius dans le Serial Monitor :
  Serial.print("Température : ");
  Serial.print(tempC);
  Serial.print(" \xC2\xB0"); // affiche le symbole du degré
  Serial.print("C | ");

  // Imprimer la température en Fahrenheit
  Serial.print(tempF);
  Serial.print(" \xC2\xB0"); // affiche le symbole du degré
  Serial.println("F");

  // Attendez 1 seconde :
  retard(1000);
}