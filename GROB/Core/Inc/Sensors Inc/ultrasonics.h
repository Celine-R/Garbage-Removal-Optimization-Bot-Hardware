/*
 * ultrasonics.h
 *
 *  Created on: Jan 26, 2025
 *      Author: Celine
 */

#ifndef INC_SENSORS_INC_ULTRASONICS_H_
#define INC_SENSORS_INC_ULTRASONICS_H_

#include "main.h"
#include <stdbool.h>

//Struct for ultrasonic sensors and its useful variables
typedef struct __Ultrasonic_Handler{

	//Timer
	TIM_HandleTypeDef* timer;

	//GPIO port and pin for controlling the forward direction on the h-bridge (if any)
	GPIO_TypeDef* TrigPort;
	uint32_t TrigPin;

	//GPIO port and pin for controlling the reverse direction on the h-bridge (if any)
	GPIO_TypeDef* EchoPort;
	uint32_t EchoPin;

}Ultrasonic;

//Initialize ultrasonic sensor
void initUltrasonic(Ultrasonic* dist_sensor,TIM_HandleTypeDef* timer,GPIO_TypeDef* TrigPort,uint32_t TrigPin,GPIO_TypeDef* EchoPort,uint32_t EchoPin);

//Read distance
uint16_t readUltrasonic(Ultrasonic* dist_sensor);

#endif /* INC_SENSORS_INC_ULTRASONICS_H_ */
