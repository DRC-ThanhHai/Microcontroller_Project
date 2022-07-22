/*
 * Button.c
 *
 *  Created on: 14 thg 8, 2020
 *      Author: Thanh Hai
 */
#include "main.h"
#include "Button_Interface_DoAnVxl.h"
#include "GLCD_DoAnVxl.h"
#include "ds1307.h"
#include "stdio.h"
#include "string.h"
#include "DHT22_DoAnVXL.h"
#include "User_DoAnVXL_BASE_LIB.h"

DS1307_TIME User_DS_Time1;
uint16_t up ;
uint16_t mode = 0;
uint16_t down;
uint16_t next = 0;
uint16_t ok = 0;
uint16_t cancel = 0;
uint16_t count = 0;

struct User_Alarm_Time
{
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
}User_Alarm_Time;

int User_UP_MODE()
{
	if(Key_Press(Up_GPIO_Port,Up_Pin))
	{
		up++;
		HAL_Delay(500);
	}
	return up;
}

void User_MODE_MODE()
{
	if(Key_Press(MODE_GPIO_Port,MODE_Pin))
	{
		mode++;
		HAL_Delay(200);
	}
	if(mode==6) mode = 0;

}

int User_OK_MODE()
{
	if(Key_Press(OK_GPIO_Port,OK_Pin)) //ok
	{
		ok++;
		HAL_Delay(20);
		return 1;
	}
	else return 0;
}

void User_Next_MODE()
{
	if(Key_Press(Next_GPIO_Port,Next_Pin))
	{
		next++;
		HAL_Delay(500);
	}
	if(next==5) next = 0;
}

int User_Next_Btn()
{
	int count = 0;
	for(next=0;next<6;next++)
	{
		if(Key_Press(Next_GPIO_Port,Next_Pin)) count++;
		HAL_Delay(10);
	}
	if(count > 2)  return 1;
	else           return 0;
}

void User_Show_Default(I2C_HandleTypeDef *i2c,User_DHT22_Data *User_DHT22)
{

	User_DS_Time= DS1307_GetTime(&User_DS1307_Handle);
	sprintf(User_GLCD_DataBuffer,"Time:%02u:%02u:%02u",User_DS_Time.hour,User_DS_Time.minute,User_DS_Time.second);
	User_GLCD_ShowString(0, 0, User_GLCD_DataBuffer);
	sprintf(User_GLCD_DataBuffer,"Date:%02u/%02u/%02u",User_DS_Time.date,User_DS_Time.month,User_DS_Time.year);
	User_GLCD_ShowString(0, 1, User_GLCD_DataBuffer);
	User_CombineFunc_ReadDHT22_ShowOnGLCD(i2c,User_DHT22);
	while((User_DS_Time.hour == User_Alarm_Time.hour)&&(User_DS_Time.minute == User_Alarm_Time.minute)&&(User_DS_Time.second == 0))
	{
		HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, 1);
		HAL_Delay(100);
		HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, 0);
		HAL_Delay(1000);
		if(Key_Press(OK_GPIO_Port, OK_Pin))
		{
			HAL_Delay(20);
			HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, 0);
			break;
		}
	}
}

void User_Show_Time_Mode()
{
	User_DS_Time= DS1307_GetTime(&User_DS1307_Handle);
	strcpy(User_GLCD_DataBuffer,"Time: ");
	User_GLCD_ShowString(0, 0, User_GLCD_DataBuffer);
	sprintf(User_GLCD_DataBuffer,"%02u:%02u:%02u",User_DS_Time.hour,User_DS_Time.minute,User_DS_Time.second);
	User_GLCD_ShowString(0, 1, User_GLCD_DataBuffer);
	strcpy(User_GLCD_DataBuffer,"Date: ");
	User_GLCD_ShowString(0, 2, User_GLCD_DataBuffer);
	sprintf(User_GLCD_DataBuffer,"%02u/%02u/%02u",User_DS_Time.date,User_DS_Time.month,User_DS_Time.year);
	User_GLCD_ShowString(0, 3, User_GLCD_DataBuffer);
}

void User_Show_Temp_Humid_Mode(I2C_HandleTypeDef *i2c,User_DHT22_Data *User_DHT22)
{
	strcpy(User_GLCD_DataBuffer,"Temperature: ");
	User_GLCD_ShowString(0, 0, User_GLCD_DataBuffer);
	User_DHT22_GetData(i2c, User_DHT22); HAL_Delay(50);
	sprintf(User_GLCD_DataBuffer,"T = %.2fC",User_DHT22_GetTemperature(User_DHT22));
	User_GLCD_ShowString(0,1,User_GLCD_DataBuffer);
	strcpy(User_GLCD_DataBuffer,"Humid: ");
	User_GLCD_ShowString(0, 2, User_GLCD_DataBuffer);
	sprintf(User_GLCD_DataBuffer,"H = %.2f%%",User_DHT22_GetHumidity(User_DHT22));
	User_GLCD_ShowString(0,3,User_GLCD_DataBuffer);
}

