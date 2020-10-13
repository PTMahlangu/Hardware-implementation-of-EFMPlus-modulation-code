

#ifndef ENCODER_H_
#define ENCODER_H_


#include "stm32f4xx.h"
// STATES
int state1(int);
int state2(int);
int state3(int);
int state4(int);

// State pointer
int (*Encoder)(int);
int (*Encoder2)(int);

#endif /* ENCODER_H_ */
