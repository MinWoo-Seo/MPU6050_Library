
#include <main.h>
#include <string.h>
#include <math.h>
#include "stm32f4xx_hal.h"

#define MPU6050_ADDRESS 0x68
#define WHO_AM_I 0x75
#define RAD2DEG 57.2957786
#define PI 3.14159265

//========Setting=======//
#define TEMPERATURE
#define ANGLE
//========Setting=======//


//========PWR_MGMT=======//
#define PWR_MGMT_1 0x6B
//========PWR_MGMT=======//

//========SMPLRT_DIV=======//
#define SMPLRT_DIV 0x19
//========SMPLRT_DIV=======//

//========STATUS=======//
#define INT_STATUS 0x3A
//========STATUS=======//


//========CONFIG=======//
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
//========CONFIG=======//

//========TEMP=======//
#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42
//========TEMP=======//

//========ACCEL=======//
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
//========ACCEL=======//

//========GYRO=======//
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48
//========GYRO=======//


//#define MPU6050_ADDRESS 0x68

//uint8_t mpu6050_i2c_address = MPU6050_ADDRESS << 1;


void Mpu6050_i2c_init(I2C_HandleTypeDef  *Your_i2c_handler);
void Mpu6050_i2c_TX (uint8_t mpu6050_register, uint8_t mpu6050_data);
uint8_t Mpu6050_i2c_RX (uint8_t mpu6050_register);
int16_t Mpu6050_ACC_X(void);
int16_t Mpu6050_ACC_Y(void);
int16_t Mpu6050_ACC_Z(void);
int16_t Mpu6050_GYRO_X(void);
int16_t Mpu6050_GYRO_Y(void);
int16_t Mpu6050_GYRO_Z(void);
double Mpu6050_XAngle(void);
double Mpu6050_YAngle(void);
float Get_temperature(void);