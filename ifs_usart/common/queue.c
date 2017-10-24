/**
  ******************************************************************************
  * @file    queue.c
  * @author  Inc
  * @version V0.0.1
  * @date    2-May-2017
  * @brief   this file provide a queue opration
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  * @Modify:
  * //2015/9/11
  * 	修改Count有可能导致的bug
  * 		因为Count的范围是0~65535,当size为0~65535时，count对应的是65536，
  *	    处理:
  *		    加判断，保证 Head 和 Tail 的最大值小于65535
  * //2016/2/14
  *     修改get_queue_count函数名称为 queue_get_count
  *     增加函数：queue_is_full,用于判断队列是否用满，满返回true，否则返回false
  *     新增枚举结构qsta_t用于函数判断OK还是ERR
  * //2016/9/20
  *     函数中加入指针判空
  *     修改函数queue_get_count, 增加函数变量用于获取count，返回状态表示成功或者失败
  * //2016/9/27
  *     优化函数判断
  * //2017/5/3
  * 删除queue_data_type， 使用uint8_t---ps,后续使用void *
  * 修改函数，读写接口只提供1个
  * qsta_t 改为qsta_t
  ******************************************************************************
  */
/*
 * !brief file macro
 */
#define _OWN_QUEUE

/*
 * !brief include header
 */
#include "queue.h"


/*
 * !brief init a queue
 * !param point to a type of queue_t
 * !param queue 's buff
 * !param buff 's size
 * !retval qsta_t
 */
qsta_t queue_init(queue_t *pQ, uint8_t *pQBuf, uint16_t hwQSize)
{
    if (pQ == NULL) {
        return QUEUE_ERR;
    }
	pQ->pQueueBuf = pQBuf;
	pQ->hwHead = 0;
	pQ->hwTail = 0;
	pQ->hwCount = 0;
	pQ->hwSize = hwQSize;

    return QUEUE_OK;
}


/*
 * !brief get count can use by queue
 * !param queue target
 * !retval count
 */
int queue_get_count(queue_t *pQ)
{
    if (pQ == NULL) {
        return 0;
    }

    return (int)pQ->hwCount;
}


/*
 * !brief check the queue is not full
 * !param target queue
 * !retval qsta_t
 */
qsta_t queue_is_full( queue_t *pQ)
{
    if ((pQ == NULL) || (pQ->pQueueBuf == NULL)) {
        return QUEUE_ERR;
    }

    if((pQ->hwHead == pQ->hwTail) && (0 != pQ->hwCount)){
        return QUEUE_OK;
    }else{
        return QUEUE_ERR;
    }
}

/*
 * !brief enqueue a byte
 * !param target queue
 * !param data
 * !retbal qsta_t
 */
static qsta_t _write( queue_t *pQ, uint8_t t_Dat )
{
    if (pQ == NULL) {
        return QUEUE_ERR;
    }

	if (queue_is_full(pQ)) {
		return QUEUE_ERR;  //queue is full and can not write
	}

	pQ->pQueueBuf[pQ->hwTail++] = t_Dat;

	if (pQ->hwTail >= pQ->hwSize) {
        pQ->hwTail = 0;
	}
	pQ->hwCount ++;

	return QUEUE_OK;
}


/*
 * !brief dequeue a byte
 * !param target queue
 * !param address of data
 * !retval qsta_t
 */
static qsta_t _read( queue_t *pQ, uint8_t *t_Dat)
{
    if (pQ == NULL) {
        return QUEUE_ERR;
    }

	//如果队列为空，则读出失败
	if( (pQ->hwHead == pQ->hwTail) && (pQ->hwCount == 0)) {
		return QUEUE_ERR;
	}

	*t_Dat = pQ->pQueueBuf[pQ->hwHead];
	pQ->hwHead ++;

    if (pQ->hwHead >= pQ->hwSize) {
        pQ->hwHead = 0;
    }

	pQ->hwCount --;

	return QUEUE_OK;
}


//----------------------------------------------------------------------------------------
//数据进队
qsta_t enqueue( queue_t *pQ, uint8_t *t_Dat, uint16_t hwLen)
{
	uint16_t i;

	//如果队列剩余空间不够，则退出
	if ((pQ == NULL) || (pQ->pQueueBuf == NULL) || (t_Dat == NULL)) {
        return QUEUE_ERR;
	}

	for(i = 0; i< hwLen; i++){
		if (QUEUE_ERR == _write(pQ, t_Dat[i])) {
			return QUEUE_ERR;
		}
	}

	return QUEUE_OK;
}


//----------------------------------------------------------------------------------------
//数据出队
qsta_t dequeue( queue_t *pQ, uint8_t *t_Dat, uint16_t hwLen)
{
	uint16_t i;

	if ((pQ == NULL) || (pQ->pQueueBuf == NULL) || (t_Dat == NULL)) {
        return QUEUE_ERR;
	}

	for(i = 0; i < hwLen; i++){
		if(QUEUE_ERR == _read(pQ, &t_Dat[i])) {
			return QUEUE_ERR;
		}
	}

	return QUEUE_OK;
}

