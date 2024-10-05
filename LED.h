// ----------------------------------------------------------
// Autor: Yixuan Chen 
// Descripción: Configurar el numero del puerto LED y contiene
// funciones para encender, apagar o hacer que parpadea el LED
// ----------------------------------------------------------

#ifndef LED_H_INCLUIDO
#define LED_H_INCLUIDO

  // ----------------------------------------------------------
  // Diseño: N ---> esperar()
  // Descripción: El tiempo de retardo en ms
  // ----------------------------------------------------------
  void esperar (long tiempo) {
    delay (tiempo);
  }

  // Constructor
  // ----------------------------------------------------------
  class LED {
  private:
    int numeroLED;
    bool encendido;

  // Configuración
  // ----------------------------------------------------------
  public:
  LED (int numero)
	: numeroLED (numero), encendido(false)

  {
    pinMode(numeroLED, OUTPUT);
    apagar ();
  }

  // ----------------------------------------------------------
  // Diseño: encender()
  // Descripción: Encender la luz, poner el numero de pin en HIGH
  // ----------------------------------------------------------
  void encender () {
    digitalWrite(numeroLED, HIGH); 
    encendido = true;
  }

  // ----------------------------------------------------------
  // Diseño: apagar()
  // Descripción: Apagar la luz, poner el numero de pin en LOW
  // ----------------------------------------------------------
  void apagar () {
	  digitalWrite(numeroLED, LOW);
	  encendido = false;
  }

  // ----------------------------------------------------------
  // Diseño: alternar()
  // Descripción: llamar la funcion encender() y apagar() 
  // alternativamente
  // ----------------------------------------------------------
  void alternar () {
    if (encendido) {
      apagar();
    } else {
      encender ();
    }
  } 

  // ----------------------------------------------------------
  // Diseño: N ---> brillar()
  // Descripción: Encender la luz por un cierto tiempo y despues
  // apagarla
  // ----------------------------------------------------------
  void brillar (long tiempo) {
	encender ();
	esperar(tiempo); 
	apagar ();
  }
}; 
#endif
