#include <stdbool.h>
#include <stdint.h>
#include "nrf_gpio.h"

#define redled 22
#define greenled 17 // blue and green are misplacaed.
#define blueled 23
#define button 25
#define micro_power_ctrl 18

int btnPressed = 0;
bool flag = true;
enum color_t {R ,G ,B} color = R;

int main(void)
{
    nrf_gpio_cfg_output(redled);
    nrf_gpio_cfg_output(greenled);
    nrf_gpio_cfg_output(blueled);
    nrf_gpio_cfg_input(button,NRF_GPIO_PIN_PULLDOWN);

    nrf_gpio_cfg_output(micro_power_ctrl);
    nrf_gpio_pin_set(micro_power_ctrl);

    while(true)
    {
      btnPressed = nrf_gpio_pin_read(button);
        if(nrf_gpio_pin_read(button) == 1)
        {
           if(flag)
           {switch (color) 
              {
              case R:     nrf_gpio_pin_set(redled);   nrf_gpio_pin_clear(greenled); nrf_gpio_pin_clear(blueled); color = G; break;
              case G:     nrf_gpio_pin_clear(redled); nrf_gpio_pin_set(greenled);   nrf_gpio_pin_clear(blueled); color = B; break;
              default:    nrf_gpio_pin_clear(redled); nrf_gpio_pin_clear(greenled); nrf_gpio_pin_set(blueled);   color = R; break;
              }
            flag=false;} 
        
        }else{flag=true;}
    }
}