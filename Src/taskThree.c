/**
 * ******************************************************************************
 @brief project program statemachine for project taskthree.c
 @file taskThree.c
 @author Ali Suleimani
 @version 1.0
 @date 16 December-2022
 @brief Functions and structures for program
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
@brief extern uint8_t, turn one of the pedestrian2 on

@param, number to the Led that is turned on
        can be 1-8, all other values turns all turn on the leds for TcpTransmit

@return nothing
*/
extern uint8_t array [3];
extern uint8_t i;
extern uint8_t Green_Led_Car;
extern uint8_t Orange_Led_Car;
extern uint8_t Red_Led_Car;
extern uint8_t Green_Led_Pedes;
extern uint8_t Red_Led_Pedes;
extern uint8_t Blue_Led_pedes;

/// extra leds that are needed for Task2
extern uint8_t Green_Led_Car4;
extern uint8_t Orange_Led_Car4;
extern uint8_t Red_Led_Car4;

extern uint8_t Green_Led_Car2;
extern uint8_t Red_Led_Car2;
extern uint8_t Orange_Led_Car2;
/// pedestrian 2
extern uint8_t Blue_Led_Pedes2;
extern uint8_t Green_Led_Pedes2;
extern uint8_t Red_Led_Pedes2;

/**
@brief void Task3TraficCar(void), turn one of the task3TraficCar on

@param, number to the Led that is turned on
        can be 1-8, all other values turns all turn on the leds for task3TraficCar

@return nothing
*/
 void Task3TraficCar(void){
	while(1){
		   // Turn on the green in one direction and red in another direction
         array [0] = Green_Led_Car | Red_Led_Car4;
		 array [1] = Red_Led_Car2;
		 array [2] = Green_Led_Car;
		 TcpTransmit();
		 HAL_Delay (400);

		   // turn on the orange leds for both direction
		 array [0] = Orange_Led_Car | Orange_Led_Car4;
		 array [1] = Orange_Led_Car2;
		 array [2] = Orange_Led_Car;
		 TcpTransmit();
		 HAL_Delay (400);

		    // turn on red leds in one direction and green in other direction. opposite of the first one
		 array [0] = Red_Led_Car | Green_Led_Car4;
		 array [1] = Green_Led_Car2;
		 array [2] = Red_Led_Car;
		 TcpTransmit();
		 HAL_Delay (400);

		   // turn on the orange leds for all direction
		 array [0] = Orange_Led_Car | Orange_Led_Car4;
		 array [1] = Orange_Led_Car2;
		 array [2] = Orange_Led_Car;
		 TcpTransmit();
		 HAL_Delay (400);

		 // if someone push the botton to pass the upper pedestrian
		if (HAL_GPIO_ReadPin(Pl1_Switch_GPIO_Port, Pl1_Switch_Pin) == 0){
			 TestPedestrian();
			}
		// if someone push the botton to pass the lower pedestrian
		if (HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == 0){
			TestPedestrian2();
			}
		   // car3 comes
		 while (HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin) == 0){
			 array [0] = Green_Led_Car|Red_Led_Car4;
			 array [1] = Red_Led_Car2|Green_Led_Pedes2;
			 array [2] = Green_Led_Car|Red_Led_Pedes;
			TcpTransmit();
			HAL_Delay (400);

			// car 3 is coming and someone press the button for the pedestrian
			if (HAL_GPIO_ReadPin(Pl1_Switch_GPIO_Port, Pl1_Switch_Pin) == 0){
				 TestPedestrian();
				}

			 /// this if statement is if car 3 is in the road and car 2 comes, it should turn to orange before
			 // turns to green to let car 2 pass
			 if (HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin)== 0){
				 array [0] = Orange_Led_Car|Orange_Led_Car4;
				 array [1] = Orange_Led_Car2;
				 array [2] = Orange_Led_Car;
				 TcpTransmit();
				 HAL_Delay(400);
			 }
               //the LED must go to orange after before it goes gos to green
			 if (HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin)== 0){
				 array [0] = Orange_Led_Car|Orange_Led_Car4;
				 array [1] = Orange_Led_Car2;
				 array [2] = Orange_Led_Car;
				 TcpTransmit();
				 HAL_Delay (400);
			 }

			 // If car 4 comes after car3 it should be green for car 4
			 while (HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin) == 0){
					 array [0] = Red_Led_Car|Green_Led_Car4;
					 array [1] = Green_Led_Car2|Red_Led_Pedes2;
					 array [2] = Red_Led_Car|Green_Led_Pedes;
					 TcpTransmit();
					 redDelayMax();

					 if (HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == 0){
								 TestPedestrian2();
								}

					 if (HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin)== 1){
						 array [0] = Orange_Led_Car|Orange_Led_Car4;
						 array [1] = Orange_Led_Car2;
						 array [2] = Orange_Led_Car;
						TcpTransmit();
						HAL_Delay (400);
					 }

					 //*** if car3 comes, car 4 comes then car 1 comes, it should be green for car1
					 if(HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin)==0){
						 array [0] = Orange_Led_Car|Orange_Led_Car4;
						 array [1] = Orange_Led_Car2;
						 array [2] = Orange_Led_Car;
						 TcpTransmit();
						 redDelayMax();
					 }
					 while (HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin) == 0){

						 array [0] = Green_Led_Car|Red_Led_Car4;
						 array [1] = Red_Led_Car2|Green_Led_Pedes2;
						 array [2] = Green_Led_Car|Red_Led_Pedes;
						 TcpTransmit();
						 redDelayMax();
						 if(HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin) == 1){
							 array [0] = Orange_Led_Car|Orange_Led_Car4;
							 array [1] = Orange_Led_Car2;
							 array [2] = Orange_Led_Car;
							 TcpTransmit();
							 redDelayMax();
						 }
					 }
				}

			 while (HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin) == 0){
				 array [0] = Red_Led_Car|Green_Led_Car4;
				 array [1] = Green_Led_Car2|Red_Led_Pedes2;
				 array [2] = Red_Led_Car|Green_Led_Pedes;
				TcpTransmit();
				redDelayMax();

				 if (HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == 0){
					 TestPedestrian2();
					}

				 // this if statement is if there is no car 2 after a while it has been
				 // and we want to go back to car3 it should turn on the orange led before red
				 if (HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin)== 1){
					 array [0] = Orange_Led_Car|Orange_Led_Car4;
					 array [1] = Orange_Led_Car2;
					 array [2] = Orange_Led_Car;
					TcpTransmit();
					HAL_Delay (400);
				 }
			 }
		 }

		     // car comes from the other direction
		 while (HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin) == 0){
			 array [0] = Red_Led_Car|Green_Led_Car4;
			 array [1] = Green_Led_Car2|Red_Led_Pedes2;
			 array [2] = Red_Led_Car|Green_Led_Pedes;
			 TcpTransmit();
			 redDelayMax();

			 // if car2 is running and someone press the button for for pedestrian 2
		 if (HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == 0){
				TestPedestrian2();
			}

			 if (HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin)== 0){
				 array [0] = Orange_Led_Car|Orange_Led_Car4;
				 array [1] = Orange_Led_Car2;
				 array [2] = Orange_Led_Car;
				 TcpTransmit();
				 HAL_Delay (400);
			 }

			 // here we check for car 1 and car , if car 2 is on and car 1 is coming it should switch to car 1
			   if (HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin)== 0){
					 array [0] = Orange_Led_Car|Orange_Led_Car4;
					 array [1] = Orange_Led_Car2;
					 array [2] = Orange_Led_Car;
					 TcpTransmit();
					 HAL_Delay (400);
				 }
				while (HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin) == 0){
					 array [0] = Green_Led_Car|Red_Led_Car4;
					 array [1] = Red_Led_Car2|Green_Led_Pedes2;
					 array [2] = Green_Led_Car|Red_Led_Pedes;
					 TcpTransmit();
					 redDelayMax();

					 if (HAL_GPIO_ReadPin(Pl1_Switch_GPIO_Port, Pl1_Switch_Pin) == 0){
						 TestPedestrian();
						}

					 if (HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin)== 1){
						 array [0] = Orange_Led_Car|Orange_Led_Car4;
						 array [1] = Orange_Led_Car2;
						 array [2] = Orange_Led_Car;
						TcpTransmit();
						HAL_Delay (400);
					 }
				}

			 while (HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin) == 0){
				 array [0] = Green_Led_Car|Red_Led_Car4;
				 array [1] = Red_Led_Car2|Green_Led_Pedes2;
				 array [2] = Green_Led_Car|Red_Led_Pedes;
				 TcpTransmit();
				 redDelayMax();
				 if (HAL_GPIO_ReadPin(Pl1_Switch_GPIO_Port, Pl1_Switch_Pin) == 0){
					 TestPedestrian();
					}

				 if (HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin)== 1){
					 array [0] = Orange_Led_Car|Orange_Led_Car4;
					 array [1] = Orange_Led_Car2;
					 array [2] = Orange_Led_Car;
					TcpTransmit();
					HAL_Delay (400);
				 }

				  // *** car2 comes, car3 comes then car 4 comes, it should be green for car 4
				 if(HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin)==0){
					 array [0] = Orange_Led_Car|Orange_Led_Car4;
					 array [1] = Orange_Led_Car2;
					 array [2] = Orange_Led_Car;
					 TcpTransmit();
					 redDelayMax();
				 }
				 while (HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin) == 0){
					 array [0] = Red_Led_Car|Green_Led_Car4;
					 array [1] = Green_Led_Car2|Red_Led_Pedes2;
					 array [2] = Red_Led_Car|Green_Led_Pedes;
					 TcpTransmit();
					 redDelayMax();
					 if(HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin) == 1){
						 array [0] = Orange_Led_Car|Orange_Led_Car4;
						 array [1] = Orange_Led_Car2;
						 array [2] = Orange_Led_Car;
						 TcpTransmit();
						 redDelayMax();
					 }
				 }
			 }
		 }

	     // car comes from the opposite direction as above
		 while (HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin) == 0){
			 array [0] = Green_Led_Car|Red_Led_Car4;
			 array [1] = Red_Led_Car2|Green_Led_Pedes2;
			 array [2] = Green_Led_Car|Red_Led_Pedes;
			 TcpTransmit();
			 redDelayMax();

			 // if car 1 is comming and someone press the button for pedestrian
			 if (HAL_GPIO_ReadPin(Pl1_Switch_GPIO_Port, Pl1_Switch_Pin) == 0){
				 TestPedestrian();
				}
			 if (HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin)== 0){
				 array [0] = Orange_Led_Car|Orange_Led_Car4;
				 array [1] = Orange_Led_Car2;
				 array [2] = Orange_Led_Car;
				 TcpTransmit();
				 HAL_Delay (400);
			 }

		 while (HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin) == 0){
			 array [0] = Red_Led_Car|Green_Led_Car4;
			 array [1] = Green_Led_Car2|Red_Led_Pedes2;
			 array [2] = Red_Led_Car|Green_Led_Pedes;
			 TcpTransmit();
			 redDelayMax();
			 if (HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == 0){
				 TestPedestrian2();
			}
			 if (HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin)== 1){
				 array [0] = Orange_Led_Car|Orange_Led_Car4;
				 array [1] = Orange_Led_Car2;
				 array [2] = Orange_Led_Car;
				 TcpTransmit();
				 HAL_Delay (400);
			 }
			 //*** if car1 comes then car 4 and when car 3 comes it should be green for car3
			 if(HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin)==0){
				 array [0] = Orange_Led_Car|Orange_Led_Car4;
				 array [1] = Orange_Led_Car2;
				 array [2] = Orange_Led_Car;
				 TcpTransmit();
				 redDelayMax();
			 }
			 while (HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin) == 0){
				 array [0] = Green_Led_Car|Red_Led_Car4;
				 array [1] = Red_Led_Car2|Green_Led_Pedes2;
				 array [2] = Green_Led_Car|Red_Led_Pedes;
				 TcpTransmit();
				 redDelayMax();

				 if(HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin) == 1){
					 array [0] = Orange_Led_Car|Orange_Led_Car4;
					 array [1] = Orange_Led_Car2;
					 array [2] = Orange_Led_Car;
					 TcpTransmit();
					 redDelayMax();
				 }
			 }
		 }
		 // car 1 is on and car 2 is coming

		 if (HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin)== 0){
			 array [0] = Orange_Led_Car|Orange_Led_Car4;
			 array [1] = Orange_Led_Car2;
			 array [2] = Orange_Led_Car;
			TcpTransmit();
			HAL_Delay (400);
		 }

		 while (HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin) == 0){
				 array [0] = Red_Led_Car|Green_Led_Car4;
				 array [1] = Green_Led_Car2|Red_Led_Pedes2;
				 array [2] = Red_Led_Car|Green_Led_Pedes;
				 TcpTransmit();
				 redDelayMax();

				 if (HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == 0){
					 TestPedestrian2();
					}

			 if (HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin)== 1){
				 array [0] = Orange_Led_Car|Orange_Led_Car4;
				 array [1] = Orange_Led_Car2;
				 array [2] = Orange_Led_Car;
				 TcpTransmit();
				 HAL_Delay (400);
			 }
			  //**** if car1 comes then car 2 and then car3, it should be green for car3
			 if(HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin)==0){
				 array [0] = Orange_Led_Car|Orange_Led_Car4;
				 array [1] = Orange_Led_Car2;
				 array [2] = Orange_Led_Car;
				 TcpTransmit();
				 redDelayMax();
			 }
			 while (HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin) == 0){
				 array [0] = Green_Led_Car|Red_Led_Car4;
				 array [1] = Red_Led_Car2|Green_Led_Pedes2;
				 array [2] = Green_Led_Car|Red_Led_Pedes;
				 TcpTransmit();
				 redDelayMax();

				 if(HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin) == 1){
					 array [0] = Orange_Led_Car|Orange_Led_Car4;
					 array [1] = Orange_Led_Car2;
					 array [2] = Orange_Led_Car;
					 TcpTransmit();
					 redDelayMax();
				 }
			 }
		   }
		}
             // condition for car 4
		 while (HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin) == 0){
			 array [0] = Red_Led_Car|Green_Led_Car4;
			 array [1] = Green_Led_Car2|Red_Led_Pedes2;
			 array [2] = Red_Led_Car|Green_Led_Pedes;
			 TcpTransmit();
			 redDelayMax();
			 // if car4 is running and someone press the button for for pedestrian 2
			 if (HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == 0){
						 TestPedestrian2();
					}

			 if (HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin)== 0){
				 array [0] = Orange_Led_Car|Orange_Led_Car4;
				 array [1] = Orange_Led_Car2;
				 array [2] = Orange_Led_Car;
				TcpTransmit();
				HAL_Delay (400);
			 }
			// Here we check if car4 is on and car3 comes it should should switch green to let cars pass
				 if (HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin)== 0){
					 array [0] = Orange_Led_Car|Orange_Led_Car4;
					 array [1] = Orange_Led_Car2;
					 array [2] = Orange_Led_Car;
					TcpTransmit();
					HAL_Delay (400);
				 }
				while (HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin) == 0){
					 array [0] = Green_Led_Car|Red_Led_Car4;
					 array [1] = Red_Led_Car2|Green_Led_Pedes2;
					 array [2] = Green_Led_Car|Red_Led_Pedes;
					TcpTransmit();
					redDelayMax();
					 if (HAL_GPIO_ReadPin(Pl1_Switch_GPIO_Port, Pl1_Switch_Pin) == 0){
						 TestPedestrian();
						}
					 if (HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin)== 1){
						 array [0] = Orange_Led_Car|Orange_Led_Car4;
						 array [1] = Orange_Led_Car2;
						 array [2] = Orange_Led_Car;
						TcpTransmit();
						HAL_Delay (400);
					 }
				}
               // here we check the condition when car1 is on drive
			 while (HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin) == 0){
				array [0] = Green_Led_Car|Red_Led_Car4;
				array [1] = Red_Led_Car2|Green_Led_Pedes2;
				array [2] = Green_Led_Car|Red_Led_Pedes;
				TcpTransmit();
				redDelayMax();
				 if (HAL_GPIO_ReadPin(Pl1_Switch_GPIO_Port, Pl1_Switch_Pin) == 0){
					 TestPedestrian();
					}

				 if (HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin)== 1){
					 array [0] = Orange_Led_Car|Orange_Led_Car4;
					 array [1] = Orange_Led_Car2;
					 array [2] = Orange_Led_Car;
					TcpTransmit();
					HAL_Delay (400);
				 }

				 //*** car4 comes, car1 comes then car2 comes, it should be green for car2
				 if(HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin)==0){
					 array [0] = Orange_Led_Car|Orange_Led_Car4;
					 array [1] = Orange_Led_Car2;
					 array [2] = Orange_Led_Car;
					 TcpTransmit();
					 redDelayMax();
				 }
				 while (HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin) == 0){
					 array [0] = Red_Led_Car|Green_Led_Car4;
					 array [1] = Green_Led_Car2|Red_Led_Pedes;
					 array [2] = Red_Led_Car|Green_Led_Pedes;
					 TcpTransmit();
					 redDelayMax();

					 if(HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin) == 1){
						 array [0] = Orange_Led_Car|Orange_Led_Car4;
						 array [1] = Orange_Led_Car2;
						 array [2] = Orange_Led_Car;
						 TcpTransmit();
						 redDelayMax();
					 }
				 }
			 }
		 }
     }
}

