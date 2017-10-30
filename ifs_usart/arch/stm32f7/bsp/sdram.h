/*************************************************************************
	> File Name: sdram.h
	> Author: 
	> Mail: 
	> Created Time: 2017年10月29日 星期日 12时11分10秒
 ************************************************************************/

#ifndef _SDRAM_H
#define _SDRAM_H

/*
 * chip 
 */
#define MT48LC4M32B2B5 0


#define SDRAM_CHIP MT48LC4M32B2B5

#define SDRAM_BANK_OFFSET                   0

#define SDRAM_COLUMN_8BIT                   ((uint32_t)0x00000000U)
#define SDRAM_COLUMN_9BIT                   ((uint32_t)0x00000001U)
#define SDRAM_COLUMN_10BIT                  ((uint32_t)0x00000002U)
#define SDRAM_COLUMN_11BIT                  ((uint32_t)0x00000003U)

#define SDRAM_ROW_11BIT                     ((uint32_t)0x00000000U)
#define SDRAM_ROW_12BIT                     ((uint32_t)0x00000004U)
#define SDRAM_ROW_13BIT                     ((uint32_t)0x00000008U)

#define SDRAM_CAS_LATENCY_1                 ((uint32_t)0x00000080U)
#define SDRAM_CAS_LATENCY_2                 ((uint32_t)0x00000100U)
#define SDRAM_CAS_LATENCY_3                 ((uint32_t)0x00000180)

#define SDRAM_MEM_BUS_WIDTH_8               ((uint32_t)0x00000000U)
#define SDRAM_MEM_BUS_WIDTH_16              ((uint32_t)0x00000010U)
#define SDRAM_MEM_BUS_WIDTH_32              ((uint32_t)0x00000020U)

#define SDRAM_INTERN_BANKS_NUM_2            ((uint32_t)0x00000000U)
#define SDRAM_INTERN_BANKS_NUM_4            ((uint32_t)0x00000040U)

#define SDRAM_WRITE_PROTECTION_DISABLE      ((uint32_t)0x00000000U)
#define SDRAM_WRITE_PROTECTION_ENABLE       ((uint32_t)0x00000200U)

#define SDRAM_CLOCK_DISABLE                 ((uint32_t)0x00000000U)
#define SDRAM_CLOCK_PERIOD_2                ((uint32_t)0x00000800U)
#define SDRAM_CLOCK_PERIOD_3                ((uint32_t)0x00000C00)

#define SDRAM_RBURST_DISABLE                ((uint32_t)0x00000000U)
#define SDRAM_RBURST_ENABLE                 ((uint32_t)0x00001000U)

#define SDRAM_RPIPE_DELAY_0               ((uint32_t)0x00000000U)
#define SDRAM_RPIPE_DELAY_1               ((uint32_t)0x00002000U)
#define SDRAM_RPIPE_DELAY_2               ((uint32_t)0x00004000U)

#if (SDRAM_CHIP == MT48LC4M32B2B5-6A)
#define SDRAM_REFRESH_COUNT                 ((uint32_t)0x0603)

#define MT48LC4M32B2B5_SDCTRL               (SDRAM_COLUMN_8BIT        |\
                                                SDRAM_ROW_13BIT          |\
                                                SDRAM_MEM_BUS_WIDTH_32   |\
                                                SDRAM_INTERN_BANKS_NUM_4 |\
                                                SDRAM_CAS_LATENCY_3      |\
                                                SDRAM_WRITE_PROTECTION_DISABLE |\
                                                SDRAM_CLOCK_PERIOD_2     |\
                                                SDRAM_RBURST_ENABLE      |\
                                                SDRAM_RPIPE_DELAY_0)

#define SDRAM_CTRL_PARAM                    MT48LC4M32B2B5_SDCTRL

#define LOAD_TO_ACTIVE_DELAY                2
#define EXIT_SELF_REFRESH_DELAY             7
#define SELF_REFRESH_TIME                   4
#define ROW_CYCLE_DELAY                     7
#define WRITE_RECOVERY_TIME                 2
#define RPDELAY                             2
#define RCD_DELAY                           2
#endif

#endif


