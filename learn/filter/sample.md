% AVR 101 - Let there be blink!
% Atommann
% April 30, 2013

简介
--------

欢迎来到单片机的世界！该教程将简单地介绍基本的 AVR 单片机编程知识，并用实际的体验方式进行学习。


----------------------

请问：它为什么叫“单片机”？

### 玩单片机的大致流程

编程环境准备
------------

我们准备用 AVR-GCC 作为编译器。

### Windows

在 Windows 里，我们可以用 [WinAVR][02] 作为开发环境，WinAVR 可以到下面的网址下载：
http://winavr.sourceforge.net/

[02]: http://sourceforge.net/projects/winavr/files/WinAVR/20100110/ "WinAVR"

安装完成之后，打开 Windows 命令行（快捷键是 Win 键+R，然后输入 cmd 回车）

[![cmd][cmd]][cmd]

执行 avr-gcc 如果有提示，表明安装成功。

[![avr-gcc][avr-gcc]][avr-gcc]

执行 avrdude 如果有提示，表明 avrdude 工作正常。


### Linux

在 Linux 里，我们可以用包管理器安装，请搜索 avr-gcc, avr-libc, avrdude 并安装相应的软件包。

### Mac OS

在 Mac OS 里安装 AVR 开发环境。

### 安装 USBasp 驱动程序

请安装 libusb_1.2.4.0，最新的驱动可以到 [USBasp][03] 官方网站下载。

[03]: http://www.fischl.de/usbasp/ "USBasp"

一个简单的任务
--------------

这里先提出一个问题：假设你手上有一个红色 LED 和一个绿色 LED，你怎样让它们交替地闪烁起来？也就是红色 LED 亮的时候绿色 LED 灭，绿色 LED 亮的时候红色 LED 灭。

要实现这个功能，方法有很多种，我们先来看看两种硬连线的方式。

### 555 的方案

[![555][555]][555]

演示 555 电路做出的效果。

### 环形振荡器方案

说明：演示环形振荡器的闪烁方案。

现在我们再问一个问题：很好，上面的两种方法都实现了闪烁功能，如果我想让 LED 闪得快一点或者闪得慢一点，那该怎么办呢？
呃，这个嘛……，请问我的电烙铁在哪里？

烧个 LED
电阻出场：欧姆定律

让单片机出场
------------

哇，我们的主角终于出场了！

### 单片机究竟是神马东西？

[![atmega8][atmega8]][atmega8]

我们先从“单片机”这三个字讲起，这三个字已经包含了足够多的信息。

* 单：就是一个的意思，比如“单身汉”，“单词”。
* 片：指的是芯片。
* 机：指的是计算机。嗯？这么小也能称之为计算机？怎么我家的计算机那么大？没错，计算机，就是可以计算的机器，单片机可以计算。

我们通常所说的计算机包含了 CPU，内存，ROM(只读存储器)，输入/输出设备。单片机在一块芯片上把所有这些功能都全部放到一块芯片上去了！(可以用麻雀虽小，五脏俱全来形容)

单片机的功能当然不能和我们的电脑相比，它要慢得多，而且非常便宜，比如我们用的这块单片机市场零售价是 10 元钱，10元钱你能买到一台笔记本电脑吗 :)

单片机会把程序存在它的闪存里，就像我们把 mp3 文件存在我们的 SD 卡里，只不过这里存的是程序，只在我们一给单片机上电，它就会自动去读取存储器里的代码，然后运行！

### 端口

[![pinout][pinout]][pinout]

[![pin_desc][pin_desc]][pin_desc]

[![pin_numbering][pin_numbering]][pin_numbering]

### Let there be blink

原理图

[![blink][blink]][blink]

伪代码(不是真正的程序，但是可以把它翻译成真正的程序)

    main:
        把 I/O 的方向设置成输出模式
    循环:
        点亮 LED
        拖延时间，什么都不干
        关掉 LED
        拖延时间，什么都不干
        重复

