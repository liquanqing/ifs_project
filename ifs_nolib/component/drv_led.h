/**
  ******************************************************************************
  * @file    drv_led.h
  * @author  Inc
  * @version V0.0.1
  * @date    2-7-2017
  * @brief   This File Is The Header For drv_led.c
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  * @Modify:
  ******************************************************************************
  */
#ifndef __DRV_LED_H
#define __DRV_LED_H
/*
 * include header
 */

/*
 * !brief export typedef                                   
 */
#define LED_USER1    0x01  
#define LED_USER2    0x02

/*
 * !brief export function                                  
 */
void hw_led_init(void);
void led_set(uint32_t led_user);
void led_reset(uint32_t led_user);
void led_toggle(uint32_t led_user);


#endif
/******************************End Of File(INC)***********************************/




