/*
 * joystick.h
 *
 *  Created on: Nov 24, 2022
 *      Author: kasperk
 */

#ifndef INC_JOYSTICK_H_
#define INC_JOYSTICK_H_

#include "spi.h"

void CS_START();
void CS_END();

typedef struct {
    int16_t ud;
    int16_t lr;
} Joystick_ud_lr;
void Joystick_Read(Joystick_ud_lr *ud_lr);
#endif /* INC_JOYSTICK_H_ */
