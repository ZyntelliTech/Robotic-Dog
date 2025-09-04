#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include "SPI.h"
#include "cybergear.h"
#define SPI_DEVICE_PATH_0 "/dev/spidev0.0"  // SPI 0.0设备路径
#define SPI_DEVICE_PATH_2 "/dev/spidev2.0"  // SPI 2.0设备路径
#define DATA_LENGTH 12  // 待发送和接收数据的长度
#define DELAY_SECONDS 1  // 延迟秒数

int spi_fd_0, spi_fd_2;
   
unsigned char rx_buffer[DATA_LENGTH];  // 接收数据的缓冲区
struct spi_ioc_transfer spi_msg;
unsigned int spi_speed_hz = 1000000;  // SPI时钟频率
unsigned char spi_mode = SPI_MODE_0;  // SPI模式
unsigned char spi_bits_per_word = 8;  // 每个字的位数


int SPI_inti() {
    

    // 打开SPI 0.0设备
    spi_fd_0 = open(SPI_DEVICE_PATH_0, O_RDWR);
    if (spi_fd_0 < 0) {
        perror("Failed to open SPI 0.0 device");
        return -1;
    }

    // 打开SPI 2.0设备
    spi_fd_2 = open(SPI_DEVICE_PATH_2, O_RDWR);
    if (spi_fd_2 < 0) {
        perror("Failed to open SPI 2.0 device");
        close(spi_fd_0);
        return -1;
    }

    // 配置SPI 0.0设备
    if (ioctl(spi_fd_0, SPI_IOC_WR_MODE, &spi_mode) < 0) {
        perror("Failed to set SPI 0.0 mode");
        close(spi_fd_0);
        close(spi_fd_2);
        return -1;
    }

    if (ioctl(spi_fd_0, SPI_IOC_WR_BITS_PER_WORD, &spi_bits_per_word) < 0) {
        perror("Failed to set SPI 0.0 bits per word");
        close(spi_fd_0);
        close(spi_fd_2);
        return -1;
    }

    if (ioctl(spi_fd_0, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed_hz) < 0) {
        perror("Failed to set SPI 0.0 speed");
        close(spi_fd_0);
        close(spi_fd_2);
        return -1;
    }

    // 配置SPI 2.0设备
    if (ioctl(spi_fd_2, SPI_IOC_WR_MODE, &spi_mode) < 0) {
        perror("Failed to set SPI 2.0 mode");
        close(spi_fd_0);
        close(spi_fd_2);
        return -1;
    }

    if (ioctl(spi_fd_2, SPI_IOC_WR_BITS_PER_WORD, &spi_bits_per_word) < 0) {
        perror("Failed to set SPI 2.0 bits per word");
        close(spi_fd_0);
        close(spi_fd_2);
        return -1;
    }

    if (ioctl(spi_fd_2, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed_hz) < 0) {
        perror("Failed to set SPI 2.0 speed");
        close(spi_fd_0);
        close(spi_fd_2);
        return -1;
    }
    return 0;
}

void sendSPIData(uint8_t identifier, uint8_t spi_buffer[])
{
        spi_msg.tx_buf = (unsigned long)spi_buffer;
        spi_msg.rx_buf = (unsigned long)rx_buffer;
    switch (identifier)
    {
    case 0:
 
        spi_msg.len = DATA_LENGTH;
        if (ioctl(spi_fd_0, SPI_IOC_MESSAGE(1), &spi_msg) < 0) {
            perror("Failed to send/receive SPI 0.0 message");
            close(spi_fd_0);
            close(spi_fd_2);
        }
        // 打印SPI 0.0接收到的数据
        printf("Received data from SPI 0.0: ");
        for (int i = 0; i < DATA_LENGTH; i++) {
            printf("%02x ", rx_buffer[i]);
        }
        printf("\n");
        break;
    
    case 2:
        spi_msg.len = DATA_LENGTH;
        if (ioctl(spi_fd_2, SPI_IOC_MESSAGE(1), &spi_msg) < 0) {
            perror("Failed to send/receive SPI 0.0 message");
            close(spi_fd_0);
            close(spi_fd_2);
        }
            printf("Received data from SPI 2.0: ");
        for (int i = 0; i < DATA_LENGTH; i++) {
            printf("%02x ", rx_buffer[i]);
        }
        printf("\n");
        
        break;
        }
        
    }
    

void SPI_Deinti()
{
    close(spi_fd_0);
    close(spi_fd_2);
}
