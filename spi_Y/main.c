#include "nrf_drv_spi.h"
#include "app_util_platform.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "boards.h"
#include "app_error.h"
#include <string.h>
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define redled 22
#define greenled 17 // blue and green are misplacaed.
#define blueled 23
#define button 25

#define SPI_INSTANCE  0 /**< SPI instance index. */
static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE);  /**< SPI instance. */
//static volatile bool spi_xfer_done;  /**< Flag used to indicate that SPI instance completed the transfer. */


/**
 * @brief SPI user event handler.
 * @param event
 */



#define RREG 0x80
#define WREG 0x7F
#define SPI_BUFSIZE 8*3*9
#define CS_PIN NRF_GPIO_PIN_MAP(0,11)

uint8_t spi_tx_buf[SPI_BUFSIZE]={1,2,3};
uint8_t spi_rx_buf[SPI_BUFSIZE];
char dataout1[5]={0};

/**
*the function for writing a value to a register:
**/
static void adsWreg (uint8_t reg, uint8_t val)
{
  uint8_t var[2];
  //nrf_delay_ms(1);
  //see pages 40,43 of datasheet
  //nrf_gpio_pin_clear(CS_PIN);
  var[0] = (WREG & reg);
  var[1] = val;
  while(nrf_drv_spi_transfer(&spi,var,2,NULL,0) != NRF_SUCCESS){}
  //nrf_delay_ms(1);
  //nrf_gpio_pin_set(CS_PIN);
}


/**
*the function for reading a value from a register:
**/
int adsRreg(int reg)
{
  uint8_t out = 0;
  uint8_t var;
  var = (RREG | reg);
  //nrf_gpio_pin_clear(CS_PIN);
  dataout1[0] = var;

  var = 0;
  dataout1[1] = 0x00;
  dataout1[2] = 0xFF;

  while(nrf_drv_spi_transfer(&spi,dataout1,2,spi_rx_buf,2) != NRF_SUCCESS){}
  //nrf_delay_ms(1);
  //nrf_gpio_pin_set(CS_PIN);
  return((int) spi_rx_buf[1]);

}

void adsBootup(void)
{
  nrf_delay_ms(2500);
  nrf_gpio_cfg_output(CS_PIN);
  nrf_gpio_pin_set(CS_PIN);
}


void spi_event_handler(nrf_drv_spi_evt_t const * p_event,
                       void *                    p_context)
{

}
void spi_init(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
    spi_config.ss_pin   = 6;
    spi_config.miso_pin = 3;
    spi_config.mosi_pin = 2;
    spi_config.sck_pin  = 4;
    APP_ERROR_CHECK(nrf_drv_spi_init(&spi, &spi_config, spi_event_handler, NULL));

}

int main(void)
{
    spi_init();
    adsBootup();
    nrf_gpio_cfg_output(greenled);

    
    

    while (1)
    {
        nrf_gpio_pin_toggle(greenled);
        nrf_delay_ms(1000);
        adsWreg(0x21,0x02);
        int value = adsRreg(0x21);
        printf("value is %d\r\n",value);
       
    }
}
