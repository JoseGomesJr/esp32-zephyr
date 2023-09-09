//
// Created by jose on 08/09/23.
//

#ifndef ESP32_ZEPHYR_PERIPHERAL_SERVICES_H
#define ESP32_ZEPHYR_PERIPHERAL_SERVICES_H

#include <zephyr/kernel.h>
#include <stddef.h>
#include <string.h>
#include <zephyr/sys/printk.h>
#include <zephyr/settings/settings.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#define SERVICE_UUID BT_UUID_DECLARE_16(0xf1)

#define WHITE_CARAC BT_UUID_DECLARE_16(0xf2)

#define NOTIFY_CARAC BT_UUID_DECLARE_16(0xf3)


typedef struct
{
    uint8_t data[185];
    uint16_t len;
} data_t;

int peripheral_ready(void);

void peripheral_task(void);

#endif //ESP32_ZEPHYR_PERIPHERAL_SERVICES_H
