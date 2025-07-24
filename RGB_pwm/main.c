#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "app_error.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "app_pwm.h"
#include "nrf_drv_gpiote.h"

#define button 25
#define redled 22
#define micro_power_ctrl 18

int brightness=0, d=-25;

APP_PWM_INSTANCE(PWM1,1);                   // Create the instance "PWM1" using TIMER1.

void in_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    if(brightness==100 || brightness==0)d=-d;
    brightness+=d;
}
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
int main(void)
{
    nrf_gpio_cfg_output(micro_power_ctrl);
    nrf_gpio_pin_set(micro_power_ctrl);
    nrf_gpio_cfg_input(button,NRF_GPIO_PIN_PULLDOWN);

    ret_code_t err_code;
    gpio_init();
    /* 1-channel PWM, 200Hz, output on DK LED pins. */
    app_pwm_config_t pwm1_cfg = APP_PWM_DEFAULT_CONFIG_1CH(5000L, redled);

    /* Initialize and enable PWM. */
    err_code = app_pwm_init(&PWM1,&pwm1_cfg,NULL);
    APP_ERROR_CHECK(err_code);
    app_pwm_enable(&PWM1);

    while (true)
    {

            while (app_pwm_channel_duty_set(&PWM1, 0, (100-brightness)) == NRF_ERROR_BUSY);

    }

}


/** @} */
