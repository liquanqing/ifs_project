/**
  ******************************************************************************
  * @file    gpio.h
  * @author  inc
  * @version VV0.0.1
  * @date    2017-08-06
  * @brief   GPIO Header File
  ******************************************************************************
  * @modify
  *
  ******************************************************************************
  */
#ifndef __GPIO_H
#define __GPIO_H

enum _GPIO {
    PORTA = 0,
    PORTB = 1,
    PORTC = 2,
    PORTD = 3,
    PORTE = 4,
    PORTF = 5,
    PORTG = 6,
    PORTH = 7,
    PORTI = 8,
    PORTJ = 9,
    PORTK = 10,
};

#define IFS_GPIO_MODE_INPUT             (0x00000000 << 0)
#define IFS_GPIO_MODE_OUTPUT            (0x00000001 << 0)
#define IFS_GPIO_MODE_ALTERNATE         (0x00000002 << 0)
#define IFS_GPIO_MODE_ANALOG            (0x00000003 << 0)

#define IFS_GPIO_SPEED_LOW              (0x00000000 << 2)
#define IFS_GPIO_SPEED_MEDIUM           (0x00000001 << 2)
#define IFS_GPIO_SPEED_HIGH             (0x00000002 << 2)
#define IFS_GPIO_SPEED_VERY_HIGH        (0x00000003 << 2)

#define IFS_GPIO_OTYPE_PP               (0x00000000 << 4)
#define IFS_GPIO_OTYPE_OD               (0x00000001 << 4)

#define IFS_GPIO_PUPD_NOPUPD            (0x00000000 << 5)
#define IFS_GPIO_PUPD_UP                (0x00000001 << 5)
#define IFS_GPIO_PUPD_DOWN              (0x00000002 << 5)

#define IFS_GPIO_AF_AF0                 (0x00000000 << 7)
#define IFS_GPIO_AF_AF1                 (0x00000001 << 7)
#define IFS_GPIO_AF_AF2                 (0x00000002 << 7)
#define IFS_GPIO_AF_AF3                 (0x00000003 << 7)
#define IFS_GPIO_AF_AF4                 (0x00000004 << 7)
#define IFS_GPIO_AF_AF5                 (0x00000005 << 7)
#define IFS_GPIO_AF_AF6                 (0x00000006 << 7)
#define IFS_GPIO_AF_AF7                 (0x00000007 << 7)
#define IFS_GPIO_AF_AF8                 (0x00000008 << 7)
#define IFS_GPIO_AF_AF9                 (0x00000009 << 7)
#define IFS_GPIO_AF_AF10                (0x0000000A << 7)
#define IFS_GPIO_AF_AF11                (0x0000000B << 7)
#define IFS_GPIO_AF_AF12                (0x0000000C << 7)
#define IFS_GPIO_AF_AF13                (0x0000000D << 7)
#define IFS_GPIO_AF_AF14                (0x0000000E << 7)
#define IFS_GPIO_AF_AF15                (0x0000000F << 7)



ifs_err_t gpio_init(uint8_t idx);
ifs_err_t gpio_deinit(uint8_t idx);
ifs_err_t gpio_config_pin(uint8_t idx, uint8_t pin_idx, uint32_t mode); 
ifs_err_t gpio_set(uint8_t idx, uint32_t pin_idx);
ifs_err_t gpio_clear(uint8_t idx, uint32_t pin_idx);
ifs_err_t gpio_toggle(uint8_t idx, uint32_t pin_idx);
ifs_err_t gpio_out(uint8_t idx, uint32_t pin_mask, uint32_t value);
ifs_err_t gpio_in(uint8_t idx, uint32_t pin_mask, uint32_t *value);
uint32_t gpio_get(uint8_t idx, uint32_t pin_mask);


#endif
/******************************End Of File(INC)*********************************/

