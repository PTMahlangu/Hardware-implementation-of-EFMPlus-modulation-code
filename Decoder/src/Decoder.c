
#include "Tables.h"

// check Lsb-bit zeros before 1
int TWO_and_Three(int InputData[] )   //check lests bits
{

  int j, count=0;
    for ( j = 15; j>6; j--)
	{
	 	if (InputData[j] == 0)
		 {
	 		 	count = count +1;
		 }
		 else
		 	break;
    }

   if ((count >=0) & (count <=5))
	{
        if ((InputData[3]== 0) & (InputData[15]== 0)) //  TO STATE2
        {
            return 2;
		}

        else if ((InputData[3]== 1) | (InputData[15]==1)) // TO STATE3
		{
			return 3;
		}
	}

}

// check Lsb-bit zeros before 1
int Table_Detector(int InputData[],int InputData2[] )   //check most bits
{
  int hold,i, temp=0;
    for ( i = 0; i<9; i++)
	{
	 	if (InputData[i] == 0)
		 {
	 		 	temp = temp +1;
		 }
		 else
		 	break;
    }

	if (temp <= 1)
	{
    	return 1;
	}

	else if ((temp >=6) & (temp <=9))
	{
    	return 4;
	}

	else
	{
		hold = TWO_and_Three(InputData2);
		return hold;
	}

}

// check Msb-bit zeros before 1
int State_Detector(int InputData[] )  //check most bits
{
  int i, temp=0;
    for ( i = 15; i>6; i--)
	{
	 	if (InputData[i] == 0)
		 {
	 		 	temp = temp +1;
		 }
		 else
		 	break;
    }


   		if ((temp >=2) & (temp <=9))
		{
	    	return 1;
		}

	   else if ((temp >=0) & (temp <=5))
		{
	        if ((InputData[3]== 0) & (InputData[15]== 0)) //  TO STATE2
	        {
	            return 2;
			}

	        if ((InputData[3]== 1) | (InputData[15]==1)) // TO STATE3
			{
				return 3;
			}
		}

		else if (temp <= 1)
		{
	    	return 4;
		}
}

//**************************************************** DECODING FUNCTION
int EFM_Decoder(int state,int table, int input_data) // InputData[] is hex
{
	int i;
    if(state == 1)         // STATE1
    {
    	if(table == 1)    // TO STATE 1
    	{
 			for( i=0; i <=sizeof(ToSate1Table1); i++)
			{
			 	if (input_data == ToSate1Table1[i][1])
			    {
					return ToSate1Table1[i][0];
				}
		    }
		}
    	else if(table == 2) // TO STATE 2
    	{
 			for( i=0; i <=sizeof(ToSate2Table1); i++)
			{
			 	if (input_data == ToSate2Table1[i][1])
			    {
					return ToSate2Table1[i][0];
				}
		    }
		}
    	else if(table == 3) // TO STATE 3
    	{
 			for( i=0; i <=sizeof(ToSate3Table1); i++)
			{
			 	if (input_data == ToSate3Table1[i][1])
			    {
					return ToSate3Table1[i][0];
				}
		    }
		}
    	else if(table == 4) // TO STATE 4
    	{
 			for( i=0; i <=sizeof(ToSate4Table1); i++)
			{
			 	if (input_data == ToSate4Table1[i][1])
			    {
					return ToSate4Table1[i][0];
				}
		    }
		}
	}


    else if(state == 2)   // STATE2
    {
      	if(table == 1)    // TO STATE 1
    	{
 			for( i=0; i <=sizeof(ToSate1Table2); i++)
			{
			 	if (input_data == ToSate1Table2[i][1])
			    {
					return ToSate1Table2[i][0];
				}
		    }
		}
    	else if(table == 2) // TO STATE 2
    	{
 			for( i=0; i <=sizeof(ToSate2Table2); i++)
			{
			 	if (input_data == ToSate2Table2[i][1])
			    {
					return ToSate2Table2[i][0];
				}
		    }
		}
    	else if(table == 3) // TO STATE 3
    	{
 			for( i=0; i <=sizeof(ToSate3Table2); i++)
			{
			 	if (input_data == ToSate3Table2[i][1])
			    {
					return ToSate3Table2[i][0];
				}
		    }
		}
    	else if(table == 4) // TO STATE 4
    	{
 			for( i=0; i <=sizeof(ToSate4Table2); i++)
			{
			 	if (input_data == ToSate4Table2[i][1])
			    {
					return ToSate4Table2[i][0];
				}
		    }
		}
    }
    else if(state == 3)   // STATE3
    {
   	    if(table == 1)    // TO STATE 1
    	{
 			for( i=0; i <=sizeof(ToSate1Table3); i++)
			{
			 	if (input_data == ToSate1Table3[i][1])
			    {
					return ToSate1Table3[i][0];
				}
		    }
		}
    	else if(table == 2) // TO STATE 2
    	{
 			for( i=0; i <=sizeof(ToSate2Table3); i++)
			{
			 	if (input_data == ToSate2Table3[i][1])
			    {
					return ToSate2Table3[i][0];
				}
		    }
		}
    	else if(table == 3) // TO STATE 3
    	{
 			for( i=0; i <=sizeof(ToSate3Table3); i++)
			{
			 	if (input_data == ToSate3Table3[i][1])
			    {
					return ToSate3Table3[i][0];
				}
		    }
		}
    	else if(table == 4) // TO STATE 4
    	{
 			for( i=0; i <=sizeof(ToSate4Table4); i++)
			{
			 	if (input_data == ToSate4Table4[i][1])
			    {
					return ToSate4Table4[i][0];
				}
		    }
		}
	}

    else if(state == 4)   // STATE4
    {
    	if(table == 1)    // TO STATE 1
    	{
 			for( i=0; i <=sizeof(ToSate1Table4); i++)
			{
			 	if (input_data == ToSate1Table4[i][1])
			    {
					return ToSate1Table4[i][0];
				}
		    }
		}
    	else if(table == 2) // TO STATE 2
    	{
 			for( i=0; i <=sizeof(ToSate2Table4); i++)
			{
			 	if (input_data == ToSate2Table4[i][1])
			    {
					return ToSate2Table4[i][0];
				}
		    }
		}
    	else if(table == 3) // TO STATE 3
    	{
 			for( i=0; i <=sizeof(ToSate3Table4); i++)
			{
			 	if (input_data == ToSate3Table4[i][1])
			    {
					return ToSate3Table4[i][0];
				}
		    }
		}
    	else if(table == 4) // TO STATE 4
    	{
 			for( i=0; i <=sizeof(ToSate4Table4); i++)
			{
			 	if (input_data == ToSate4Table4[i][1])
			    {
					return ToSate4Table4[i][0];
				}
		    }
		}
	}
}

