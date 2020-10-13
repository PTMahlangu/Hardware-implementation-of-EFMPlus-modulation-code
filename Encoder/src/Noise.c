#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include<string.h>
#include <stdlib.h>
#include <math.h>

 /* AWGN channel (using Box-Muller transform) */

float Add_Noise(float EcN0dB)
{
	float u1, u2;
	float r,n_re,noise;
	const float pi = 3.14159265358979;
	float EcN0Lin =  pow(10,(float) -1*EcN0dB/20);


	u1 = (double)rand()/((double)RAND_MAX + (double)1);
	u2 = (double)rand()/((double)RAND_MAX + (double)1);

	r = sqrt(-2*log(u1 ));
	n_re = r*cos(2*pi*u2);
	noise = (1/sqrt(2))*EcN0Lin*n_re;

	return noise;

}


