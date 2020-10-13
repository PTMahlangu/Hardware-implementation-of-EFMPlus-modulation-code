#include "stm32f4xx.h"
#include<string.h>
#include "Tables.h"

// States
int state1(int);
int state2(int);
int state3(int);
int state4(int);

// State pointer
int (*Encoder)(int) = state1;
int (*Encoder2)(int) = state1;

// State 1 Function
int state1(int input_data)
{
	int i, length = sizeof(ToSate1Table1)/sizeof(int);
			for( i=0; i <=length; i++)
			{
			 	if (input_data == ToSate1Table1[i][0])
			    {
			 		Encoder = state1;
					return ToSate1Table1[i][1];
				}
			 	else if (input_data == ToSate2Table1[i][0])
			    {
			 		Encoder = state2;
					return ToSate2Table1[i][1];
				}
				else if (input_data == ToSate3Table1[i][0])
			    {
			    	Encoder = state3;
					return ToSate3Table1[i][1];
				}
				else if (input_data == ToSate4Table1[i][0])
			    {
			    	Encoder = state4;
					return ToSate4Table1[i][1];
				}

		    }// END OF FOR LOOP
}// END OF STATE1

// State 2 Function
int state2(int input_data)
{
	int i, length = sizeof(ToSate1Table2)/sizeof(int);
			for( i=0; i <=length; i++)
			{
			 	if (input_data == ToSate1Table2[i][0])
			    {
			    	Encoder = state1;
					return ToSate1Table2[i][1];
				}
			 	else if (input_data == ToSate2Table2[i][0])
			    {
			    	Encoder = state2;
					return ToSate2Table2[i][1];
				}
				else if (input_data == ToSate3Table2[i][0])
			    {
			    	Encoder = state3;
					return ToSate3Table2[i][1];
				}
				else if (input_data == ToSate4Table2[i][0])
			    {
			    	Encoder = state4;
					return ToSate4Table2[i][1];
				}// END OF ELSE IF

		    }// END OF FOR LOOP
}// END OF STATE2

// State 3 Function
int state3(int input_data)
{
	int i, length = sizeof(ToSate1Table3)/sizeof(int);
			for( i=0; i <=length; i++)
			{
			 	if (input_data == ToSate1Table3[i][0])
			    {
			    	Encoder = state1;
					return ToSate1Table3[i][1];
				}
			 	else if (input_data == ToSate2Table3[i][0])
			    {
			    	Encoder = state2;
					return ToSate2Table3[i][1];
				}
				else if (input_data == ToSate3Table3[i][0])
			    {
			    	Encoder = state3;
					return ToSate3Table3[i][1];
				}
				else if (input_data == ToSate4Table3[i][0])
			    {
			    	Encoder = state4;
					return ToSate4Table3[i][1];
				}// END OF ELSE IF

		    }// END OF FOR LOOP
}// END OF STATE3

// State 4 Function
int state4(int input_data)
{
	int i, length = sizeof(ToSate1Table4)/sizeof(int);
			for( i=0; i <=length; i++)
			{
			 	if (input_data == ToSate1Table4[i][0])
			    {
			    	Encoder = state1;
					return ToSate1Table4[i][1];
				}
			 	else if (input_data == ToSate2Table4[i][0])
			    {
			    	Encoder = state2;
					return ToSate2Table4[i][1];
				}
				else if (input_data == ToSate3Table4[i][0])
			    {
			    	Encoder = state3;
					return ToSate3Table4[i][1];
				}
				else if (input_data == ToSate4Table4[i][0])
			    {
			    	Encoder = state4;
					return ToSate4Table4[i][1];
				}// END OF ELSE IF

		    }// END OF FOR LOOP
}// END OF STATE4

