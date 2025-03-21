#include "stm32f10x.h"                  // Device header
#include "myiic.h"
#include "delay.h"

/*
* 写SCL
*/
void myiic_w_scl(iicx_e iicx, BitAction bit_value)
{
    switch(iicx)
    {
        case MY_IIC1:
            GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)bit_value);//BitAction SET RESET
            delay_us(10);
            break;
        case MY_IIC2:
            break;
        default:
            break;
    }
}
/*
* 写SDA
*/
void myiic_w_sda(iicx_e iicx, BitAction BitValue)
{
    switch(iicx)
    {
        case MY_IIC1:
            GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)BitValue);
            delay_us(10);
            break;
        case MY_IIC2:
            break;
        default:
            break;
    }
}
/*
* 读SDA
*/
uint8_t myiic_r_sda(iicx_e iicx)
{
    uint8_t bit_value;
    switch(iicx)
    {
        case MY_IIC1:
            bit_value = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
            delay_us(10);
            break;
        default:            
            bit_value = (uint8_t)Bit_RESET;
            break;
    }
    return bit_value;
}
/*
* IIC初始化
*/
void myiic_init(iicx_e iicx)
{
    switch(iicx)
    {
        case MY_IIC1:
            //SCL PB10 SDA PB11
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
            
            GPIO_InitTypeDef GPIO_InitStructure;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//开漏输出
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            //SCL SDA置高电平
            GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
            break;
        case MY_IIC2:
            break;
        default:
            break;
    }
}
/*
* IIC启动
*/
void myiic_start(iicx_e iicx)
{
    myiic_w_sda(iicx, Bit_SET);
    myiic_w_scl(iicx, Bit_SET);
    myiic_w_sda(iicx, Bit_RESET);
    myiic_w_scl(iicx, Bit_RESET);
}
/*
* IIC停止
*/
void myiic_stop(iicx_e iicx)
{
    myiic_w_sda(iicx, Bit_RESET);
    myiic_w_scl(iicx, Bit_SET);
    myiic_w_sda(iicx, Bit_SET);
}
/*
* IIC发送一个字节
*/
void myiic_send_byte(iicx_e iicx, uint8_t data)
{
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        myiic_w_sda(iicx, (BitAction)(data & (0x80 >> i)));
        myiic_w_scl(iicx, Bit_SET);
        myiic_w_scl(iicx, Bit_RESET);
    }
}
/*
* IIC接收一个字节
*/
uint8_t myiic_receive_byte(iicx_e iicx)
{
    uint8_t i;
    uint8_t data = 0;
    myiic_w_sda(iicx, Bit_SET);
    for(i = 0; i < 8; i++)
    {        
        myiic_w_scl(iicx, Bit_SET);
        if(myiic_r_sda(iicx) == 0x1)
        {
            data |= (0x80 >> i);
        }
        myiic_w_scl(iicx, Bit_RESET);
    }
    return data;
}
/*
* IIC发送应答
*/
void myiic_send_ack(iicx_e iicx, BitAction ack)
{
    myiic_w_sda(iicx, ack);
    myiic_w_scl(iicx, Bit_SET);
    myiic_w_scl(iicx, Bit_RESET);
}
/*
* IIC接收应答
*/
uint8_t myiic_receive_ack(iicx_e iicx)
{
    uint8_t ack;
    myiic_w_sda(iicx, Bit_SET);
    myiic_w_scl(iicx, Bit_SET);
    ack = myiic_r_sda(iicx);
    myiic_w_scl(iicx, Bit_RESET);
    return ack;
}
