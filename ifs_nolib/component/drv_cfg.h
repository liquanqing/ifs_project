/**
  ******************************************************************************
  * @file    drv_cfg.h
  * @author  Inc
  * @version V0.0.1
  * @date    2-7-2017
  * @brief   This File has configure the drivers which will need to use;
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  * @Modify:
  ******************************************************************************
  */
#ifndef __DRV_CFG_H
#define __DRV_CFG_H
/*
 * include header
 */
#if defined(USE_HAL_DRIVER)
#include "stm32f7xx_hal.h"
#endif

/* USE DEVICE */
#define INC_USE_DRV_LED


#ifdef INC_USE_DRV_LED
/*
 * !brief device header
 */
#include "drv_led.h"

#define INC_USE_DRV_LED_USER1
#define INC_USE_DRV_LED_USER2

#endif

#endif
/******************************End Of File(INC)***********************************/




