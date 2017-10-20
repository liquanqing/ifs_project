/**
  ******************************************************************************
  * @file   drv_led.c
  * @author  Inc
  * @version V0.0.1
  * @date    2-7-2017
  * @brief   This Module Is Use To Driver The LED On Board
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
/*
 * !brief include header
 */

#include "ifs_lib.h"
#include "drv_led.h"


#ifndef NULL
#define NULL ((void *)0)
#endif

/*
 * !brief user define
 */
#define LED_USER1_PORT  IFS_GPIOJ
#define LED_USER1_PIN   5

#define LED_USER2_PORT  IFS_GPIOJ
#define LED_USER2_PIN   13

/*
 * !brief All LED Init
 * !param None
 * !retval None
 */
void hw_led_init(void)
{
    ifs.gpio.init(LED_USER1_PORT);
    ifs.gpio.config_pin(LED_USER1_PORT, 
                        LED_USER1_PIN, 
                        IFS_GPIO_OUT_PP);
    ifs.gpio.init(LED_USER2_PORT);
    ifs.gpio.config_pin(LED_USER2_PORT, 
                        LED_USER2_PIN, 
                        IFS_GPIO_OUT_PP);
}

/*
 * !brief LED Set High
 * !param LED ID
 * !retval None
 */
void led_set(uint32_t led_user)
{
    if (led_user & LED_USER1) {
        ifs.gpio.set(LED_USER1_PORT, LED_USER1_PIN);
    }
    if (led_user & LED_USER2) {
        ifs.gpio.set(LED_USER2_PORT, LED_USER2_PIN);
    }
}
                                          
/*
 * !brief LED Set Low
 * !param LED ID
 * !retval None
 */
void led_reset(uint32_t led_user)
{
    if (led_user & LED_USER1) {
        ifs.gpio.clear(LED_USER1_PORT, LED_USER1_PIN);
    }
    if (led_user & LED_USER2) {
        ifs.gpio.clear(LED_USER2_PORT, LED_USER2_PIN);
    }
}


/*
 * !brief LED Toggle
 * !param LED ID
 * !retval None
 */
void led_toggle(uint32_t led_user)
{
    if (led_user & LED_USER1) {
        ifs.gpio.toggle(LED_USER1_PORT, LED_USER1_PIN);
    }
    if (led_user & LED_USER2) {
        ifs.gpio.toggle(LED_USER2_PORT, LED_USER2_PIN);
    }
}


/******************************End Of File(INC)***********************************/

