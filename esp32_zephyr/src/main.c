#include <zephyr/kernel.h>
#include <stddef.h>
#include <string.h>
#include <zephyr/sys/printk.h>
#include <zephyr/settings/settings.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

typedef struct
{
    uint8_t data[185];
    uint16_t len;
} data_t;

static data_t data_e={
        .len=0
};

static struct k_msgq my_msgq;

struct bt_gatt_exchange_params exchange_params;

static struct bt_uuid_128 vnd_canais_uuid = BT_UUID_INIT_128(
        0xf1, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
        0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12);

static struct bt_uuid_128 vnd_canais_caracter_uuid = BT_UUID_INIT_128(
        0xf2, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
        0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12);

static struct bt_uuid_128 vnd_info_uuid = BT_UUID_INIT_128(
        0x13, 0xde, 0xbc, 0x7a, 0x78, 0x56, 0x34, 0x12,
        0x78, 0x56, 0x00, 0x12, 0x48, 0x56, 0x34, 0x00);

static struct bt_uuid_32 vnd_info_caracter_uuid = BT_UUID_INIT_128(
        0xf0, 0xfe, 0xbc, 0x14, 0x78, 0x56, 0x34, 0x12,
        0x98, 0x56, 0x34, 0x12, 0x89, 0x56, 0x34, 0x00);


static ssize_t read_channels(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                             void *buf, uint16_t len, uint16_t offset) {
    const uint8_t *value = attr->user_data;

    return bt_gatt_attr_read(conn, attr, buf, data_e.len, offset, value,
                             sizeof(data_e));
}

static ssize_t write_channels(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                              const void *buf, uint16_t len, uint16_t offset,
                              uint8_t flags) {
    static data_t data;
    data.len = len;
    memcpy(data.data, buf, len);
    k_msgq_put(&my_msgq, &data, K_NO_WAIT);

    return len;
}

BT_GATT_SERVICE_DEFINE(vnd_canais,
                       BT_GATT_PRIMARY_SERVICE(&vnd_canais_uuid),
                       BT_GATT_CHARACTERISTIC(&vnd_canais_caracter_uuid.uuid,
                                              BT_GATT_CHRC_WRITE,
                                              BT_GATT_PERM_WRITE,
                                              NULL, write_channels, NULL),
);
BT_GATT_SERVICE_DEFINE(vnd_info,
                       BT_GATT_PRIMARY_SERVICE(&vnd_info_uuid),
                       BT_GATT_CHARACTERISTIC(&vnd_info_caracter_uuid.uuid,
                                              BT_GATT_CHRC_NOTIFY | BT_GATT_CHRC_READ,
                                              BT_GATT_PERM_READ,
                                              read_channels, NULL, NULL),
                       BT_GATT_CCC(NULL, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
);

static const struct bt_data ad[] = {
        BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
        BT_DATA_BYTES(BT_DATA_UUID16_ALL,
                      BT_UUID_16_ENCODE(BT_UUID_HRS_VAL),
                      BT_UUID_16_ENCODE(BT_UUID_BAS_VAL),
                      BT_UUID_16_ENCODE(BT_UUID_CTS_VAL)),
        BT_DATA_BYTES(BT_DATA_UUID128_ALL,
                      0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
                      0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12),
};


static void exchange_func(struct bt_conn *conn, uint8_t err, struct bt_gatt_exchange_params *params) {
    if (!err) {
        uint16_t mtu = bt_gatt_get_mtu(conn);
        printk("New MTU is %d", mtu);
    }
}

static void connected(struct bt_conn *conn, uint8_t err) {
    if (err) {
        printk("Connection failed (err 0x%02x)\n", err);
    } else {
        printk("Connected\n");
        exchange_params.func = exchange_func;
        bt_gatt_exchange_mtu(conn, &exchange_params);
    }
}

static void disconnected(struct bt_conn *conn, uint8_t reason) {
    printk("Disconnected (reason 0x%02x)\n", reason);
}

static void auth_passkey_display(struct bt_conn *conn, unsigned int passkey) {
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    printk("Passkey for %s: %06u\n", addr, passkey);
}

static void auth_cancel(struct bt_conn *conn) {
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    printk("Pairing cancelled: %s\n", addr);
}

static struct bt_conn_auth_cb auth_cb_display = {
        .passkey_display = auth_passkey_display,
        .passkey_entry = NULL,
        .cancel = auth_cancel,
};


static struct bt_conn_cb conn_callbacks = {
        .connected = connected,
        .disconnected = disconnected,
};

static void init_msg(void){
    char __aligned(4) my_msgq_buffer[10 * sizeof(data_t)];
    k_msgq_init(&my_msgq, my_msgq_buffer, sizeof(data_t), 10);
}

void bt_ready(void) {
    int err;

    //information.number_of_channels = NUMBER_OF_CHANNELS;

    err = bt_enable(NULL);
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
        return;
    }

    init_msg();
    if (IS_ENABLED(CONFIG_SETTINGS)) {
        settings_load();
    }


    printk("Bluetooth initialized\n");

    err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err) {
        printk("Advertising failed to start (err %d)\n", err);
        return;
    }

    bt_conn_cb_register(&conn_callbacks);
    bt_conn_auth_cb_register(&auth_cb_display);

    //bt_gatt_notify(NULL, &vnd_info.attrs[1], &data_e, data_e.len);

    printk("Advertising successfully started\n");
}


//K_THREAD_DEFINE(ble_thread_id, STACKSIZE, ble_thread, NULL, NULL, NULL,
//                PRIORITY, 0, 0);

void main(void)
{
    /* Implement notification. At the moment there is no suitable way
     * of starting delayed work so we do it here
     */
    bt_ready();
    while (1) {
        k_sleep(K_SECONDS(1));

        /* Adicionar uma verificação quando o num_channels for mudado*/

    }
}

