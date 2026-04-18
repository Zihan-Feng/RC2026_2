/**
 * @file Motor.cpp
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
#include "Motor.hpp"
#include <cstdint>
#include <cstring>

// id换
static int8_t djiSlotFromIds(uint32_t tx_id, uint32_t rx_id) {
  if (tx_id == 0x200) {
    if (rx_id >= 0x201 && rx_id <= 0x204) {
      return static_cast<int8_t>(rx_id - 0x201);
    }
    return -1;
  }

  if (tx_id == 0x1FF) {
    if (rx_id >= 0x205 && rx_id <= 0x208) {
      return static_cast<int8_t>(rx_id - 0x205);
    }
    return -1;
  }

  return -1;
}

void packDJIMotorCanMsg(uint32_t tx_id, const uint32_t motor_ids[],
                        const int16_t commands[], uint8_t motor_count,
                        uint8_t data[8], uint8_t &len) {
  len = 8;
  for (uint8_t i = 0; i < 8; ++i) {
    data[i] = 0;
  }

  for (uint8_t i = 0; i < motor_count; ++i) {
    if (motor_ids[i] == 0) {
      continue;
    }

    int8_t slot = -1;
    if (tx_id == 0x200) {
      if (motor_ids[i] >= 0x201 && motor_ids[i] <= 0x204) {
        slot = static_cast<int8_t>(motor_ids[i] - 0x201);
      }
    } else if (tx_id == 0x1FF) {
      if (motor_ids[i] >= 0x205 && motor_ids[i] <= 0x208) {
        slot = static_cast<int8_t>(motor_ids[i] - 0x205);
      }
    }

    if (slot < 0 || slot > 3) {
      continue;
    }

    const int16_t cmd = commands[i];
    data[slot * 2] = static_cast<uint8_t>(cmd >> 8);
    data[slot * 2 + 1] = static_cast<uint8_t>(cmd & 0xFF);
  }
}
