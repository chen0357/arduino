// --------------------------------------------------------------
// Autor: Yixuan Chen 
// Descripción: Configura los parametros del publicador para 
// la publicación del ibeacon
// --------------------------------------------------------------
#include "EmisoraBLE.h"
#include "PuertoSerie.h"
#ifndef PUBLICADOR_H_INCLUIDO
#define PUBLICADOR_H_INCLUIDO

// Constructor
// --------------------------------------------------------------
class Publicador {

private:

  uint8_t beaconUUID[16] = { 
	'E', 'P', 'S', 'G', '-', 'G', 'T', 'I', 
	'-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
	};

  
public:
  EmisoraBLE laEmisora {
	"GTI-3A_CHEN", 
	  0x004c, 
	  4 
	};

  const int RSSI = -53; 

// --------------------------------------------------------------
public:

  enum MedicionesID  {
	CO = 11,
	TEMPERATURA = 12,
	RUIDO = 13
  };

  Publicador( ) {
  } 

  // --------------------------------------------------------------
  // Diseño: encenderEmisora()
  // Descripción: Llama la función encenderEmisora() de la clase EmisoraBLE
  // --------------------------------------------------------------
  void encenderEmisora() {
	(*this).laEmisora.encenderEmisora();
  } 

  // --------------------------------------------------------------
  // Diseño: R,N,N ---> publicarCO() 
  // Descripción: Recibe parametros para publicar el valor de co
  // --------------------------------------------------------------
 void publicarCO(int16_t valorCO, uint8_t contador, long tiempoEspera) {
    Globales::elPuerto.escribir("Iniciando CO broadcasting...\n");


 // Print CO value to the serial monitor
    Globales::elPuerto.escribir("CO Reading: ");
    Globales::elPuerto.escribir(valorCO);
    Globales::elPuerto.escribir("\n");

    uint16_t major = (MedicionesID::CO << 8) + contador;
    (*this).laEmisora.emitirAnuncioIBeacon((*this).beaconUUID, major, valorCO, (*this).RSSI);

    esperar(tiempoEspera);

    (*this).laEmisora.detenerAnuncio();
    Globales::elPuerto.escribir("CO broadcasting detenido.\n");
  } 

  // --------------------------------------------------------------
  // Diseño: R,N,N ---> publicarTemperatura() 
  // Descripción: Recibe parametros para publicar el valor de temperatura
  // --------------------------------------------------------------
  void publicarTemperatura(int16_t valorTemperatura, uint8_t contador, long tiempoEspera) {
    Globales::elPuerto.escribir("Iniciando Temperatura broadcasting...\n");

    uint16_t major = (MedicionesID::TEMPERATURA << 8) + contador;
    (*this).laEmisora.emitirAnuncioIBeacon((*this).beaconUUID, major, valorTemperatura, (*this).RSSI);

    esperar(tiempoEspera);

    (*this).laEmisora.detenerAnuncio();
    Globales::elPuerto.escribir("Temperatura broadcasting detenido.\n");
  } 
	
}; 
#endif
