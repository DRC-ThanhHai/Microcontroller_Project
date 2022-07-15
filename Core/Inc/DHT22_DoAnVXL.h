/*
 * DHT22_DoAnVXL.h
 *
 *  Created on: Jul 25, 2020
 *      Author: KHOA
 */

#ifndef DHT22_DOANVXL_H_
#define DHT22_DOANVXL_H_

#define DHT22_WakeUp    0x3517
#define DHT22_Measure   0x5c24
#define DHT22_Sleep     0xb098
#define DHT22_Address 	0xE0

#include "stm32f1xx_hal.h"
typedef struct User_DHT22_Data
{
   float User_DHT22_Temperature;
   float User_DHT22_Humidity;
}User_DHT22_Data;
void User_DHT22_Write(I2C_HandleTypeDef *hi2c, uint16_t DHT22_command);
void User_DHT22_GetData(I2C_HandleTypeDef *hi2c,User_DHT22_Data *User_DHT22);
float User_DHT22_GetTemperature(User_DHT22_Data *User_DHT22);
float User_DHT22_GetHumidity(User_DHT22_Data *User_DHT22);
#endif /* DHT22_DOANVXL_H_ */
