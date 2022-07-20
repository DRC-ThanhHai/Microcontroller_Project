#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "NTPClient.h"
#include <SoftwareSerial.h>
SoftwareSerial swSer;
WiFiUDP myUDP;
#define ESP_TX (12)
#define ESP_RX (13)
void ESP_HandleDataReceive();
typedef enum
{
  Request_ESPscanwifi                 = 0,
  Request_ESPSleep_WakeExternal       = 1,
  Request_ESPStopSendingTime          = 2,
  Request_SendTimeContinuously        = 3,
  Request_ESPWifiDisconnect           = 4,
  Request_ESPWifiReconnect            = 5,
  Request_ESPSendPresentTime          = 6,
  Request_ViewESPCommand              = 7,
  ESPReceiveDataFromPCAndSendToMCU    = 8,

  MCU_GetCommand                      = 9
} ESP_Ins;
typedef enum
{
  Status_ESPBusy                      = 1,
  Status_ESPReady                     = 2
} ESP_Status;
bool ESP_StopSendingTime = false;
const char WiFiID1[] = "Ngoc Hai";
const char WiFiPassword1[] = "0903817572";
const char WiFiID2[] = "RedmiKhoa";
const char WiFiPassword2[] = "248715121";
NTPClient myNTP(myUDP, "2.vn.pool.ntp.org", 7 * 3600); // 7*3600 = GMT+7
unsigned long timer;
void ViewESPCommand_Func()
{
  Serial.println("Command for ESP:");
  Serial.println("0:Scanwifi");
  Serial.println("1:ESPSleep");
  Serial.println("2:ESPStopSendingTime");
  Serial.println("3:ESPSendTimeContinuously");
  Serial.println("4:ESPWifiDisconnect");
  Serial.println("5:ESPWifiReconnect");
  Serial.println("6:ESPSendPresentTime");
  Serial.println("7:View Command ESP");
  Serial.println("8:Get data from PC, send to MCU");
  Serial.println("9:MCU Get command from PC");
}
void ESP_ConnectNetwork(char *WiFiName, char *Pass)
{
  WiFi.disconnect();
  WiFi.begin(WiFiName, Pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    swSer.print("WaitCn~");
    Serial.println("WaitCn");
  }
  Serial.println("WFCn");
  swSer.print("WFCn~");
  ViewESPCommand_Func();
}
void ESP_DeepSleepMode(uint64_t TimeWakeUpMicroSecond)
{
  swSer.print("DSleep~");
  delay(100);
  swSer.print("PressResetToWake");

  Serial.println("DSlp-PrsRstToWkUp");
  ESP.deepSleep(TimeWakeUpMicroSecond);
}
void ESP_FindKnownSSIDAndConnect()
{
  int n = WiFi.scanNetworks();
  bool DetectKnownWiFi[2] = {false};
  int16_t RSSIValue[2] = {0};
  if (n == 0)
  {
    Serial.print("0WF");
    swSer.print("0WF~");
  }
  else
  {
    for (int i = 0; i < n; ++i)
    {
      if (WiFi.SSID(i) == WiFiID1)
      {
        Serial.print(WiFi.SSID(i));
        Serial.println("Found");
        swSer.print(WiFiID1);
        swSer.print(" F~");
        delay(10);
        DetectKnownWiFi[0] = true;
        RSSIValue[0] = WiFi.RSSI(i); //RSSI trả về kiểu int32_t nhưng giá trị không lớn nên có thể dùng int16_t

      }
      else if (WiFi.SSID(i) == WiFiID2)
      {
        Serial.print(WiFi.SSID(i));
        Serial.println("Found");
        swSer.print(WiFiID2);
        swSer.print(" F~");
        delay(10);
        DetectKnownWiFi[1] = true;
        RSSIValue[1] = WiFi.RSSI(i); //RSSI trả về kiểu int32_t nhưng giá trị không lớn nên có thể dùng int16_t
        ESP_ConnectNetwork((char *)WiFiID2, (char *)WiFiPassword2);
      }
      else if (DetectKnownWiFi[0] && DetectKnownWiFi[1]) break;
    }

    switch (DetectKnownWiFi[0])
    {
      case 0:
        switch (DetectKnownWiFi[1])
        {
          case 0:
            swSer.print("NoKwnWFF~");
            Serial.println("NoKwnWFF");
            break;
          case 1:
            ESP_ConnectNetwork((char *)WiFiID2, (char *)WiFiPassword2);
            break;
        }
        break;
      case 1:
        switch (DetectKnownWiFi[1])
        {
          case 0:
            ESP_ConnectNetwork((char *)WiFiID1, (char *)WiFiPassword1);
            break;
          case 1:
            if (RSSIValue[0] > RSSIValue[1])
            {
              ESP_ConnectNetwork((char *)WiFiID1, (char *)WiFiPassword1);
              //  swSer.print("  1Cn~"); // kiểm tra hàm if chạy đúng hay sai
              Serial.println("1Cn~");
            }
            else
            {
              ESP_ConnectNetwork((char *)WiFiID2, (char *)WiFiPassword2);
              //  swSer.print("  2Cn~"); // kiểm tra hàm if chạy đúng hay sai
              Serial.println("2Cn~");
            }
            break;
        }
        break;
      default:
        break;
    }
  }
}
void ESP_ScanWifi()
{
  int n = WiFi.scanNetworks();

  if (n == 0)
  {
    Serial.print("No WiFi");
  }
  else
  {
    for (int i = 0; i < n; ++i)
    {
      Serial.print(WiFi.SSID(i));//Tên Wifi
      Serial.print(" ");
      Serial.println(WiFi.RSSI(i));//Cường độ tín hiệu
      delay(10);
    }
  }

}
void ESP_SendTimeContinuously()
{
  swSer.print("Loading~");
  while (WiFi.status() == WL_CONNECTED && !ESP_StopSendingTime) // dùng while tại đây thì esp gửi thời gian liên tục
  {
    if ((unsigned long)(millis() - timer) > 1000)
    {
      myNTP.update();
      timer = millis();
      swSer.print(myNTP.getFormattedTime());
      swSer.print("~");
      Serial.println(myNTP.getFormattedTime());

    }
    if (Serial.available() || swSer.available() )
    {
      ESP_HandleDataReceive();
    }

  }
  ESP_StopSendingTime = false;
}
void ESP_SendPresentTime()
{
  swSer.print("Loading~");
  swSer.print(myNTP.getFormattedTime());
  Serial.println(myNTP.getFormattedTime());
  swSer.print("~");
}
void ESPReceiveDataFromPCAndSendToMCU_Func()
{
  Serial.println("In Function");
  Serial.println("Type . to get out");
  int c = 0, temp_c = 0;

  while (true)
  {
    /*
     * không dùng chung với các lệnh đọc ký tự khác
     * nếu c = Serial.read(); đặt trước thì swSer.write toàn bộ là '255'
     * nếu swSer.write đặt trước thì 2 hàm luân phiên đọc các ký tự gửi đến VD:123456
     * swSer.write đọc 1 3 5
     * c = Serial.read(); đọc 2 4 6
    while (Serial.available() > 0)
    {
      
      swSer.write(Serial.read()); 
      yield();
      c = Serial.read();
    }
    */
    while (Serial.available() > 0)
    {
      c = Serial.read();
    }
    
      if (temp_c != c)
      {
        Serial.println(char(c));
        swSer.write(c);//print trong trường hợp này truyền đi số ASCII theo byte: VD 0 = 48 => gửi byte là số 4 và byte là số 8
        temp_c = c;
      }


      if (char(c) == '.')
      {
        Serial.println("Stop Function");
        ViewESPCommand_Func();
        break;
      }
    
  }
}
void ESP_HandleDataReceive()
{
  String s;

  if (swSer.available())
  {
    s = swSer.readStringUntil('\n');
  }
  if (Serial.available())
  {
    s = Serial.readStringUntil('\n');
  }
  char c[] = {0};
  strcpy(c, s.c_str());
  int num = atoi(c);
  switch (num)
  {
    case Request_ESPscanwifi:
      ESP_ScanWifi();
      break;
    case Request_ESPSleep_WakeExternal :
      ESP_DeepSleepMode(0);
      break;
    case Request_SendTimeContinuously:
      ESP_SendTimeContinuously();
      break;
    case Request_ESPStopSendingTime:
      ESP_StopSendingTime = true;
      break;
    case Request_ESPSendPresentTime:
      ESP_SendPresentTime();
      break;
    case Request_ESPWifiDisconnect:
      WiFi.disconnect();
      Serial.println("DisCnY");
      break;
    case Request_ESPWifiReconnect:
      ESP_FindKnownSSIDAndConnect();
      break;
    case Request_ViewESPCommand:
      ViewESPCommand_Func();
      break;
    case ESPReceiveDataFromPCAndSendToMCU:
      ESPReceiveDataFromPCAndSendToMCU_Func();
    case MCU_GetCommand:
      swSer.print("MCUGetCmd");
      Serial.println("MCUGetCmdFromPC");
    default:
      break;
  }
}
