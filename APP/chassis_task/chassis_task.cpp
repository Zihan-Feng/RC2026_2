/**
 * @file chassis_task.cpp
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

#include "chassis_task.h"
#include "Motor.hpp"
#include "com_config.h"
#include "topic_pool.h"
#include "topics.h"

#include <cstring>

osThreadId_t ChassisTaskHandle;

extern C620Motor chassis_motor1, chassis_motor2, chassis_motor3, chassis_motor4;

Subscriber *chassis_cmd_sub;
pub_chassis_cmd chassis_cmd_data;

// 用到的初始化
static inline void chassisInit() {
  // PID初始化

  // 订阅初始化
  chassis_cmd_sub = register_sub("chassis_cmd", 8);
}

static inline void cmdCalculate() {}

void chassisTask(void *argument) {
  TickType_t currentTime = xTaskGetTickCount();

  chassisInit();
  publish_data chassis_cmd_sub_data;

  for (;;) {
    chassis_cmd_sub_data = chassis_cmd_sub->get_data(chassis_cmd_sub);
    if (chassis_cmd_sub_data.len ==
            static_cast<int>(sizeof(chassis_cmd_data)) &&
        chassis_cmd_sub_data.data != nullptr) {
      std::memcpy(&chassis_cmd_data, chassis_cmd_sub_data.data,
                  sizeof(chassis_cmd_data));
    }
    vTaskDelayUntil(&currentTime, 5); // 每1ms执行一次发送任务
  }
}