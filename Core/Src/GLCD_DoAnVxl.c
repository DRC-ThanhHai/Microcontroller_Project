#include "GLCD_DoAnVxl.h"
#include "stdio.h"
#include "main.h"
#include "string.h"
void User_GLCD_TestGLCDPin(uint8_t delay)
{
	HAL_GPIO_TogglePin(E_GPIO_Port, E_Pin);
	HAL_GPIO_TogglePin(RS_GPIO_Port, RS_Pin);
//	HAL_GPIO_TogglePin(RW_GPIO_Port, RW_Pin);
	HAL_GPIO_TogglePin(DB4_GPIO_Port, DB4_Pin);
	HAL_GPIO_TogglePin(DB5_GPIO_Port, DB5_Pin);
	HAL_GPIO_TogglePin(DB6_GPIO_Port, DB6_Pin);
	HAL_GPIO_TogglePin(DB7_GPIO_Port, DB7_Pin);
	HAL_Delay(delay);
}
void User_GLCD_GotoXY(uint8_t x,uint8_t y)
{
   switch(y)
   {
      case 0:
      User_GLCD_SendCommand(GLCD_Line0+x);
      break;
      case 1:
      User_GLCD_SendCommand(GLCD_Line1+x);
      break;
      case 2:
      User_GLCD_SendCommand(GLCD_Line2+x);
      break;
      case 3:
      User_GLCD_SendCommand(GLCD_Line3+x);
      break;
   }
}
void User_GLCD_ShowString(uint8_t x,uint8_t y,char *DataString)
{
   User_GLCD_GotoXY(x,y);
   uint8_t i=0;
      while(DataString[i] !=0) // NEU NOI DUNG CUA CHUOI KHAC NULL
      {
         User_GLCD_SendData(DataString[i]);
         i++;

      }
      while(i<16)
      {
          DataString[i]=' ';
         User_GLCD_SendData(DataString[i]);
         i++;
      }

}

void User_GLCD_SendCommand(uint8_t Command)
{
	HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,0);
	HAL_GPIO_WritePin(E_GPIO_Port,E_Pin,0);
	HAL_GPIO_WritePin(E_GPIO_Port,E_Pin,1);
	HAL_GPIO_WritePin(DB4_GPIO_Port,DB4_Pin,Command & 0x10);
	HAL_GPIO_WritePin(DB5_GPIO_Port,DB5_Pin,Command & 0x20);
	HAL_GPIO_WritePin(DB6_GPIO_Port,DB6_Pin,Command & 0x40);
	HAL_GPIO_WritePin(DB7_GPIO_Port,DB7_Pin,Command & 0x80);
	HAL_GPIO_WritePin(E_GPIO_Port,E_Pin,1);
	HAL_GPIO_WritePin(E_GPIO_Port,E_Pin,0);
	HAL_GPIO_WritePin(E_GPIO_Port,E_Pin,1);
	HAL_GPIO_WritePin(DB4_GPIO_Port,DB4_Pin,Command & 0x01);
	HAL_GPIO_WritePin(DB5_GPIO_Port,DB5_Pin,Command & 0x02);
	HAL_GPIO_WritePin(DB6_GPIO_Port,DB6_Pin,Command & 0x04);
	HAL_GPIO_WritePin(DB7_GPIO_Port,DB7_Pin,Command & 0x08);
	HAL_GPIO_WritePin(E_GPIO_Port,E_Pin,0);
	HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,1);

}
void User_GLCD_SendData(uint8_t Data)
{

	HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,1);
	HAL_GPIO_WritePin(E_GPIO_Port,E_Pin,0);
	HAL_GPIO_WritePin(E_GPIO_Port,E_Pin,1);
	HAL_GPIO_WritePin(DB4_GPIO_Port,DB4_Pin,Data & 0x10);
	HAL_GPIO_WritePin(DB5_GPIO_Port,DB5_Pin,Data & 0x20);
	HAL_GPIO_WritePin(DB6_GPIO_Port,DB6_Pin,Data & 0x40);
	HAL_GPIO_WritePin(DB7_GPIO_Port,DB7_Pin,Data & 0x80);
	HAL_GPIO_WritePin(E_GPIO_Port,E_Pin,1);
	HAL_GPIO_WritePin(E_GPIO_Port,E_Pin,0);
	HAL_GPIO_WritePin(E_GPIO_Port,E_Pin,1);
	HAL_GPIO_WritePin(DB4_GPIO_Port,DB4_Pin,Data & 0x01);
	HAL_GPIO_WritePin(DB5_GPIO_Port,DB5_Pin,Data & 0x02);
	HAL_GPIO_WritePin(DB6_GPIO_Port,DB6_Pin,Data & 0x04);
	HAL_GPIO_WritePin(DB7_GPIO_Port,DB7_Pin,Data & 0x08);
	HAL_GPIO_WritePin(E_GPIO_Port,E_Pin,0);
	HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,0);
}
void User_GLCD_ShowStringNoXY(char *DataString)
{
   uint8_t i=0;
      while(DataString[i] !=0) // NEU NOI DUNG CUA CHUOI KHAC NULL
      {
         User_GLCD_SendData(DataString[i]);
         i++;
      }
      while(i<16)
      {
          DataString[i]=' ';
         User_GLCD_SendData(DataString[i]);
         i++;
      }

}
void User_GLCD_Init()
{
	User_GLCD_SendCommand(GLCD_Basic4Bit);
	User_GLCD_SendCommand(GLCD_DisplayOn);
	User_GLCD_SendCommand(GLCD_Clear);
	HAL_Delay(20);
	User_GLCD_SendCommand(GLCD_Entry);
	HAL_Delay(100);
	strcpy(User_GLCD_DataBuffer," TruongMinhKhoa");
	User_GLCD_ShowString(0,0,User_GLCD_DataBuffer);
	strcpy(User_GLCD_DataBuffer,"   17151216");
	User_GLCD_ShowString(0,1,User_GLCD_DataBuffer);
	strcpy(User_GLCD_DataBuffer,"  TranThanhHai");
	User_GLCD_ShowString(0,2,User_GLCD_DataBuffer);
	strcpy(User_GLCD_DataBuffer,"   17151197");
	User_GLCD_ShowString(0,3,User_GLCD_DataBuffer);
	HAL_Delay(500);
	User_ClearArrayBuffer((char*)User_GLCD_DataBuffer);
	User_GLCD_SendCommand(GLCD_Clear);
	HAL_Delay(20);
}
void User_GLCD_ConvertInt16ToChar(char *String,uint16_t numToConvert)
{
	sprintf(String,"%d",numToConvert);
	User_GLCD_ShowStringNoXY(String);
}
void User_GLCD_ConvertFloatToChar(char *String,float numToConvert)
{
	sprintf(String,"%.2f",numToConvert);
	User_GLCD_ShowStringNoXY(String);
}

void User_GLCD_ClearDisplay()
{
	User_GLCD_SendCommand(GLCD_Clear);
	HAL_Delay(20);
}
