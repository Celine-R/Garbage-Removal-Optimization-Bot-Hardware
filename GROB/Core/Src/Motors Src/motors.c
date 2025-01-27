/*
 * motors.c
 *
 *  Created on: Jan 24, 2025
 *      Author: Celine
 */

#include "Motors Inc/motors.h"
#include "main.h"

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2;


void startMotor(Motor* motor, bool isFwd, uint8_t duty){
	//set the initial motor direction (if winch or flipper)

	if (motor->usesMotorDriver){
		if (isFwd){
				goForward(motor);
				motor->isFwd = true;
			}
		else{
				goBackward(motor);
				motor->isFwd = false;
			}
	}

	//Start PWM generation
	HAL_TIM_Base_Start(motor->timer);
	HAL_TIM_PWM_Start(motor->timer, motor->channel);

	//set Motor speed
	setMotorSpeed(motor,duty);
}

//Start brushes
void startBrushes(Motor* Lmotor,Motor* Rmotor, uint8_t Lduty, uint8_t Rduty){
	//Start PWM generation
	HAL_TIM_Base_Start(Lmotor->timer);
	HAL_TIM_PWM_Start(Lmotor->timer, Lmotor->channel);
	HAL_TIM_PWM_Start(Rmotor->timer, Rmotor->channel);

	//set Motor speed
	setMotorSpeed(Lmotor,Lduty);
	setMotorSpeed(Rmotor,Rduty);
}

void stopMotor(Motor* motor){
	//Stop PWM generation
	HAL_TIM_PWM_Stop(motor->timer, motor->channel);
	HAL_TIM_Base_Stop(motor->timer);

}

void stopBrushes(Motor* Lmotor, Motor* Rmotor, uint8_t brush_stationary_duty){
	//Stop PWM generation
	HAL_TIM_PWM_Stop(Lmotor->timer, Lmotor->channel);
	HAL_TIM_PWM_Stop(Rmotor->timer, Rmotor->channel);
	HAL_TIM_Base_Stop(Lmotor->timer);

	Lmotor->duty = brush_stationary_duty;
	Rmotor->duty = brush_stationary_duty;
}


//Initialize the motor and all its parameters
void initMotor(Motor* motor, TIM_HandleTypeDef* timer, uint32_t timerChannel, uint8_t initialDuty,
		GPIO_TypeDef* fwdPort, uint32_t fwdPin, GPIO_TypeDef* revPort, uint32_t revPin, bool isInitialFwd, bool usesMotorDriver)
{
	//Initialize the core parameters and default values (direction, duty)
	motor->timer = timer;
	motor->channel = timerChannel;
	motor->duty = initialDuty;
	motor->fwdPort = fwdPort;
	motor->fwdPin = fwdPin;
	motor->revPort = revPort;
	motor->revPin = revPin;
	motor->isFwd = isInitialFwd;
	motor->usesMotorDriver= usesMotorDriver;

}
//Change the speed (duty cycle) of the motor
void setMotorSpeed(Motor* motor, uint8_t duty){
	motor->duty = duty;
	__HAL_TIM_SET_COMPARE(motor->timer, motor->channel, duty);
}

//Reverses the direction of the motor
void reverseDirection(Motor* motor){

	//switch directions based off our current direction
	if (motor->isFwd){
		goBackward(motor);
	}
	else {
		goForward(motor);
	}

}

//Makes the motor go forward
void goForward(Motor* motor){

	//Switch GPIO direction to forward
	HAL_GPIO_WritePin(motor->fwdPort, motor->fwdPin, 1);
	HAL_GPIO_WritePin(motor->revPort, motor->revPin, 0);

	//Track this in the bool
	motor->isFwd = true;
}

//Makes the motor reverse
void goBackward(Motor* motor){

	//Switch GPIO direction to reverse
	HAL_GPIO_WritePin(motor->revPort, motor->revPin, 1);
	HAL_GPIO_WritePin(motor->fwdPort, motor->fwdPin, 0);

	//Track this in the bool
	motor->isFwd = false;

}
