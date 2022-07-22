/*
 * Button_Interface_DoAnVXL.h
 *
 *  Created on: Aug 12, 2020
 *      Author: KHOA
 */

#ifndef INC_BUTTON_INTERFACE_DOANVXL_H_
#define INC_BUTTON_INTERFACE_DOANVXL_H_
//User_Button_countNext = 0;
//User_Button_countCancel = 0;
//User_Button_countDown = 0;
//User_Button_countUp = 0;
//User_Button_countMode=0;
//User_Button_countOK=0;

int User_Button_Up();
void User_Button_Donw();
void User_Button_Next();
void User_Button_Cancel();
void User_Button_Mode();
void User_Button_OK();
int Key_Press(GPIO_TypeDef *GPIO_Port,uint16_t GPIO_Pin);


#endif /* INC_BUTTON_INTERFACE_DOANVXL_H_ */
