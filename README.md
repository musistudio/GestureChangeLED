## 基于Arduino与APSD9960传感器的手势改变RGB灯小例子

#### 1. 所需材料

Arduino uno开发板 * 1

APSD9960传感器 * 1

共阳RGB灯 若干

电阻 若干

#### 2. 使用方法

克隆本项目到本地，把APDS_Library文件夹复制到arduino的libraries文件夹下，打开 **GestureTest.ino**文件并且编译一下看看是否通过。编译通过后上传到arduino开发板

#### 3. 硬件连接方式

| Arduino Pin | APDS-9960 Board | Function  |
| ----------- | --------------- | --------- |
| 3.3V        | VCC             | Power     |
| GND         | GND             | Ground    |
| A4          | SDA             | I2C Data  |
| A5          | SCL             | I2C Clock |
| 2           | INT             | Interrupt |

| Arduino Pin | RGB   |
| ----------- | ----- |
| 3.3v        | Vcc   |
| 9           | Red   |
| 6           | Blue  |
| 5           | Green |

硬件连接好后就可以进行测试了，demo还在制作中。