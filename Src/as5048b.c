#include "as5048b.h"

HAL_StatusTypeDef AS5048B_Init(AS5048B_HandleTypeDef* has5048b, uint8_t ADDRESS, I2C_HandleTypeDef* I2C_Handle)
{
  if (I2C_Handle == NULL) {
    return HAL_ERROR;
  }
  has5048b->ADDRESS = ADDRESS<<1;
  has5048b->HI2C = I2C_Handle;
  return HAL_OK;
}

uint16_t AS5048B_Read_RawAngle(AS5048B_HandleTypeDef* has5048b)
{
  has5048b->TxBuffer[0] = READ_ANGLE_CMD;
  do {
    if(HAL_I2C_Master_Transmit_IT(has5048b->HI2C, (uint16_t)has5048b->ADDRESS, (uint8_t*)has5048b->TxBuffer, 1)!= HAL_OK) {
      Error_Handler();
    }
    while (HAL_I2C_GetState(has5048b->HI2C) != HAL_I2C_STATE_READY);
  } while(HAL_I2C_GetError(has5048b->HI2C) == HAL_I2C_ERROR_AF);

  do {
    if(HAL_I2C_Master_Receive_IT(has5048b->HI2C, (uint16_t)has5048b->ADDRESS, (uint8_t *)has5048b->RxBuffer, 2) != HAL_OK) {
      Error_Handler();
    }
  } while(HAL_I2C_GetError(has5048b->HI2C) == HAL_I2C_ERROR_AF);
  return (has5048b->RxBuffer[1]<<6) | (has5048b->RxBuffer[0]&0x3F);
}

double AS5048B_Read_DegAngle(AS5048B_HandleTypeDef* has5048b)
{
  return AS5048B_Read_RawAngle(has5048b)*360.0/16383;
}
