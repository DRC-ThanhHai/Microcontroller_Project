#include "DoAnVXL_ESPLib.h"
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  swSer.begin(9600, SWSERIAL_8N1, ESP_RX, ESP_TX, false, 95, 11);
  Serial.begin(9600);

  ESP_FindKnownSSIDAndConnect    ();

  myNTP.begin();
  timer = millis();

}
void loop() {
  // put your main code here, to run repeatedly:
  
  if (Serial.available() || swSer.available() ) // ngắt UART khi có tín hiệu UART sẽ ngắt nhận 1 byte từ máy tính gửi hoặc nhận từ PIC
  {
    ESP_HandleDataReceive();
    /* print sẽ gửi ký tự số là mã ascii của ký tự nhận từ bàn phím p
      nếu print số 0 thì sẽ gửi số 4 -> 8
      nếu print số 0 thì sẽ gửi số 4 -c> 9
      Mỗi số là 1 byte char => 49 = 2 bytes, 117 = 3 bytes
      write sẽ gửi ký tự của mã ascii đó
      Số 0 có mã ascii là 48 -> gửi đi 1 byte char là 0
      Chữ u có mã ascii là 117 -> gửi đi 1 byte char là u
    */
  }
}
