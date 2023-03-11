/*
 * joystick.c
 *
 *  Created on: Nov 24, 2022
 *      Author: kasperk
 */


#include "joystick.h"
#include "gpio.h"

void CS_START(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}

void CS_END(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
}

void Joystick_Read(Joystick_ud_lr *ud_lr){
    //Up down
	uint8_t pTxData[2] = {0b00011000, 0};
    uint8_t pRxData[2] = {0, 0};

    CS_START();
    HAL_SPI_TransmitReceive(&hspi4, pTxData, pRxData, 2, HAL_MAX_DELAY);
    CS_END();

    ud_lr->lr = (pRxData[0] << 8) | (pRxData[1]);

    pTxData[0] = 0b00100000;
    CS_START();
    HAL_SPI_TransmitReceive(&hspi4, pTxData, pRxData, 2, HAL_MAX_DELAY);
    CS_END();


    ud_lr->ud = (pRxData[0] << 8) | (pRxData[1]);



}
