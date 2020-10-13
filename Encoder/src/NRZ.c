#include "stm32f4xx.h"
#include<string.h>
#include "NRZ.h"



// NON-RETURN-TO-ZERO FUNCTION
void NRZ(int *in_data,int in_size,int *Out_data)
{
	int i;
	Out_data[0]=0;
	for(i = 0;i <in_size-1;i++)
	{
		 if(((in_data[i] ==1) & (in_data[i+1] ==-1) ) || ((in_data[i] ==-1) & (in_data[i+1] ==1) ))
		 {
		 	Out_data[i+1]=1;
		 }
		 else {Out_data[i+1]=0;}
	}
}

// NON-RETURN-TO-ZERO-INVERLY FUNCTION
void NRZI(int *input_data,int in_size,int *Output)
{
	int k,i=0;
	for(k = 0;k <in_size;k++)
	{
        if(i==0)
		{
			if (input_data[k] == 1)	{Output[k]=-1;i=1;}
            else                    {Output[k]=1 ;i=0;}
		}

        else if(i==1)
		{
            if (input_data[k] == 1) {Output[k]=1 ;i=0;}
            else                    {Output[k]=-1;i=1;}
		}
	}
}



