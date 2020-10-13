/*
 * NRZ.h
 *
 *  Created on: Oct 27, 2019
 *      Author: CogCell
 */

#ifndef NRZ_H_
#define NRZ_H_
#include "stm32f4xx.h"

void NRZ(int *in_data,int in_size,int *Out_data);
void NRZI(int *input_data,int in_size,int *Output);

#endif /* NRZ_H_ */
