/*
  用 LM35 进行温度测量

  inspired by
  ladyada https://learn.adafruit.com/tmp36-temperature-sensor
  pscmpf http://pscmpf.blogspot.com/2008/12/arduino-lm35-sensor.html

*/

int reading;        // 存放 ADC 原始数据
float voltage;      // 存放电压值
float temperature;  // 存放温度值
int sensorPin = A0; // LM35 第 2 pin 接到 A0 上

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // 读 sensorPin 上的电压
  // 会得到一个 0 to 1023 之间的值
  reading = analogRead(sensorPin);

  // 转换成电压值
  voltage = reading * 5.0;     // 5V Arduino
  voltage = voltage / 1024.0;
  //voltage = (reading * 5) / 1024; // 这行代码似乎可以代替上面两行，试一试把上两行换成这一行
                                    // 观察有什么效果

  // 打印电压
  // 随时可以用 print 查看数据的正确性
  Serial.print(voltage); Serial.println(" V");

  // 得到温度值，单位 °C
  temperature = voltage * 100;

  // 把温度值发送到电脑串口
  Serial.print(temperature); Serial.println(" °C");
  delay(1000); // 等一会儿再进行下次测量
}

