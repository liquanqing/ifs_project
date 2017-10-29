/*************************************************************************
	> File Name: sdram.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月29日 星期日 12时11分05秒
 ************************************************************************/
#include "ifs.h"
#include "gpio.h"
#include "stm32f7xx.h"


/*
 * !brief sdram gpio config
 * !param none
 * !retval none
 */
static void sdram_gpio_config(void)
{
    uint32_t sd_ctrl_reg = 0, sd_time_reg = 0;
    uint16_t m_reg_val = 0;

    RCC->AHB3ENR |= 1 << 0; // enable fmc clk
    gpio_init(IFS_GPIOD);
    gpio_init(IFS_GPIOE);
    gpio_init(IFS_GPIOF);
    gpio_init(IFS_GPIOG);
    gpio_init(IFS_GPIOH);
    gpio_init(IFS_GPIOI);
    /*
     * FMC_A0~A12: GPIOF_0~5(A0~A5), GPIOF_12~15)(A6~A9), GPIOG_0~2(A10~A12)
     * FMC_D0~D31: GPIOD_14~15(D0~D1), GPIOD_0~1(D2~D3), GPIOE_7~15(D4~D12)
     *             GPIOH_8~15((D16~D23), GPIOI_0~3(D24~D27), GPIOI_6~7(D28~D29)
                   GPIOI_9~10(D30~D31)
     * FMC_BA1~0 : GPIOG_4~5(A0~A1)
     * FMC_NBL0~3: GPIOE_0~1(NBL0~NBL1) GPIOI_4~5(NBL2~NBL3)
     * FMC_SDNWE : GPIOH_5
     * FMC_SDNRAS: GPIOF_11
     * FMC_SDNCAS: GPIOG_15
     * FMC_SDCLK : GPIOG_8
     * FMC_SDNE0 : GPIOH_3
     * FMC_SDCKE0: GPIOH_2
     * FMC_SDNWE : GPIOH_5
     */





}
