/*************************************************************************
	> File Name: sys.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月20日 星期五 01时07分11秒
 ************************************************************************/

#include "stm32f7xx.h"


/*
 * !brief set VectTab
 * !base address
 * !    Flash or sram
 * !offset of base address
 */
void nvic_set_vector_tab(uint32_t base_addr, uint32_t offset)
{
    SCB->VTOR = base_addr | (offset & (uint32_t)0xFFFFFE00);
}


/*
 * !brief set nvic group 0~4
 * !group 0~4
 * !    group should be NVIC_PRIORITYGROUP_0
 *                      NVIC_PRIORITYGROUP_1
 *                      NVIC_PRIORITYGROUP_2
 *                      NVIC_PRIORITYGROUP_3
 *                      NVIC_PRIORITYGROUP_4
 * !retval none
 */
void nvic_group_config(uint32_t group)
{
    NVIC_SetPriorityGrouping(group);
}

/*
 * !brief set nvic configuration
 * !param PreemptionPriority 0 is highest
 * !param SubPriority 0 is highest
 * !param channel irq_channel
 * !retval none
 */
void nvic_channel_config(IRQn_Type IRQn, uint32_t preemption, uint8_t sub)
{
    uint32_t prioritygroup = 0x00;
    prioritygroup = NVIC_GetPriorityGrouping();
  
    NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, preemption, sub));
}

/*
 * !brief config external interrupt
 * !param gpio A~x(just in the max frame of your chip)
 * !param pin 0 ~ 15
 * !param trim 1:down trip, 2:up trip, 3:up down trip
 * !retval none
 */
void extern_interrupt_config(uint8_t gpiox, uint8_t pin, uint8_t trim)
{
    uint8_t ext_offset = (pin % 4) * 4;
    RCC->APB2ENR |= 1 << 14;
    SYSCFG->EXTICR[pin / 4] &= ~(0x000F << ext_offset);
    SYSCFG->EXTICR[pin / 4] |= gpiox << ext_offset;

    EXTI->IMR |= 1 << pin;

    if (trim & 0x01) EXTI->FTSR |= 1 << pin;
    if (trim & 0x02) EXTI->RTSR |= 1 << pin;
}

void sys_soft_reset(void)
{
    SCB->AIRCR = 0x05FA0000 | (uint32_t)0x04;
}

void cache_enable(void)
{
    SCB_EnableICache();
    SCB_EnableDCache();
    SCB->CACR |= 1 << 2;
}

//Fvco=Fs*(plln/pllm);
//Fsys=Fvco/pllp=Fs*(plln/(pllm*pllp));
//Fusb=Fvco/pllq=Fs*(plln/(pllm*pllq));
//
#define PLLN  432
#define PLLM  25
#define PLLP  2
#define PLLQ  9
void sys_clock_config(void)
{
    uint32_t timeout = 0;

	RCC->CR|=1<<16;				//HSE ON

	while(((RCC->CR & (1 << 17)) == 0)&&(timeout < 0X1FFF))
        timeout++;//WAIT HSE RDY

	if(timeout == 0X1FFF)
        return;
	else   
	{
		RCC->APB1ENR|=1<<28;	//open power control
		PWR->CR1|=3<<14; 		//high mode
		PWR->CR1|=1<<16; 		//
		PWR->CR1|=1<<17; 		
		RCC->CFGR|=(0<<4)|(5<<10)|(4<<13);
		RCC->CR&=~(1<<24);		
		RCC->PLLCFGR=PLLM | (PLLN << 6) | (((PLLP >> 1) - 1) << 16) | (PLLQ << 24) |(1 << 22);
		RCC->CR|=1<<24;		
		while((RCC->CR&(1<<25))==0);
		FLASH->ACR|=1<<8;		
		FLASH->ACR|=1<<9;	
		FLASH->ACR|=7<<0;
		RCC->CFGR&=~(3<<0);	
		RCC->CFGR|=2<<0;
		while((RCC->CFGR&(3<<2))!=(2<<2));
	} 
}
