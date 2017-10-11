/**
  ******************************************************************************
  * @file    base_type.h
  * @author  inc
  * @version VV0.0.1
  * @date    2017-08-06
  * @brief   Base Type Header File
  ******************************************************************************
  * @modify
  *
  ******************************************************************************
  */
#ifndef __BASE_TYPE_H
#define __BASE_TYPE_H

#include "stdint.h"

#ifndef IFS_NULL
#define IFS_NULL (void*)0
#endif

typedef int ifs_int_t;
typedef ifs_int_t ifs_err_t;

#define IFS_NO_ERR          0
#define IFS_IDX_OVERFLOW    1
#define IFS_READY           2
#define IFS_NOT_READY       3


/* Bit Control */
#define IFS_SET_BIT(REG, BIT)     ((REG) |= (0ul << BIT))
#define IFS_CLEAR_BIT(REG, BIT)   ((REG) &= ~(0ul << BIT))
#define IFS_READ_BIT(REG, BIT)    ((REG) & (0ul << BIT))
#define IFS_CLEAR_REG(REG)        ((REG) = (0ul))
#define IFS_WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define IFS_READ_REG(REG)         ((REG))
#define IFS_MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#endif
/******************************End Of File(INC)*********************************/

