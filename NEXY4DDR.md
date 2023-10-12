# Basic

HomePage：https://digilent.com/reference/programmable-logic/nexys-4-ddr/start

Reference Manual：https://digilent.com/reference/programmable-logic/nexys-4-ddr/reference-manual

# Component

![Alt text](./image/component.png)

![Alt text](./image/component_description.png)

## Jumper
- 跳线，可以手动切换从而改变
- 必须在断电的状态下进行切换

### JP1
- 控制编程模式（JTAG / SPI / USB）

### JP2
- 控制外部配置（USB / SD）
- 似乎是 JP1 的辅助

### JP3 
- 控制电源输入来源
- 默认是 USB-JTAG 接口
- 还可以使用外部电源 / 外部电池组

## Configuration Way
### USB-JTAG 电路
- 也就是我们用的，电脑连线 vivado 传 bit

### SPI 端口传输
- 同样是通过 vivado，但传到非易失性闪存器件
- 断电后只要重新上电就会自动复位，无需再次传送 bit
- 写非常慢 (4-5min)，但是配置非常快 (1s)

### Micro SD Card
- FAT32 文件系统，单个 .bit 文件放在根目录中
- 可以自动读取
- 插槽在板子背面 (J1)

### USB
- 和 Micro SD Card 的前两点一致
- 插槽是 USB HOST (J5)

### Memory
- 128MiB 的 DDR2 SDRAM，可以通过官网提供的 DDR-to-SRAM adapter module 方便交互，也有更复杂的写法
- 16MiB 的 non-volatile serial Flash device，对应前面说的 SPI 端口传输

### USB-UART Bridge
- 待研读，关于数据传输可能性

### USB HID Host
- Hub support is not currently available，只能用单键盘 / 鼠标

### KeyBoard
[图片]
- 每个按键都被分配了一个唯一的代码，每次按键时发送代码
- 长按时大约每 100ms 重复发送一次
- 待研读

### Mouse
- 待研读

### Tri-Color LED
- LD16 LD17 是两个支持红绿蓝三色输入的 LED
- 建议使用 PWM（这是啥？待研读）