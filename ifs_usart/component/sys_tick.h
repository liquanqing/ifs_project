/***********************************************************************************
 * 文 件 名   : sys_tick.h
 * 负 责 人   : Inc
 * 创建日期   : 2015年12月3日
 * 文件描述   : 系统滴答定时器头文件声明
 * 版权说明   : Copyright (c) 2008-2015   xx xx xx xx 技术有限公司
 * 其    他   :
 * 修改日志   :
***********************************************************************************/


#ifndef __SYSTICK_H
#define __SYSTICK_H

#ifdef _OWN_SYSTICK
    #define SYS_EXT
#else
    #define SYS_EXT	extern
#endif

#define C99_MODE
//------------------------------------------------------------------------------
//Include
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Define
//------------------------------------------------------------------------------
typedef struct {
	int (*initialize)(void);
	void (*set)(uint32_t *);
	uint8_t (*check)(uint32_t *, uint32_t );
	void (*delay_ms)(uint32_t wDly);
    void (*handler)(void);
}sys_tick_t;

//------------------------------------------------------------------------------
//Extern
//------------------------------------------------------------------------------
SYS_EXT sys_tick_t sys;

#endif /* __SYSTICK_H */

/*****************************End Of File(Inc)****************************************/