void User_Set_Time_Mode()
{
	strcpy(User_GLCD_DataBuffer,"Set Time? ");
	User_GLCD_ShowString(0, 0, User_GLCD_DataBuffer);
	strcpy(User_GLCD_DataBuffer,"  YES (OK)");
	User_GLCD_ShowString(0, 1, User_GLCD_DataBuffer);
	strcpy(User_GLCD_DataBuffer,"  NO  (CANCEL)");
	User_GLCD_ShowString(0, 2, User_GLCD_DataBuffer);
	strcpy(User_GLCD_DataBuffer,"              ");
	User_GLCD_ShowString(0, 3, User_GLCD_DataBuffer);
}

void User_Set_Alarm_Mode()
{
	strcpy(User_GLCD_DataBuffer,"Set Alarm? ");
	User_GLCD_ShowString(0, 0, User_GLCD_DataBuffer);
	strcpy(User_GLCD_DataBuffer,"  YES (OK)");
	User_GLCD_ShowString(0, 1, User_GLCD_DataBuffer);
	strcpy(User_GLCD_DataBuffer,"  NO  (CANCEL)");
	User_GLCD_ShowString(0, 2, User_GLCD_DataBuffer);
	strcpy(User_GLCD_DataBuffer,"              ");
	User_GLCD_ShowString(0, 3, User_GLCD_DataBuffer);
}

void User_Show_Time_ESP_Mode(uint8_t *User_UART_RCV)
{
	strcpy(User_GLCD_DataBuffer,"Show Time ESP");
	User_GLCD_ShowString(0, 0, User_GLCD_DataBuffer);
	strcpy(User_GLCD_DataBuffer,"Cancel to ESC");
	User_GLCD_ShowString(0, 2, User_GLCD_DataBuffer);
	strcpy(User_GLCD_DataBuffer,"             ");
	User_GLCD_ShowString(0, 3, User_GLCD_DataBuffer);
	HAL_Delay(200);
	while(1)
	{
		User_CombineFunc_UARTReceiveData_ShowOnGLCD(0,1,16,(char*)User_GLCD_DataBuffer, User_UART_RCV);
		if(Key_Press(Cancel_GPIO_Port, Cancel_Pin))
		{
			HAL_Delay(20);
			break;
		}
	}
}
int User_Up_Btn(int up)
{
	if(Key_Press(Up_GPIO_Port, Up_Pin))
	{
		up++;
		HAL_Delay(300);
	}
	return up;
}

int User_Down_Btn(int down) // Down
{
	if(Key_Press(Down_GPIO_Port, Down_Pin))
	{
		down--;
		HAL_Delay(300);
	}
	return down;
}

