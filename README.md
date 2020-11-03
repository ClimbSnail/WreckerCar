## 机械臂清障车介绍
本作品参加2017年12月中日韩创新工程竞赛，获金奖（大三上参加的）

![](https://gitee.com/ClimbSnailQ/Project_Image/raw/master/OtherProject/WreckerCar_mini.jpg)

![WreckerCar_mini.jpg](./Image/WreckerCar_mini.jpg)



![](https://gitee.com/ClimbSnailQ/Project_Image/raw/master/OtherProject/WreckerCar_mini2.jpg)

![WreckerCar_mini2.jpg](./Image/WreckerCar_mini2.jpg)

B站视频[链接](https://b23.tv/BV1qs411L7e6) https://b23.tv/BV1qs411L7e6

如用于学习，可自行去STC官网下载STC12系列的芯片手册。


### 作品简介
1. 电路板:电路图的设计，pcb板的绘制都是由我们自行完成，交由专业厂家打烊，制作成如今的成品。整个作品电源降压、升压部分也特别多，也是一个大工程。

2. 使用价格低廉的51系列主控，对硬件合理的分配及算法的优化，最大程度的挖掘硬件的性能。

3. 控制:使用手机端的app连接机械臂清障车的蓝牙，通过手机蓝牙给控制板发送指令，使之执行特定的动作。

4. 机械臂:使用模拟的六路pwm，并作用独特的联动算法，所有舵机的角度由程序自动计算然后分配，无需人工，使得控制机械臂的时候变得十分简单。

5. 主控控制步进升降:为了增强步进电机的扭力，使用了步进电机驱动器。主控芯片给步进电机驱动器一定的脉冲，从而使信号放大驱动步进电机。

6. 车轮:使用pwm信号并使用光耦隔离驱动多mos管输出大电流以保证底盘四个555电机的正常工作。程序中内置加速减速控制，可实时调车速，保证不同路况的安全运行。使用左右轮差速的方案使得车体在最小的空间中也能完成转向。

7. 水泵和扫帚:使用类似车轮的控制mos管的方案驱动水泵或减速电机。（可调速控制）

8. 车体测边的垃圾箱:使用一个舵机控制车体侧边的垃圾箱收放。

9. 铲斗使用一个舵机完成前后来回铲。

10. 红外功能:为保证安全，车前装有一个红外传感器，当前方有墙之类的障碍使系统自动让车体制动，避免发生意外。

11. LED灯:为适应清障车夜间工作，额外添加了大功率led灯，此led可以实时调整亮度。

12. 远程图像回传摄像头:通过对普通路由器的改装，并刷入基于linux系统的openwrt系统，使日常电脑用的摄像头能够连接路由器，并且使用电脑或者手机浏览器登入查看实时监控。（登入地址http://192.168.1.1:8080/?action=stream）

#### 文件结构
* WreckerCarPCB_Project _（清障车的电路工程文件 AD17绘制）_
* WreckerCar_Code _（清障车的51控制代码 MDK5工程）_
* StructuralDraw _（清障车的solidwork2016结构工程）_
* Image _（实物图片）_
* 多功能消防清障车说明书.doc _（中日韩2017比赛时提交的作品说明书）_
	
#### PCB 3D预览图

![](https://gitee.com/ClimbSnailQ/Project_Image/raw/master/OtherProject/WreckerCar_PCB3D.png)

![WreckerCar_PCB3D.png](./Image/WreckerCar_PCB3D.png)

![](https://gitee.com/ClimbSnailQ/Project_Image/raw/master/OtherProject/WreckerCar_PCD_TOP.png)

![WreckerCar_PCD_TOP.png](./Image/WreckerCar_PCD_TOP.png)

#### 电路存在的问题
	1. 车轮使用的是四个555电机，TB6612不足以驱动（一片TB6612驱一个555时供电不到3s TB6612烧炸）
	2. 由于电机驱动问题，最后另外买了网上现成的驱动板（不用板载的TB6612驱动）。
	3. 铲斗用的步进驱动从原来的A4988改为了TB6600驱动器。

#### 关于代码问题
	1. 之前预计着添加OLED屏幕，调试的过程中烧坏了，最终决定舍弃。


