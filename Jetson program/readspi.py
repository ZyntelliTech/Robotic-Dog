import spidev
import time

def send_data_via_spi(data, bus, device):
    spi = spidev.SpiDev()
    spi.open(bus, device)
    spi.max_speed_hz = 1000000

    # 转换输入数据为整数列表
    data = [int(x, 16) for x in data.split()]

    # 发送数据
    spi.xfer(data)

    # 关闭SPI设备
    spi.close()

# 打开包含数组的文本文件
with open('arrays.txt', 'r') as file:
    # 逐行读取文件
    for line in file:
        # 去除行末尾的换行符
        line = line.rstrip()

        # 发送数据到 SPI 设备 0.0
        send_data_via_spi(line, 0, 0)

        # 发送数据到 SPI 设备 2.0
        send_data_via_spi(line, 2, 0)

        # 添加10毫秒的延迟
        time.sleep(0.01)