#include "EncoderPCNT.h"

// 設定編碼器腳位與 PCNT 單元
EncoderPCNT encoder(GPIO_NUM_39, GPIO_NUM_36, PCNT_UNIT_0);

void setup() {
  Serial.begin(115200);
  encoder.begin();         // 初始化編碼器
  encoder.resetEncoder();  // 歸零計數
  Serial.println("EncoderPCNT 範例：即時顯示編碼器計數值");
  Serial.println("輸入 r 可歸零計數");
}

void loop() {
  long pos = encoder.get_count();
  Serial.printf("目前編碼器計數值: %ld\n", pos);

  // 若收到序列埠輸入 r，則歸零
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == 'r' || cmd == 'R') {
      encoder.resetEncoder();
      Serial.println("計數歸零！");
    }
  }

  delay(200); // 每 0.2 秒更新一次
}