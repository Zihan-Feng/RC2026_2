#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "bsp_dwt.h"
#include "cmsis_os.h"

/*------------------------------------extern------------------------------------*/

/*-----------------------------------macro------------------------------------*/

/*----------------------------------function----------------------------------*/

uint8_t comServiceInit();

void can1SendTask(void *argument);
void can2SendTask(void *argument);
void can3SendTask(void *argument);
void uart3RxProcessTask(void *argument);
void usbCdcProcessTask(void *argument);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#endif