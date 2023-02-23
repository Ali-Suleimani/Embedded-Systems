/**
 * ******************************************************************************
@brief	Test, tests for pingpong_program
@file	test.c
@author	Ali Suleimani
@version 1.0
@date 16-December-2022
@brief tests for the trafic light project
******************************************************************************
*/

#include <taskThree.h>
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/**
@brief test_function, turn one of the leds on

@param  void TestPedestrian(void),void  TestPedestrian2(void); void redDelayMax(void);
void Test_program(void), number to the Led that is turned on
       functions are of type void can be 1-8, all other values turns all leds off

@return void
*/
void TestPedestrian(void);
void  TestPedestrian2(void);
void redDelayMax(void);
/**
@brief test_program, turn one of the pingpong leds on

@param  void TestPedestrian(void),void  TestPedestrian2(void); void redDelayMax(void);
void Test_program(void), number to the Led that is turned on
       functions are of type void can be 1-8, all other values turns all leds off

@return void
*/
void Test_program(void)
{
	Task3TraficCar();
	TcpTransmit();
	TcpTransmitCrossWalk();
    TestPedestrian();
    TestPedestrian2();
    redDelayMax();
}

