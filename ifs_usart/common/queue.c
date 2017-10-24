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
  * 	�޸�Count�п��ܵ��µ�bug
  * 		��ΪCount�ķ�Χ��0~65535,��sizeΪ0~65535ʱ��count��Ӧ����65536��
  *	    ����:
  *		    ���жϣ���֤ Head �� Tail �����ֵС��65535
  * //2016/2/14
  *     �޸�get_queue_count��������Ϊ queue_get_count
  *     ���Ӻ�����queue_is_full,�����ж϶����Ƿ�������������true�����򷵻�false
  *     ����ö�ٽṹqsta_t���ں����ж�OK����ERR
  * //2016/9/20
  *     �����м���ָ���п�
  *     �޸ĺ���queue_get_count, ���Ӻ����������ڻ�ȡcount������״̬��ʾ�ɹ�����ʧ��
  * //2016/9/27
  *     �Ż������ж�
  * //2017/5/3
  * ɾ��queue_data_type�� ʹ��uint8_t---ps,����ʹ��void *
  * �޸ĺ�������д�ӿ�ֻ�ṩ1��
  * qsta_t ��Ϊqsta_t
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

	//�������Ϊ�գ������ʧ��
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
//���ݽ���
qsta_t enqueue( queue_t *pQ, uint8_t *t_Dat, uint16_t hwLen)
{
	uint16_t i;

	//�������ʣ��ռ䲻�������˳�
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
//���ݳ���
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

