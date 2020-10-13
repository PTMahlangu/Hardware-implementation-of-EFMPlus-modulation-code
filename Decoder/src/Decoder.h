/*
 * Decoder.h
 *
 *  Created on: Sep 3, 2019
 *      Author: project
 */

#ifndef DECODER_H_
#define DECODER_H_

int TWO_and_Three(int InputData[] );
int Table_Detector(int InputData[],int InputData2[] ) ;
int State_Detector(int InputData[]) ;
int EFM_Decoder(int state,int table, int input_data);

#endif /* DECODER_H_ */