void User_Set_Time()
{
	strcpy(User_GLCD_DataBuffer,"Set Time Mode ");
	User_GLCD_ShowString(0, 0, User_GLCD_DataBuffer);
	strcpy(User_GLCD_DataBuffer,"Use Up & Down");
	User_GLCD_ShowString(0, 1, User_GLCD_DataBuffer);

	HAL_Delay(200);

	User_Next_MODE();

	if(next == 0)
	{
		strcpy(User_GLCD_DataBuffer,"Hour?");
		User_GLCD_ShowString(0, 2, User_GLCD_DataBuffer);
		sprintf(User_GLCD_DataBuffer,"%02u",User_DS_Time.hour);
		User_GLCD_ShowString(0, 3, User_GLCD_DataBuffer);
		HAL_Delay(50);
		if(Key_Press(Up_GPIO_Port, Up_Pin))
		{
			User_DS_Time.hour = User_Up_Btn(User_DS_Time.hour);
			if(User_DS_Time.hour > 23) User_DS_Time.hour = 0;
		}
		if(Key_Press(Down_GPIO_Port, Down_Pin))
		{
			User_DS_Time.hour = User_Down_Btn(User_DS_Time.hour);
			if(User_DS_Time.hour == 255) User_DS_Time.hour = 24;
		}
//		DS1307_SetTime(&User_DS1307_Handle, User_DS_Time);
	}
	if(next == 1)
	{
		strcpy(User_GLCD_DataBuffer,"Minute?");
		User_GLCD_ShowString(0, 2, User_GLCD_DataBuffer);
		sprintf(User_GLCD_DataBuffer,"%02u",User_DS_Time.minute);
		User_GLCD_ShowString(0, 3, User_GLCD_DataBuffer);
		HAL_Delay(50);
		if(Key_Press(Up_GPIO_Port, Up_Pin))
		{
			User_DS_Time.minute = User_Up_Btn(User_DS_Time.minute);
			if(User_DS_Time.minute > 59) User_DS_Time.minute = 0;
		}
		if(Key_Press(Down_GPIO_Port, Down_Pin))
		{
			User_DS_Time.minute = User_Down_Btn(User_DS_Time.minute);
			if(User_DS_Time.minute == 255) User_DS_Time.minute = 60;
		}
	}
	if(next == 2)
	{
		strcpy(User_GLCD_DataBuffer,"Day?");
		User_GLCD_ShowString(0, 2, User_GLCD_DataBuffer);
		sprintf(User_GLCD_DataBuffer,"%02u",User_DS_Time.date);
		User_GLCD_ShowString(0, 3, User_GLCD_DataBuffer);
		HAL_Delay(50);
		if(Key_Press(Up_GPIO_Port, Up_Pin))
		{
			User_DS_Time.date = User_Up_Btn(User_DS_Time.date);
			if(User_DS_Time.date > 31) User_DS_Time.date = 0;
		}
		if(Key_Press(Down_GPIO_Port, Down_Pin))
		{
			User_DS_Time.date = User_Down_Btn(User_DS_Time.date);
			if(User_DS_Time.date == 255) User_DS_Time.date = 31;
		}
	}
	if(next == 3)
	{
		strcpy(User_GLCD_DataBuffer,"Month?");
		User_GLCD_ShowString(0, 2, User_GLCD_DataBuffer);
		sprintf(User_GLCD_DataBuffer,"%02u",User_DS_Time.month);
		User_GLCD_ShowString(0, 3, User_GLCD_DataBuffer);
		HAL_Delay(50);
		if(Key_Press(Up_GPIO_Port, Up_Pin))
		{
			User_DS_Time.month = User_Up_Btn(User_DS_Time.month);
			if(User_DS_Time.month > 12) User_DS_Time.month = 0;
		}
		if(Key_Press(Down_GPIO_Port, Down_Pin))
		{
			User_DS_Time.month = User_Down_Btn(User_DS_Time.month);
			if(User_DS_Time.month == 255) User_DS_Time.month = 12;
		}
	}
	if(next == 4)
	{
		strcpy(User_GLCD_DataBuffer,"Year?");
		User_GLCD_ShowString(0, 2, User_GLCD_DataBuffer);
		sprintf(User_GLCD_DataBuffer,"%02u",User_DS_Time.year);
		User_GLCD_ShowString(0, 3, User_GLCD_DataBuffer);
		HAL_Delay(50);
		if(Key_Press(Up_GPIO_Port, Up_Pin))
		{
			User_DS_Time.year = User_Up_Btn(User_DS_Time.year);
			if(User_DS_Time.year > 99) User_DS_Time.year = 0;
		}
		if(Key_Press(Down_GPIO_Port, Down_Pin))
		{
			User_DS_Time.year = User_Down_Btn(User_DS_Time.year);
			if(User_DS_Time.year < 0) User_DS_Time.year = 99;
		}
	}
	if (Key_Press(OK_GPIO_Port,OK_Pin))
	{
		HAL_Delay(100);
		DS1307_SetTime(&User_DS1307_Handle, User_DS_Time);
		mode = 0;
	}
}

