# EncoderPCNT 函式庫

## 簡介
EncoderPCNT 是一個基於 ESP32 PCNT 外設的編碼器計數函式庫，能夠高效且精確地讀取旋轉編碼器的脈衝計數，適合用於馬達位置偵測、機器人、計量等應用。

## 安裝方式
1. 複製 `src` 資料夾到 Arduino 或 PlatformIO 的 `libraries` 目錄下。
2. 在您的程式碼中加入：
   ```cpp
   #include "EncoderPCNT.h"
   ```

## 支援平台
- ESP32

---

## 如何使用

### 1. 硬體接線
將編碼器的 A、B 相連接到 ESP32 的兩個 GPIO 腳位，例如 GPIO39 與 GPIO36。  
（腳位可依需求調整，請與您的硬體接線一致）

### 2. 初始化與計數讀取

```cpp
#include "EncoderPCNT.h"

// 設定編碼器腳位與 PCNT 單元
EncoderPCNT encoder(GPIO_NUM_39, GPIO_NUM_36, PCNT_UNIT_0);

void setup() {
  Serial.begin(115200);
  encoder.begin();         // 初始化編碼器
  encoder.resetEncoder();  // 歸零計數
}

void loop() {
  long pos = encoder.get_count();
  Serial.printf("目前編碼器計數值: %ld\n", pos);
  delay(200);
}
```

### 3. 歸零計數
在程式中呼叫 `encoder.resetEncoder();` 可將計數歸零。  
範例程式也支援在序列埠輸入 `r` 來歸零。

---

## API 說明

| 方法                | 說明                       |
|---------------------|----------------------------|
| `EncoderPCNT(a, b, unit)` | 建構子，設定 A、B 相腳位與 PCNT 單元 |
| `begin()`           | 初始化 PCNT 外設           |
| `get_count()`       | 取得目前計數值             |
| `resetEncoder()`    | 歸零計數                   |

---

## 範例程式

```cpp
#include "EncoderPCNT.h"

EncoderPCNT encoder(GPIO_NUM_39, GPIO_NUM_36, PCNT_UNIT_0);

void setup() {
  Serial.begin(115200);
  encoder.begin();
  encoder.resetEncoder();
  Serial.println("EncoderPCNT 範例：即時顯示編碼器計數值");
  Serial.println("輸入 r 可歸零計數");
}

void loop() {
  long pos = encoder.get_count();
  Serial.printf("目前編碼器計數值: %ld\n", pos);

  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == 'r' || cmd == 'R') {
      encoder.resetEncoder();
      Serial.println("計數歸零！");
    }
  }

  delay(200);
}
```

---

## 檔案結構

```
EncoderPCNT/
│
├── src/
│   ├── EncoderPCNT.h
│   └── EncoderPCNT.cpp
└── examples/
    └── encoder_demo/
        └── encoder_demo.ino
```

---

## 常見問題 FAQ

**Q：支援哪些平台？**  
A：目前僅支援 ESP32，其他平台暫不支援。

**Q：如何更換編碼器腳位？**  
A：在建構 EncoderPCNT 物件時，指定不同的 GPIO 腳位即可。

**Q：計數值是否會溢位？**  
A：計數值為 long 型別，正常使用下不易溢位。如需多圈計數或更高精度，請自行管理。

---


- 作者：catsshocker
- 部分由AI製作 使用時以實際效果為準
