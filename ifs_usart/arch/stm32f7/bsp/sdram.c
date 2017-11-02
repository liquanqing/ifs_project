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
    gpio_config_pin(IFS_GPIOD, 
                    IFS_PIN_14 | IFS_PIN_15 | IFS_PIN_0 | IFS_PIN_1 | IFS_PIN_8 | IFS_PIN_9 | IFS_PIN_10, 
                    IFS_GPIO_ALTERNATE | IFS_GPIO_AF_AF12);
    gpio_config_pin(IFS_GPIOE,
                    IFS_PIN_7 | IFS_PIN_8 | IFS_PIN_9 | IFS_PIN_10 | IFS_PIN_11 | IFS_PIN_12 | IFS_PIN_13 | IFS_PIN_14 | IFS_PIN_15 | IFS_PIN_0 | IFS_PIN_1,
                    IFS_GPIO_ALTERNATE | IFS_GPIO_AF_AF12);
    gpio_config_pin(IFS_GPIOF,
                    IFS_PIN_0 | IFS_PIN_1 | IFS_PIN_2 | IFS_PIN_3 | IFS_PIN_4 | IFS_PIN_5 | IFS_PIN_11 | IFS_PIN_12 | IFS_PIN_13 | IFS_PIN_14 | IFS_PIN_15,
                    IFS_GPIO_ALTERNATE | IFS_GPIO_AF_AF12);
    gpio_config_pin(IFS_GPIOG,
                    IFS_PIN_0 | IFS_PIN_1 | IFS_PIN_2 | IFS_PIN_4 | IFS_PIN_5 | IFS_PIN_8 | IFS_PIN_15,
                    IFS_GPIO_ALTERNATE | IFS_GPIO_AF_AF12);
    gpio_config_pin(IFS_GPIOH,
                    IFS_PIN_2 | IFS_PIN_3 | IFS_PIN_5 | IFS_PIN_8 | IFS_PIN_9 | IFS_PIN_10 | IFS_PIN_11 | IFS_PIN_12 | IFS_PIN_13 | IFS_PIN_14 | IFS_PIN_15,
                    IFS_GPIO_ALTERNATE | IFS_GPIO_AF_AF12);
    gpio_config_pin(IFS_GPIOI,
                    IFS_PIN_0 | IFS_PIN_1 | IFS_PIN_2 | IFS_PIN_3 | IFS_PIN_4 | IFS_PIN_5 | IFS_PIN_6 | IFS_PIN_7 | IFS_PIN_9 | IFS_PIN_10,
                    IFS_GPIO_ALTERNATE | IFS_GPIO_AF_AF12);

}

static uint8_t sdram_send_command(uint8_t bankx, uint8_t cmd, uint8_t refresh, uint16_t regval)
{
    uint32_t retry=0;
	uint32_t tempreg=0; 
	tempreg|=cmd<<0;			//设置指令
	tempreg|=1<<(4-bankx);		//设置发送指令到bank5还是6
	tempreg|=(refresh - 1) <<5;		//设置自刷新次数
	tempreg|=regval<<9;			//设置模式寄存器的值
	FMC_Bank5_6->SDCMR=tempreg;	//配置寄存器
	while((FMC_Bank5_6->SDSR&(1<<5)))//等待指令发送完成 
	{
		retry++;
		if(retry>0X1FFFFF)return 1; 
	}
	return 0;	
}

/*
 * !brief init sdram sequence
 * !param none
 * !retval none
 */
static void sdram_init_sequence(void)
{
    uint32_t tmpr1 = 0;

    RCC->AHB3ENR |= 1 << 0; // enable fmc clk

    /*
    tmpr1 |= (uint32_t)(Init->ColumnBitsNumber   |\
                        Init->RowBitsNumber      |\
                        Init->MemoryDataWidth    |\
                        Init->InternalBankNumber |\
                        Init->CASLatency         |\
                        Init->WriteProtection    |\
                        Init->SDClockPeriod      |\
                        Init->ReadBurst          |\
                        Init->ReadPipeDelay
                        );                                      
                        */
    tmpr1 = (uint32_t)(SDRAM_CTRL_PARAM);                                      
    FMC_Bank5_6->SDCR[0] = tmpr1;


    /*
    Timing.LoadToActiveDelay    = 2;
    Timing.ExitSelfRefreshDelay = 7;
    Timing.SelfRefreshTime      = 4;
    Timing.RowCycleDelay        = 7;
    Timing.WriteRecoveryTime    = 2;
    Timing.RPDelay              = 2;
    Timing.RCDDelay             = 2;
    
    tmpr1 &= ((uint32_t)~(FMC_SDTR1_TMRD  | FMC_SDTR1_TXSR | FMC_SDTR1_TRAS | \
                          FMC_SDTR1_TRC  | FMC_SDTR1_TWR | FMC_SDTR1_TRP | \
                          FMC_SDTR1_TRCD));
    
    tmpr1 |= (uint32_t)(((Timing->LoadToActiveDelay)-1)           |\
                       (((Timing->ExitSelfRefreshDelay)-1) << 4) |\
                       (((Timing->SelfRefreshTime)-1) << 8)      |\
                       (((Timing->RowCycleDelay)-1) << 12)       |\
                       (((Timing->WriteRecoveryTime)-1) <<16)    |\
                       (((Timing->RPDelay)-1) << 20)             |\
                       (((Timing->RCDDelay)-1) << 24));
    Device->SDTR[FMC_SDRAM_BANK1] = tmpr1;
    */
    
    tmpr1 |= (uint32_t)(((LOAD_TO_ACTIVE_DELAY)-1)           |\
                       (((EXIT_SELF_REFRESH_DELAY)-1) << 4) |\
                       (((SELF_REFRESH_TIME)-1) << 8)      |\
                       (((ROW_CYCLE_DELAY)-1) << 12)       |\
                       (((WRITE_RECOVERY_TIME)-1) <<16)    |\
                       (((RPDELAY)-1) << 20)             |\
                       (((RCD_DELAY)-1) << 24));
    FMC_Bank5_6->SDTR[0] = tmpr1;
}

static void sdram_config_refresh_rate(uint32_t refresh_count)
{
    FMC_Bank5_6->SDRTR = (refresh_count << 1);
}

static void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 10000; i++) {
        ;
    }
}

void sdram_init(void)
{
    uint32_t tmpmrd = 0;
    sdram_gpio_config();
    sdram_init_sequence();
    sdram_send_command(0, 1, 1, 0);
    delay();
    sdram_send_command(0, 2, 1, 0);
    sdram_send_command(0, 3, 8, 0);
    tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |\
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |\
                     SDRAM_MODEREG_CAS_LATENCY_3           |\
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |\
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
    sdram_send_command(0, 4, 1, tmpmrd);
    sdram_config_refresh_rate(REFRESH_COUNT);
}