void User_Set_Alarm()
{
	strcpy(User_GLCD_DataBuffer,"Set Alarm Mode ");
	User_GLCD_ShowString(0, 0, User_GLCD_DataBuffer);
	strcpy(User_GLCD_DataBuffer,"Input AlarmTime");
	User_GLCD_ShowString(0, 1, User_GLCD_DataBuffer);
	HAL_Delay(200);
	User_Next_MODE();
	if(next == 0)
	{
		strcpy(User_GLCD_DataBuffer,"Hour?");
		User_GLCD_ShowString(0, 2, User_GLCD_DataBuffer);
		sprintf(User_GLCD_DataBuffer,"%02u",User_Alarm_Time.hour);
		User_GLCD_ShowString(0, 3, User_GLCD_DataBuffer);
		HAL_Delay(50);
		if(Key_Press(Up_GPIO_Port, Up_Pin))
		{
			User_Alarm_Time.hour = User_Up_Btn(User_Alarm_Time.hour);
			if(User_Alarm_Time.hour > 24) User_Alarm_Time.hour = 0;
		}
		if(Key_Press(Down_GPIO_Port, Down_Pin))
		{
			User_Alarm_Time.hour = User_Down_Btn(User_Alarm_Time.hour);
			if(User_Alarm_Time.hour == 255) User_Alarm_Time.hour = 24;
		}
	}
	if(next == 1)
	{
		strcpy(User_GLCD_DataBuffer,"Minute?");
		User_GLCD_ShowString(0, 2, User_GLCD_DataBuffer);
		sprintf(User_GLCD_DataBuffer,"%02u",User_Alarm_Time.minute);
		User_GLCD_ShowString(0, 3, User_GLCD_DataBuffer);
		HAL_Delay(50);
		if(Key_Press(Up_GPIO_Port, Up_Pin))
		{
			User_Alarm_Time.minute = User_Up_Btn(User_Alarm_Time.minute);
			if(User_Alarm_Time.minute > 59) User_Alarm_Time.minute = 0;
		}
		if(Key_Press(Down_GPIO_Port, Down_Pin))
		{
			User_Alarm_Time.minute = User_Down_Btn(User_Alarm_Time.minute);
			if(User_Alarm_Time.minute == 255) User_Alarm_Time.minute = 60;
		}
	}
	if(next == 2)
	{
		strcpy(User_GLCD_DataBuffer,"Second?");
		User_GLCD_ShowString(0, 2, User_GLCD_DataBuffer);
		sprintf(User_GLCD_DataBuffer,"%02u",User_Alarm_Time.second);
		User_GLCD_ShowString(0, 3, User_GLCD_DataBuffer);
		HAL_Delay(200);
	}
	if(next == 3)
	{
		strcpy(User_GLCD_DataBuffer,"Set Alarm Mode ");
		User_GLCD_ShowString(0, 0, User_GLCD_DataBuffer);
		strcpy(User_GLCD_DataBuffer,"Press OK to set");
		User_GLCD_ShowString(0, 1, User_GLCD_DataBuffer);
		HAL_Delay(200);
	}
	if (Key_Press(OK_GPIO_Port,OK_Pin)) {HAL_Delay(100); mode = 0;}
	if(next > 3) next = 0;
}

void User_Mode(I2C_HandleTypeDef *i2c,User_DHT22_Data *User_DHT22,uint8_t *User_UART_RCV)
{

	if (mode == 0) User_Show_Default(i2c,User_DHT22);
	if (mode == 1) User_Show_Time_Mode();
	if (mode == 2) User_Show_Temp_Humid_Mode(i2c,User_DHT22);
	if (mode == 3)
	{
		User_Set_Time_Mode();
		if(Key_Press(OK_GPIO_Port, OK_Pin)) {HAL_Delay(100); mode = 7;}
		if(Key_Press(Cancel_GPIO_Port, Cancel_Pin)) mode = 4;
	}
	if (mode == 4)
	{
		User_Set_Alarm_Mode();
		if(Key_Press(OK_GPIO_Port, OK_Pin)) {HAL_Delay(100); mode = 8;}
		if(Key_Press(Cancel_GPIO_Port, Cancel_Pin)) mode = 5;
	}
	if (mode == 5) User_Show_Time_ESP_Mode((uint8_t *)User_UART_RCV);
	{
		if(Key_Press(Cancel_GPIO_Port, Cancel_Pin)) {HAL_Delay(100); mode = 0;}
	}
	if (mode == 7) User_Set_Time();
	if (mode == 8) User_Set_Alarm();

	//User_DS_Time= DS1307_GetTime(&User_DS1307_Handle);
	User_MODE_MODE();
}

void User_Test_Button()
{
	User_GLCD_ShowString(0, 2, "TEST BUTTON");
	HAL_Delay(200);
	if(Key_Press(Up_GPIO_Port,Up_Pin))
	{
		User_GLCD_ShowString(0, 0, "UP");
	}
	if(Key_Press(Down_GPIO_Port,Down_Pin))
	{
		User_GLCD_ShowString(0, 0, "DOWN");
	}
	if(Key_Press(Next_GPIO_Port,Next_Pin))
	{
		User_GLCD_ShowString(0, 0, "NEXT");
	}
	if(Key_Press(MODE_GPIO_Port,MODE_Pin))
	{
		User_GLCD_ShowString(0, 0, "MODE");
	}
	if(Key_Press(OK_GPIO_Port,OK_Pin))
	{
		User_GLCD_ShowString(0, 0, "OK");
	}
	if(Key_Press(Cancel_GPIO_Port,Cancel_Pin))
	{
		User_GLCD_ShowString(0, 0, "CANCEL");
	}
}
