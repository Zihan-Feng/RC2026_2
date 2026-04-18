#pragma once

/* 定义任务间的通讯结构体 */
#pragma pack(1)

// 底盘运动指令
typedef struct {
  float linear_x_;
  float linear_y_;
  float omega_;
} pub_chassis_cmd;

#pragma pack()