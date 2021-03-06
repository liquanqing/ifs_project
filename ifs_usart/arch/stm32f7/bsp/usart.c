/**
  ******************************************************************************
  * @file    usart.c
  * @author  Inc
  * @version V0.0.1
  * @date    2017-08-06
  * @brief   Source File For USART
  ******************************************************************************
  * @modify
  *
  ******************************************************************************
  */
#include "../../ifs.h"
#include "usart.h"

#if INC_USING_IFS_USART
#include "stm32f7xx.h"
#include "sys.h"

#define PCLK1_CLK       50000000UL
#define PCLK2_CLK       100000000UL

#define USART_PORT_NUM  8

#ifndef NULL
#define NULL    (void *)0
#endif

static rx_cb usart_onrx[USART_PORT_NUM];
static tx_cb usart_ontx[USART_PORT_NUM];
static void *usart_cb_param[USART_PORT_NUM];

const USART_TypeDef *usart_group[USART_PORT_NUM] = {
    USART1,
    USART2,
    USART3,
    UART4,
    UART5,
    USART6,
    UART7,
    UART8
};

const IRQn_Type usart_irq[USART_PORT_NUM] = {
    USART1_IRQn,
    USART2_IRQn,
    USART3_IRQn,
    UART4_IRQn,
    UART5_IRQn,
    USART6_IRQn,
    UART7_IRQn,
    UART8_IRQn
};

ifs_err_t usart_init(uint8_t idx)
{
    uint8_t id;
    USART_TypeDef *usart = IFS_NULL;
    IFS_ASSERT((idx <= USART_PORT_NUM) || (i > 0));
    if (0 == idx) idx = 1;
    id = idx - 1;
    usart = (USART_TypeDef *)usart_group[id];
    
    if (USART1 == usart) {
        IFS_SET_BIT(RCC->APB2ENR, 4);
        //RCC->APB2ENR |= 1ul << 4;
    } else if (USART2 == usart) {
        //RCC->APB1ENR |= 1ul << 17;
        IFS_SET_BIT(RCC->APB1ENR, 17);
    } else if (USART3 == usart) {
        IFS_SET_BIT(RCC->APB1ENR, 18);
        //RCC->APB1ENR |= 1ul << 18;
    } else if (UART4 == usart) {
        IFS_SET_BIT(RCC->APB1ENR, 19);
        //RCC->APB1ENR |= 1ul << 19;
    } else if (UART5 == usart) {
        IFS_SET_BIT(RCC->APB1ENR, 20);
        //RCC->APB1ENR |= 1ul << 20;
    } else if (USART6 == usart) {
        IFS_SET_BIT(RCC->APB2ENR, 5);
        //RCC->APB2ENR |= 1ul << 5;
    } else if (UART7 == usart) {
        IFS_SET_BIT(RCC->APB1ENR, 30);
        //RCC->APB1ENR |= 1ul << 30;
    } else if (UART8 == usart) {
        IFS_SET_BIT(RCC->APB1ENR, 31);
        //RCC->APB1ENR |= 1ul << 31;
    }
    return IFS_NO_ERR;
}

ifs_err_t usart_deinit(uint8_t idx)
{
    uint8_t id;
    USART_TypeDef *usart = IFS_NULL;
    IFS_ASSERT((idx <= USART_PORT_NUM) || (i > 0));
    if (0 == idx) idx = 1;
    id = idx - 1;
    usart = (USART_TypeDef *)usart_group[id];
    
    if (USART1 == usart) {
        IFS_CLEAR_BIT(RCC->APB2ENR, 4);
        //RCC->APB2ENR |= 1ul << 4;
    } else if (USART2 == usart) {
        //RCC->APB1ENR |= 1ul << 17;
        IFS_CLEAR_BIT(RCC->APB1ENR, 17);
    } else if (USART3 == usart) {
        IFS_CLEAR_BIT(RCC->APB1ENR, 18);
        //RCC->APB1ENR |= 1ul << 18;
    } else if (UART4 == usart) {
        IFS_CLEAR_BIT(RCC->APB1ENR, 19);
        //RCC->APB1ENR |= 1ul << 19;
    } else if (UART5 == usart) {
        IFS_CLEAR_BIT(RCC->APB1ENR, 20);
        //RCC->APB1ENR |= 1ul << 20;
    } else if (USART6 == usart) {
        IFS_CLEAR_BIT(RCC->APB2ENR, 5);
        //RCC->APB2ENR |= 1ul << 5;
    } else if (UART7 == usart) {
        IFS_CLEAR_BIT(RCC->APB1ENR, 30);
        //RCC->APB1ENR |= 1ul << 30;
    } else if (UART8 == usart) {
        IFS_CLEAR_BIT(RCC->APB1ENR, 31);
        //RCC->APB1ENR |= 1ul << 31;
    }
    return IFS_NO_ERR;
}

