/*
 * DHT22_DoAnVXL.c
 *
 *  Created on: Jul 25, 2020
 *      Author: KHOA
 */
#include "DHT22_DoAnVXL.h"
#include "main.h"
void User_DHT22_Write(I2C_HandleTypeDef *hi2c, uint16_t DHT22_command)
{
	uint8_t CommandWrite[2]={0};
	CommandWrite[0] = DHT22_command >> 8;
	CommandWrite[1] = DHT22_command;
	HAL_I2C_Master_Transmit(hi2c, DHT22_Address, CommandWrite, 2, HAL_MAX_DELAY);
}
void User_DHT22_GetData(I2C_HandleTypeDef *hi2c,User_DHT22_Data *User_DHT22)
{
	uint8_t DHT22_I2CDataBufferReceived[6]={0};
	uint16_t Buffer=0;
	User_DHT22_Write(hi2c,DHT22_WakeUp);
	HAL_Delay(100);
	User_DHT22_Write(hi2c,DHT22_Measure);
	HAL_I2C_Master_Receive(hi2c,DHT22_Address +1,DHT22_I2CDataBufferReceived,6,HAL_MAX_DELAY);
	User_DHT22_Write(hi2c,DHT22_Sleep);
	Buffer=DHT22_I2CDataBufferReceived[3];
	Buffer<<=8;
	Buffer+=DHT22_I2CDataBufferReceived[4];
	User_DHT22->User_DHT22_Temperature = -45 + 175 * ((float)Buffer/(float)65536);
	Buffer=DHT22_I2CDataBufferReceived[0];
	Buffer<<=8;
	Buffer+=DHT22_I2CDataBufferReceived[1];
	User_DHT22->User_DHT22_Humidity = 100 * ((float)Buffer/(float)65536);
	for(uint8_t i=0;i<6;i++)
	{
		DHT22_I2CDataBufferReceived[i]=0;
	}
}
float User_DHT22_GetTemperature(User_DHT22_Data *User_DHT22)
{
  return User_DHT22->User_DHT22_Temperature;
}

float User_DHT22_GetHumidity(User_DHT22_Data *User_DHT22)
{
  return User_DHT22->User_DHT22_Humidity;
}

