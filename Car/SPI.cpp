#include "SPI.h"
#include "global.h"

SPI::SPI()
{
    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
    }

    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failedg. Are you running as root??\n");
    }
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256); // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
}

void SPI::send_read(int8_t * spiOut_, int8_t * spiIn_)	
{

	for(int8_t i = 0; i< 7; i++)
	{
		spiIn_[i] = bcm2835_spi_transfer(spiOut_[i]);
	}
}

