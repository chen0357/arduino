// ------------------------------------------------------
// Autor: Yixuan Chen 

// ------------------------------------------------------

#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO

class Medidor {

private:
  int pinGas = 5;
  int pinRef = 28;
  int pinTemperatura = 29;

public:
  float rawGas;
  float rawRef;
  float rawTemperatura;

  float vGas;
  float vRef;
  float vTemperatura;

  float vMedida;
  float concentracion;
  float incrementoTemperatura;
  float temperatura;


  // Constructor
  // ------------------------------------------------------
  Medidor(  ) {
    
  }   

  // ------------------------------------------------------
  void iniciarMedidor() {
    
    pinMode(pinGas,INPUT);
    pinMode(pinRef,INPUT);
    pinMode(pinTemperatura,INPUT);
    
  } 

  // En esta version se devuelve un valor constante
  // ------------------------------------------------------
  int medirCO() {

    
    rawGas =analogRead(pinGas);
    rawRef =analogRead(pinRef);
    rawTemperatura =analogRead(pinTemperatura);

    vGas = ( rawGas / 5566)*3.3;
    vRef =  (rawRef/ 5566)*3.3;
    vTemperatura = rawTemperatura*3.3;

    vMedida= (vGas - vRef) / (499 * 100 * 0.000001);
    
return  vMedida;
	 
  } 

  // En esta version se devuelve un valor constante
  // ------------------------------------------------------
  int medirTemperatura() {
    
    temperatura=87*vTemperatura-18;
    return 20;

  } 
	
};
#endif
