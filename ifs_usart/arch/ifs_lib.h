/**
  ******************************************************************************
  * @file    inc_lib.h
  * @author  Inc
  * @version VV0.0.1
  * @date    2017-08-06
  * @brief   Lib Header
  ******************************************************************************
  * @modify
  *
  ******************************************************************************
  */
#ifndef __INC_LIB_H
#define __INC_LIB_H

#define STM32F769

#include "ifs.h"
#ifdef STM32F769
#include "stm32f7xx.h"
#include "./stm32f7/bsp/sys.h"

#if INC_USING_IFS_GPIO
#include "./stm32f7/bsp/gpio.h"
#endif

#if INC_USING_IFS_USART
#include "./stm32f7/bsp/usart.h"
#endif

#endif

#if INC_USING_IFS
extern const ifs_info_t ifs;
#endif

#endif
/******************************End Of File(INC)*********************************/

