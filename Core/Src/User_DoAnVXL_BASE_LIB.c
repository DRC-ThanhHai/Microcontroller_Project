/*
 * User_DoAnVXL.c
 *
 *  Created on: Jul 25, 2020
 *      Author: KHOA
 */

#include "User_DoAnVXL_BASE_LIB.h"
#include <string.h>

void User_ClearArrayBuffer(char* Buffer)
{
	for(uint8_t i=0;i<16;i++)
	{
		Buffer[i]=0;
	}
}
void User_CombineFunc_ReadDHT22_ShowOnGLCD(I2C_HandleTypeDef *i2c,User_DHT22_Data *User_DHT22)
{
	User_DHT22_GetData(i2c, User_DHT22); HAL_Delay(50);
	User_GLCD_GotoXY(0, 2);
	sprintf(User_GLCD_DataBuffer,"Temp  = %.2fC",User_DHT22_GetTemperature(User_DHT22));
	User_GLCD_ShowStringNoXY(User_GLCD_DataBuffer);
	User_GLCD_GotoXY(0, 3);
	sprintf(User_GLCD_DataBuffer,"Humid = %.2f%%",User_DHT22_GetHumidity(User_DHT22));
		User_GLCD_ShowStringNoXY(User_GLCD_DataBuffer);
	HAL_Delay(1); // delay to avoid get fail data
}

void User_CombineFunc_UARTReceiveData_ShowOnGLCD(uint8_t x,uint8_t y, uint8_t User_NumOfUARTBuffer,char * User_GLCD_Buffer,char * User_UARTBuffer)
{
	for(uint8_t i=0;i< User_NumOfUARTBuffer;i++)
	{
		if(User_UARTBuffer[i]== '~')
		{
			User_UARTBuffer[i]= 0;
			strcpy(User_GLCD_Buffer,User_UARTBuffer);
			for(uint8_t k=0;k<i;k++)
			{
				*(User_UARTBuffer+i)=0;
			}
			break;
		}

		User_GLCD_ShowString(0, 1, User_GLCD_Buffer);
	}


}
