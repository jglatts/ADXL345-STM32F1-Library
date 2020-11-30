/*
 * adxl345.c
 *
 * Implementation file for ADXL345 library
 *
 *  Created on: Nov 29, 2020
 *      Author: johng
 */
#include "stm32f1xx_hal.h"
#include "adxl345.h"

void ADXL_write(I2C_HandleTypeDef* hi2c1, uint8_t reg, uint8_t value)
{
	uint8_t data[2];
	data[0] = reg;
	data[1] = value;
	HAL_I2C_Master_Transmit(hi2c1, ADXL_ADDRESS, data, 2, 100);
}

void ADXL_read_values(I2C_HandleTypeDef* hi2c1, uint8_t reg)
{
	HAL_I2C_Mem_Read(hi2c1, ADXL_ADDRESS, reg, 1, data_rec, 6, 100);
}

void ADXL_read_address(I2C_HandleTypeDef* hi2c1, uint8_t reg)
{
	uint8_t chipid = 0; // don't make this a global
	HAL_I2C_Mem_Read(hi2c1, ADXL_ADDRESS, reg, 1, &chipid, 1, 100);
}

int ADXL_check_z_val(void)
{
	return (z < Z_VAL);
}

int ADXL_check_y_val(void)
{
	return (y < Y_VAL);
}

int ADXL_check_y_val_right(void)
{
	return (y > Y_VAL_RIGHT);
}

int ADXL_check_x_val(void)
{
	return (x < X_VAL);
}

void ADXL_Init(I2C_HandleTypeDef* hi2c1)
{
	ADXL_read_address(hi2c1, 0x00); // read the DEVID
	ADXL_write(hi2c1, 0x31, 0x01);  // data_format range= +- 4g
	ADXL_write(hi2c1, 0x2d, 0x00);  // reset all bits
	ADXL_write(hi2c1, 0x2d, 0x08);  // power_cntl measure and wake up 8hz
}

void ADXL_run(I2C_HandleTypeDef* hi2c1)
{
	ADXL_read_values(hi2c1, 0x32);
    x = ((data_rec[1]<<8)|data_rec[0]);
    y = ((data_rec[3]<<8)|data_rec[2]);
    z = ((data_rec[5]<<8)|data_rec[4]);
    xg = x * .0078;
    yg = y * .0078;
    zg = z * .0078;
}
