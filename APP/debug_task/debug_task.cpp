#include "debug_task.h"
#include "topics.h"

osThreadId_t Debug_TaskHandle;

typedef struct
{
    float yaw;
    float pitch;
    float roll;
} imu_msg_t;

static Publisher *imu_pub = NULL;
static imu_msg_t imu_msg;   // 建议静态或长期有效内存

void Debug_Task(void *argument) {
  portTickType currentTime;
  currentTime = xTaskGetTickCount();
  imu_pub = register_pub("imu_attitude");
  publish_data msg;
  for (;;) {
    imu_msg.yaw += 1.0f;
    imu_msg.pitch += 2.0f;
    imu_msg.roll += 3.0f;

    msg.data = (uint8_t *)&imu_msg;
    msg.len = sizeof(imu_msg_t);

    imu_pub->publish(imu_pub, msg);

    vTaskDelayUntil(&currentTime, 5);
    // vTaskDelay(5);
  }
}