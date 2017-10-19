/*
  LM35 输出 CSV 文件进行数据记录
*/

int reading;        // 存放 ADC 原始数据
float voltage;      // 存放电压值
float temperature;  // 存放温度值
int sensorPin = A0; // LM35 第 2 pin 接到 A0 上
unsigned long time; // 时间戳

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  time = millis(); // 读当前时间
  // 读 sensorPin 上的电压
  // 会得到一个 0 to 1023 之间的值
  reading = analogRead(sensorPin);

  // 转换成电压值
  voltage = reading * 5.0;     // 5V Arduino
  voltage = voltage / 1024.0;

  // 得到温度值，单位 °C
  temperature = voltage * 100;

  //prints time since program started
  Serial.print(time/1000); // in seconds
  Serial.print(", ");      // 打印 CSV (Comma-Separated Values) 格式

  Serial.print(temperature); // 把温度值发送到电脑串口
  delay(1000); // 等一会儿再进行下次测量
}

