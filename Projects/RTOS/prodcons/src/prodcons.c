//****** Universidade Tecnológica Federal do Paraná - UTFPR     ******\\
//****** Engenharia Eletrônica - DAELN                          ******\\
//****** Sistemas embarcados - Professor: Hugo Vieira Neto      ******\\
//****** Aluno: Bruno Soares de Souza 1558781                   ******\\
// Prática 5:

//Exercício 5:
//  
//  Tp = 500 ms e Tc = 1s
//      LEDs ficam acesos 1 segundo de cada vez, na velocidade do consumidor, pois ele consome um de cada vez
//          Consumidor tem que esperar o produtor liberar para ele consumir algo
//              O que mesmo sendo feito em 500ms, o consumidor ainda tem que esperar ser liberado o buffer

// 1 e 2)
//  Tp = 2s , Tc = 250 ms
//    LEDs mudam a cada 2 segundos, porque enquanto o produtor está com o semáforo,
//          não há dados para serem consumidos, e o consumidor fica aguardando ser liberado
//
//  tp = 500 ms, tc = 500 ms
//      LEDs mudam a cada meio segundo, cada item produzido é logo em seguida consumido

// No geral nota-se a dependência entre os dois, para a garantia da exclusB9Dão mútua.

// 3)
// Não há impacto entre duas tarefas, pois uma produz e a outra consome, e há exclusão mútua
// Considerando também que todo o buffer é modificado por vez de acesso


#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS


#include "driverbuttons.h" // Projects/drivers
#include "driverleds.h"

#define BUFFER_SIZE 8

osThreadId_t produtor_id, consumidor_id;
osSemaphoreId_t vazio_id, cheio_id;
uint8_t buffer[BUFFER_SIZE];

    uint8_t index_i = 0, count = 0;

    const int buttonDebounceTime = 300;

void GPIOJ_Handler(void)
{
  ButtonIntDisable(USW1);
//  ButtonIntClear(USW1);  poderia ser aqui

    osSemaphoreAcquire(vazio_id, 0); //ISR, não pode travar o sistema
    buffer[index_i] = count; // coloca no buffer
    osSemaphoreRelease(cheio_id); // sinaliza um espaço a menos
    
    index_i++; // incrementa índice de colocação no buffer
    if(index_i >= BUFFER_SIZE)
    {
      index_i = 0;
    }
         
    count++;
    count &= 0x0F; // produz nova informação

} // GPIOJ_Handler


void consumidor(void *arg){
  uint8_t index_o = 0, state;
  
  while(1){
    
    osSemaphoreAcquire(cheio_id, osWaitForever); // há dado disponível?
    state = buffer[index_o]; // retira do buffer
    osSemaphoreRelease(vazio_id); // sinaliza um espaço a mais
    
    index_o++;
    if(index_o >= BUFFER_SIZE) // incrementa índice de retirada do buffer
      index_o = 0;
    
    LEDWrite(LED4 | LED3 | LED2 | LED1, state); // apresenta informação consumida

    osDelay(buttonDebounceTime);
    ButtonIntClear(USW1);
    ButtonIntEnable(USW1);
    
    } // while
} // consumidor

void main(void){
  SystemInit();
  LEDInit(LED4 | LED3 | LED2 | LED1);
  
  //botao
  ButtonInit(USW1);
  ButtonIntEnable(USW1);

  osKernelInitialize();

  consumidor_id = osThreadNew(consumidor, NULL, NULL);

  vazio_id = osSemaphoreNew(BUFFER_SIZE, BUFFER_SIZE, NULL); // espaços disponíB9Dveis = BUFFER_SIZE
  cheio_id = osSemaphoreNew(BUFFER_SIZE, 0, NULL); // espaços ocupados = 0
  

  
  if(osKernelGetState() == osKernelReady)
    osKernelStart();

  while(1);
} // main
