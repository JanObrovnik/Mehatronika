#include <SoftwareSerial.h> // Uvozitev knjiznice

SoftwareSerial SerialUART(20, 21); // Definiramo SoftwareSerial objekt z RX na pin-u 20 in TX na pin-u 21

void setup() {

  SerialUART.begin(9600); // Nastavimo hitrost prenosa, hitrost mara biti enaka na obeh mikrokrmilnikih

  Serial.begin(9600); // Dodamo, da lahko racunalnik prebere prejeto porocilo

}

void loop() {

  Serial.println(SerialUART.read()); // Preberemo prejeto porocilo in ga izpisemo na konzoli

}
