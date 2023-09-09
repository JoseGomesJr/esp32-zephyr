//
// Created by jose on 08/09/23.
//

#ifndef CENTRAL_GATT_WRITE_CENTRAL_CONNECTION_H
#define CENTRAL_GATT_WRITE_CENTRAL_CONNECTION_H
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/settings/settings.h>
#include <zephyr/console/console.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/sys/byteorder.h>

#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>


#define SERVICE_UUID BT_UUID_DECLARE_16(0xf1)

#define WHITE_CARAC BT_UUID_DECLARE_16(0xf2)

#define NOTIFY_CARAC BT_UUID_DECLARE_16(0xf3)


int central_gatt_init(void);

void central_write(void);

#endif //CENTRAL_GATT_WRITE_CENTRAL_CONNECTION_H
