/*
 * Viterbi.h
 *
 *  Created on: Oct 11, 2019
 *      Author: project
 */

#ifndef VITERBI_H_
#define VITERBI_H_

#include "stm32f4xx.h"

void To_Binary(int n, int binaryNum[] );
void int_to_bin_digit(unsigned int in, int count, int* out);
void Viterbi(int SIZE_V, int *Conv_output,int *Output_Data );

#endif /* VITERBI_H_ */
