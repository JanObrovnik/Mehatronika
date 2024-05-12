#include <SoftwareSerial.h> // Uvozitev knjiznice

SoftwareSerial SerialUART(20, 21); // Definiramo SoftwareSerial objekt z RX na pin-u 20 in TX na pin-u 21

void setup() {

  SerialUART.begin(9600); // Nastavimo hitrost prenosa, hitrost mara biti enaka na obeh mikrokrmilnikih

}

void loop() {

  SerialUART.write(12) // Posljemo vrednost 12

  delay(1000)

}
