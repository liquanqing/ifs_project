/**
  ******************************************************************************
  * @file    inc_ifs.h
  * @author  inc
  * @version VV0.0.1
  * @date    2017-08-06
  * @brief   Interface Header File
  ******************************************************************************
  * @modify
  *
  ******************************************************************************
  */
#ifndef __IFS_H
#define __IFS_H

#include "base_type.h"
#include "lib_config.h"

#if INC_USING_IFS_GPIO

struct _ifs_gpio_t {
    ifs_err_t (*init)(uint8_t idx);
    ifs_err_t (*deinit)(uint8_t idx);
    ifs_err_t (*config_pin)(uint8_t idx, uint8_t pin_idx, uint32_t mode);
    ifs_err_t (*set)(uint8_t idx, uint32_t pin_idx);
    ifs_err_t (*clear)(uint8_t idx, uint32_t pin_idx);
    ifs_err_t (*toggle)(uint8_t idx, uint32_t pin_idx);
    ifs_err_t (*out)(uint8_t idx, uint32_t pin_mask, uint32_t value);
    ifs_err_t (*in)(uint8_t idx, uint32_t pin_mask, uint32_t *value);
    uint32_t (*get)(uint8_t idx, uint32_t pin_mask);
};
typedef struct _ifs_gpio_t ifs_gpio_t;


#if INC_USING_IFS_USART
typedef void (*tx_cb)(void *);
typedef void (*rx_cb)(void *, uint16_t dat);

struct _ifs_usart_t {
    ifs_err_t (*init)(uint8_t idx);
    ifs_err_t (*deinit)(uint8_t idx);
    ifs_err_t (*config)(uint8_t idx, uint32_t baudrate, uint32_t mode);
    ifs_err_t (*put)(uint8_t idx, uint16_t data);
    uint16_t (*get)(uint8_t idx);
    ifs_err_t (*add_callback)(uint8_t idx, uint8_t priproty, void *param, tx_cb tx, rx_cb rx);
    ifs_err_t (*tx_ready)(uint8_t idx);
    ifs_err_t (*rx_ready)(uint8_t idx);
};
typedef struct _ifs_usart_t ifs_usart_t;
#endif
#endif


#if INC_USING_IFS
struct _ifs_info_t {
#if INC_USING_IFS_GPIO
    ifs_gpio_t gpio;
#if INC_USING_IFS_USART
    ifs_usart_t usart;
#endif
#endif
};
typedef struct _ifs_info_t ifs_info_t;
#endif

/* Bit Control */
#define IFS_SET_BIT(REG, BIT)     ((REG) |= (1ul << BIT))
#define IFS_CLEAR_BIT(REG, BIT)   ((REG) &= ~(1ul << BIT))
#define IFS_READ_BIT(REG, BIT)    ((REG) & (1ul << BIT))
#define IFS_CLEAR_REG(REG)        ((REG) = (0x0))
#define IFS_WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define IFS_READ_REG(REG)         ((REG))
#define IFS_MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))


/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_IFS_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *   which reports the name of the source file and the source
  *   line number of the call that failed. 
  *   If expr is true, it returns no value.
  * @retval None
  */
  #define IFS_ASSERT(expr) ((expr) ? (void)0 : assert_ifs_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_ifs_failed(uint8_t* file, uint32_t line);
#else
  #define IFS_ASSERT(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif
/******************************End Of File(INC)*********************************/

