/*************************************************************************
	> File Name: sys.h
	> Author: 
	> Mail: 
	> Created Time: 2017年10月20日 星期五 01时07分23秒
 ************************************************************************/

#ifndef _SYS_H
#define _SYS_H

#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007U) /*!< 0 bits for pre-emption priority
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006U) /*!< 1 bits for pre-emption priority
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005U) /*!< 2 bits for pre-emption priority
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004U) /*!< 3 bits for pre-emption priority
                                                                 1 bits for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003U) /*!< 4 bits for pre-emption priority
                                                                 0 bits for subpriority */


void nvic_set_vector_tab(uint32_t base_addr, uint32_t offset);
void nvic_group_config(uint32_t group);
void nvic_channel_config(IRQn_Type IRQn, uint32_t preemption, uint8_t sub);
void extern_interrupt_config(uint8_t gpiox, uint8_t pin, uint8_t trim);
void sys_soft_reset(void);
void cache_enable(void);
void sys_clock_config(void);
#endif
