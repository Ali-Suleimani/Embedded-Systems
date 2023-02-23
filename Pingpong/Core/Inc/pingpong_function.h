/*
 * pingpong_function.h
 *
 *  Created on: 9 nov. 2022
 *      Author: Ali suleimani
 */

#ifndef INC_PINGPONG_FUNCTION_H_
#define INC_PINGPONG_FUNCTION_H_

#include <stdint.h>
#include <stdbool.h>
void Led_on(uint8_t Lednr);
void Show_points(uint8_t L_points, uint8_t R_points);
bool L_hit(void);
bool R_hit(void);

#endif /* INC_PINGPONG_FUNCTION_H_ */
