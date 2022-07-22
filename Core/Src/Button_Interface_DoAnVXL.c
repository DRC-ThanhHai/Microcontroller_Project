#include "main.h"
#include "Button_Interface_DoAnVxl.h"
//

int DL_BTN;
//uint8_t User_Button_countCancel = 0;
//uint8_t User_Button_countDown = 0;
//uint8_t User_Button_countUp = 0;
//uint8_t User_Button_countMode=0;
//uint8_t User_Button_countOK=0;

int User_Button_Up()
{
	if(HAL_GPIO_ReadPin(Up_GPIO_Port, Up_Pin)==0)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(Up_GPIO_Port, Up_Pin)==0)
		{
			return 1;

		}

	}
	else return 0;
}

int Key_Press(GPIO_TypeDef *GPIO_Port,uint16_t GPIO_Pin)
{
	if(!HAL_GPIO_ReadPin(GPIO_Port,GPIO_Pin))
	{
		DL_BTN++;
		if(DL_BTN==1) return 1;
		else
		{
			if(DL_BTN>=50) DL_BTN = 0;
		}
	}
	else return 0;
}


/*
void User_Button_Down()
{
	if(HAL_GPIO_ReadPin(Down_GPIO_Port, Down_Pin)==0)
		{
			HAL_Delay(20);
			if(HAL_GPIO_ReadPin(Down_GPIO_Port, Down_Pin)==0)
			{
				User_Button_countDown++;
				HAL_Delay(200);
			}
		}

}
void User_Button_Next()
{

	if(HAL_GPIO_ReadPin(Next_GPIO_Port, Next_Pin)==0)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(Next_GPIO_Port, Next_Pin)==0)
		{
			User_Button_countNext++;
			HAL_Delay(200);
		}
	}


}
void User_Button_Cancel()
{
	if(HAL_GPIO_ReadPin(Cancel_GPIO_Port, Cancel_Pin)==0)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(Cancel_GPIO_Port, Cancel_Pin)==0)
		{
			User_Button_countCancel++;
			HAL_Delay(200);
		}
	}

}
void User_Button_Mode()
{
	if(HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin)==0)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin)==0)
		{
			User_Button_countMode++;
			HAL_Delay(200);
		}
	}
}
void User_Button_OK()
{
	if(HAL_GPIO_ReadPin(OK_GPIO_Port, OK_Pin)==0)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(OK_GPIO_Port, OK_Pin)==0)
		{
			User_Button_countOK++;
			HAL_Delay(200);
		}
	}

}
*/
