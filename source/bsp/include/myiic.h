#ifndef _MYIIC_H
#define _MYIIC_H

#include "stm32f10x.h"
#include "adaptor.h"

typedef enum
{
    MY_IIC1 = 0x0,
    MY_IIC2 = 0x1,
}iicx_e;

void myiic_w_scl(iicx_e iicx, BitAction bit_value);
void myiic_w_sda(iicx_e iicx, BitAction BitValue);
uint8_t myiic_r_sda(iicx_e iicx);
void myiic_init(iicx_e iicx);
void myiic_start(iicx_e iicx);
void myiic_stop(iicx_e iicx);
void myiic_send_byte(iicx_e iicx, uint8_t data);
uint8_t  myiic_receive_byte(iicx_e iicx);
void myiic_send_ack(iicx_e iicx, BitAction ack);
uint8_t myiic_receive_ack(iicx_e iicx);

#endif
