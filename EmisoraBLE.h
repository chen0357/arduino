// ----------------------------------------------------------
// Autor: Yixuan Chen 
// Descripción: Configura la cabecera del beacon, añadir la
// carga como uuid,major,minor,txpower y comienzo el envío 
// del anuncio
// ----------------------------------------------------------
#ifndef EMISORA_H_INCLUIDO
#define EMISORA_H_INCLUIDO

// ----------------------------------------------------------
#include "ServicioEnEmisora.h"

// ----------------------------------------------------------
class EmisoraBLE {
private:

  const char * nombreEmisora;
  const uint16_t fabricanteID;
  const int8_t txPower;

// Constructor
// ----------------------------------------------------------
public:

  using CallbackConexionEstablecida = void ( uint16_t connHandle );
  using CallbackConexionTerminada = void ( uint16_t connHandle, uint8_t reason);

  EmisoraBLE( const char * nombreEmisora_, const uint16_t fabricanteID_, const int8_t txPower_ ):
	nombreEmisora( nombreEmisora_ ) , 	
  fabricanteID( fabricanteID_ ) ,	
  txPower( txPower_ )
  {
	
  } 
	
  // ----------------------------------------------------------
  // Diseño: encenderEmisora()
  // Descripción: Encender el bluetooth de la placa, y por si acaso
  // detener el anuncio si está enviando algo
  // ----------------------------------------------------------
  void encenderEmisora() {
	
	  Bluefruit.begin(); 

	  (*this).detenerAnuncio();
  } 

  // ----------------------------------------------------------
  // Diseño: N,N,N ---> encenderEmisora()
  // Descripción: Encender el bluetooth de la placa y llamar las
  // dos funciones para establecer conexion, en caso de fallo
  // volverá a intentar otra vez
  // ----------------------------------------------------------
  void encenderEmisora( CallbackConexionEstablecida cbce, CallbackConexionTerminada cbct ) {

	encenderEmisora();

	instalarCallbackConexionEstablecida( cbce );
	instalarCallbackConexionTerminada( cbct );
  } 

  // ----------------------------------------------------------
  // Diseño: detenerAnuncio()
  // Descripción: Verifica si la emisora esta emitiendo anuncio,
  // en caso de sí, pues se parará la emisión
  // ----------------------------------------------------------
  void detenerAnuncio() {

	if ( (*this).estaAnunciando() ) {
	  Bluefruit.Advertising.stop(); 
	  }
  }  
  
  // ----------------------------------------------------------
  // Diseño: estaAnunciando() ---> Bool
  // Descripción: Comprueba si la emisora esta enviando anuncios
  // ----------------------------------------------------------
  bool estaAnunciando() {
	return Bluefruit.Advertising.isRunning();
  } // ()

  // ----------------------------------------------------------
  // Diseño: N,N,N,N ---> emitirAnuncioIBeacon()
  // Descripción: Recibe la carga de IBeacon, configura los 
  // parametros de bluetooth y emite anuncios
  // ----------------------------------------------------------
  void emitirAnuncioIBeacon( uint8_t * beaconUUID, int16_t major, int16_t minor, uint8_t rssi ) {

	(*this).detenerAnuncio();
	
	BLEBeacon elBeacon( beaconUUID, major, minor, rssi ); 
	elBeacon.setManufacturer( (*this).fabricanteID );

	Bluefruit.setTxPower( (*this).txPower );
	Bluefruit.setName( (*this).nombreEmisora ); 
	Bluefruit.ScanResponse.addName(); 

	Bluefruit.Advertising.setBeacon( elBeacon ); 
	Bluefruit.Advertising.restartOnDisconnect(true); 
	Bluefruit.Advertising.setInterval(32, 244);   
	Bluefruit.Advertising.start( 0 ); 	
  } 

