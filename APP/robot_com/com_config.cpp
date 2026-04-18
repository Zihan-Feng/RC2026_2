#include "com_config.h"
#include "FreeRTOS.h"
#include "task.h"

#include "Canbus.hpp"
#include "Motor.hpp"
#include <cstdint>

osThreadId_t CAN1_Send_TaskHandle;
osThreadId_t CAN2_Send_TaskHandle;
osThreadId_t CAN3_Send_TaskHandle;

extern FDCAN_HandleTypeDef hfdcan1;
extern FDCAN_HandleTypeDef hfdcan2;
extern FDCAN_HandleTypeDef hfdcan3;

CanBus fdcan1_bus(hfdcan1);
CanBus fdcan2_bus(hfdcan2);
CanBus fdcan3_bus(hfdcan3);

// can设备

// 底盘电机
// C620Motor chassis_motor1(&fdcan2_bus, 0x201, 0, 0x200, 0);
// C620Motor chassis_motor2(&fdcan2_bus, 0x202, 0, 0x200, 0);
// C620Motor chassis_motor3(&fdcan2_bus, 0x203, 0, 0x200, 0);
// C620Motor chassis_motor4(&fdcan2_bus, 0x204, 0, 0x200, 0);

//
C610Motor arm2006_motor(&fdcan2_bus, 0x201, 0, 0x200, 0);
C620Motor arm3508_motor(&fdcan2_bus, 0x203, 0, 0x200, 0);

uint8_t comServiceInit() {
  // can外设初始化
  canFilterInit(&hfdcan2, FDCAN_STANDARD_ID, FDCAN_FILTER_TO_RXFIFO0, 0, 0);
  canFilterInit(&hfdcan2, FDCAN_STANDARD_ID, FDCAN_FILTER_TO_RXFIFO1, 0, 0);
  bspCanInit(&hfdcan2);
  canFilterInit(&hfdcan3, FDCAN_STANDARD_ID, FDCAN_FILTER_TO_RXFIFO0, 0, 0);
  canFilterInit(&hfdcan3, FDCAN_STANDARD_ID, FDCAN_FILTER_TO_RXFIFO1, 0, 0);
  bspCanInit(&hfdcan3);

  // can 总线初始化
  fdcan1_bus.init();
  fdcan2_bus.init();
  fdcan3_bus.init();

  // chassis_motor1.init();
  // chassis_motor2.init();
  // chassis_motor3.init();
  // chassis_motor4.init();

  arm2006_motor.init();
  arm3508_motor.init();

  // fdcan2_bus.registerDevice(&chassis_motor1);
  // fdcan2_bus.registerDevice(&chassis_motor2);
  // fdcan2_bus.registerDevice(&chassis_motor3);
  // fdcan2_bus.registerDevice(&chassis_motor4);
  fdcan2_bus.registerDevice(&arm2006_motor);
  fdcan2_bus.registerDevice(&arm3508_motor);

  return 0;
}

void can1SendTask(void *argument) {
  TickType_t currentTime = xTaskGetTickCount();

  for (;;) {

    vTaskDelayUntil(&currentTime, 1); // 每1ms执行一次发送任务
  }
}

void can2SendTask(void *argument) {
  TickType_t currentTime = xTaskGetTickCount();
  CanBus::ClassicPack pack;
  pack.type = CanBus::Type::STANDARD;
  pack.id = 0x200; // DJI Group 2

  uint8_t len = 8;
  for (;;) {
    // 调用方负责保证 motor_count 和 motor_ids/commands 数组对应
    // 如果需要聚合多个电机到 0x200 帧：
    uint32_t motor_ids[] = {arm3508_motor.id(), arm2006_motor.id()};
    int16_t commands[] = {static_cast<int16_t>(arm3508_motor.cmdTrans()),
                          static_cast<int16_t>(arm2006_motor.cmdTrans())};
    packDJIMotorCanMsg(0x200, motor_ids, commands, 2, pack.data, len);
    arm3508_motor.manager_->addCanMsg(pack);
    //
    // 对于当前代码（arm2006_motor, arm3508_motor），需要逐个构建帧
    // 或者如果需要聚合，调用方提前提取 ID 和命令值

    vTaskDelayUntil(&currentTime, 1); // 每1ms执行一次发送任务
  }
}

void can3SendTask(void *argument) {
  TickType_t currentTime = xTaskGetTickCount();
  for (;;) {

    vTaskDelayUntil(&currentTime, 1); // 每1ms执行一次发送任务
  }
}
