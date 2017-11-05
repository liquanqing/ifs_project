/***********************************************************************************
 * �� �� ��   : INC_SysTick.c
 * �� �� ��   : Inc
 * ��������   : 2015��12��3��
 * �ļ�����   : ϵͳ�δ�ʱ��
 * ��Ȩ˵��   : Copyright (c) 2008-2015
 * ��    ��   :
 * �޸���־   :
***********************************************************************************/

#define _OWN_SYSTICK
//-------------------------------------------------------------------------
//Include
//-------------------------------------------------------------------------
#include "ifs_lib.h"
#include "sys_tick.h"



SYS_EXT int systick_init(void);
SYS_EXT void wait_init(uint32_t* pBaseTime);
SYS_EXT uint8_t wait_check(uint32_t* pBaseTime, uint32_t WaitSet);
SYS_EXT void sys_delay_ms(uint32_t wDly);
SYS_EXT void systick_handler(void);

//-------------------------------------------------------------------------
//Variable
//-------------------------------------------------------------------------
#ifdef C99_MODE
sys_tick_t sys = {
	.initialize = systick_init,
	.set = wait_init,
	.check = wait_check,
	.delay_ms = sys_delay_ms,
	.handler = systick_handler,
};

#else

sys_tick_t sys = {
	systick_init,
	wait_init,
	wait_check,
	sys_delay_ms,
	systick_handler
};

#endif /* C99_MODE */

static __IO uint32_t g_wSysTickClock= 0; /* add by Inc, 2015-12-03, ԭ��: ϵͳʱ��*/


//-------------------------------------------------------------------------
//Function
//-------------------------------------------------------------------------

/*****************************************************************************
 * �� �� ��  : systick_init
 * �� �� ��  : Inc
 * ��������  : 2015��12��3��
 * ��������  : ϵͳʱ����ʼ������
 * �������  : void  ��
 * �������  : ��
 * �� �� ֵ  : int
 * ���ù�ϵ  :
 * ��    ��  :

*****************************************************************************/
int systick_init( void )
{
    sys_tick_init(200000);
	return 0;
}

/*****************************************************************************
 * �� �� ��  : sys_delay_ms
 * �� �� ��  : Inc
 * ��������  : 2015��12��3��
 * ��������  : ���뼶��ʱ
 * �������  : uint32_t wDly  ��ʱʱ��  ��λ������
 * �������  : ��
 * �� �� ֵ  :
 * ���ù�ϵ  :
 * ��    ��  :

*****************************************************************************/
void sys_delay_ms(uint32_t wDly)
{
	uint32_t i32;

	if(wDly <= 1)
		wDly = 2;

	//�������ʱ��
	i32 = g_wSysTickClock;

	//�����ʱʱ��
	i32 += wDly;
	while(i32 != g_wSysTickClock);
}


/*****************************************************************************
 * �� �� ��  : wait_init
 * �� �� ��  : Inc
 * ��������  : 2015��12��3��
 * ��������  : ��ʼ������ʱ������ȡ��ǰʱ��
 * �������  : uint32_t* pBaseTime  ����ʱ��
 * �������  : ��
 * �� �� ֵ  :
 * ���ù�ϵ  :
 * ��    ��  :

*****************************************************************************/
void wait_init(uint32_t* pBaseTime)
{
	*pBaseTime = g_wSysTickClock;	//mTMRBase;
}


/*****************************************************************************
 * �� �� ��  : wait_check
 * �� �� ��  : Inc
 * ��������  : 2015��12��3��
 * ��������  : �����������ʱ��
 * �������  : uint32_t* pBaseTime  ����ʱ��
               uint32_t WaitSet     ��������ʱ�䣬��λ������
 * �������  : ��
 * �� �� ֵ  :
 * ���ù�ϵ  :
 * ��    ��  :

*****************************************************************************/
uint8_t wait_check(uint32_t* pBaseTime, uint32_t WaitSet)
{
	uint32_t i32;

	//��ֵ
	i32 = g_wSysTickClock - (*pBaseTime);

	//�ж�
	if(i32 >= WaitSet)
	{
		//ʱ�䵽
		(*pBaseTime) =g_wSysTickClock;
		return 0;
	}

	return 1;
}

/*****************************************************************************
 * �� �� ��  : sistick_handler
 * �� �� ��  : Inc
 * ��������  : 2015��12��3��
 * ��������  : ϵͳ�δ�ʱʱ���жϵ��ú���
 * �������  : void  ��
 * �������  : ��
 * �� �� ֵ  :
 * ���ù�ϵ  :
 * ��    ��  :

*****************************************************************************/
void systick_handler(void)
{
	g_wSysTickClock++;
}


/************************ (C) COPYRIGHT Inc *****END OF FILE****/
