//****** Universidade Tecnológica Federal do Paraná - UTFPR     ******\\
//****** Engenharia Eletrônica - DAELN                          ******\\
//****** Sistemas embarcados - Professor: Hugo Vieira Neto      ******\\
//****** Aluno: Bruno Soares de Souza 1558781                   ******\\

// Pratica 3 - Código Gray em 3 bits separado por estados

#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "driverlib/systick.h"
#include "driverleds.h" // Projects/drivers

// MEF com 8 estados e 1 evento temporal que alterna entre eles
// Seleção por estado

volatile uint8_t Evento = 0;



void SysTick_Handler(void){
  Evento = 1;
} // SysTick_Handler

void main(void){
  
  int estado_Numero = 0; // estado inicial 0
  
  LEDInit(LED1); // bit 0
  LEDInit(LED2); // bit 1
  LEDInit(LED3); // bit 2
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
  SysTickIntEnable();
  SysTickEnable();

  
  while(1){
    
    switch(estado_Numero){
      
    case 0: // zeram os 3 caso o programa seja parado em outro estado e reiniciado com algum led aceso
      LEDOff(LED1); 
      LEDOff(LED2);
      LEDOff(LED3);   
      
      if(Evento){
        Evento = 0;
        estado_Numero ++;
      } // if
      break;
      
      
    case 1:
      LEDOn(LED1);  
      
      if(Evento){
        Evento = 0;
        estado_Numero ++;
      } // if
      break;

    case 2:

      LEDOn(LED2);
      
      if(Evento){
        Evento = 0;
        estado_Numero ++;
      } // if
      break;

    case 3:
      LEDOff(LED1);
      
      if(Evento){
        Evento = 0;
        estado_Numero ++;
      } // if
      break;

    case 4:
      
      LEDOn(LED3);     
      
      if(Evento){
        Evento = 0;
        estado_Numero ++;
      } // if
      break;

    case 5:
      LEDOn(LED1);  
      
      if(Evento){
        Evento = 0;
        estado_Numero ++;
      } // if
      break;

    case 6:
      LEDOff(LED2);

      if(Evento){
        Evento = 0;
        estado_Numero ++;
      } // if
      break;

    case 7:
      LEDOff(LED1);    
      
      if(Evento)
      {
        Evento = 0;
        estado_Numero = 0;
      } // if
      break;

     
    } // switch
  } // while
} // main
