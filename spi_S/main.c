
#include "nrf_drv_spi.h"
#include "app_util_platform.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "boards.h"
#include "app_error.h"
#include <string.h>

#define ledred 22

#define SPI_INSTANCE  0 /**< SPI instance index. */
static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE);  /**< SPI instance. */
static volatile bool spi_xfer_done;  /**< Flag used to indicate that SPI instance completed the transfer. */

/**
 * @brief SPI user event handler.
 * @param event
 */

 void spi_event_handler(nrf_drv_spi_evt_t const * p_event,void * p_context)
{
    spi_xfer_done = true;
}

 void spi_init(void)
{
    nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;

    spi_config.ss_pin   = 6;
    spi_config.miso_pin = 3;
    spi_config.mosi_pin = 2;
    spi_config.sck_pin  = 4;
    spi_config.frequency = NRF_DRV_SPI_FREQ_8M;
    spi_config.mode = NRF_DRV_SPI_MODE_0;
    spi_config.bit_order = NRF_DRV_SPI_BIT_ORDER_MSB_FIRST;

    APP_ERROR_CHECK(nrf_drv_spi_init(&spi, &spi_config, spi_event_handler, NULL)); 
}


#define SPI_BUFSIZE 8*3*9
#define CS_PIN NRF_GPIO_PIN_MAP(0,11)

uint8_t spi_tx_buf[SPI_BUFSIZE]={0};
uint8_t spi_rx_buf[SPI_BUFSIZE];
char dataout1[2]={0};

/**
*the function for writing a value to a register:
**/
static void adsWreg (uint8_t reg, uint8_t val)
{ printf("write\r\n");
  uint8_t var[2];
  var[0] = reg & ~(1 << 7);
  var[1] = val;
  //while(nrf_drv_spi_transfer(&spi,&var,2,&spi_rx_buf,2) != NRF_SUCCESS){printf("write\r\n");}
  printf("write\r\n");

}


/**
*the function for reading a value from a register:
**/
int adsRreg(int reg)
{ printf("read\r\n");
  uint8_t out = 0;
  uint8_t var;
  var = reg | (1 << 7);
  dataout1[0] = var;


 // while(nrf_drv_spi_transfer(&spi,&dataout1,2,&spi_rx_buf,2) != NRF_SUCCESS){printf("read\r\n");}
  printf("read\r\n");
  return((int) spi_rx_buf[1]);
}

void adsBootup(void)
{
  nrf_delay_ms(2500);
  nrf_gpio_cfg_output(CS_PIN);
  nrf_gpio_pin_set(CS_PIN);
}


int main(void)
{
    spi_init();
    adsBootup();
    nrf_gpio_cfg_output(ledred);

    while (1)
    {
      nrf_gpio_pin_toggle(ledred);
      printf("read\r\n");
      adsWreg(0x21,0x4);
      printf("read\r\n");
      int val = adsRreg(0x21);
      printf("value: %d\r\n",val);
      nrf_delay_ms(500);

    }
}
