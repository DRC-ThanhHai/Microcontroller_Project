/*
 * User_DoAnVXL.h
 *
 *  Created on: Jul 25, 2020
 *      Author: KHOA
 */

#ifndef USER_DOANVXL_BASE_LIB_H_
#define USER_DOANVXL_BASE_LIB_H_

#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "main.h"
#include "GLCD_DoAnVxl.h"
#include "DHT22_DoAnVXL.h"
#include "Button_Interface_DoAnVxl.h"
#include "Mode.h"

void User_ClearArrayBuffer(char* Buffer);
void User_CombineFunc_ReadDHT22_ShowOnGLCD();
void User_CombineFunc_UARTReceive_ShowOnGLCD( uint8_t x,uint8_t y, uint8_t User_NumOfUARTBuffer,char * User_GLCD_Buffer,char * User_UARTBuffer);
#endif /* USER_DOANVXL_BASE_LIB_H_ */
