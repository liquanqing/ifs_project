/*************************************************************************
	> File Name: sdram.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月29日 星期日 12时11分05秒
 ************************************************************************/
#include "ifs.h"
#include "gpio.h"
#include "sdram.h"
#include "stm32f7xx.h"


/*
 * !brief sdram gpio config
 * !param none
 * !retval none
 */
static void sdram_gpio_config(void)
{
    gpio_init(IFS_GPIOD);
    gpio_init(IFS_GPIOE);
    gpio_init(IFS_GPIOF);
    gpio_init(IFS_GPIOG);
    gpio_init(IFS_GPIOH);
    gpio_init(IFS_GPIOI);
    /*
     * FMC_A0~A12: GPIOF_0~5(A0~A5), GPIOF_12~15)(A6~A9), GPIOG_0~2(A10~A12)
     * FMC_D0~D31: GPIOD_14~15(D0~D1), GPIOD_0~1(D2~D3), GPIOE_7~15(D4~D12) GPIOD_8~10(D13~D15)
     *             GPIOH_8~15((D16~D23), GPIOI_0~3(D24~D27), GPIOI_6~7(D28~D29)
                   GPIOI_9~10(D30~D31)
     * FMC_SDNWE : GPIOH_5
     * FMC_SDNRAS: GPIOF_11
     * FMC_SDNCAS: GPIOG_15
     * FMC_SDCLK : GPIOG_8
     * FMC_BA1~0 : GPIOG_4~5(A0~A1)
     * FMC_NBL0~3: GPIOE_0~1(NBL0~NBL1) GPIOI_4~5(NBL2~NBL3)
     * FMC_SDNE0 : GPIOH_3
     * FMC_SDCKE0: GPIOH_2
     */
    gpio_config(IFS_GPIOD, 
                IFS_PIN_14 | IFS_PIN_15 | IFS_PIN_0 | IFS_PIN_1 | IFS_PIN_8 | IFS_PIN_9 | IFS_PIN_10, 
                IFS_GPIO_ALTERNATE);
    gpio_config(IFS_GPIOE,
                IFS_PIN_7 | IFS_PIN_8 | IFS_PIN_9 | IFS_PIN_10 | IFS_PIN_11 | IFS_PIN_12 | IFS_PIN_13 | IFS_PIN_14 | IFS_PIN_15 | IFS_PIN_0 | IFS_PIN_1,
                IFS_GPIO_ALTERNATE);
    gpio_config(IFS_GPIOF,
                IFS_PIN_0 | IFS_PIN_1 | IFS_PIN_2 | IFS_PIN_3 | IFS_PIN_4 | IFS_PIN_5 | IFS_PIN_11 | IFS_PIN12 | IFS_PIN13 | IFS_PIN_14 | IFS_PIN_15,
                IFS_GPIO_ALTERNATE);
    gpio_config(IFS_GPIOG,
                IFS_PIN_0 | IFS_PIN_1 | IFS_PIN_2 | IFS_PIN_4 | IFS_PIN_5 | IFS_PIN_8 | IFS_PIN_15,
                IFS_GPIO_ALTERNATE);
    gpio_config(IFS_GPIOH,
                IFS_PIN_2 | IFS_PIN_3 | IFS_PIN_5 | IFS_PIN_8 | IFS_PIN_9 | IFS_PIN_10 | IFS_PIN_11 | IFS_PIN_12 | IFS_PIN_13 | IFS_PIN_14 | IFS_PIN_15,
                IFS_GPIO_ALTERNATE);
    gpio_config(IFS_GPIOI,
                IFS_PIN_0 | IFS_PIN_1 | IFS_PIN_2 | IFS_PIN_3 | IFS_PIN_4 | IFS_PIN_5 | IFS_PIN_6 | IFS_PIN_7 | IFS_PIN_9 | IFS_PIN_10,
                IFS_GPIO_ALTERNATE);

}

/*
 * !brief init sdram sequence
 * !param none
 * !retval none
 */
static void sdram_init_sequence(void)
{
    uint32_t tmp_r1 = 0, tmp_r2  = 0;

    RCC->AHB3ENR |= 1 << 0; // enable fmc clk

    tmpr1 = FMC_Bank5_6->SDCR[FMC_SDRAM_OFFSET];
    /* Clear NC, NR, MWID, NB, CAS, WP, SDCLK, RBURST, and RPIPE bits */
    tmpr1 &= ((uint32_t)~(FMC_SDCR1_NC  | FMC_SDCR1_NR | FMC_SDCR1_MWID | \
                          FMC_SDCR1_NB  | FMC_SDCR1_CAS | FMC_SDCR1_WP   | \
                          FMC_SDCR1_SDCLK | FMC_SDCR1_RBURST | FMC_SDCR1_RPIPE));

    tmpr1 |= (uint32_t)(SDRAM_CTRL_PARAM);                                      
    FMC_Bank5_6->SDCR[FMC_SDRAM_OFFSET] = tmpr1;

    tmpr1 = FMC_Bank5_6->SDTR[FMC_SDRAM_OFFSET];
    /* Clear TMRD, TXSR, TRAS, TRC, TWR, TRP and TRCD bits */
    tmpr1 &= ((uint32_t)~(FMC_SDTR1_TMRD  | FMC_SDTR1_TXSR | FMC_SDTR1_TRAS | \
                          FMC_SDTR1_TRC  | FMC_SDTR1_TWR | FMC_SDTR1_TRP | \
                          FMC_SDTR1_TRCD));
    
    tmpr1 |= (uint32_t)(((LOAD_TO_ACTIVE_DELAY)-1)           |\
                       (((EXIT_SELF_REFRESH_DELAY)-1) << 4) |\
                       (((SELF_REFRESH_TIME)-1) << 8)      |\
                       (((ROW_CYCLE_DELAY)-1) << 12)       |\
                       (((WRITE_RECOVERY_TIME)-1) <<16)    |\
                       (((RPDELAY)-1) << 20)             |\
                       (((RCD_DELAY)-1) << 24));
    Device->SDTR[FMC_SDRAM_BANK1] = tmpr1;
}

void sdram_init(void)
{
    sdram_gpio_config();
    sdram_init_sequence();
}
