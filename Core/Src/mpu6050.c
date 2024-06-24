/*
 * mpu6050.c
 *
 *  Created on: Jun 19, 2024
 *      Author: sun
 */
#include "mpu6050.h"
#include "MyI2C.h"
#include "MPU6050_Reg.h"
#include "i2c.h"
#define MPU6050_ADDRESS		0xD0

int16_t AX, AY, AZ, GX, GY, GZ;

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t *Data, uint16_t Len)
{
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDRESS, RegAddress,I2C_MEMADD_SIZE_8BIT, Data, Len, 0xfff);
}

void MPU6050_ReadReg(uint8_t RegAddress, uint8_t *Data, uint16_t Len)
{
	HAL_I2C_Mem_Read(&hi2c2, MPU6050_ADDRESS, RegAddress,I2C_MEMADD_SIZE_8BIT, Data, Len, 0xfff);
}

void MPU6050_Init(void)
{
	HAL_Delay(50);
	uint8_t data;
	data = 0x01;
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, &data, 1);
	data = 0x00;
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, &data, 1);
	data = 0x09;
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, &data, 1);
	data = 0x06;
	MPU6050_WriteReg(MPU6050_CONFIG, &data, 1);
	data = 0x18;
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, &data, 1);
	data = 0x18;
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, &data, 1);
}

//uint8_t MPU6050_GetID(void)
//{
//	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
//}

void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
		uint8_t data[12];
    uint8_t DataH, DataL;
    MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H, data, 12);

    DataH = data[0];
    DataL = data[1];
    *AccX = (DataH << 8) | DataL;

    DataH = data[2];
    DataL = data[3];
    *AccY = (DataH << 8) | DataL;

    DataH = data[4];
    DataL = data[5];
    *AccZ = (DataH << 8) | DataL;

    DataH = data[6];
    DataL = data[7];
    *GyroX = (DataH << 8) | DataL;

    DataH = data[8];
    DataL = data[9];
    *GyroY = (DataH << 8) | DataL;

    DataH = data[10];
    DataL = data[11];
    *GyroZ = (DataH << 8) | DataL;
}

void MPU6050_GetAcc(int16_t *AccX, int16_t *AccY, int16_t *AccZ)
{
		uint8_t buf[6];
		MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H, buf, 6);
		*AccX=((uint16_t)buf[0] << 8) | buf[1];
		*AccY=((uint16_t)buf[2] << 8) | buf[3];
		*AccZ=((uint16_t)buf[4] << 8) | buf[5];
}


void MPU6050_GetGyro(int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
		uint8_t buf[6];
		MPU6050_ReadReg(MPU6050_GYRO_XOUT_H, buf, 6);
		*GyroX=((uint16_t)buf[0] << 8) | buf[1];
		*GyroY=((uint16_t)buf[2] << 8) | buf[3];
		*GyroZ=((uint16_t)buf[4] << 8) | buf[5];
}