C 代码

    #include "avr/io.h"   // 包含 I/O 头文件
    #define F_CPU 12000000UL
    #include "util/delay.h"   // 包含头文件，延时要用到它

    int main(void)
    {
        DDRC = 0b00111111;  // 数据方向是控制，是输出，还是输入
        PORTC = 0b0000; // 设置单片机端口初始状态

        while (1) // 死循环
        {
            PORTC = 0b00000001;
            _delay_ms(200);     // 延时 200 毫秒
            PORTC = 0b00000010;
            _delay_ms(200);     // 延时 200 毫秒
        }
    }


解释上面程序的工作原理。

### 快一点，慢一点

    #include "avr/io.h"   // 包含 I/O 头文件
    #define F_CPU 12000000UL
    #include "avr/io.h"   // 包含头文件，延时要用到它

    int main(void)
    {
        DDRC = 0b00000000;  // 数据方向是控制，是输出，还是输入

        _delay_ms(5000);    // 延时 5 秒
        PORTC = 0b00111111; // 设置单片机端口初始状态

        while (1) // 死循环
        {
        }
    }


修改 _delay_ms(200); 里的时间参数。

玩单片机的一般流程
------------------

### 编辑(写程序)

在文本编辑器中写程序。
图。

### 编译

用 AVR-GCC 把 C 代码翻译成机器码。怎么翻译？我们只需要执行 make 命令即可。
图。

#### 下载

现在，我们得到了单片机需要的可以运行的代码，但是这些代码现在存在我们的电脑上，怎样才能把它弄到单片机里去呢？

#### AVR 编程器


[![programmer][programmer]][programmer]

演示如何用 AVR 编程器来烧写固件。

那，我们需要一个编程器吗？答案是否，因为我们这个硬件把编程器也包含进去了！下面我们来看看怎么操作。

#### 进入引导模式

首先，我们要进入单片机的引导程序(bootloader)，具体操作方法如下：

1. 按住 USB 接口一端的“引导程序激活”按钮操持不放。

2. 按一下复位键(在电源 LED 指示灯旁边)。

3. 松开“引导程序激活”按钮。

不出意外，你会发现电脑会自动识别出一个新的 USB 设备，这个设备叫 USBasp，它就是一个 AVR 编程器，借助它，我们可以用一个叫 avrdude 的软件把单片机的代码下载到芯片里。

#### make program

如果你喜欢动手敲命令，你可以用下面这条命令把程序“烧”进 AVR 里：

avrdude -c usbasp -p atmega328p -U flash:w:filename.hex

这样做的缺点是，每次都要打这么多字，真是太麻烦了！我们可以偷个懒，走个捷径。实际上，因为我们的工程目录里已经有了一个 Makefile，它里面就包含了如何下载程序的信息。我们只需要执行

make program

程序就能下载到单片机里去了！是不是很容易！

注意：当程序成功下载到芯片之后你可能会看到像 "avrdude: error: usbasp_transmit: usb_control_msg: sending control message failed, win error: A device attached to the system is not functioning." 这样的错误提示，不用理它，可以直接忽略。事实上我们下载程序的时候没有发生错误，这个提示是 bootloader 在跳转程序的时候导致的。


面包板的用法
------------

### 为什么叫“面包板”？

[![breadboard][breadboard]][breadboard]

我们现在回到 1900 年左右(那时还没有晶体管，也没有现在面包店里卖的[切片面包][01]，切片面包在 1928 年首次出现)，人们做原型电路的时候就是用切面包用的砧板来搭电路的，因为这种木板很容易弄到而且也不贵，这个词一直沿用到今天。

[![chopping_board][chopping_board]][chopping_board]

[01]: http://en.wikipedia.org/wiki/Sliced_bread "切片面包"

<!---
tool photos
-->

[breadboard]: ./figures/ab0cw-breadboard.jpg "breadboard"
[chopping_board]: ./figures/Chopping_Board.jpg "chopping board"
[atmega8]: ./figures/atmega8.jpg "atmega8"
[programmer]: ./figures/programmer.jpg "programmer"
[555]: ./figures/555test.gif "555"
[pinout]: ./figures/pinout.png "pinout"
[pin_desc]: ./figures/pin_desc.png "pin_desc"
[pin_numbering]: ./figures/pin_numbering.svg "pin_numbering"
[blink]: ./figures/blink.png "blink"
[cmd]: ./figures/cmd.png "cmd"
[avr-gcc]: ./figures/avr-gcc.png "avr-gcc"

