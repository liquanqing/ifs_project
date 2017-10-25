/**
  ******************************************************************************
  * @file    usart.h
  * @author  Inc
  * @version VV0.0.1
  * @date    2017-08-06
  * @brief   Header File For Usart
  ******************************************************************************
  * @modify
  *
  ******************************************************************************
  */
#ifndef __USART_H
#define __USART_H

#define IFS_USART1                  0
#define IFS_USART2                  1
#define IFS_USART3                  2
#define IFS_UART4                   3
#define IFS_UART5                   4
#define IFS_USART6                  5
#define IFS_UART7                   6
#define IFS_UART8                   7

#define IFS_USART_PARITY_NONE           (0 << 2)
#define IFS_USART_PARITY_EVEN           (1 << 2)
#define IFS_USART_PARITY_ODD            (2 << 2)

#define IFS_USART_STOPBIT_1             (0 << 4)
#define IFS_USART_STOPBIT_1_5           (1 << 4)
#define IFS_USART_STOPBIT_2             (2 << 4)

#define IFS_USART_DATA_LENGTH_8         (0 << 0)
#define IFS_USART_DATA_LENGTH_9         (1 << 0)
#define IFS_USART_DATA_LENGTH_7         (2 << 0)

#define IFS_USART_8N1                   (IFS_USART_DATA_LENGTH_8 \
                                        | IFS_USART_STOPBIT_1    \
                                        | IFS_USART_PARITY_NONE)

typedef void (*tx_cb)(void *);
typedef void (*rx_cb)(void *, uint16_t dat);

ifs_err_t usart_init(uint8_t idx);
ifs_err_t usart_deinit(uint8_t idx);
ifs_err_t usart_config(uint8_t idx, uint32_t baudrate, uint32_t mode);
ifs_err_t usart_add_callback(uint8_t idx, void *param, tx_cb tx, rx_cb rx);
ifs_err_t usart_put(uint8_t idx, uint16_t data);
uint16_t  usart_get(uint8_t idx);
ifs_err_t usart_tx_ready(uint8_t idx);
ifs_err_t usart_rx_ready(uint8_t idx);

#endif /* __USART_H */
/******************************End Of File(INC)*********************************/

