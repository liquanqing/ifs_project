/**
  ******************************************************************************
  * @file    queue.h
  * @author  Inc
  * @version V0.0.1
  * @date    2-May-2017
  * @brief   The Header For queue.c
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
/*
 * !brief include header
 */
#ifndef __QUEUE_H
#define __QUEUE_H

#include "stdint.h"
#include "stdbool.h"

/*
 * !brief header file define
 */
#ifdef _OWN_QUEUE
	#define QUEUE_EXT
#else
	#define QUEUE_EXT	extern
#endif

/*
 * !brief type of queue
 */
typedef struct {
	uint8_t     *pQueueBuf;	    //���л�����
	uint16_t	hwHead;			//����ͷָ��
	uint16_t 	hwTail;			//����βָ��
	uint16_t 	hwCount;		//�����е���Ч����
	uint16_t 	hwSize;			//���г���
}queue_t;

typedef enum{
    QUEUE_ERR = 0,
    QUEUE_OK = !QUEUE_ERR,
}qsta_t;


#ifndef NULL
#define NULL 0
#endif

/*
 * !brief export
 */
/*
 * !brief init a queue
 */
QUEUE_EXT qsta_t   queue_init( queue_t *pQ, uint8_t *pQBuf, uint16_t hwQSize);
/*
 * !brief get the count with user can use to the queue
 */
QUEUE_EXT int queue_get_count(queue_t *pQ);
/*
 * !brief check the queue isn't full
 */
QUEUE_EXT qsta_t   queue_is_full( queue_t *pQ);
/*
 * !brief multily pop nums of data in queue
 */
QUEUE_EXT qsta_t enqueue( queue_t *pQ, uint8_t *t_Dat, uint16_t hwLen);
/*
 * !brief multily push nums of data to queue
 */
QUEUE_EXT qsta_t dequeue( queue_t *pQ, uint8_t *t_Dat, uint16_t hwLen);



#endif
/***************************End Of File(Copyright of Inc)***********************************************/
