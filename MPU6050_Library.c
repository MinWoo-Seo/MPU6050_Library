#include "MPU6050_Library.h"



//#define MPU6050_ADDRESS 0x68

static I2C_HandleTypeDef i2cHandler;
//static I2C_HandleTypeDef hi2c1;



uint8_t mpu6050_i2c_address = MPU6050_ADDRESS << 1;


void Mpu6050_i2c_init(I2C_HandleTypeDef  *Your_i2c_handler){
 
  //i2cHandler = Your_i2c_handler;
  memcpy(&i2cHandler, Your_i2c_handler, sizeof(*Your_i2c_handler));
}

void Mpu6050_i2c_TX (uint8_t mpu6050_register, uint8_t mpu6050_data){
  uint8_t data[2]={0,};
  data[0] = mpu6050_register;
  data[1] = mpu6050_data;
   
  HAL_I2C_Master_Transmit(&i2cHandler, mpu6050_i2c_address, data, 2, 100);
}

uint8_t Mpu6050_i2c_RX (uint8_t mpu6050_register){
    uint8_t save_data_to_buffer;
    HAL_I2C_Master_Transmit(&i2cHandler, mpu6050_i2c_address, &mpu6050_register, 1, 100);
    HAL_I2C_Master_Receive(&i2cHandler, mpu6050_i2c_address, (uint8_t *)&save_data_to_buffer, sizeof(save_data_to_buffer), 100);
    return save_data_to_buffer;
}

int16_t Mpu6050_ACC_X(void){
  uint8_t ACC_data_X[2]={0,};
  int16_t ACC_data_X_result;
  //float ACC_X;
  
  ACC_data_X[0] = Mpu6050_i2c_RX(ACCEL_XOUT_H);
  ACC_data_X[1] = Mpu6050_i2c_RX(ACCEL_XOUT_L);
  ACC_data_X_result = (ACC_data_X[0]<<8) | ACC_data_X[1];
  //ACC_X = ACC_data_X_result/16384.0;
  
  return ACC_data_X_result;
  
}
int16_t Mpu6050_ACC_Y(void){
  uint8_t ACC_data_Y[2]={0,};
  int16_t ACC_data_Y_result;
  //float ACC_Y;
  
  ACC_data_Y[0] = Mpu6050_i2c_RX(ACCEL_YOUT_H);
  ACC_data_Y[1] = Mpu6050_i2c_RX(ACCEL_YOUT_L);
  ACC_data_Y_result = (ACC_data_Y[0]<<8) | ACC_data_Y[1];
  //ACC_Y = ACC_data_Y_result/16384.0;
  
  return ACC_data_Y_result;
}
int16_t Mpu6050_ACC_Z(void){
  uint8_t ACC_data_Z[2]={0,};
  int16_t ACC_data_Z_result;
  //float ACC_Z;
  
  ACC_data_Z[0] = Mpu6050_i2c_RX(ACCEL_ZOUT_H);
  ACC_data_Z[1] = Mpu6050_i2c_RX(ACCEL_ZOUT_L);
  ACC_data_Z_result = (ACC_data_Z[0]<<8) | ACC_data_Z[1];
  //ACC_Z = ACC_data_Z_result/16384.0;
  
  return ACC_data_Z_result;
  
}

int16_t Mpu6050_GYRO_X(void){
  uint8_t GYRO_data_X[2]={0,};
  int16_t GYRO_data_X_result;
  //float GYRO_X;
  
  GYRO_data_X[0] = Mpu6050_i2c_RX(GYRO_XOUT_H);
  GYRO_data_X[1] = Mpu6050_i2c_RX(GYRO_XOUT_L);
  GYRO_data_X_result = (GYRO_data_X[0]<<8) | GYRO_data_X[1];
  //GYRO_X = GYRO_data_X_result/131.0;
  
  return GYRO_data_X_result;
 }
int16_t Mpu6050_GYRO_Y(void){
  uint8_t GYRO_data_Y[2]={0,};
  int16_t GYRO_data_Y_result;
  //float GYRO_Y;
  
  GYRO_data_Y[0] = Mpu6050_i2c_RX(GYRO_YOUT_H);
  GYRO_data_Y[1] = Mpu6050_i2c_RX(GYRO_YOUT_L);
  GYRO_data_Y_result = (GYRO_data_Y[0]<<8) | GYRO_data_Y[1];
  //GYRO_Y = GYRO_data_Y_result/131.0;
  
  return GYRO_data_Y_result;
 }
int16_t Mpu6050_GYRO_Z(void){
  uint8_t GYRO_data_Z[2]={0,};
  int16_t GYRO_data_Z_result;
  //float GYRO_Z;
  
  GYRO_data_Z[0] = Mpu6050_i2c_RX(GYRO_ZOUT_H);
  GYRO_data_Z[1] = Mpu6050_i2c_RX(GYRO_ZOUT_L);
  GYRO_data_Z_result = (GYRO_data_Z[0]<<8) | GYRO_data_Z[1];
  //GYRO_Z = GYRO_data_Z_result/131.0;
  
  return GYRO_data_Z_result;
 }


double Mpu6050_XAngle(void){
  double accXangle;
  //double gyroXrate;
  double angleX;

  accXangle = (atan2(Mpu6050_ACC_Y(),Mpu6050_ACC_Z())+PI)*RAD2DEG;
  //gyroXrate = (double)Mpu6050_GYRO_X()/131.0;
  angleX = accXangle - 180.0;
  return angleX;
}

double Mpu6050_YAngle(void){
  double accYangle;
  //double gyroYrate;
  double angleY;
  
  accYangle = (atan2(Mpu6050_ACC_X(),Mpu6050_ACC_Z())+PI)*RAD2DEG;

  //gyroYrate = -((double)Mpu6050_GYRO_Y()/131.0);
  angleY = accYangle - 180.0;
  
  return angleY;
}

float Get_temperature(void){
  
  uint8_t temp_data[2]={0,};
  int16_t temp_data_result;
  float temp_data_float;
  
  temp_data[0] = Mpu6050_i2c_RX(TEMP_OUT_H);
  temp_data[1] = Mpu6050_i2c_RX(TEMP_OUT_L);
  
  temp_data_result = (temp_data[0]<<8) |  temp_data[1];
  temp_data_float = (temp_data_result/340)+36.53;
  
  return temp_data_float;

}

