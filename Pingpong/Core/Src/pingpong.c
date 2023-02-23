/** ******************************************************************************
 @brief Pingpong-program, Pingpong statemachine for Pingpong-program pingpong.c
 @file pingpong.c
 @author Ali Suleimani
 @version 1.0
 @date 11-November-2022
 @brief Functions and structures for program Pingpong
 ****************************************************************************** */
/* Includes ------------------------------------------------------------------*/

#include "pingpong.h"
#include "stdbool.h"
#include "pingpong_function.h"
//#include "gpio.h"
//#include <stdio.h>
#include <stdint.h>

/* Define states for state machine*/
typedef enum {
	Start, MoveRight, MoveLeft
} states;

static states State, NextState;

void pingpong(void) {
	bool ButtonPressed = false; // To remember that button is pressed
	bool L_player = false;
    bool R_player = false;
	uint32_t Varv, Speed; // Ball speed
	uint8_t Led; // LED nr

	State = Start; // Initiate State 1§to Start
	NextState = Start;

	uint8_t L_player_point = 0; // To show the score for left player
	uint8_t R_player_point = 0; // To show the score for right player
	/* Infinite loop */
	while (1) {
		State = NextState;
		switch (State) // State machine
		{
		case Start:
			Speed = 500000; // Number of loops
			Led_on(0); // Turn off all LEDs
			if (L_hit() == true  && L_player == false) {
				L_player = true;
				R_player = false;
				Led = 1;
				NextState = MoveRight;
				while (L_hit() == true)
					;
			}

			else if (R_hit() == true && R_player == false) {
				R_player = true;
				L_player = false;
				Led = 8;
				NextState = MoveLeft;
				while (R_hit() == true)
					;
			}

			else
				NextState = Start; // Stay
			break;

		case MoveRight: {
			Led_on(Led);
			Varv = Speed;

			while (Varv != 0) {
				if (R_hit())
					ButtonPressed = true;  // R hit
				Varv--;
			}

			if (ButtonPressed) // R pressed
			{
				if (Led == 8) //and LED8 activa
						{
					NextState = MoveLeft; // return ball
					Speed = Speed + 50000;
					Led = 7;
				} else {

					L_player_point++; // increase the score for left player
					Show_points(L_player_point, R_player_point); // To show the scores

					/* To reset all scores*/
					if (L_player_point == 4) {
						L_player_point = 0;
						R_player_point = 0;
					}

					NextState = Start; // hit to early
				}
			} else {
				if (Led == 9) //no hit or to late
						{
					L_player_point++; // increase the score for left player
					Show_points(L_player_point, R_player_point); // To show the scores

					/* To reset all scores*/
					if (L_player_point == 4) {
						L_player_point = 0;
						R_player_point = 0;
					}
					NextState = Start;
				} else {
					NextState = MoveRight; // ball continues to move right
				}
			}

			if (!ButtonPressed)
				Led++; // prepare to turn next LED on
			ButtonPressed = false;
		}
			break;

		case MoveLeft: {
			Led_on(Led);
			Varv = Speed;

			while (Varv != 0) {
				if (L_hit())
					ButtonPressed = true; // L hit
				Varv--;
			}

			if (ButtonPressed) // L pressed
			{
				if (Led == 1) //and LED1 active
						{
					NextState = MoveRight;
					Speed = Speed - 50000;
					Led = 2;
				} else {
					R_player_point++; // increase the score for right player
					Show_points(L_player_point, R_player_point); // To show the scores

					/* To reset all scores*/
					if (R_player_point == 4) {
						L_player_point = 0;
						R_player_point = 0;
					}
					NextState = Start; // hit to early
				}
			}

			else {
				if (Led == 0) //no hit or to late
						{
					R_player_point++; // increase the score for right player
					Show_points(L_player_point, R_player_point); // To show the scores

					/* To reset all scores*/
					if (R_player_point == 4) {
						L_player_point = 0;
						R_player_point = 0;
					}
					NextState = Start;
				} else
					NextState = MoveLeft; // ball continues to move left
			}

			if (!ButtonPressed)
				Led--; // prepare to turn next LED on
			ButtonPressed = false;
		}
			break;

		default:
			break;
		}
	}

} //End of function Pingpong
