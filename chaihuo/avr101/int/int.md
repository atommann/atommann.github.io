% AVR 101 - Excuse me... (中断的概念)
% Atommann
% May 01, 2013

简介
--------

* 我笔记本中的插图 或者别的插图
* 秒钟 马潮书中的例子
* 用示波器显示晶振的波形

中断是什么？
------------

先让我们看一下“中断”这个词在我们现实生活中的含义。中断的英语单词是 interrupt，这个词有“暂停；中断；打扰；打断；妨碍”等意思。

举个例子，比如我正在读一本非常精彩的书，突然有人打我电话，我就把书签夹在正在读的那一页，然后接电话，电话接完后又回来读书，从刚才停下的地方开始阅读。电话中断了我的阅读！

我们现实生活里中断的例子非常多，大家随便就可以举上几个例子。

实际上，单片机的中断也是这样工作的！中断程序运行的时候，我们的主程会停止工作。稍后我们将用例子作演示。

体验中断
--------

百闻不如一见，让我们用一个实际的例子来体验一下中断，看看传说中的单片机中断是什么样子的。

### 原理图

首先，按照下面的图把电路在面包板上搭好。

[![toggle_led][toggle_led]][toggle_led]

### 翻转 LED

[下载源程序][int1_toggle]。

[int1_toggle]: ./int1-toggle.zip "INT1 Togle"


    #include <avr/io.h>
    #include <avr/interrupt.h> // 使用中断必须包含这个文件，sei(), cli() 和 ISR() 等中断相关的定义都在这个头文件里

    // 外部中断1 (INT1) 中断服务例程
    ISR (INT1_vect)
    {
        PORTC = PORTC ^ 1; // (1) 翻转 LED 的状态
    }
    
    // 端口和 INT1 初始化
    void init(void)
    {
        DDRC = 0xFF; // 将 PORTC 设置成输出模式
        PORTC = 0x00;
    
        // 设置化外部中断1
        EICRA = 0b00001000; // (1 << ISC11) 下降沿触发中断 see datasheet page 72
        EIMSK = 0b00000010; // (1 << INT1)  开启 INT1      see datasheet page 73
    }
    
    int main(void)
    {
        init(); // 初始化
        sei();  // 开启全局中断
    
        while (1)
        {
            // 这里面什么都没有
        }
    }

注释(1)里面的 ^ 符号是 C 语言里的异或(XOR)运算，它的行为如下:

A    B    结果
--   ---  ----
0    1    1
1    1    0

也就是说

* 如果原来 LED 是熄灭的，那和 1 进行 XOR 之后就会亮
* 如果原来 LED 是亮着的，那和 1 进行 XOR 之后就熄灭

因此，每当你按一下键，LED 的状态就会翻转。

### 中断会打断我们主程序的运行

试试下面的例子([下载源程序][int1])：

[int1]: ./int1.zip "INT1"

    #include <avr/io.h>
    #define F_CPU 12000000UL // 12 MHz
    #include <util/delay.h>
    #include <avr/interrupt.h> // sei(), cli() 和 ISR() 等中断相关的定义都在这个头文件里
    
    // 外部中断1 (INT1) 中断服务例程
    ISR (INT1_vect)
    {
        uint8_t i, temp;
        
        temp = PORTC;    // 先把 PORTC 里面的数据保存起来
    
        // 我们让 LED 闪烁 5 次
        for(i = 0; i<5; i++)
        {
            PORTC = 0b00000000;
            _delay_ms(500);      // 亮半秒钟(注意：在中断里使用延时不是好的编程习惯，这里仅供演示)
            PORTC = 0b11111111;
            _delay_ms(500);      // 灭半秒钟
        }
    
        PORTC = temp;            // 恢复 PORTC 的值
    }
    
    // 端口和 INT1 初始化
    void init(void)
    {
        DDRC = 0xFF; // 将 PORTC 设置成输出模式
        PORTC = 0x00;
    
        // 设置化外部中断1
        EICRA = 0b00001000; // (1 << ISC11) 下降沿触发中断 see datasheet page 72
        EIMSK = 0b00000010; // (1 << INT1)  开启 INT1      see datasheet page 73
    }

    int main(void)
    {
        unsigned char i;
    
        init(); // 初始化
        sei();  // 开启全局中断
    
        while (1)
        {
            for (i=0; i<6; i++)
            {
                PORTC = (1 << i); // 移位操作
                _delay_ms(500);
            }
        }
    }

按一下接在 INT1 上的按键，观察效果。

外部中断
--------

