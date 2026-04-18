/**
 * @file control_task.cpp
 * @author Keten (2863861004@qq.com)
 * @brief 控制中枢，遥控/上位机 接口都接入到此，然后向其他任务发布可能的控制指令
 * @version 0.1
 * @date 2026-04-18
 *
 * @copyright Copyright (c) 2026
 *
 * @attention :
 * @note :
 * @versioninfo :
 */
#include "control_task.h"
#include "topic_pool.h"
#include "topics.h"

osThreadId_t ControlTaskHandle;

// 发布底盘控制指令
Publisher *chassis_cmd_pub;
pub_chassis_cmd chassis_cmd;

void controlInit() { chassis_cmd_pub = register_pub("chassis_cmd"); }

void controlTask(void *argument) {
  TickType_t currentTime = xTaskGetTickCount();

  controlInit();

  for (;;) {
    publish_data p_chassis_cmd_data;
    chassis_cmd.linear_x_ = 0.5;
    chassis_cmd.linear_y_ = 0.5;
    p_chassis_cmd_data.data = (uint8_t *)&chassis_cmd;
    p_chassis_cmd_data.len = sizeof(chassis_cmd);
    chassis_cmd_pub->publish(chassis_cmd_pub, p_chassis_cmd_data);

    vTaskDelayUntil(&currentTime, 5);
  }
}