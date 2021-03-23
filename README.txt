软件采用Keil MDK5，代码使用最新版HAL库
时钟配置请参考CUBEMX文档

接线说明：
左轮pwm-PA8
右轮pwm-PA9
舵机pwm-PA10

避障左：
echo-PB10
triger-PB3
避障中：
echo-PB0
triger-PB4
避障右：
echo-PB8
triger-PB5

电机控制线路：(控制前进后退，从左到右接即可，目前没用到后退)
MOTOR_IN1-PA1
MOTOR_IN2-PA2
MOTOR_IN3-PA3
MOTOR_IN4-PA4

离合-PA5（暂未使用）

uwb：（只需要接基站1的数据，基站2只需要通电即可，基站1放在左边，基站2放在右边）
RX接单片机TX-PB6
TX接单片机RX-PB7

数据说明：
lenL、lenM、lenR分别代表距离传感器左中右检测到的距离，检测距离有效值范围为30cm-170cm（不精确且有抖动，建议更换tof10120距离传感器更准确）
distl_ave、distr_ave分别代表左右基站离标签的距离
motor_speed_set后参数代表小车速度，与英文相对应

uwb算法原理：（在main_control中）
通过比较左右基站到标签的距离大小来确定小车的转向，若需要让小车靠右行驶，只需要在左边基站到标签距离数值加上一定数据即可

避障模式和uwb模式切换原理：(在main_control中)
当避障传感器检测到前方障碍物距离小于60cm时即启动避障模式，否则则为uwb模式
如需单独对两种模式进行调试，只需要更改if else语句关闭其中模式即可

整体算法说明：
整个程序由CUBEMX生成系统配置，采用HAL库进行代码编写，使用FreeRTOS做为嵌入式操作系统，进行任务管理，共开启5个线程
其中三个线程分别计算避障传感器的距离（在wave.c中）
另一个线程用于处理uwb数据（在uwb.c中）
最后一个线程优先级最高，用于控制小车运行逻辑（在main_control中）
另外，小车电机的相关配置在motor.c中，仅为数据配置，并未占用任何线程

系统文件说明：
gpio.c为io口的相关配置，在之后使用离合时可进行更改
usart.c为串口配置，即uwb参数配置
tim.c为避障传感器和电机、舵机pwm定时器配置
main.h中有各io口名称宏定义