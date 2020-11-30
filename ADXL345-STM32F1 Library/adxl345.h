/*
 * adx345.h
 *
 * Header file for ADXL345 library
 *
 *  Created on: Nov 29, 2020
 *      Author: johng
 */
#ifndef INC_ADXL345_H_
#define INC_ADXL345_H_

#include "stm32f1xx_hal.h"

#define ADXL_ADDRESS 0x53 << 1
#define X_VAL -5
#define Y_VAL -50
#define Y_VAL_RIGHT 50
#define Z_VAL 70

uint8_t data_rec[6];
int16_t x, y, z;
float xg, yg, zg;
char x_char[3], y_char[3], z_char[3];

void ADXL_Init(I2C_HandleTypeDef*);
void ADXL_run(I2C_HandleTypeDef*);
void ADXL_adxl_write(I2C_HandleTypeDef*, uint8_t, uint8_t);
void ADXL_adxl_read_values(I2C_HandleTypeDef*, uint8_t);
void ADXL_adxl_read_address(I2C_HandleTypeDef*, uint8_t);
int  ADXL_check_z_val(void);
int  ADXL_check_y_val(void);
int  ADXL_check_y_value_right(void);
int  ADXL_check_x_val(void);

#endif /* INC_ADXL345_H_ */
