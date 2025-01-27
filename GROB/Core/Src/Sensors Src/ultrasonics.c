/*
 * ultrasonics.c
 *
 *  Created on: Jan 26, 2025
 *      Author: Celine
 */

#include "Sensors Inc/ultrasonics.h"
#include "main.h"

extern TIM_HandleTypeDef htim1;

void initUltrasonic(Ultrasonic* dist_sensor,TIM_HandleTypeDef* timer,GPIO_TypeDef* TrigPort,uint32_t TrigPin,GPIO_TypeDef* EchoPort,uint32_t EchoPin)
{
	//Initialize the core parameters and default values (direction, duty)
	dist_sensor->timer = timer;
	dist_sensor->TrigPort = TrigPort;
	dist_sensor->TrigPin = TrigPin;
	dist_sensor->EchoPort = EchoPort;
	dist_sensor->EchoPin = EchoPin;


	HAL_TIM_Base_Start(dist_sensor->timer);
	HAL_GPIO_WritePin(TrigPort, TrigPin, GPIO_PIN_RESET);
}

//Return distance in cm
uint16_t readUltrasonic(Ultrasonic* dist_sensor){

	uint32_t pMillis;
	uint32_t val1 = 0;
	uint32_t val2 = 0;
	uint16_t distance  = 0;

	HAL_GPIO_WritePin(dist_sensor->TrigPort,dist_sensor->TrigPin, GPIO_PIN_SET);
  __HAL_TIM_SET_COUNTER(dist_sensor->timer, 0);
   while (__HAL_TIM_GET_COUNTER (dist_sensor->timer) < 10);  // wait for 10 us
   HAL_GPIO_WritePin(dist_sensor->TrigPort, dist_sensor->TrigPin, GPIO_PIN_RESET);

   pMillis = HAL_GetTick();
   while (!(HAL_GPIO_ReadPin (dist_sensor->EchoPort, dist_sensor->EchoPin)) && pMillis + 10 >  HAL_GetTick());
   val1 = __HAL_TIM_GET_COUNTER (dist_sensor->timer);

   pMillis = HAL_GetTick();
   while ((HAL_GPIO_ReadPin (dist_sensor->EchoPort, dist_sensor->EchoPin)) && pMillis + 50 > HAL_GetTick());
   val2 = __HAL_TIM_GET_COUNTER (dist_sensor->timer);

   distance = (val2-val1)* 0.034/2;

   return distance;
}
