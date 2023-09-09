//
// Created by jose on 08/09/23.
//
#include "central_connection.h"

static void central_disconn(struct bt_conn *conn, uint8_t reason);

static void central_conn(struct bt_conn *conn, uint8_t conn_err);

static uint8_t central_discover_func(struct bt_conn *conn,
                                     const struct bt_gatt_attr *attr,
                                     struct bt_gatt_discover_params *params);

static void central_scan_start(void);

static bool central_eir_found(struct bt_data *data, void *user_data);

uint8_t central_notify(struct bt_conn *conn, struct bt_gatt_subscribe_params *params,
                       const void *buf, uint16_t length);

static int central_write_input(uint8_t *buf, uint16_t buf_len);

static struct {
    struct bt_conn_cb conn;
    struct bt_conn *default_conn;
    struct bt_uuid_16 discover_uuid;
    struct bt_gatt_discover_params discover_params;
    struct bt_gatt_subscribe_params subscribe_params;
    uint16_t write_handle;
} self = {
    .conn          = {.connected = central_conn, .disconnected = central_disconn

    },
    .default_conn  = NULL,
    .discover_uuid = BT_UUID_INIT_16(0),
    .write_handle  = 0,
};

static bool central_eir_found(struct bt_data *data, void *user_data)
{
    bt_addr_le_t *addr = user_data;
    int i;

    printk("[AD]: %u data_len %u.\n", data->type, data->data_len);

    switch (data->type) {
    case BT_DATA_UUID16_SOME:
    case BT_DATA_UUID16_ALL:
        if (data->data_len % sizeof(uint16_t) != 0U) {
            printk("AD mal formado.\n");
            return true;
        }

        for (i = 0; i < data->data_len; i += sizeof(uint16_t)) {
            struct bt_le_conn_param *param;
            struct bt_uuid *uuid;
            uint16_t u16;
            int err;

            memcpy(&u16, &data->data[i], sizeof(u16));
            uuid = BT_UUID_DECLARE_16(sys_le16_to_cpu(u16));
            if (bt_uuid_cmp(uuid, SERVICE_UUID)) {
                continue;
            }

            err = bt_le_scan_stop();
            if (err) {
                printk("Falha no scan (err %d).\n", err);
                continue;
            }

            param = BT_LE_CONN_PARAM_DEFAULT;
            err   = bt_conn_le_create(addr, BT_CONN_LE_CREATE_CONN, param,
                                      &self.default_conn);
            if (err) {
                printk("Falha na criação da conexão (err %d).\n", err);
                central_scan_start();
            }
            return false;
        }
    }
    return true;
}

static void central_callbak_scan(const bt_addr_le_t *addr, int8_t rssi, uint8_t type,
                                 struct net_buf_simple *ad)
{
    char dev[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(addr, dev, sizeof(dev));
    printk("[DEVICE]: %s, AD evt type %u, AD data len %u, RSSI %i\n", dev, type, ad->len,
           rssi);

    if (type == BT_GAP_ADV_TYPE_ADV_IND || type == BT_GAP_ADV_TYPE_ADV_DIRECT_IND) {
        bt_data_parse(ad, central_eir_found, (void *) addr);
    }
}

static void central_scan_start(void)
{
    int err;
    err = bt_le_scan_start(BT_LE_SCAN_ACTIVE, central_callbak_scan);
    if (err) {
        printk("Scanning failed to start (err %d)\n", err);
        return;
    }
}

static void central_conn(struct bt_conn *conn, uint8_t conn_err)
{
    char addr[BT_ADDR_LE_STR_LEN];
    int err;

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    if (conn_err) {
        printk("Failed to connect to %s (%u)\n", addr, conn_err);

        bt_conn_unref(self.default_conn);
        self.default_conn = NULL;

        central_scan_start();
        return;
    }

    printk("Connected: %s\n", addr);

    if (conn == self.default_conn) {
        memcpy(&self.discover_uuid, SERVICE_UUID, sizeof(self.discover_uuid));
        self.discover_params.uuid         = &self.discover_uuid.uuid;
        self.discover_params.func         = central_discover_func;
        self.discover_params.start_handle = BT_ATT_FIRST_ATTRIBUTE_HANDLE;
        self.discover_params.end_handle   = BT_ATT_LAST_ATTRIBUTE_HANDLE;
        self.discover_params.type         = BT_GATT_DISCOVER_PRIMARY;

        err = bt_gatt_discover(self.default_conn, &self.discover_params);
        if (err) {
            printk("Discover failed(err %d)\n", err);
            return;
        }
    }
}

static void central_disconn(struct bt_conn *conn, uint8_t reason)
{
    int err;
    printk("Desconectado. (motivo: %u).\n", reason);

    if (self.default_conn) {
        bt_conn_unref(self.default_conn);
        self.default_conn = NULL;
    }

    central_scan_start();
}

uint8_t central_notify(struct bt_conn *conn, struct bt_gatt_subscribe_params *params,
                       const void *buf, uint16_t length)
{
    if (!buf) {
        printk("[Unsubscribed]\n");
        params->value_handle = 0U;
        return BT_GATT_ITER_CONTINUE;
    }

    char data[length + 1];

    memcpy(data, buf, length);
    data[length] = '\0';

    printk("Dados recebidos como notificação: %s. Length %u.\n", data, length);
    return BT_GATT_ITER_CONTINUE;
}

static uint8_t central_discover_func(struct bt_conn *conn,
                                     const struct bt_gatt_attr *attr,
                                     struct bt_gatt_discover_params *params)
{
    int err;

