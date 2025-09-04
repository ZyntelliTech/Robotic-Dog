#include "main.h"
#include <stdint.h>

int SPI_inti();
void sendSPIData(uint8_t identifier, uint8_t spi_buffer[]);
void SPI_Deinti();