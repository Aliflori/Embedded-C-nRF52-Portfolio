
#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"
#include "boards.h"
#include "bsp.h"

#define redled 22
#define greenled 17 // blue and green are misplacaed.
#define blueled 23
#define button 25

#define micro_power_ctrl 18

enum color_t {R ,G ,B} color = R;

void in_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
switch (color) 
              {
              case R:     nrf_gpio_pin_set(redled); nrf_gpio_pin_clear(greenled); nrf_gpio_pin_clear(blueled); color = G; break;
              case G:     nrf_gpio_pin_clear(redled); nrf_gpio_pin_set(greenled); nrf_gpio_pin_clear(blueled); color = B; break;
              default:    nrf_gpio_pin_clear(redled); nrf_gpio_pin_clear(greenled); nrf_gpio_pin_set(blueled); color = R; break;
              }
}
/**
 * @brief Function for configuring: PIN_IN pin for input, PIN_OUT pin for output,
 * and configures GPIOTE to give an interrupt on pin change.
 */
static void gpio_init(void)
{
    ret_code_t err_code;

    err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);


    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_LOTOHI(true);
    in_config.pull = NRF_GPIO_PIN_PULLDOWN;

    err_code = nrf_drv_gpiote_in_init(button, &in_config, in_pin_handler);
    APP_ERROR_CHECK(err_code); 

    nrf_drv_gpiote_in_event_enable(button, true);
}

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    nrf_gpio_cfg_output(redled);
    nrf_gpio_cfg_output(greenled);
    nrf_gpio_cfg_output(blueled);
    nrf_gpio_cfg_input(button,NRF_GPIO_PIN_PULLDOWN);

    nrf_gpio_cfg_output(micro_power_ctrl);
    nrf_gpio_pin_set(micro_power_ctrl);

    gpio_init();

    while (true)
    {
        // Do nothing.
    }
}


/** @} */
