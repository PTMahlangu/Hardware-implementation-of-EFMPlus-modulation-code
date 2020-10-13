#include "stm32f4xx.h"
#include<string.h>
#include "Viterbi.h"


void To_Binary(int n, int binaryNum[] )
{
    // counter for binary array
    int i = 0 ;
    while (n > 0)
	{
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
}

void int_to_bin_digit(unsigned int in, int count, int* out)
{
    /* assert: count <= sizeof(int)*CHAR_BIT */
    unsigned int mask = 1U << (count-1);
    int i;
    for (i = 0; i < count; i++) {
        out[i] = (in & mask) ? 1 : 0;
        in <<= 1;
    }
}

void Viterbi(int SIZE_V, int *Conv_output,int *Output_Data )
{
		int N = SIZE_V/4;                							// SIZE_V size of input data
		int Input_Data[SIZE_V];
		unsigned int i,j,k;
		int binaryNum[4] ;
		int binary[4] ;
		int Branch_Metric[16][SIZE_V];
		int Metric[16][SIZE_V]       ;
		int Path_Metric[16][SIZE_V];

		for(j = 0;j < SIZE_V;j++)
		{
			if(Conv_output[j] == 1){Input_Data[j]= -1;}
			else {Input_Data[j]= 1;}
		}

		// Euclidean distance function

		for(i = 0;i <4;i++)  // FOR STAGE 1 TO 4
		{
		    for(k = 0;k < 16;k++)
			{
		    	int_to_bin_digit(k, 4, binaryNum);
			    for(j = 0;j < 4;j++)
				{
					if (binaryNum[j]==1) {binary[j]=-1;}
					else {binary[j]=1;}
				}
				Branch_Metric[k][i] =binary[0]*Input_Data[4*i] + binary[1]*Input_Data[4*i+1] + binary[2]*Input_Data[4*i+2] + binary[3]*Input_Data[4*i+3]; // Euclidean distance computation
			}
			// STAGE 1
			Metric[0][1] = Branch_Metric[0][0];
	        Metric[8][1] = Branch_Metric[15][0];
	        Path_Metric[0][1] =Path_Metric[8][1] = 0;
	        // STAGE 2
	        Metric[0][2]  = Branch_Metric[0][1]  +  Metric[0][1];
	    	Metric[8][2]  = Branch_Metric[15][1] +  Metric[0][1];
	    	Metric[4][2]  = Branch_Metric[12][1] +  Metric[8][1];
	    	Metric[12][2] = Branch_Metric[3][1]  +  Metric[8][1];
	    	Path_Metric[0][2] =Path_Metric[8][2] = 0;
	    	Path_Metric[4][2]=Path_Metric[12][2] = 8;

			// STAGE 3
		    Metric[0][3] = Branch_Metric[0][2]  + Metric[0][2];
		    Metric[8][3] = Branch_Metric[15][2] + Metric[0][2];
		    Metric[4][3]  = Branch_Metric[12][2] +  Metric[8][2];
		    Metric[12][3] = Branch_Metric[3][2] +  Metric[8][2];
	    	Path_Metric[0][3] =Path_Metric[8][3] = 0;
	    	Path_Metric[4][3]=Path_Metric[12][3] = 8;

		    Metric[2][3]  = Branch_Metric[10][2] +  Metric[4][2];
		    Metric[10][3] = Branch_Metric[5][2] +  Metric[4][2];
		    Path_Metric[2][3] = Path_Metric[10][3]= 4;

		    Metric[6][3]  = Branch_Metric[6][2] +  Metric[12][2];
		    Metric[14][3] = Branch_Metric[1][2] +  Metric[12][2];
		    Path_Metric[6][3] = Path_Metric[14][3]= 12;

		    // STAGE 4
		    Metric[0][4]  = Branch_Metric[0][3]  +  Metric[0][3];
		    Path_Metric[0][4]= 0;
		    Metric[1][4]  = Branch_Metric[13][3] +  Metric[2][3];
		    Path_Metric[1][4]= 2;
		    Metric[2][4]  = Branch_Metric[10][3] +  Metric[4][3];
		    Path_Metric[2][4]= 4;
		    Metric[3][4]  = Branch_Metric[7][3]  +  Metric[6][3];
		    Path_Metric[3][4]= 6;
		    Metric[4][4]  = Branch_Metric[12][3] +  Metric[8][3];
		    Path_Metric[4][4]= 8;
		    Metric[5][4]  = Branch_Metric[1][3]  +  Metric[10][3];
		    Path_Metric[5][4]= 10;
		    Metric[6][4]  = Branch_Metric[6][3]  +  Metric[12][3];
		    Path_Metric[6][4]= 12;
		    Metric[7][4]  = Branch_Metric[11][3] +  Metric[14][3];
		    Path_Metric[7][4]= 14;
		    Metric[8][4]  = Branch_Metric[15][3] +  Metric[0][3];
		    Path_Metric[8][4]= 0;
		    Metric[9][4]  = Branch_Metric[2][3]  +  Metric[2][3];
		    Path_Metric[9][4]= 2;
		    Metric[10][4] = Branch_Metric[5][3]  +  Metric[4][3];
		    Path_Metric[10][4]= 4;
		    Metric[11][4] = Branch_Metric[14][3]  +  Metric[6][3];
		    Path_Metric[11][4]= 6;
		    Metric[12][4] = Branch_Metric[3][3]  +  Metric[8][3];
		    Path_Metric[12][4]= 8;
		    Metric[13][4] = Branch_Metric[14][3] +  Metric[10][3];
		    Path_Metric[13][4]= 10;
		    Metric[14][4] = Branch_Metric[1][3]  +  Metric[12][3];
		    Path_Metric[14][4]= 12;
		    Metric[15][4] = Branch_Metric[4][3]  +  Metric[14][3];
		    Path_Metric[15][4]= 14;
		}  // END OF STAGE 1 TO 4

	//----------------------------- FOR STAGE 5 TO N
		i =4;
		while(i < N)
		{
		    for(k = 0;k < 16;k++)
			{
		    	int_to_bin_digit(k, 4, binaryNum);
			    for(j = 0;j < 4;j++)
				{
					if (binaryNum[j]==1) {binary[j]=-1;}
					else {binary[j]=1;}
				}

				Branch_Metric[k][i] =binary[0]*Input_Data[4*i] + binary[1]*Input_Data[4*i+1] + binary[2]*Input_Data[4*i+2] + binary[3]*Input_Data[4*i+3]; // Euclidean distance computation
		    }

		   Metric[0][i+1] = ((Metric[0][i] + Branch_Metric[0][i]) > (Metric[1][i] + Branch_Metric[15][i]))? (Metric[0][i] + Branch_Metric[0][i]):(Metric[1][i] + Branch_Metric[15][i]);
		   Path_Metric[0][i+1] = ((Metric[0][i] + Branch_Metric[0][i]) > (Metric[1][i] + Branch_Metric[15][i]))? 0:1;

		   Metric[1][i+1] = ((Metric[2][i] + Branch_Metric[13][i]) > (Metric[3][i] + Branch_Metric[2][i]))? (Metric[2][i] + Branch_Metric[13][i]):(Metric[3][i] + Branch_Metric[2][i]);
		   Path_Metric[1][i+1] = ((Metric[2][i] + Branch_Metric[13][i]) > (Metric[3][i] + Branch_Metric[2][i]))? 2:3;

		   Metric[2][i+1] = ((Metric[4][i] + Branch_Metric[10][i]) > (Metric[5][i] + Branch_Metric[5][i]))? (Metric[4][i] + Branch_Metric[10][i]):(Metric[5][i] + Branch_Metric[5][i]);
		   Path_Metric[2][i+1] = ((Metric[4][i] + Branch_Metric[10][i]) > (Metric[5][i] + Branch_Metric[5][i]))? 4:5;

		   Metric[3][i+1] = ((Metric[6][i] + Branch_Metric[7][i]) > (Metric[7][i] + Branch_Metric[8][i]))? (Metric[6][i] + Branch_Metric[7][i]):(Metric[7][i] + Branch_Metric[8][i]);
		   Path_Metric[3][i+1] = ((Metric[6][i] + Branch_Metric[7][i]) > (Metric[7][i] + Branch_Metric[8][i]))? 6:7;

		   Metric[4][i+1] = ((Metric[8][i] + Branch_Metric[12][i]) > (Metric[9][i] + Branch_Metric[3][i]))? (Metric[8][i] + Branch_Metric[12][i]):(Metric[9][i] + Branch_Metric[3][i]);
		   Path_Metric[4][i+1] = ((Metric[8][i] + Branch_Metric[12][i]) > (Metric[9][i] + Branch_Metric[3][i]))? 8:9;

		   Metric[5][i+1] = ((Metric[10][i] + Branch_Metric[1][i]) > (Metric[11][i] + Branch_Metric[14][i]))? (Metric[10][i] + Branch_Metric[1][i]):(Metric[11][i] + Branch_Metric[14][i]);
		   Path_Metric[5][i+1] = ((Metric[10][i] + Branch_Metric[1][i]) > (Metric[11][i] + Branch_Metric[14][i]))? 10:11;

		   Metric[6][i+1] = ((Metric[12][i] + Branch_Metric[6][i]) > (Metric[13][i] + Branch_Metric[9][i]))? (Metric[12][i] + Branch_Metric[6][i]):(Metric[13][i] + Branch_Metric[9][i]);
		   Path_Metric[6][i+1] = ((Metric[12][i] + Branch_Metric[6][i]) > (Metric[13][i] + Branch_Metric[9][i]))? 12:13;

		   Metric[7][i+1] = ((Metric[14][i] + Branch_Metric[11][i]) > (Metric[15][i] + Branch_Metric[4][i]))? (Metric[14][i] + Branch_Metric[11][i]):(Metric[15][i] + Branch_Metric[4][i]);
		   Path_Metric[7][i+1] = ((Metric[14][i] + Branch_Metric[11][i]) > (Metric[15][i] + Branch_Metric[4][i]))? 14:15;

		   Metric[8][i+1] = ((Metric[0][i] + Branch_Metric[15][i]) > (Metric[1][i] + Branch_Metric[0][i]))? (Metric[0][i] + Branch_Metric[15][i]):(Metric[1][i] + Branch_Metric[0][i]);
		   Path_Metric[8][i+1] = ((Metric[0][i] + Branch_Metric[15][i]) > (Metric[1][i] + Branch_Metric[0][i]))? 0:1;

		   Metric[9][i+1] = ((Metric[2][i] + Branch_Metric[2][i]) > (Metric[3][i] + Branch_Metric[13][i]))? (Metric[2][i] + Branch_Metric[2][i]):(Metric[3][i] + Branch_Metric[13][i]);
		   Path_Metric[9][i+1] = ((Metric[2][i] + Branch_Metric[2][i]) > (Metric[3][i] + Branch_Metric[13][i]))? 2:3;

		   Metric[10][i+1] = ((Metric[4][i] + Branch_Metric[5][i]) > (Metric[5][i] + Branch_Metric[10][i]))? (Metric[4][i] + Branch_Metric[5][i]):(Metric[5][i] + Branch_Metric[10][i]);
		   Path_Metric[10][i+1] = ((Metric[4][i] + Branch_Metric[5][i]) > (Metric[5][i] + Branch_Metric[10][i]))? 4:5;

		   Metric[11][i+1] = ((Metric[6][i] + Branch_Metric[8][i]) > (Metric[7][i] + Branch_Metric[7][i]))? (Metric[6][i] + Branch_Metric[8][i]):(Metric[7][i] + Branch_Metric[7][i]);
		   Path_Metric[11][i+1] = ((Metric[6][i] + Branch_Metric[8][i]) > (Metric[7][i] + Branch_Metric[7][i]))? 6:7;

		   Metric[12][i+1] = ((Metric[8][i] + Branch_Metric[3][i]) > (Metric[9][i] + Branch_Metric[12][i]))? (Metric[8][i] + Branch_Metric[3][i]):(Metric[9][i] + Branch_Metric[12][i]);
		   Path_Metric[12][i+1] = ((Metric[8][i] + Branch_Metric[3][i]) > (Metric[9][i] + Branch_Metric[12][i]))? 8:9;

		   Metric[13][i+1] = ((Metric[10][i] + Branch_Metric[14][i]) > (Metric[11][i] + Branch_Metric[1][i]))? (Metric[10][i] + Branch_Metric[14][i]):(Metric[11][i] + Branch_Metric[1][i]);
		   Path_Metric[13][i+1] = ((Metric[10][i] + Branch_Metric[14][i]) > (Metric[11][i] + Branch_Metric[1][i]))? 10:11;

		   Metric[14][i+1] = ((Metric[12][i] + Branch_Metric[9][i]) > (Metric[13][i] + Branch_Metric[6][i]))? (Metric[12][i] + Branch_Metric[9][i]):(Metric[13][i] + Branch_Metric[6][i]);
		   Path_Metric[14][i+1] = ((Metric[12][i] + Branch_Metric[9][i]) > (Metric[13][i] + Branch_Metric[6][i]))? 12:13;

		   Metric[15][i+1] = ((Metric[14][i] + Branch_Metric[4][i]) > (Metric[15][i] + Branch_Metric[11][i]))? (Metric[14][i] + Branch_Metric[4][i]):(Metric[15][i] + Branch_Metric[11][i]);
		   Path_Metric[15][i+1] = ((Metric[14][i] + Branch_Metric[4][i]) > (Metric[15][i] + Branch_Metric[11][i]))? 14:15;

		   i=i+1;
		}

	//_______________________________________________Decoding_________________________________
		int max = Metric[0][i];
		int index = 0;
		int ii;
		// find last  MAX value in trellis graph
		for (ii = 0; ii < 16; ii++)
		{
			if (max < Metric[ii][i])
			{
				max = Metric[ii][i];
				index = ii;
			}
		}

	// Trace back and decode bits function
		unsigned int x_axis =i;
		unsigned int y_axis= index;

		while (x_axis !=0)
		{
			 if ((y_axis ==0) || (y_axis ==1) || (y_axis ==2) || (y_axis ==3) || (y_axis ==4) || (y_axis ==5) || (y_axis ==6) || (y_axis ==7))
			 {
			 	y_axis = Path_Metric[y_axis][x_axis];
			 	Output_Data[x_axis] =0;
			 	x_axis=x_axis-1;
			 }

			 else if ((y_axis ==8) || (y_axis ==9) || (y_axis ==10) || (y_axis ==11) || (y_axis ==12) || (y_axis ==13) || (y_axis ==14) || (y_axis ==15))
			 {
			 	y_axis = Path_Metric[y_axis][x_axis];
			 	Output_Data[x_axis] =1;
			 	x_axis=x_axis-1;

			 }

		} // End of WHILE loop

  }