ifs_err_t usart_config(uint8_t idx, uint32_t baudrate, uint32_t mode)
{
    uint8_t id;
    uint32_t pclk;
    uint32_t datalenth = (mode >> 0) & 0x3;
    uint32_t parity = (mode >> 2) & 0x3;
    uint32_t stopbit = (mode >> 4) & 0x3;
    USART_TypeDef *usart = IFS_NULL;
    
    IFS_ASSERT((idx <= USART_PORT_NUM) || (i > 0));
    id = idx;
    usart = (USART_TypeDef *)usart_group[id];
    
    if ((USART1 == usart) || (USART6 == usart)) {
        pclk = PCLK2_CLK;
    } else {
        pclk = PCLK1_CLK;
    }
    
    // config baudrate on ovr16 mode
    //usart->BRR = (pclk + baudrate / 2) / baudrate;
    IFS_WRITE_REG(usart->BRR, (pclk + baudrate / 2) / baudrate);
    // before config usart must be disable
    IFS_CLEAR_REG(usart->CR1);
    // config dat lenth to 8bit or 9bit
    if (0 == datalenth) {
        // 8bit
        IFS_CLEAR_BIT(usart->CR1, 28);
        IFS_CLEAR_BIT(usart->CR1, 12);
    } else if (1 == datalenth) {
        // 9bit
        IFS_CLEAR_BIT(usart->CR1, 28);
        IFS_SET_BIT(usart->CR1, 12);
    } else {
        // 7bit
        IFS_SET_BIT(usart->CR1, 28);
        IFS_CLEAR_BIT(usart->CR1, 12);
    }
    
    // config parity
    usart->CR1 |= parity  << 9;
//    if (0 == parity) {
//        // none parity
//        IFS_CLEAR_BIT(usart->CR1, 10);
//        IFS_CLEAR_BIT(usart->CR1, 9);
//    } else if (1 == parity) {
//        // even
//        IFS_SET_BIT(usart->CR1, 10);
//        IFS_CLEAR_BIT(usart->CR1, 9);
//    } else {
//        // odd
//        IFS_SET_BIT(usart->CR1, 10);
//        IFS_SET_BIT(usart->CR1, 9);
//    }
    
    // config stopbit
    usart->CR2 |= stopbit << 12;
//    if (0 == stopbit) {
//        // none parity
//        IFS_CLEAR_BIT(usart->CR2, 13);
//        IFS_CLEAR_BIT(usart->CR2, 12);
//    } else if (1 == stopbit) {
//        // even
//        IFS_SET_BIT(usart->CR2, 13);
//        IFS_CLEAR_BIT(usart->CR2, 12);
//    } else if (2 == stopbit) {
//    } else {
//        // odd
//        IFS_SET_BIT(usart->CR2, 13);
//        IFS_SET_BIT(usart->CR2, 12);
//    }
    usart->CR1 |= 1 << 3; // enable txd
    usart->CR1 |= 1 << 2; // enable rxd
    //usart->CR1 |= 1 << 5; // interrupt with recieve buff not empty
    //NVIC_EnableIRQ(usart_irq[id]);
    //NVIC_SetPriority(usart_irq[id], 1);
    usart->CR1 |= 1 << 0; // enable usart
    return IFS_NO_ERR;
}

ifs_err_t usart_add_callback(uint8_t idx, uint8_t priproty, void *param, tx_cb tx, rx_cb rx)
{
    USART_TypeDef *usart = IFS_NULL;
    usart = (USART_TypeDef *)usart_group[idx];
    usart_onrx[idx] = rx;
    usart_ontx[idx] = tx;
    usart_cb_param[idx] = param;

    if (tx != NULL) {
        usart->CR1 |= 1 << 6;
    }

    if (rx != NULL) {
        usart->CR1 |= 1 << 5;
    }
    if ((tx != NULL) || (rx != NULL))
        nvic_channel_config(usart_irq[idx], priproty, 0);
    return IFS_NO_ERR;
}

ifs_err_t usart_put(uint8_t idx, uint16_t data)
{
    USART_TypeDef *usart = IFS_NULL;
    
    IFS_ASSERT((idx <= USART_PORT_NUM) || (idx > 0));
    usart = (USART_TypeDef *)usart_group[idx];
    
    usart->TDR = data;
    return IFS_NO_ERR;
}

uint16_t  usart_get(uint8_t idx)
{
    USART_TypeDef *usart = IFS_NULL;
    
    IFS_ASSERT((idx <= USART_PORT_NUM) || (idx > 0));
    usart = (USART_TypeDef *)usart_group[idx];
    
    return usart->RDR;
}

ifs_err_t usart_tx_ready(uint8_t idx)
{
    USART_TypeDef *usart = IFS_NULL;
    
    IFS_ASSERT((idx <= USART_PORT_NUM) || (idx > 0));
    usart = (USART_TypeDef *)usart_group[idx];
    
    if (usart->ISR & (1 << 7)) {
        usart->ICR |= (1 << 7);
        return IFS_READY;
    } else {
        return IFS_NOT_READY;
    }
}

