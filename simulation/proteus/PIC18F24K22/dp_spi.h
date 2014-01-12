#ifndef DP_SPI_H
#define DP_SPI_H

#include <spi.h>
#include <stdint.h>

void spi_initialize();
uint8_t spi_tranceive(uint8_t value);

#endif // DP_SPI_H
