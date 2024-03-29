//
// Created by jose on 08/09/23.
//

#include "peripheral_services.h"

static ssize_t read_channels(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                             void *buf, uint16_t len, uint16_t offset);

static ssize_t write_channels(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                              const void *buf, uint16_t len, uint16_t offset,
                              uint8_t flags);

static void connected(struct bt_conn *conn, uint8_t err);

static void disconnected(struct bt_conn *conn, uint8_t reason);

static struct {
    struct {
        struct k_msgq periheral_menssage_ble;
        char __aligned(4) msgq_buffer[10 * sizeof(data_t)];
    };
    struct bt_gatt_exchange_params exchange_params;
    struct bt_conn_cb conn_callbacks;
    struct bt_conn *default_conn;
    data_t data_e;

} self = {
    .data_e = {0},
    .conn_callbacks = {
        .connected    = connected,
        .disconnected = disconnected,
    },
    .default_conn = NULL,
};

void ble_peripheral_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value) {
    ARG_UNUSED(attr);
    bool notify_enabled = (value == BT_GATT_CCC_NOTIFY);
    printk("NOTIFY %s.\n",(notify_enabled ? "enabled" : "disabled"));
}

static ssize_t write_channels(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                              const void *buf, uint16_t len, uint16_t offset,
                              uint8_t flags)
{
    static data_t data;
    data.len = len;
    memcpy(data.data, buf, len);
    k_msgq_put(&self.periheral_menssage_ble, &data, K_NO_WAIT);

    return len;
}
static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS,(BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA_BYTES(BT_DATA_UUID16_ALL,BT_UUID_16_ENCODE(0xf1),),
};

BT_GATT_SERVICE_DEFINE(
    peripheral_service, BT_GATT_PRIMARY_SERVICE(SERVICE_UUID),
    BT_GATT_CHARACTERISTIC(WHITE_CARAC, BT_GATT_CHRC_WRITE, BT_GATT_PERM_WRITE, NULL,
                           write_channels, NULL),
    BT_GATT_CHARACTERISTIC(NOTIFY_CARAC, BT_GATT_CHRC_NOTIFY,
                           BT_GATT_PERM_NONE, NULL, NULL, NULL),
    BT_GATT_CCC(ble_peripheral_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),);


static void exchange_func(struct bt_conn *conn, uint8_t err,
                          struct bt_gatt_exchange_params *params)
{
    if (!err) {
        uint16_t mtu = bt_gatt_get_mtu(conn);
        printk("New MTU is %d", mtu);
    }
}

static void connected(struct bt_conn *conn, uint8_t err)
{
    if (err) {
        printk("Connection failed (err 0x%02x)\n", err);
    } else {
        printk("Connected\n");
        self.default_conn = bt_conn_ref(conn);
        self.exchange_params.func = exchange_func;
        bt_gatt_exchange_mtu(conn, &self.exchange_params);
    }
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
    int err;
    printk("Disconnected (reason 0x%02x)\n", reason);

    if (self.default_conn) {
        bt_conn_unref(self.default_conn);
        self.default_conn = NULL;
    }

    err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err) {
        printk("Falha ao iniciar o Advertising. (err %d).\n", err);
    }
}

static struct bt_conn_cb conn_callbacks = {
    .connected    = connected,
    .disconnected = disconnected,
};

static void init_msg(void)
{
    k_msgq_init(&self.periheral_menssage_ble, self.msgq_buffer, sizeof(data_t), 10);
}

int peripheral_ready(void)
{
    int err;

    err = bt_enable(NULL);
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
        return -EBUSY;
    }

    init_msg();
    if (IS_ENABLED(CONFIG_SETTINGS)) {
        settings_load();
    }

    printk("Bluetooth initialized\n");

    err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err) {
        printk("Advertising failed to start (err %d)\n", err);
        return -EBUSY;
    }

    bt_conn_cb_register(&conn_callbacks);

    // bt_gatt_notify(NULL, &vnd_info.attrs[1], &data_e, data_e.len);

    printk("Advertising successfully started\n");

    return 0;
}

void peripheral_task(void){
    int err;
    data_t data = {0};

    while (true){
        k_msgq_get(&self.periheral_menssage_ble, &data, K_FOREVER);
        for (int i = 0; i < data.len; i++) {
            if ((data.data[i] >= 'a') && ((data.data[i] <= 'z'))) {
                data.data[i] = 'A' + (data.data[i] - 'a');
            }
        }

        printk("Enviando Dado...\n");
        printk("%s.\n",data.data);

        err = bt_gatt_notify(NULL, &peripheral_service.attrs[3], data.data, data.len);
        if (err) {
            printk("ERRO AO NOTIFICAR.\n");
        }
    }
}
