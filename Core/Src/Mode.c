/*
 * Button.c
 *
 *  Created on: 14 thg 8, 2020
 *      Author: Thanh Hai
 */
#include "main.h"
#include "Button_Interface_DoAnVxl.h"
#include "GLCD_DoAnVxl.h"
int User_Button_countUp = 0;
uint16_t mode = 0;
uint16_t down = 0;
uint16_t next = 0;
uint16_t ok = 0;
uint16_t cancel = 0;
void User_UP_MODE()
{
	if(Key_Press(Up_Pin,20))
	{
		User_Button_countUp ++;
		HAL_Delay(500);
		sprintf(User_GLCD_DataBuffer,"U=%d",User_Button_countUp);
		User_GLCD_ShowString(0, 0, User_GLCD_DataBuffer);
	}
}

void User_DOWN_MODE()
{
	if(Key_Press(Down_Pin,20))
	{
		down ++;
		HAL_Delay(500);
		sprintf(User_GLCD_DataBuffer,"D=%d",down);
		User_GLCD_ShowString(3, 0, User_GLCD_DataBuffer);
	}
}

void User_MODE_MODE()
{
	if(Key_Press(MODE_Pin,20))
	{
		mode++;
		HAL_Delay(500);
		sprintf(User_GLCD_DataBuffer,"MODE=%d",mode);
		User_GLCD_ShowString(0, 1, User_GLCD_DataBuffer);
	}
}

void User_OK_MODE()
{
	if(Key_Press(OK_Pin,20))
	{
		ok++;
		HAL_Delay(500);
		sprintf(User_GLCD_DataBuffer,"OK=%d",ok);
		User_GLCD_ShowString(4, 1, User_GLCD_DataBuffer);
	}
}

void User_Next_MODE()
{
	if(Key_Press(Next_Pin,20))
	{
		next++;
		HAL_Delay(500);
		sprintf(User_GLCD_DataBuffer,"NEXT=%d",next);
		User_GLCD_ShowString(0, 2, User_GLCD_DataBuffer);
	}
}

void User_Cancel_MODE()
{
	if(Key_Press(Cancel_Pin,20))
	{
		ok++;
		HAL_Delay(500);
		sprintf(User_GLCD_DataBuffer,"C=%d",ok);
		User_GLCD_ShowString(4, 2, User_GLCD_DataBuffer);
	}
}

int User_Mode_Button()
{
	int count = 0;
	for(mode=0;mode<5;mode++)
	{
		if(Key_Press(MODE_Pin,20))
		{
			count ++;
			HAL_Delay(100);
		}
	}
	if (count>2) return 1;
	else return 0;
}

void User_Show_Default()
{

}
void User_Show_Time_Mode()
{
	strcpy(User_GLCD_DataBuffer,"Time: ");
	User_GLCD_ShowString(0, 0, User_GLCD_DataBuffer);
	strcpy(User_GLCD_DataBuffer,"Date: ");
	User_GLCD_ShowString(0, 2, User_GLCD_DataBuffer);
}

void User_Show_Temp_Humid_Mode()
{
	strcpy(User_GLCD_DataBuffer,"Temperature: ");
	User_GLCD_ShowString(0, 0, User_GLCD_DataBuffer);
	sprintf(User_GLCD_DataBuffer,"Humid: ");
	User_GLCD_ShowString(0, 2, User_GLCD_DataBuffer);
}

void User_Set_Time_Mode()
{
	strcpy(User_GLCD_DataBuffer,"Set Time? ");
	User_GLCD_ShowString(0, 0, User_GLCD_DataBuffer);
}

void User_Set_Allarm_Mode()
{
	strcpy(User_GLCD_DataBuffer,"Set Allarm? ");
	User_GLCD_ShowString(0, 0, User_GLCD_DataBuffer);
}

void User_Mode()
{
	if(User_Mode_Button())
	{
		if (mode == 0) User_Show_Default();
		if (mode == 1) User_Show_Time_Mode();
		if (mode == 2) User_Show_Temp_Humid_Mode();
		if (mode == 3) User_Set_Time_Mode();
		if (mode == 4) User_Set_Allarm_Mode();
	}
}

void User_Test_Button()
{
	User_GLCD_ShowString(0, 2, "TEST BUTTON");

	if(Key_Press(Up_Pin,20))
	{
		User_GLCD_ShowString(0, 0, "UP");
	}
	if(Key_Press(Down_Pin,20))
	{
		User_GLCD_ShowString(0, 0, "DOWN");
	}
	if(Key_Press(Next_Pin,20))
	{
		User_GLCD_ShowString(0, 0, "NEXT");
	}
	/*
	if(Key_Press(MODE_Pin,20))
	{
		User_GLCD_ShowString(0, 0, "MODE");
	}

	if(Key_Press(OK_Pin,20))
	{
		User_GLCD_ShowString(0, 0, "OK");
	}
	if(Key_Press(Cancel_Pin,20))
	{
		User_GLCD_ShowString(0, 0, "CANCEL");
	}
	*/

}
