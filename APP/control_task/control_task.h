/**
 * @file control_task.h
 * @author Keten (2863861004@qq.com)
 * @brief
 * @version 0.1
 * @date 2026-04-18
 *
 * @copyright Copyright (c) 2026
 *
 * @attention :
 * @note :
 * @versioninfo :
 */
#pragma once

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "task.h"
#include "topics.h"

void controlInit();

void controlTask(void *argument);