/**
 * * ******************************************************************************
 @brief description of this file. This file contains the functions which are needed for the task 3
 @file def_function.c
 @author Ali Suleimani
 @version 1.0
 @date 16-december-2022
 @brief Functions and structures for program project
 ****************************************************************************** */
/* Includes ------------------------------------------------------------------
 */

#include <taskThree.h>
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "def_function.h"

 /**
@brief definition of uint8_t array , turn on the leds on

@param uint8_t array,uint8_t i  , number to the Led that is turned on
       Lednr can be 1-8, all other values turns all leds on

@return nothing
*/
// definition of variable
uint8_t array [3] = {0b00000000, 0b00000000, 0b00000000};
uint8_t i;

uint8_t Green_Led_Car  = 0b00000100;  // index [0] and [2]
uint8_t Orange_Led_Car = 0b00000010;  // index [0] and [2]
uint8_t Red_Led_Car    = 0b00000001;  // index [2]
uint8_t Green_Led_Pedes = 0b00010000;  // index[2]
uint8_t Red_Led_Pedes  = 0b00001000;  // index [2]
uint8_t Blue_Led_pedes = 0b00100000;  // index [0]

// extra leds that are needed for Task2
uint8_t Green_Led_Car4  = 0b0100000;    // index [0]
uint8_t Orange_Led_Car4 = 0b0010000;   // index [0]
uint8_t Red_Led_Car4 = 0b0001000;   // index [0]

uint8_t Green_Led_Car2  = 0b00000100;    // index [1]
uint8_t Red_Led_Car2    = 0b00000001;      // index [1]
uint8_t Orange_Led_Car2 = 0b00000010;   // index [1]
/// pedestrian 2
uint8_t Blue_Led_Pedes2 = 0b00100000;   // index [1]
uint8_t Green_Led_Pedes2 = 0b00010000;  // index [1]
uint8_t Red_Led_Pedes2 = 0b00001000;    // index [1]

/**
@brief void TestPedestrian2(void), turn one of the pedestrian2 on

@param, number to the Led that is turned on
        can be 1-8, all other values turns all turn on the leds for pedestrian

@return nothing
*/
void TestPedestrian2(void){
	for(i = 1; i < 8; i++){
		array [2] = 0b0;
		array [0] = Green_Led_Car4;
		array [1] =  Blue_Led_Pedes2|Red_Led_Pedes2|Green_Led_Car2;
		TcpTransmit();
		HAL_Delay (400);
		// turn of the blue LED to make it toggle
		array [0] = Green_Led_Car4;
		array [1] = Red_Led_Pedes2|Green_Led_Car2;
		TcpTransmit();
		HAL_Delay (400);
	}
	// turn on the orange led for car before the waking delay;
	for(i = 1; i < 4; i++){
		 array [0] =Orange_Led_Car4;
		 array [1] = Orange_Led_Car2|Blue_Led_Pedes2|Red_Led_Pedes2;
		 TcpTransmit();
		 HAL_Delay (400);
		 // turn off the blue led to make it toggle
		 array [0] = Orange_Led_Car4;
		 array [1] = Red_Led_Pedes2|Orange_Led_Car2;
		 TcpTransmit();
		 HAL_Delay (400);
	}
		 // turn on the green led for pedestrian and red led for car for cross waking
		array [0] =Red_Led_Car4;
		array [1] = Green_Led_Pedes2|Red_Led_Car2;
		TcpTransmitCrossWalk();
		HAL_Delay (1500);

		array [0] =Orange_Led_Car;
		array [1] = Orange_Led_Car2|Red_Led_Pedes2;
		TcpTransmit();
		HAL_Delay (400);
}

/**
@brief void TestPedestrian(void), turn one of the pedestrian on

@param, number to the Led that is turned on
        can be 1-8, all other values turns all turn on the leds for pedestrian

@return nothing
*/
void TestPedestrian(void){
		for(i = 1; i < 8; i++){
			array [1] = 0b0;
			array [0] = Green_Led_Car;
			array [2] =  Blue_Led_pedes|Red_Led_Pedes|Green_Led_Car;
			TcpTransmit();
			HAL_Delay (400);
			// turn of the blue LED to make it toggle
			array [0] = Green_Led_Car;
			array [2] =  Red_Led_Pedes|Green_Led_Car;
			TcpTransmit();
			HAL_Delay (400);
		}
		// turn on the orange led for car before the waking delay;
		for(i = 1; i < 4; i++){
			 array [0] =Orange_Led_Car;
			 array [2] =  Blue_Led_pedes|Red_Led_Pedes|Orange_Led_Car;
			 TcpTransmit();
			 HAL_Delay (400);
			 // turn off the blue led to make it toggle
			 array [0] = Orange_Led_Car;
			 array [2] =  Red_Led_Pedes|Orange_Led_Car;
			 TcpTransmit();
			 HAL_Delay (400);
		}
			 // turn on the green led for pedestrian and red led for car for cross waking
			array [0] =Red_Led_Car;
			array [2] =  Green_Led_Pedes|Red_Led_Car;
			TcpTransmitCrossWalk();
			HAL_Delay (1500);

			array [0] =Orange_Led_Car;
			array [2] =  Red_Led_Pedes|Orange_Led_Car;
			TcpTransmit();
			HAL_Delay (400);
}
/**
@brief void TcpTransmit(void), turn one of the pedestrian2 on

@param, number to the Led that is turned on
        can be 1-8, all other values turns all turn on the leds for TcpTransmit

@return nothing
*/
void TcpTransmit(void){
	HAL_SPI_Transmit(&hspi3, array, 3, 1);  // is to send data to shift register
	HAL_GPIO_WritePin(STCP_GPIO_Port, STCP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(STCP_GPIO_Port, STCP_Pin, GPIO_PIN_RESET);
}
/**
@brief void TcpTransmitCrossWalk(void), turn one of the pedestrian2 on

@param, number to the Led that is turned on
        can be 1-8, all other values turns all turn on the leds for TcpTransmitCrossWalk

@return nothing
*/
void TcpTransmitCrossWalk(void){
	HAL_SPI_Transmit(&hspi3, array, 3, 1);
	 HAL_GPIO_WritePin(STCP_GPIO_Port, STCP_Pin, GPIO_PIN_SET);
	// HAL_Delay(1000);
	 HAL_GPIO_WritePin(STCP_GPIO_Port, STCP_Pin, GPIO_PIN_RESET);
	 //HAL_Delay(1000);
}
/**
@brief void redDelayMax(void), turn one of the redDelayMax on

@param, number to the Led that is turned on
        can be 1-8, all other values turns all turn on the leds for redDelayMax

@return nothing
*/

void redDelayMax(void){
	HAL_Delay(1000);
}

