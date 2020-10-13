/*
 * Noise.h
 *
 *  Created on: Nov 7, 2019
 *      Author: project
 */

#ifndef NOISE_H_
#define NOISE_H_
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include<string.h>
#include <stdlib.h>
#include <math.h>

float Add_Noise(float EcN0dB);

#endif /* NOISE_H_ */
