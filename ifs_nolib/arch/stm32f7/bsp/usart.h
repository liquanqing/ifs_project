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

ifs_err_t usart_init(uint8_t idx);
ifs_err_t usart_deinit(uint8_t idx);
ifs_err_t usart_config(uint8_t idx, uint32_t baudrate, uint32_t mode);
ifs_err_t usart_put(uint8_t idx, uint16_t data);
uint16_t  usart_get(uint8_t idx);
ifs_err_t usart_tx_ready(uint8_t idx);
ifs_err_t usart_rx_ready(uint8_t idx);

#endif /* __USART_H */
/******************************End Of File(INC)*********************************/

