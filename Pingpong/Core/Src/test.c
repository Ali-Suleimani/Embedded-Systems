/** ******************************************************************************
@brief	Test, tests for pingpong_program
@file	test.c
@author	Ali Suleimani
@version 1.0
@date 04-November-2021
@brief tests for program Pingpong
****************************************************************************** */


#include <stdint.h>
#include "pingpong_function.h"
#include "main.h"
#include "stdbool.h"

/**
@brief Test_program, call the functions Test_Led(),
					Test_Show_points() and  Test_buttons().
*/
void Test_program(void)
{
	Test_Led();
	Test_Show_points();
	Test_buttons();
}

/**
@brief Test_Led, turn on the pingpong leds
@param void
@return void
*/
void Test_Led(void)
{
	int8_t Lednr;
	// Loop checking that alll leds can be turned on
	for (Lednr = 1; Lednr <= 8; Lednr++)
	{
		Led_on(Lednr);
		HAL_Delay(500);
	}

	Led_on(9); //Turn off led 8
	HAL_Delay(1000);
	return;
}

/**
@brief Test_Show_points, to show the scores
@return void
*/
void Test_Show_points()
{
	Show_points(2,3);
	return;
}

/**
@brief Test_buttons, to check the bottons
@param void
@return void
*/
void Test_buttons(void)
{
	int8_t j;
	/* Checking buttons */
	j=4;
	Led_on(j); // Light on

	while (j<9 && j>0)
	{
		if ( L_hit() == true ) // Wait for left button hit
		{
			j++; // next led to the right
			Led_on(j); // Light on
			HAL_Delay(100); // 100 ms
			while ( L_hit() == true ); // Wait for button release
			HAL_Delay(100); // 100 ms
		}

		if ( R_hit() == true ) // Wait for right button hit
		{
			j--; // next led to the left
			Led_on(j); // Light on
			HAL_Delay(100); // 100 ms
			while ( R_hit() == true ); // Wait for button release
			HAL_Delay(100); // 100 ms
			if (j<1) j=0; // Start again from left
		}

	}
return;
}
