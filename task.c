/*
 * task.c
 *
 *  Created on: Nov 21, 2021
 *      Author: Duong
 */


#include<main.h>
#include<task.h>
void initLED(void){ // Off
	HAL_GPIO_WritePin(LED_PIN,LED1,1);
	HAL_GPIO_WritePin(LED_PIN,LED2,1);
	HAL_GPIO_WritePin(LED_PIN,LED3,1);
	HAL_GPIO_WritePin(LED_PIN,LED4,1);
}
void task1(void){
	HAL_GPIO_TogglePin(LED_PIN,LED1);
}

void task2(void){
	HAL_GPIO_TogglePin(LED_PIN,LED2);
}

void task3(void){
	HAL_GPIO_TogglePin(LED_PIN,LED3);
}

void task4(void){
	HAL_GPIO_TogglePin(LED_PIN, LED4);
}
