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

#include "ifs.h"

#if INC_USING_IFS_GPIO
#include "./cpu/stm32f7/gpio.h"
#endif

#if INC_USING_IFS_USART
#include "./cpu/stm32f7/usart.h"
#endif

#if INC_USING_IFS
extern const ifs_info_t ifs;
#endif

#endif
/******************************End Of File(INC)*********************************/