  // ----------------------------------------------------------
  // Diseño: [String],N ---> emitirAnuncioIBeaconLibre()
  // Descripción: Emite un IBeacon configurado con otros parametros
  // propios
  // ----------------------------------------------------------
  void emitirAnuncioIBeaconLibre( const char * carga, const uint8_t tamanyoCarga ) {

	(*this).detenerAnuncio(); 

	Bluefruit.Advertising.clearData(); 
	Bluefruit.ScanResponse.clearData(); 

	Bluefruit.setName( (*this).nombreEmisora );
	Bluefruit.ScanResponse.addName();

	Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);

	uint8_t restoPrefijoYCarga[4+21] = {
	  0x4c, 0x00, // companyID 2
	  0x02, // ibeacon type 1byte
	  21, // ibeacon length 1byte (dec=21)  longitud del resto // 0x15 // ibeacon length 1byte (dec=21)  longitud del resto
	  '-', '-', '-', '-', 
	  '-', '-', '-', '-', 
	  '-', '-', '-', '-', 
	  '-', '-', '-', '-', 
	  '-', '-', '-', '-', 
	  '-'
	};

	memcpy( &restoPrefijoYCarga[4], &carga[0], ( tamanyoCarga > 21 ? 21 : tamanyoCarga ) ); 

	Bluefruit.Advertising.addData( BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA,
								   &restoPrefijoYCarga[0],
								   4+21 );

	Bluefruit.Advertising.restartOnDisconnect(true);
	Bluefruit.Advertising.setInterval(32, 244);   
	Bluefruit.Advertising.setFastTimeout(30);     
	Bluefruit.Advertising.start( 0 ); 

	Globales::elPuerto.escribir( "emitiriBeacon libre  Bluefruit.Advertising.start( 0 );  \n");
  } 

  // ----------------------------------------------------------
  // Diseño: String ---> anyadirServicio() ---> bool
  // Descripción: Recibe un objeto de la clase ServicioEnEmisora
  // para comprobar si la emisora de bluetooth tiene un servico
  // añadido
  // ----------------------------------------------------------
  bool anyadirServicio( ServicioEnEmisora & servicio ) {

	Globales::elPuerto.escribir( " Bluefruit.Advertising.addService( servicio ); \n");

	bool r = Bluefruit.Advertising.addService( servicio );

	if ( ! r ) {
	  Serial.println( " SERVICION NO AÑADIDO \n");
	}

	return r;
  } 

  // ----------------------------------------------------------
  // Diseño: String ---> anyadirServicioConSusCaracteristicas() ---> Bool
  // ----------------------------------------------------------
  bool anyadirServicioConSusCaracteristicas( ServicioEnEmisora & servicio ) { 
	return (*this).anyadirServicio( servicio );
  } // 

  // ----------------------------------------------------------
  template <typename ... T>
  bool anyadirServicioConSusCaracteristicas( ServicioEnEmisora & servicio,
											 ServicioEnEmisora::Caracteristica & caracteristica,
											 T& ... restoCaracteristicas) {

	servicio.anyadirCaracteristica( caracteristica );

	return anyadirServicioConSusCaracteristicas( servicio, restoCaracteristicas... );
	
  } 

  // ----------------------------------------------------------
  template <typename ... T>
  bool anyadirServicioConSusCaracteristicasYActivar( ServicioEnEmisora & servicio,
													 // ServicioEnEmisora::Caracteristica & caracteristica,
													 T& ... restoCaracteristicas) {

	bool r = anyadirServicioConSusCaracteristicas( servicio, restoCaracteristicas... );

	servicio.activarServicio();

	return r;
	
  } 

  // ----------------------------------------------------------
  void instalarCallbackConexionEstablecida( CallbackConexionEstablecida cb ) {
	Bluefruit.Periph.setConnectCallback( cb );
  } 

  // ----------------------------------------------------------
  void instalarCallbackConexionTerminada( CallbackConexionTerminada cb ) {
	Bluefruit.Periph.setDisconnectCallback( cb );
  } 

  // ----------------------------------------------------------
  BLEConnection * getConexion( uint16_t connHandle ) {
	return Bluefruit.Connection( connHandle );
  }

}; 

#endif


