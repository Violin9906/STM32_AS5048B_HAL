# STM32_AS5048B_HAL
> AS5048B Library for STM32(HAL)

[TOC]

## How To Use

You need to add `./Src/as5048b.c` to your project, and add `./Src/as5048b.h` to your include path.

I suggest you generate your code with STM32CubeMX, so the HAL library can insert into your project automatically, on which is this AS5048B library based.

Enable I2C in your STM32CubeMX, then you will get a *I2C_HandleTypeDef* variable in `i2c.c`. Assuming that it is named *hi2c*. Then you can initialize an AS5048B sensor like this:

```C
#include "as5048b.h"

AS5048B_HandleTypeDef as5048b;
AS5048B_Init(&as5048b, YOUR_AS5048B_I2C_ADDRESS, &hi2c);
```

Now you get a handle of your as5048b sensor. If you want get the angle in degree, just do this:

```C
AS5048B_Read_DegAngle(&as5048b);
```

This function returns a *double* value, which is the angle in degree. You can also get the raw angle data, which ranges 0~16383, by using function `AS5048B_Read_RawAngle`。

More function will add into this library soon.

## API

### AS5048B_Init

```C
void AS5048B_Init(AS5048B_HandleTypeDef* has5048b, uint8_t ADDRESS, I2C_HandleTypeDef* I2C_Handle);
```

Initialize an AS5048B sensor.

### AS5048B_Read_RawAngle

```C
uint16_t AS5048B_Read_RawAngle(AS5048B_HandleTypeDef* has5048b);
```

Read the Raw angle value from the sensor.

### AS5048B_Read_DegAngle

```C
double AS5048B_Read_DegAngle(AS5048B_HandleTypeDef* has5048b);
```

Read the angle value in degree from the sensor.