恭喜！如果你完成了上面的两个例子，实际上已经实际体验了单片机的外部中断！让我们来解释一下什么是外部中断。

[![intx][intx]][intx]

图中的红色标识就是外部中断，INT0 和 INT1。在我们的单片机开发板上，INT0 已经被 USB 通讯所占用，因此我们使用 INT1 来做实验。

INT0 和 INT1 的工作原理是：当这个引脚上的电压有变化的时候，就会导致中断发生，因为这个电压变化发生在单片机的外部，所以称为外部中断，可以理解成是在外部发生的中断。

### 寄存器，寄存器！

以前我们讲过，单片机就像一台迷你电脑，它上面集成了很多外围设备，每个设备都是由一些叫做寄存器的东西所控制的。中断也一样，要想使用中断，首先就要设置寄存器。

那我们要设置那些寄存器呢？答案就是看单片机的[数据手册][mega328p_datasheet](可以把单片机的数据手册看成是“权威指南”)或者参考一些图书。

[mega328p_datasheet]: http://www.atmel.com/Images/Atmel-8271-8-bit-AVR-Microcontroller-ATmega48A-48PA-88A-88PA-168A-168PA-328-328P_datasheet.pdf "ATmega328P datasheet"

在数据手册第 72 页，就是 INT0 和 INT1 的相关描述，我们会用到两个寄存器。

* EICRA – External Interrupt Control Register A
* EIMSK – External Interrupt Mask Register

ISC11  ISC10  行为描述
-----  -----  --------
0      0      INT1 上的低电平会产生一个中断请求
0      1      只要在 INT1 上有任何逻辑电压变化都会产生一个中断请求
1      0      INT1 上的下降沿会产生一个中断请求
1      1      INT1 上的上升沿会产生一个中断请求


注意“请求”这个词，它指的是向 CPU 请求，意思是“啊，我这里有个中断，快来看看啊！”

我们来看看什么叫“上升沿”和“下降沿”。

### 中断服务程序(ISR)

ISR, Interrupt Service Routine

定时器溢出中断
---------------

讲 Timer 0 的控制寄存器 TCCR0 和 TCNT0

怎样设置时钟

[下载源代码][overflow]。

[overflow]: ./overflow.zip "Timer 0 Overflow"



    #include <avr/io.h>
    #include <avr/interrupt.h>

    volatile uint8_t counter;
    
    int main(void)
    {
        // 设置 Timer 0 的时钟信号
        TCCR0B = (1 << CS02); // Prescaler 256
 
        // 打开溢出中断功能
        TIMSK0 |= (1 << TOIE0);
        
        // 打开全局中断开关
        sei();
        
        while(1)
        {
            // 可以在这里写其它的代码
        }
    }
 
    /*
    溢出中断处理程序
    当 TCNT0 的值超出 255 时就会归零
    这里下面的程序就会被执行
    */

    ISR (TIMER0_OVF_vect)
    {
        if (counter++ >= 181)
    }

要使用 Timer 0 的溢出中断，我们需要设置两个寄存器。

TCCR0B – Timer/Counter Control Register B

ATmega328P 数据手册第 108 页。

CS02   CS01   CS00  行为描述
-----  -----  ----  --------
0      0      0     不接时钟信号(Timer/Counter 处于停止状态)
0      0      1     IO 时钟频率/1
0      1      0     IO 时钟频率/8
0      1      1     IO 时钟频率/64
1      0      0     IO 时钟频率/256
1      0      1     IO 时钟频率/1024
1      1      0     T0 脚(PORTD.4)上的外部时钟源，下降沿
1      1      1     T0 脚(PORTD.4)上的外部时钟源，上升沿

TIMSK0 – Timer/Counter Interrupt Mask Register

ATmega328P 数据手册第 110 页。



单片机上有很多种中断，我们要对它进行设置，把中断和一个对应的程序连接起来，这个程序叫中断服务例程(Interrupt Service Routine, 缩写是 ISR)，意思是说当中断发生的时候，这个程序就要为中断“服务”，非常形象。

单片机的 Timer/Counter 是单片机里最复杂的东西。

中断有什么好处？
----------------

### 餐厅服务员的例子

### 轮询

游乐场
------------

### Timer 计数功能

用一个转盘，IR LED 光电传感器，对脉冲进行计数。或者用对射的方案，只要有东西经过就能计数。


<!---
figures
-->

[toggle_led]: ./figures/toggle_led.png "toggle led"
[intx]: ./figures/atmega328-intx.jpg "ATmega328 INTx"

