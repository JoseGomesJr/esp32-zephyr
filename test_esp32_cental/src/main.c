/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>

#include "central_connection.h"

#define STRING_INPUT_STACK_SIZE 1024
K_THREAD_DEFINE(string_input, STRING_INPUT_STACK_SIZE, central_write, NULL, NULL, NULL, 1, 0, 1000);


int main(void)
{
    int err;
    err = central_gatt_init();

    if (err) {
        printk("Erro ao conectar o dispositivo");
        return -EBUSY;
    }
    return 0;
}
