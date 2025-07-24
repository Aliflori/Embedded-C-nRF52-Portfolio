#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "string.h"
#include "nrf_gpio.h"
#include "app_uart.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf.h"
#include "nrf_drv_twi.h"

#include "app_timer.h"
#include "nrf_drv_clock.h"


#include "nrf_uart.h"

#include "ssd_lcd_By_Naghiloo.c"


#define redled 22
#define greenled 17 // blue and green are misplacaed.
#define blueled 23
#define micro_power_ctrl 18
#define empty 0


//#define ENABLE_LOOPBACK_TEST  /**< if defined, then this example will be a loopback test, which means that TX should be connected to RX to get data loopback. */

#define UART_TX_BUF_SIZE 8                         /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE 8                         /**< UART RX buffer size. */

char in_text [100] = {};
char out_text [100] = {};
//-------------------------------- Timer -------------------------------------------

int sec = 0;
int min = 0;


// use a function to calculate the number of tick needed to 
// create a delay of 1000 millisec and store this value in INTERVAL constant
#define INTERVAL APP_TIMER_TICKS(1000)

// For each application timer we need to create a handle which points to that instance
// so for evey application timer (Software timer) you create, you need to define a handle
// create a handle and name it as:  m_app_timer_id 
APP_TIMER_DEF(m_app_timer_id);



// its really important to initialize the clock other wise the app timer will not work
// so make sure you initialize it once in your code and if you are using a soft device
// then you don't need to initialize the clock as the soft device automatically initializes it.
static void lfclk_config(void)
{
	// initialize the low power low frequency clock
  ret_code_t err_code = nrf_drv_clock_init();
  APP_ERROR_CHECK(err_code);

	// request the lf clock to not to generate any events on ticks
	// One tick =  1 value increment in the counter register
  nrf_drv_clock_lfclk_request(NULL);

}




bool flag = true;

// create a simple handler function which will be called once the timer reaches its 
// desired number of ticks value
static void app_timer_handler(void * p_context)
{
        char temp[100];
        sec++;
        if(sec == 60){
        sec = 0;
        min++;                    
}

        if (strcmp(&in_text,"clock") == 0)
            {
                if(flag)
                {
                flag = false;
                LCD_Clear();
                nrf_gpio_pin_clear(redled);
                nrf_gpio_pin_clear(blueled);
                nrf_gpio_pin_clear(greenled);
                }

                draw(38,3,digit(min/10));           
                draw(51,3,digit(min%10));
                draw(64,3,colon);              
                draw(77,3,digit(sec/10));
                draw(90,3,digit(sec%10));

                nrf_gpio_pin_toggle(redled);
                nrf_gpio_pin_toggle(blueled);
                nrf_gpio_pin_toggle(greenled);
            }

sprintf(&temp, "%d:%d\n",min,sec);
uart_put_str(temp);



}



// a function to initialize the Application timers
static void timers_init(void)
{
	// a variable to hold error value
    ret_code_t err_code;

	// Initialize the timer 
    err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

	// Create an application timer with the handle, mode and interrupt event handle function
    err_code = app_timer_create(&m_app_timer_id, APP_TIMER_MODE_REPEATED, app_timer_handler);
    APP_ERROR_CHECK(err_code);

}

//----------------------------------------------------------------------------------

void uart_error_handle(app_uart_evt_t * p_event)
{
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
}


/**
 * @brief TWI events handler.
 */
void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            m_xfer_done = true;
            break;
        default:
            break;
    }
}
/**
 * @brief TWI initialization.
 */
void twi_init (void)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_config = {
       .scl                = TWI_SCL_SSD,
       .sda                = TWI_SDA_SSD,
       .frequency          = NRF_DRV_TWI_FREQ_400K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi);
}



/**
 * @brief Function for main application entry.
 */

int main(void)
{
    twi_init();
    LCD_init();

    nrf_gpio_cfg_output(redled);
    nrf_gpio_cfg_output(greenled);
    nrf_gpio_cfg_output(blueled);
    nrf_gpio_cfg_output(micro_power_ctrl);
    nrf_gpio_pin_set(micro_power_ctrl);

    uint32_t err_code;



    const app_uart_comm_params_t comm_params =
      {
          7,
          11,
          empty,
          empty,
          APP_UART_FLOW_CONTROL_DISABLED,
          false,
          NRF_UART_BAUDRATE_115200
      };

    APP_UART_FIFO_INIT(&comm_params,
                         UART_RX_BUF_SIZE,
                         UART_TX_BUF_SIZE,
                         uart_error_handle,
                         APP_IRQ_PRIORITY_LOWEST,
                         err_code);

    APP_ERROR_CHECK(err_code);
  

// call the function to initialize the clock
    lfclk_config();
// initialize the timer by calling this function which is performing all the basic steps
    timers_init();

// start the timer so that it can generate events on the desired tick value
    err_code = app_timer_start(m_app_timer_id, INTERVAL, NULL);

    while (true)
    {
            
            uart_get_str(&in_text,true,false);

            if (strcmp(&in_text,"red") == 0)
            {
                nrf_gpio_pin_set(redled);
                nrf_gpio_pin_clear(blueled);
                nrf_gpio_pin_clear(greenled);
                draw(0,0,redimage);
            } 

            if (strcmp(&in_text,"blue") == 0)
            {
                nrf_gpio_pin_clear(redled);
                nrf_gpio_pin_set(blueled);
                nrf_gpio_pin_clear(greenled);
                draw(0,0,blueimage);
            }

            if (strcmp(&in_text,"green") == 0)
            {
                nrf_gpio_pin_clear(redled);
                nrf_gpio_pin_clear(blueled);
                nrf_gpio_pin_set(greenled);
                draw(0,0,greenimage);
            }
             
            if(strcmp(&in_text,"clock") != 0)
                flag = true;
                

              
    }
}


/**
 * @brief Function for main application entry.
 */