ifs_err_t usart_rx_ready(uint8_t idx)
{
    USART_TypeDef *usart = IFS_NULL;
    
    IFS_ASSERT((idx <= USART_PORT_NUM) || (idx > 0));
    usart = (USART_TypeDef *)usart_group[idx];
    
    if (usart->ISR & (1 << 5)) {
        return IFS_READY;
    } else {
        return IFS_NOT_READY;
    }
}

static void _irq_handler(uint8_t idx)
{
    USART_TypeDef *usart = IFS_NULL;
    
    usart = (USART_TypeDef *)usart_group[idx];
    
    if ((usart->ISR & (1ul << 5)) && (usart_onrx[idx] != NULL)) {
        usart_onrx[idx](usart_cb_param[idx], usart->RDR);
    }

    if ((usart->ISR & (1ul << 6)) && (usart_ontx[idx] != NULL)) {
        usart->ICR |= (1 << 6);
        usart_ontx[idx](usart_cb_param[idx]);
    }
}


void USART1_IRQHandler(void)
{
    #if 0
    if ((USART1->ISR & (1ul << 5)) && (usart_onrx[0] != NULL)) {
        usart_onrx[0](usart_cb_param[0], USART1->RDR);
    }

    if ((USART1->ISR & (1ul << 6)) && (usart_ontx[0] != NULL)) {
        USART1->ICR |= (1 << 6);
        usart_ontx[0](usart_cb_param[0]);
    }
    #else
    _irq_handler(0);
    #endif
}

void USART2_IRQHandler(void)
{
    #if 0
    if ((USART2->ISR & (1ul << 5)) && (usart_onrx[1] != NULL)) {
        usart_onrx[1](usart_cb_param[1], USART2->RDR);
    }

    if ((USART2->ISR & (1ul << 6)) && (usart_ontx[1] != NULL)) {
        USART2->ICR |= (1 << 6);
        usart_ontx[1](usart_cb_param[1]);
    }
    #else
    _irq_handler(1);
    #endif
}

void USART3_IRQHandler(void)
{
    #if 0
    if ((USART3->ISR & (1ul << 5)) && (usart_onrx[2] != NULL)) {
        usart_onrx[2](usart_cb_param[2], USART3->RDR);
    }

    if ((USART3->ISR & (1ul << 6)) && (usart_ontx[2] != NULL)) {
        USART3->ICR |= (1 << 6);
        usart_ontx[2](usart_cb_param[2]);
    }
    #else
    _irq_handler(2);
    #endif
}

void UART4_IRQHandler(void)
{
    #if 0
    if ((UART4->ISR & (1ul << 5)) && (usart_onrx[3] != NULL)) {
        usart_onrx[3](usart_cb_param[3], UART4->RDR);
    }

    if ((UART4->ISR & (1ul << 6)) && (usart_ontx[3] != NULL)) {
        UART4->ICR |= (1 << 6);
        usart_ontx[3](usart_cb_param[3]);
    }
    #else
    _irq_handler(3);
    #endif
}

void UART5_IRQHandler(void)
{
    #if 0
    if ((UART5->ISR & (1ul << 5)) && (usart_onrx[4] != NULL)) {
        usart_onrx[4](usart_cb_param[4], UART5->RDR);
    }

    if ((UART5->ISR & (1ul << 6)) && (usart_ontx[4] != NULL)) {
        UART5->ICR |= (1 << 6);
        usart_ontx[4](usart_cb_param[4]);
    }
    #else
    _irq_handler(4);
    #endif
}

void USART6_IRQHandler(void)
{
    #if 0
    if ((USART6->ISR & (1ul << 5)) && (usart_onrx[5] != NULL)) {
        usart_onrx[5](usart_cb_param[5], USART6->RDR);
    }

    if ((USART6->ISR & (1ul << 6)) && (usart_ontx[5] != NULL)) {
        USART6->ICR |= (1 << 6);
        usart_ontx[5](usart_cb_param[5]);
    }
    #else
    _irq_handler(5);
    #endif
}

void UART7_IRQHandler(void)
{
    #if 0
    if ((UART7->ISR & (1ul << 5)) && (usart_onrx[6] != NULL)) {
        usart_onrx[6](usart_cb_param[6], UART7->RDR);
    }

    if ((UART7->ISR & (1ul << 6)) && (usart_ontx[6] != NULL)) {
        UART7->ICR |= (1 << 6);
        usart_ontx[6](usart_cb_param[6]);
    }
    #else
    _irq_handler(6);
    #endif
}

void UART8_IRQHandler(void)
{
    #if 0
    if ((UART8->ISR & (1ul << 5)) && (usart_onrx[7] != NULL)) {
        usart_onrx[7](usart_cb_param[7], UART8->RDR);
    }

    if ((UART8->ISR & (1ul << 6)) && (usart_ontx[7] != NULL)) {
        UART8->ICR |= (1 << 6);
        usart_ontx[7](usart_cb_param[7]);
    }
    #else
    _irq_handler(7);
    #endif
}

#endif
/******************************End Of File(INC)*********************************/
