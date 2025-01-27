/*
 * bts7960.h
 *
 *  Created on: Jan 26, 2025
 *      Author: Celine
 */

#ifndef INC_MOTORS_INC_BTS7960_H_
#define INC_MOTORS_INC_BTS7960_H_

#include "main.h"
#include <stdbool.h>

//Struct for bts7960 motor driver and its useful variables
typedef struct __BTS7960_Handler{

	//Timer for PWM counting
	TIM_HandleTypeDef* timer;

	//Output forward PWM channel
	uint32_t crush_pwm_channel;

	//Output reverse PWM channel
	uint32_t uncrush_pwm_channel;

	//0-100% representing the forward duty cycle of the motor
	uint8_t crush_duty;

	//0-100% representing the reverse duty cycle of the motor
	uint8_t uncrush_duty;

	//GPIO port and pin for controlling the forward direction on the h-bridge (if any)
	GPIO_TypeDef* crushPort;
	uint32_t crushPin;

	//GPIO port and pin for controlling the reverse direction on the h-bridge (if any)
	GPIO_TypeDef* uncrushPort;
	uint32_t uncrushPin;

	//Tracks the direction of the motor
	bool toCrush;

}BTS7960;

//Start winch in a specified direction with certain speed
void startWinch(BTS7960* winch, bool crush, uint8_t duty);

//Stop motor
void stopWinch(BTS7960* winch);

//Initialize motor
void initWinch(BTS7960* winch, TIM_HandleTypeDef* timer, uint32_t crushChannel, uint32_t uncrushChannel,uint8_t crushDuty,
		uint8_t uncrushDuty, GPIO_TypeDef* crushPort, uint32_t crushPin, GPIO_TypeDef* uncrushPort, uint32_t uncrushPin, bool isInitialFwd);

//Makes the motor go forward
void goForwardWinch(BTS7960* winch,uint8_t duty);

//Makes the motor reverse
void goBackwardWinch(BTS7960* winch,uint8_t duty);



#endif /* INC_MOTORS_INC_BTS7960_H_ */
