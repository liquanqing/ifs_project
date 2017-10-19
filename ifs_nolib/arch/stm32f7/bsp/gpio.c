/**
  ******************************************************************************
  * @file    gpio.c
  * @author  inc
  * @version VV0.0.1
  * @date    2017-08-06
  * @brief   GPIO Source File
  ******************************************************************************
  * @modify
  *
  ******************************************************************************
  */
#include "../../ifs.h"

#if INC_USING_IFS_GPIO
#include "stm32f7xx.h"
/*
 * !brief this func will open gpio clk .etc
 * !param gpio index
 * !retval err code
 */
ifs_err_t gpio_init(uint8_t idx)
{
    assert_param(IS_GPIO_OVERSTEP(idx));

    SET_BIT(RCC->AHB1ENR, 1 << (RCC_AHB1ENR_GPIOAEN_Pos + idx));
    return IFS_NO_ERR;
}

/*
 * !brief close gpio clk .etc
 * !param gpio index
 * !retval err code
 */
ifs_err_t gpio_deinit(uint8_t idx)
{
    assert_param(IS_GPIO_OVERSTEP(idx));

    CLEAR_BIT(RCC->AHB1ENR, 1 << (RCC_AHB1ENR_GPIOAEN_Pos + idx));
    return IFS_NO_ERR;
}

/*
 * !brief config pin to mode on :push_pull pull_up/down or opendraw
 * !param idx gpio_index
 * !param pin_idx gpio_pin index
 * !param mode configure_option
 * !retval err code
 */
ifs_err_t gpio_config_pin(uint8_t idx, uint8_t pin_idx, uint32_t mode)
{
    GPIO_TypeDef *gpio;
    uint32_t tmpmode = mode & 0x03;
    uint32_t tmpspeed = (mode >> 2) & 0x03;
    uint32_t tmpotype = (mode >> 4) & 0x01;
    uint32_t tmppupd = (mode >> 5) & 0x03;
    uint32_t tmpafio = (mode >> 7) & 0x0F;
    
    gpio = (GPIO_TypeDef *)(GPIOA_BASE + (idx << 10));
    
    gpio->MODER   = (gpio->MODER   & ~(((uint32_t)0x03) << (pin_idx << 1))) | (tmpmode << (pin_idx << 1));
    gpio->OSPEEDR = (gpio->OSPEEDR & ~(((uint32_t)0x03) << (pin_idx << 1))) | (tmpspeed << (pin_idx << 1));
    gpio->OTYPER  = (gpio->OTYPER  & ~(((uint32_t)0x01) << (pin_idx))) | (tmpotype << pin_idx);
    gpio->PUPDR   = (gpio->PUPDR   & ~(((uint32_t)0x03) << (pin_idx << 1))) | (tmppupd << (pin_idx << 1));
    if (2 == tmpmode) {
        gpio->AFR[pin_idx >> 3] &= ~(0x0F << ((pin_idx & 0x07) << 2));
        gpio->AFR[pin_idx >> 3] |= (tmpafio << ((pin_idx & 0x07) << 2));
    }
    return IFS_NO_ERR;
}

ifs_err_t gpio_set(uint8_t idx, uint32_t pin_idx)
{
    //GPIO_TypeDef *gpio;
    
    //gpio = (GPIO_TypeDef *)(GPIOA_BASE + (idx << 10));
    //gpio->BSRR |= (1 << pin_idx);
    ((GPIO_TypeDef *)(GPIOA_BASE + (idx << 10)))->BSRR |= (1 << pin_idx);
    return IFS_NO_ERR;
}

ifs_err_t gpio_clear(uint8_t idx, uint32_t pin_idx)
{
    //GPIO_TypeDef *gpio;
    //uint32_t tmppin = pin_idx + 16;
    
    //gpio = (GPIO_TypeDef *)(GPIOA_BASE + (idx << 10));
    ((GPIO_TypeDef *)(GPIOA_BASE + (idx << 10)))->BSRR |= (1 << (pin_idx + 16));
    
    return IFS_NO_ERR;
}

ifs_err_t gpio_toggle(uint8_t idx, uint32_t pin_idx)
{
    //GPIO_TypeDef *gpio;
    
    //gpio = (GPIO_TypeDef *)(GPIOA_BASE + (idx << 10));
    ((GPIO_TypeDef *)(GPIOA_BASE + (idx << 10)))->ODR ^= (1 << pin_idx);
    
    return IFS_NO_ERR;
}

ifs_err_t gpio_out(uint8_t idx, uint32_t pin_mask, uint32_t value)
{
    //GPIO_TypeDef *gpio;
    
    //gpio = (GPIO_TypeDef *)(GPIOA_BASE + (idx << 10));
    ((GPIO_TypeDef *)(GPIOA_BASE + (idx << 10)))->ODR = value;
    
    return IFS_NO_ERR;
}

ifs_err_t gpio_in(uint8_t idx, uint32_t pin_mask, uint32_t *value)
{
    //GPIO_TypeDef *gpio;
    
    //gpio = (GPIO_TypeDef *)(GPIOA_BASE + (idx << 10));
    *value = ((GPIO_TypeDef *)(GPIOA_BASE + (idx << 10)))->IDR;
    
    return IFS_NO_ERR;
}

uint32_t gpio_get(uint8_t idx, uint32_t pin_mask)
{
    //GPIO_TypeDef *gpio;
    
    //gpio = (GPIO_TypeDef *)(GPIOA_BASE + (idx << 10));
    return ((GPIO_TypeDef *)(GPIOA_BASE + (idx << 10)))->IDR;
}



#endif
/******************************End Of File(INC)*********************************/

