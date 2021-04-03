#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS

osThreadId_t thread1_id, thread2_id;

void MyThread(void *arg)
{
  
  uint8_t state = 0;
  uint32_t tick;
  
  while(1){
    tick = osKernelGetTickCount();
    
    state ^= (uint8_t)arg;
    LEDWrite((uint8_t)arg, state);
    
    osDelayUntil(tick + 100);
  } // while
}  
//  
//  uint8_t *Ponteiro;
//  
//  
//  
//  Ponteiro = arg;
//  
// // int param;
//  int ala = (int)arg;
//  param = (int) arg;
//
//  
//  uint8_t lala;
//  
//  lala = 1;
//  lala = 2;
//  
  
  //lala = (int) arg;
  
//  
//  if ((int)arg == 1 )
//  {
//  while(1){
//    state ^= LED1;
//    LEDWrite(LED1, state);
//    
//    osDelay(100);
//  } // while
//  }
//} // thread1
//
//void thread2(void *arg){
//  uint8_t state = 0;
//  uint32_t tick;
//  
//  while(1){
//    tick = osKernelGetTickCount();
//    
//    state ^= LED2;
//    LEDWrite(LED2, state);
//    
//    osDelayUntil(tick + 100);
//  } // while
//} // thread2

//void MyThread(void *arg)
//{
//  uint8_t state = 0;
//  
//  int valor, *Pvalor;
//
//  Pvalor = arg;
////  valor = *Pvalor;
//  
//  valor = (int) arg;
//  
//  //if arg == 1 -> led 1
//  //if arg == 2 -> led 2
//  if (*Pvalor == 1)
//  {
//      while(1)
//      {
//      state ^= LED1;
//      LEDWrite(LED1, state);
//      osDelay(100);
//      } // while
//    // thread1
//  }
//
//  uint32_t tick;
//  
//  while(1)
//  {
//    tick = osKernelGetTickCount();
//    
//    state ^= LED2;
//    LEDWrite(LED2, state);
//    
//    osDelayUntil(tick + 100);
//  } // while
//} // thread2

void main(void){
  LEDInit(LED2 | LED1);

//  uint8_t entrada1, entrada2;
  
//  entrada1 = 1;
//  entrada2 = 2;
//  
  osKernelInitialize();

  
  thread1_id = osThreadNew(MyThread, (void*)1, NULL);// (void*)entrada1, NULL);
  thread2_id = osThreadNew(MyThread, (void*)2, NULL);

  if(osKernelGetState() == osKernelReady)
    osKernelStart();

  while(1);
} // main
