# Sprint_0_Arduino de Yixuan Chen

El objectivo del proyecto es que detecte y calcule el valor de temperatura y co que hay en el medio mediante y que estos valores los envia a la aplicación del móvil android mediante un emisor BLE de CO, de cierta manera se interactua con la base de datos del servidor. Por otro lado, la página web del cliente también se puede visualizar estos valores e interactuar con ellos 

## Tabla de Contenidos

- [Descripción](#descripción)
- [Materiales](#materiales)
- [Instalación](#instalación)
- [Código](#código)
- [Uso](#uso)


## Descripción

Para este sprint, el objetivo de la parte arduino es enviar el valor de co obtenido por el sensor utilizando el mini módulo Sparkfun Pro nRF82540.

## Materiales

- Arduino Uno
- Módulo Sparkfun Pro nRF82540 mini
- Cable USB para la conexión Arduino-PC
- ULPSM-O3 968-046

## Instalación

- Asegúrate de tener una placa Arduino compatible y un módulo BLE
- Abre el archivo de código fuente en el entorno de desarrollo de Arduino
- Conecta tu placa Arduino a tu computadora a través del puerto USB
- Compila y carga el código en tu placa Arduino
- Asegúrate de que el módulo BLE esté configurado y emparejado con tu dispositivo móvil o central BLE
- Ejecuta la aplicación correspondiente en tu dispositivo para recibir los valores de CO transmitidos por la placa Arduino

## Código

En principio del código está la fución 'setup()' que se encarga de iniciar la placa Arduino y el módulo BLE, luego esta la función 'loop()', que es el bucle del programa y se encarga de la medición y publicación continua de los valores de CO y temperatura.



