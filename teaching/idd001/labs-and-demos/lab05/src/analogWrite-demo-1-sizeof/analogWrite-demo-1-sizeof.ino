// 呼吸灯
// 在 Uno 上 pin 3, 5, 6, 9, 10, 11 支持 analogWrite()
// 也就是带 ~ 的 pin
#define LED_PIN 3

// 存放 LED 亮度值的查找表(lookup table)
uint8_t sine_table[] = {
  1,   1,   2,   3,   5,   8,  11,  15,  20,  25,
 30,  36,  43,  49,  56,  64,  72,  80,  88,  97,
105, 114, 123, 132, 141, 150, 158, 167, 175, 183,
191, 199, 206, 212, 219, 225, 230, 235, 240, 244,
247, 250, 252, 253, 254, 255, 254, 253, 252, 250,
247, 244, 240, 235, 230, 225, 219, 212, 206, 199,
191, 183, 175, 167, 158, 150, 141, 132, 123, 114,
105,  97,  88,  80,  72,  64,  56,  49,  43,  36,
 30,  25,  20,  15,  11,   8,   5,   3,   2,   1, 0};

// 计算查找表中的元素数量
int numData = (sizeof sine_table) / (sizeof sine_table[0]); // 在这里 numData = 91 <1>

void setup() {
  Serial.begin(9600);
  Serial.println(numData); // 打印出数字帮助我们确认
}

void loop() {
  for (int i = 0; i < numData; i++) {
    analogWrite(LED_PIN, sine_table[i]);
    delay(50);
  }
}
