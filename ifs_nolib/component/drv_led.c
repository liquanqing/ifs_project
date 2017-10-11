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

#include "drv_cfg.h"
#include "ifs_lib.h"

#ifdef INC_USE_DRV_LED



#ifndef NULL
#define NULL ((void *)0)
#endif

/*
 * !brief user define
 */
#ifdef INC_USE_DRV_LED_USER1
#define RCC_LED_USER1_EN()  do{__HAL_RCC_GPIOJ_CLK_ENABLE();}while(0)
#define LED_USER1_PORT  PORTJ
#define LED_USER1_PIN   5
#endif

#ifdef INC_USE_DRV_LED_USER2
#define RCC_LED_USER2_EN()  do{__HAL_RCC_GPIOJ_CLK_ENABLE();}while(0)
#define LED_USER2_PORT  PORTJ
#define LED_USER2_PIN   13
#endif

/*
 * !brief All LED Init
 * !param None
 * !retval None
 */
void hw_led_init(void)
{
#ifdef INC_USE_DRV_LED_USER1
    ifs.gpio.init(LED_USER1_PORT);
    ifs.gpio.config_pin(LED_USER1_PORT, 
                        LED_USER1_PIN, 
                        IFS_GPIO_MODE_OUTPUT | IFS_GPIO_SPEED_HIGH | IFS_GPIO_OTYPE_PP | IFS_GPIO_PUPD_NOPUPD);
#endif
#ifdef INC_USE_DRV_LED_USER2
    ifs.gpio.init(LED_USER2_PORT);
    ifs.gpio.config_pin(LED_USER2_PORT, 
                        LED_USER2_PIN, 
                        IFS_GPIO_MODE_OUTPUT | IFS_GPIO_SPEED_HIGH | IFS_GPIO_OTYPE_PP | IFS_GPIO_PUPD_NOPUPD);
#endif
}

/*
 * !brief LED Set High
 * !param LED ID
 * !retval None
 */
void led_set(uint32_t led_user)
{
#ifdef INC_USE_DRV_LED_USER1
    if (led_user & LED_USER1) {
#if defined(USE_HAL_DRIVER)
        ifs.gpio.set(LED_USER1_PORT, LED_USER1_PIN);
#endif
    }
#endif
#ifdef INC_USE_DRV_LED_USER2
    if (led_user & LED_USER2) {
#if defined(USE_HAL_DRIVER)
        ifs.gpio.set(LED_USER2_PORT, LED_USER2_PIN);
#endif
    }
#endif
}
                                          
/*
 * !brief LED Set Low
 * !param LED ID
 * !retval None
 */
void led_reset(uint32_t led_user)
{
#ifdef INC_USE_DRV_LED_USER1
    if (led_user & LED_USER1) {
#if defined(USE_HAL_DRIVER)
        ifs.gpio.clear(LED_USER1_PORT, LED_USER1_PIN);
#endif
    }
#endif
#ifdef INC_USE_DRV_LED_USER2
    if (led_user & LED_USER2) {
#if defined(USE_HAL_DRIVER)
        ifs.gpio.clear(LED_USER2_PORT, LED_USER2_PIN);
#endif
    }
#endif
}


/*
 * !brief LED Toggle
 * !param LED ID
 * !retval None
 */
void led_toggle(uint32_t led_user)
{
#ifdef INC_USE_DRV_LED_USER1
    if (led_user & LED_USER1) {
#if defined(USE_HAL_DRIVER)
        ifs.gpio.toggle(LED_USER1_PORT, LED_USER1_PIN);
#endif
    }
#endif
#ifdef INC_USE_DRV_LED_USER2
    if (led_user & LED_USER2) {
#if defined(USE_HAL_DRIVER)
        ifs.gpio.toggle(LED_USER2_PORT, LED_USER2_PIN);
#endif
    }
#endif
}

#endif /* ifdef INC_USE_DRV_LED */

/******************************End Of File(INC)***********************************/

