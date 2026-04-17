#include "com_config.h"

#include "topics.h"
#include <string.h>

typedef struct
{
    float yaw;
    float pitch;
    float roll;
} imu_msg_t;

static Subscriber *imu_sub = NULL;
static imu_msg_t imu_local;

osThreadId_t CAN1_Send_TaskHandle;
osThreadId_t CAN2_Send_TaskHandle;
osThreadId_t CAN3_Send_TaskHandle;

QueueHandle_t CAN1_TxPort;
QueueHandle_t CAN2_TxPort;
QueueHandle_t CAN3_TxPort;


uint8_t Common_Service_Init()
{
    CAN1_TxPort = xQueueCreate(CAN1_TX_QUEUE_SIZE, sizeof(FDCAN_TxFrame_TypeDef));
    CAN2_TxPort = xQueueCreate(CAN2_TX_QUEUE_SIZE, sizeof(FDCAN_TxFrame_TypeDef));
    CAN3_TxPort = xQueueCreate(CAN3_TX_QUEUE_SIZE, sizeof(FDCAN_TxFrame_TypeDef));

    if ((CAN1_TxPort == NULL) || (CAN2_TxPort == NULL) || (CAN3_TxPort == NULL))
    {
        return 1;
    }

    return 0;
}

void CAN1_Rx_Callback(FDCAN_RxFrame_TypeDef *can_instance)
{
    if (can_instance->Header.IdType == FDCAN_STANDARD_ID)
    {
        /* 标准帧接收处理 */
        switch (can_instance->Header.Identifier)
        {
        case 0x201: {
            
            break;
        }
        case 0x202: {
            
        }
        case 0x203: {
            
        }
        case 0x204: {
            
        }
        
        default:
            break;
        }
    }
    else if (can_instance->Header.IdType == FDCAN_EXTENDED_ID)
    {
        /* 扩展帧接收处理 */
    }
}
void CAN2_Rx_Callback(FDCAN_RxFrame_TypeDef *can_instance)
{
    if (can_instance->Header.IdType == FDCAN_STANDARD_ID)
    {
        /* 标准帧接收处理 */
        switch (can_instance->Header.Identifier)
        {
        case 0x201: {
            
            break;
        }
        case 0x202: {
            
        }
        case 0x203: {
            
        }
        case 0x204: {
            
        }
        
        default:
            break;
        }

    }
    else if (can_instance->Header.IdType == FDCAN_EXTENDED_ID)
    {
        /* 扩展帧接收处理 */
    }
}
void CAN3_Rx_Callback(FDCAN_RxFrame_TypeDef *can_instance)
{
    if (can_instance->Header.IdType == FDCAN_STANDARD_ID)
    {
        /* 标准帧接收处理 */
        switch (can_instance->Header.Identifier)
        {
        case 0x201: {

            break;
        }
        case 0x202: {

        }
        case 0x203: {

        }
        case 0x204: {

        }

        default:
            break;
        }
    }
    else if (can_instance->Header.IdType == FDCAN_EXTENDED_ID)
    {
        /* 扩展帧接收处理 */
    }
}

 void CAN1_Send_Task(void *argument) {
    portTickType currentTime = xTaskGetTickCount();

    FDCAN_TxFrame_TypeDef temp_can_txmsg;
    uint8_t free_can_mailbox;
    for (;;){
        if (xQueueReceive(CAN1_TxPort, &temp_can_txmsg, 0) == pdTRUE) {
        do {
        free_can_mailbox = HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan1);
      } while (free_can_mailbox == 0);
        CAN_Transmit(&temp_can_txmsg); 
        } 
        vTaskDelayUntil(&currentTime, 1); // 每1ms执行一次发送任务
    }
}

void CAN2_Send_Task(void *argument) {
    portTickType currentTime = xTaskGetTickCount();

    FDCAN_TxFrame_TypeDef temp_can_txmsg;
    uint8_t free_can_mailbox;
    imu_sub = register_sub("imu_attitude", 4);
    for (;;){
        publish_data rx = imu_sub->get_data(imu_sub);
        if (rx.len == sizeof(imu_msg_t) && rx.data != NULL)
        {
            memcpy(&imu_local, rx.data, sizeof(imu_msg_t));
            // imu_local 里就是最新一帧
        }
        else if (rx.len == -1)
        {
            // 当前没有新数据
        }
        if (xQueueReceive(CAN2_TxPort, &temp_can_txmsg, 0) == pdTRUE) {
        do {
        free_can_mailbox = HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan2);
      } while (free_can_mailbox == 0);
        CAN_Transmit(&temp_can_txmsg); 
        } 
        vTaskDelayUntil(&currentTime, 1); // 每1ms执行一次发送任务
    }
}

void CAN3_Send_Task(void *argument) {
    portTickType currentTime = xTaskGetTickCount();

    FDCAN_TxFrame_TypeDef temp_can_txmsg;
    uint8_t free_can_mailbox;
    for (;;){
        if (xQueueReceive(CAN3_TxPort, &temp_can_txmsg, 0) == pdTRUE) {
        do {
        free_can_mailbox = HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan3);
      } while (free_can_mailbox == 0);
        CAN_Transmit(&temp_can_txmsg); 
        } 
        vTaskDelayUntil(&currentTime, 1); // 每1ms执行一次发送任务
    }
}

