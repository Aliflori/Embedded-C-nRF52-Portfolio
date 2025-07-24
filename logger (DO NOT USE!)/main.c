#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nordic_common.h"
#include "boards.h"
#include "nrf_delay.h"

// Must include these headers to work with nrf logger
#include "nrf_log.h"
#include "nrf_log_default_backends.h"
#include "nrf_log_ctrl.h"



/**
 * @brief Function for application main entry.
 */

uint32_t count = 0;

int main(void)
{
    nrf_gpio_cfg_output(22);
// Initialize the Logger module and check if any error occured during initialization
   // APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
	
// Initialize the default backends for nrf logger
   // NRF_LOG_DEFAULT_BACKENDS_INIT();

// print the log msg over uart port
   // NRF_LOG_INFO("This is log data from nordic device..");
    printf("This is log data from nordic device..");


    while (true)
    {	// Dsiplay the logger info with variable
        // NRF_LOG_INFO("Counter Value: %d", count);
        printf("Counter Value: %d", count);
        nrf_gpio_pin_set(22);
        nrf_delay_ms(500); // delay for 500 ms
        count++; // increment the counter by 1
    }
}
/** @} */
