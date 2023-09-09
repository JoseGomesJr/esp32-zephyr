#include "peripheral_services.h"



#define STRING_OUTPUT_STACK_SIZE 1024
K_THREAD_DEFINE(peripheral_string, STRING_OUTPUT_STACK_SIZE, peripheral_task, NULL, NULL, NULL,
                7, 0, 0);

int main(void)
{
    int err;
    err = peripheral_ready();
    if(err){
        printk("Erro ao inicializar o dispositivo Periférico!.\n");
        return 0;
    }
    return 0;
}

