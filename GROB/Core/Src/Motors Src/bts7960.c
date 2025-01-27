/*
 * bts7960.c
 *
 *  Created on: Jan 26, 2025
 *      Author: Celine
 */

#include "Motors Inc/bts7960.h"
#include "main.h"

extern TIM_HandleTypeDef htim4;


void startWinch(BTS7960* winch, bool crush, uint8_t duty){
	//Start base
	HAL_TIM_Base_Start(winch->timer);
	//Set enable pins or keep connected to 5V
	HAL_GPIO_WritePin(Winch_FWD_EN_GPIO_Port, Winch_FWD_EN_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(Winch_REV_EN_GPIO_Port, Winch_REV_EN_Pin,GPIO_PIN_SET);
	//set the initial motor direction
	if (crush){
			goForwardWinch(winch,duty);
			winch->toCrush = true;
		}
	else{
			goBackwardWinch(winch,duty);
			winch->toCrush = false;
		}
}


void stopWinch(BTS7960* winch){
	//Stop PWM generation
	HAL_TIM_PWM_Stop(winch->timer, winch->crush_pwm_channel);
	HAL_TIM_PWM_Stop(winch->timer, winch->uncrush_pwm_channel);
	HAL_TIM_Base_Stop(winch->timer);
	winch->crush_duty = 0;
	winch->uncrush_duty = 0;
	HAL_GPIO_WritePin(Winch_FWD_EN_GPIO_Port, Winch_FWD_EN_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Winch_REV_EN_GPIO_Port, Winch_REV_EN_Pin,GPIO_PIN_RESET);

}


//Initialize the motor driver for the winch and all its parameters
void initWinch(BTS7960* winch, TIM_HandleTypeDef* timer, uint32_t crushChannel, uint32_t uncrushChannel,uint8_t crushDuty,
		uint8_t uncrushDuty, GPIO_TypeDef* crushPort, uint32_t crushPin, GPIO_TypeDef* uncrushPort, uint32_t uncrushPin, bool isInitialFwd)
{
	//Initialize the core parameters and default values (direction, duty)
	winch->timer = timer;
	winch->crush_pwm_channel = crushChannel;
	winch->uncrush_pwm_channel = uncrushChannel;
	winch->crush_duty = crushDuty;
	winch->uncrush_duty = uncrushDuty;
	winch->crushPort = crushPort;
	winch->crushPin = crushPin;
	winch->uncrushPort = uncrushPort;
	winch->uncrushPin = uncrushPin;
	winch->toCrush = isInitialFwd;

}


//Makes the motor go forward
void goForwardWinch(BTS7960* winch,uint8_t duty){

	//Start PWM generation
	HAL_TIM_PWM_Start(winch->timer, winch->crush_pwm_channel);
	//Set speed
	winch->crush_duty = duty;
	__HAL_TIM_SET_COMPARE(winch->timer, winch->crush_pwm_channel, duty);
}

//Makes the motor reverse
void goBackwardWinch(BTS7960* winch,uint8_t duty){

	//Start PWM generation
	HAL_TIM_PWM_Start(winch->timer, winch->uncrush_pwm_channel);
	//Set speed
	winch->crush_duty = duty;
	__HAL_TIM_SET_COMPARE(winch->timer, winch->uncrush_pwm_channel, duty);

}

