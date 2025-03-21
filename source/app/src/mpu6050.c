#include "mpu6050.h"
#include "myiic.h"



void mpu6050_write_reg(uint8_t reg_address, uint8_t data)
{
    myiic_start(MY_IIC1);
    myiic_send_byte(MY_IIC1, MPU6050_ADDRESS);
    myiic_receive_ack(MY_IIC1);
    myiic_send_byte(MY_IIC1, reg_address);
    myiic_receive_ack(MY_IIC1);
    myiic_send_byte(MY_IIC1, data);
    myiic_stop(MY_IIC1);
}

uint8_t mpu6050_read_reg(uint8_t reg_address)
{
    uint8_t data;
    myiic_start(MY_IIC1);
    myiic_send_byte(MY_IIC1, MPU6050_ADDRESS);
    myiic_receive_ack(MY_IIC1);
    myiic_send_byte(MY_IIC1, reg_address);
    myiic_receive_ack(MY_IIC1);

    myiic_start(MY_IIC1);    
    myiic_send_byte(MY_IIC1, MPU6050_ADDRESS | 0x01);
    myiic_receive_ack(MY_IIC1);
    data = myiic_receive_byte(MY_IIC1);
    myiic_send_ack(MY_IIC1, Bit_RESET);
    myiic_stop(MY_IIC1);

    return data;

}

void mpu6050_init(void)
{
    myiic_init(MY_IIC1);
	mpu6050_write_reg(MPU6050_PWR_MGMT_1, 0x01);		//电源管理寄存器1，取消睡眠模式，选择时钟源为X轴陀螺仪
	mpu6050_write_reg(MPU6050_PWR_MGMT_2, 0x00);		//电源管理寄存器2，保持默认值0，所有轴均不待机
	mpu6050_write_reg(MPU6050_SMPLRT_DIV, 0x09);		//采样率分频寄存器，配置采样率
	mpu6050_write_reg(MPU6050_CONFIG, 0x06);			//配置寄存器，配置DLPF
	mpu6050_write_reg(MPU6050_GYRO_CONFIG, 0x18);	//陀螺仪配置寄存器，选择满量程为±2000°/s
	mpu6050_write_reg(MPU6050_ACCEL_CONFIG, 0x18);	//加速度计配置寄存器，选择满量程为±16g

}

uint8_t mpu6050_get_id(void)
{
    return mpu6050_read_reg(MPU6050_WHO_AM_I);
}

void mpu6050_get_data(int16_t *AccX, int16_t *AccY, int16_t *AccZ, int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
    uint8_t DataH, DataL;								//定义数据高8位和低8位的变量
	
	DataH = mpu6050_read_reg(MPU6050_ACCEL_XOUT_H);		//读取加速度计X轴的高8位数据
	DataL = mpu6050_read_reg(MPU6050_ACCEL_XOUT_L);		//读取加速度计X轴的低8位数据
	*AccX = (DataH << 8) | DataL;						//数据拼接，通过输出参数返回
	
	DataH = mpu6050_read_reg(MPU6050_ACCEL_YOUT_H);		//读取加速度计Y轴的高8位数据
	DataL = mpu6050_read_reg(MPU6050_ACCEL_YOUT_L);		//读取加速度计Y轴的低8位数据
	*AccY = (DataH << 8) | DataL;						//数据拼接，通过输出参数返回
	
	DataH = mpu6050_read_reg(MPU6050_ACCEL_ZOUT_H);		//读取加速度计Z轴的高8位数据
	DataL = mpu6050_read_reg(MPU6050_ACCEL_ZOUT_L);		//读取加速度计Z轴的低8位数据
	*AccZ = (DataH << 8) | DataL;						//数据拼接，通过输出参数返回
	
	DataH = mpu6050_read_reg(MPU6050_GYRO_XOUT_H);		//读取陀螺仪X轴的高8位数据
	DataL = mpu6050_read_reg(MPU6050_GYRO_XOUT_L);		//读取陀螺仪X轴的低8位数据
	*GyroX = (DataH << 8) | DataL;						//数据拼接，通过输出参数返回
	
	DataH = mpu6050_read_reg(MPU6050_GYRO_YOUT_H);		//读取陀螺仪Y轴的高8位数据
	DataL = mpu6050_read_reg(MPU6050_GYRO_YOUT_L);		//读取陀螺仪Y轴的低8位数据
	*GyroY = (DataH << 8) | DataL;						//数据拼接，通过输出参数返回
	
	DataH = mpu6050_read_reg(MPU6050_GYRO_ZOUT_H);		//读取陀螺仪Z轴的高8位数据
	DataL = mpu6050_read_reg(MPU6050_GYRO_ZOUT_L);		//读取陀螺仪Z轴的低8位数据
	*GyroZ = (DataH << 8) | DataL;						//数据拼接，通过输出参数返回

}

