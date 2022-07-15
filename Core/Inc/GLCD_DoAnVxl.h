#ifndef GLCD_DoAnVxl_H_
#define GLCD_DoAnVxl_H_


#include "stm32f1xx_hal.h"
#define GLCD_Clear          0x01
#define GLCD_Home           0x02
#define GLCD_Entry          0x06
#define GLCD_DisplayOn      0x0C
#define GLCD_DisplayOff     0x08
#define GLCD_CursorOn       0x0E
#define GLCD_CursorBlink    0x0F
#define GLCD_Basic          0x30
#define GLCD_Extend         0x34
#define GLCD_GraphicMode    0x36
#define GLCD_TextMode       0x30
#define GLCD_Standby        0x01
#define GLCD_Scroll         0x03
#define GLCD_SCROLLADDR     0x40
#define GLCD_Address        0x80
#define GLCD_Line0          0x80
#define GLCD_Line1          0x90
#define GLCD_Line2          0x88
#define GLCD_Line3          0x98
#define GLCD_Basic4Bit      0x20

char User_GLCD_DataBuffer[16];
//void User_GLCD_SendCommand(uint8_t Command);
//void User_GLCD_SendData(uint8_t data);
void User_GLCD_TestGLCDPin(uint8_t delay);
void User_GLCD_SendCommand(uint8_t Command);
void User_GLCD_ShowStringNoXY(char *DataString);
void User_GLCD_GotoXY(uint8_t x,uint8_t y);
void User_GLCD_ShowString(uint8_t x,uint8_t y,char *DataString);
void User_GLCD_Init();
void User_GLCD_ConvertInt16ToChar(char *String,uint16_t numToConvert);
void User_GLCD_ConvertFloatToChar(char *String,float numToConvert);
void User_GLCD_ClearDisplay();
#endif /* GLCD_DoAnVxl_H_ */
