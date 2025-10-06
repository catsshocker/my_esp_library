# Hbridge 函式庫

## 簡介
Hbridge 是一個用於控制 H 橋電路的 Arduino/ESP32 函式庫，適用於馬達驅動等應用。  
本函式庫測試時使用 TB6612FNG，支援馬達正反轉、速度控制、煞車與滑行等功能。

## 安裝方式
1. 下載本函式庫，將 `src` 資料夾複製到 Arduino 的 `libraries` 目錄下，或使用 PlatformIO 直接引用。
2. 在您的程式碼中加入：
   ```cpp
   #include "Hbridge.h"
   ```

## 支援平台
- ESP32
- Arduino (部分功能需自行移植)

---

## 如何使用

### 1. 硬體接線
以 TB6612FNG 為例，您需要將 ESP32/Arduino 的 GPIO 腳位連接到 H 橋模組的 IN1、IN2、PWM、STBY 等腳位。  
請參考下表設定：

| 馬達 | IN1 | IN2 | PWM | STBY (啟動) |
|------|-----|-----|-----|-------------|
| A    | 25  | 33  | 32  | 26          |
| B    | 27  | 14  | 12  | 26          |

> **注意**：腳位可依需求調整，請與您的硬體接線一致。

### 2. 初始化馬達控制器

```cpp
#include "Hbridge.h"

MotorController mc(26); // 26號腳位控制馬達啟動與否

void setup() {
    // 設定馬達A的控制腳位
    mc.motorA.setPin(GPIO_NUM_25, GPIO_NUM_33, GPIO_NUM_32);
    // 設定馬達B的控制腳位
    mc.motorB.setPin(GPIO_NUM_27, GPIO_NUM_14, GPIO_NUM_12);

    // 設定停止模式
    mc.motorA.setStopMode(BRAKE); // 煞車
    mc.motorB.setStopMode(COAST); // 滑行

    // 設定馬達B反轉
    mc.motorB.reverse = true;

    delay(300); // 上電緩衝
    mc.begin(); // 初始化
    mc.enable(); // 啟動馬達
}
```

### 3. 控制馬達速度與方向

```cpp
// 馬達A正轉，速度128
mc.motorA.setSpeed(128);

// 馬達B反轉，速度255
mc.motorB.setSpeed(-255);

// 停止馬達A
mc.motorA.stop();

// 停用所有馬達
mc.disable();
```

### 4. 進階範例：漸變速度

```cpp
for(int i=0; i<=255; i++){
    mc.motorA.setSpeed(i);   // 逐漸加速
    mc.motorB.setSpeed(-i);  // 逐漸反向加速
    delay(10);
}
```

---

## API 詳細說明

### MotorController 類別
| 方法/屬性 | 說明 |
|-----------|------|
| `MotorController(enablePin)` | 建構子，指定啟動腳位 |
| `begin()` | 初始化所有馬達 |
| `enable()` / `disable()` | 啟用/停用馬達 |
| `motorA` / `motorB` | 兩組馬達物件 |

### Motor 類別
| 方法/屬性 | 說明 |
|-----------|------|
| `setPin(in1, in2, pwm)` | 設定馬達控制腳位 |
| `setSpeed(speed)` | 設定馬達速度，範圍 -255 ~ 255 |
| `setStopMode(mode)` | 設定停止模式（BRAKE/COAST）|
| `stop()` | 停止馬達 |
| `reverse` | 是否反轉方向（bool）|

### 停止模式
- `BRAKE`：馬達立即煞停
- `COAST`：馬達自然滑行停止

---

## 常見應用場景

- 智慧小車、機器人底盤
- 雙馬達驅動的履帶車
- 需要正反轉與速度控制的直流馬達應用

---

## 檔案結構

```
Hbridge/
│
├── library.properties
├── README.md
├── src/
│   ├── Hbridge.h
│   └── Hbridge.cpp
└── examples/
    └── Hbridge_test/
        └── Hbridge_test.ino
```

## 
- made by catsshocker
- 部分由AI製作 使用時以實際效果為準

