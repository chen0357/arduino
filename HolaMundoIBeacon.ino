// --------------------------------------------------------------
// Autor: yixuan Chen 
// Descripción: Inicialmente configura la placa y la inicializa,
// coge los valores de CO y temperatura desde varios sensores
// y comienza el proceso del envío de Beacon.
// --------------------------------------------------------------

// --------------------------------------------------------------
#include <bluefruit.h>
#include "LED.h"
#include "PuertoSerie.h"

// --------------------------------------------------------------
namespace Globales {
  
  LED elLED ( /* NUMERO DEL PIN LED = */ 7 );

  PuertoSerie elPuerto ( /* velocidad = */ 115200 ); 

};

// --------------------------------------------------------------
#include "EmisoraBLE.h"
#include "Publicador.h"
#include "Medidor.h"

// --------------------------------------------------------------
namespace Globales {

  Publicador elPublicador;

  Medidor elMedidor;

};

// --------------------------------------------------------------
void inicializarPlaquita () {

  

} 

// setup() 
// --------------------------------------------------------------
void setup() {

  Globales::elPuerto.esperarDisponible();

  inicializarPlaquita();

  Globales::elPublicador.encenderEmisora();

  Globales::elMedidor.iniciarMedidor();

  esperar( 1000 );

  Globales::elPuerto.escribir( "---- setup(): fin ---- \n " );

  ServicioEnEmisora miServicio("MyService");
  miServicio.activarServicio();


} 


// Encender y apagar la lucecita cada cierto tiempo
// --------------------------------------------------------------
inline void lucecitas() {
  using namespace Globales;

  elLED.brillar( 100 ); 
  esperar ( 400 ); 
  elLED.brillar( 100 ); 
  esperar ( 400 );  
  Globales::elLED.brillar( 100 ); 
  esperar ( 400 ); 
  Globales::elLED.brillar( 1000 ); 
  esperar ( 1000 ); 
} 


// loop ()
// --------------------------------------------------------------
namespace Loop {
  uint8_t cont = 0;
};

void loop () {

  using namespace Loop;
  using namespace Globales;

  cont++;

  elPuerto.escribir( "\n---- loop(): empieza " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );

  lucecitas();

  //Cojo el valor de co, y lo publico
  int valorCO = elMedidor.medirCO();
  elPublicador.publicarCO( valorCO, cont, 1000);
  
   //Cojo el valor de temperatura, y lo publico
  int valorTemperatura = elMedidor.medirTemperatura(); 
  elPublicador.publicarTemperatura( valorTemperatura, cont, 1000);

  esperar( 2000 );

  elPublicador.laEmisora.detenerAnuncio();
  
  elPuerto.escribir( "---- loop(): acaba **** " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );
  
} 

