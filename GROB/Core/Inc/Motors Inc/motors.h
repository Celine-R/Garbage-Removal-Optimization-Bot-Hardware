/*
 * motors.h
 *
 *  Created on: Jan 24, 2025
 *      Author: Celine
 */

#ifndef INC_MOTORS_INC_MOTORS_H_
#define INC_MOTORS_INC_MOTORS_H_

#include "main.h"
#include <stdbool.h>

//Struct for motors and its useful variables
typedef struct __Motor_Handler{

	//Timer for PWM counting
	TIM_HandleTypeDef* timer;

	//Output PWM channel
	uint32_t channel;

	//0-100% representing the duty cycle of the motor
	uint8_t duty;

	//GPIO port and pin for controlling the forward direction on the h-bridge (if any)
	GPIO_TypeDef* fwdPort;
	uint32_t fwdPin;

	//GPIO port and pin for controlling the reverse direction on the h-bridge (if any)
	GPIO_TypeDef* revPort;
	uint32_t revPin;

	//Tracks the direction of the motor
	bool isFwd;

	//Tracks whether the motor uses a Motor Driver
	bool usesMotorDriver;
}Motor;
//Start motor in a specified direction with certain speed (not used for brushes)
void startMotor(Motor* motor,bool isFwd, uint8_t duty);

//Start brushes
void startBrushes(Motor* Lmotor,Motor* Rmotor, uint8_t Lduty, uint8_t Rduty);

//Stop brushes
void stopBrushes(Motor* Lmotor, Motor* Rmotor, uint8_t brush_stationary_duty);

//Stop motor
void stopMotor(Motor* motor);

//Initialize motor
void initMotor(Motor* motor, TIM_HandleTypeDef* timer, uint32_t timerChannel, uint8_t initialDuty,
		GPIO_TypeDef* fwdPort, uint32_t fwdPin, GPIO_TypeDef* revPort, uint32_t revPin, bool isInitialFwd, bool is_Reversible);
//Change the speed (duty cycle) of the motor
void setMotorSpeed(Motor* motor, uint8_t duty);

//Reverses the direction of the motor
void reverseDirection(Motor* motor);

//Makes the motor go forward
void goForward(Motor* motor);

//Makes the motor reverse
void goBackward(Motor* motor);

#endif /* INC_MOTORS_INC_MOTORS_H_ */
