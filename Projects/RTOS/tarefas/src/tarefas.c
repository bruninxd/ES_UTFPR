//ALUNO BRUNO SOARES DE SOUZA
//1558781

#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS

osThreadId_t thread1_id, thread2_id, thread3_id, thread4_id;

typedef struct{
  uint8_t num_LED;
  uint32_t time_LED;
}LED_struct;

void MyThread(void *arg)
{
  uint8_t state = 0;
  uint32_t tick;
  
  while(1)
  {
    tick = osKernelGetTickCount();

    state ^= ((LED_struct*)arg)->num_LED;
    LEDWrite(((LED_struct*)arg)->num_LED, state);
    
    osDelayUntil(tick + ((LED_struct*)arg)->time_LED);
  } // while
}  
    
void main(void){
  LEDInit(LED4 |LED3 |LED2 | LED1);
  
  
  LED_struct LED_stru1, LED_stru2, LED_stru3, LED_stru4;
  
  LED_stru1.num_LED = 1;
  LED_stru1.time_LED = 200;
  LED_stru2.num_LED = 2;
  LED_stru2.time_LED = 300;
  LED_stru3.num_LED = 4;
  LED_stru3.time_LED = 500;
  LED_stru4.num_LED = 8;
  LED_stru4.time_LED = 700;
  
  osKernelInitialize();

  thread1_id = osThreadNew(MyThread, (void*)&LED_stru1, NULL);
  thread2_id = osThreadNew(MyThread, (void*)&LED_stru2, NULL);
  thread3_id = osThreadNew(MyThread, (void*)&LED_stru3, NULL);
  thread4_id = osThreadNew(MyThread, (void*)&LED_stru4, NULL);

  if(osKernelGetState() == osKernelReady)
    osKernelStart();

  while(1);
} // main