    if (!attr) {
        printk("Discover complete\n");
        (void) memset(params, 0, sizeof(*params));
        return BT_GATT_ITER_STOP;
    }

    printk("[ATTRIBUTE] handle %u\n", attr->handle);

    if (!bt_uuid_cmp(self.discover_params.uuid, SERVICE_UUID)) {
        memcpy(&self.discover_uuid, WHITE_CARAC, sizeof(self.discover_uuid));
        self.discover_params.uuid         = &self.discover_uuid.uuid;
        self.discover_params.start_handle = attr->handle+1;
        self.discover_params.type         = BT_GATT_DISCOVER_CHARACTERISTIC;

        printk("OKOKK-- %d\n", self.discover_uuid.val);
        err = bt_gatt_discover(conn, &self.discover_params);
        if (err) {
            printk("Discover failed (err %d).\n", err);
        }
    }else if (!bt_uuid_cmp(self.discover_params.uuid, WHITE_CARAC)) {
        memcpy(&self.discover_uuid, NOTIFY_CARAC, sizeof(self.discover_uuid));
        self.discover_params.uuid          = &self.discover_uuid.uuid;
        self.discover_params.start_handle  = attr->handle + 1;
        self.discover_params.type          = BT_GATT_DISCOVER_CHARACTERISTIC;
        self.write_handle                 = bt_gatt_attr_value_handle(attr);
        printk("OKOKK-- %d\n", self.discover_uuid.val);
        err = bt_gatt_discover(conn, &self.discover_params);
        if (err) {
            printk("Discover failed (err %d).\n", err);
        }
    }
    else if (!bt_uuid_cmp(self.discover_params.uuid, NOTIFY_CARAC)) {
        memcpy(&self.discover_uuid, BT_UUID_GATT_CCC, sizeof(self.discover_uuid));
        self.discover_params.uuid         = &self.discover_uuid.uuid;
        self.discover_params.start_handle = attr->handle + 1;
        self.discover_params.type         = BT_GATT_DISCOVER_DESCRIPTOR;
        self.subscribe_params.value_handle = bt_gatt_attr_value_handle(attr);

        printk("OKOKK-- %d\n", self.discover_uuid.val);
        err = bt_gatt_discover(conn, &self.discover_params);
        if (err) {
            printk("Discover failed (err %d).\n", err);
        }
    }
   else {
        self.subscribe_params.notify     = central_notify;
        self.subscribe_params.value      = BT_GATT_CCC_NOTIFY;
        self.subscribe_params.ccc_handle = attr->handle;

        err = bt_gatt_subscribe(conn, &self.subscribe_params);
        if (err && err != -EALREADY) {
            printk("Subscribe failed (err %d)\n", err);
        } else {
            printk("[SUBSCRIBED]\n");
        }

        return BT_GATT_ITER_STOP;
    }

    return BT_GATT_ITER_STOP;
}

int central_gatt_init(void)
{
    int err;

    err = bt_enable(NULL);
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
        return -EIO;
    }

    if (IS_ENABLED(CONFIG_SETTINGS)) {
        settings_load();
    }

    bt_conn_cb_register(&self.conn);

    central_scan_start();

    printk("Bluetooth initialized\n");
    return 0;
}

static int central_write_input(uint8_t *buf, uint16_t buf_len)
{
    int err = 0;

    if (self.default_conn == NULL) {
        printk("Not connected!");
        return -EFAULT;
    }

    err = bt_gatt_write_without_response(self.default_conn, self.write_handle, buf,
                                         buf_len, false);
    if (err) {
        printk("%s: Write cmd failed (%d).\n", __func__, err);
        return -EBUSY;
    }

    return 0;
}

void central_write(void)
{
    int err    = 0;
    char *line = NULL;

    console_getline_init();

    while (true) {
        if (self.default_conn == NULL) {
            printk("Not connected!");
        }

        printk("Digite uma string:\n");
        printk(">\n");
        line = console_getline();

        if (line == NULL) {
            printk("entrada inválida!\n");
            continue;
        }

        printk("Enviando dado...\n");
        printk("%s\n", line);
        err = central_write_input(line, strlen(line));

        if(err){
            printk("Erro na escrita da mensagem");
        }
    }
}