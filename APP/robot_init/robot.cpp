#include "robot.h"
#include "Canbus.hpp"
#include "com_config.h"
#include "robot_task.h"

/* 更多特色功能可以在这里通过宏开关来决定是否使用 */

void Robot_Init() {
  /* 关闭中断，防止在初始化过程中发生中断 */
  __disable_irq();

  DWT_Init(275);

  // 通信外设初始化
  if (comServiceInit() != 0) {
    Error_Handler();
  }

  /* freertos任务调度初始化 */
  osTaskInit();

  /*初始化完成，开启中断 */
  __enable_irq();
}
