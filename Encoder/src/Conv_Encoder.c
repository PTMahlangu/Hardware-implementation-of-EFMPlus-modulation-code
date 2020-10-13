
#include "stm32f4xx.h"
#include<string.h>
#include "Conv_Encoder.h"

// Convolutional encoder: Rate = 1/4, K =5
void Conv_Encoder(int *in_data,int N,int *Conv_output)
{ 	int i;
	int s_reg[5]                                       = {0};
	int G[4]                     		               = {0};

	// Convolutional encoder function
	for(i = 0;i <N+1;i++)
	{

		s_reg[4]=s_reg[3];
		s_reg[3]=s_reg[2];
		s_reg[2]=s_reg[1];
		s_reg[1]=s_reg[0];
		s_reg[0]=in_data[i];

	    G[0] = s_reg[0]^s_reg[1]^s_reg[2]^s_reg[3]^s_reg[4];
	    G[1] = s_reg[0]^s_reg[1]^s_reg[3]^s_reg[4];
	    G[2] = s_reg[0]^s_reg[2]^s_reg[4];
	    G[3] = s_reg[0]^s_reg[3]^s_reg[4];

	    Conv_output[4*i]   = G[0];
	    Conv_output[4*i+1] = G[1];
	    Conv_output[4*i+2] = G[2];
	    Conv_output[4*i+3] = G[3];
	}
}
