/**
  ******************************************************************************
  * @file    ifs.c
  * @author  Inc
  * @version VV0.0.1
  * @date    2017-08-06
  * @brief   Source Lib For Interface
  ******************************************************************************
  * @modify
  *
  ******************************************************************************
  */

#include "ifs_lib.h"
#if INC_USING_IFS

const ifs_info_t ifs = {
#if INC_USING_IFS_GPIO
    {
        .init       = gpio_init,
        .deinit     = gpio_deinit,
        .config_pin = gpio_config_pin,
        .set        = gpio_set,
        .clear      = gpio_clear,
        .toggle     = gpio_toggle,
        .out        = gpio_out,
        .in         = gpio_in,
        .get        = gpio_get,
    },
#if INC_USING_IFS_USART
    {
        .init       = usart_init,    
        .deinit     = usart_deinit,
        .config     = usart_config,
        .put        = usart_put,
        .get        = usart_get,
        .tx_ready   = usart_rx_ready,
        .rx_ready   = usart_rx_ready,
    },
#endif
#endif
};
#endif
/******************************End Of File(INC)*********************************/

