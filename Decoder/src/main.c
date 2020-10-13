/* Includes */
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include<string.h>
#include "Tables.h"
#include "Decoder.h"
#include "Viterbi.h"
#include <stdlib.h>
#include "defines.h"
#include "tm_stm32f4_spi.h"
#include "stm32f4xx_spi.h"
#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_fonts.h"
#include "NRZ.h"


enum { samples = 15 };
/* Private macro */

/* Private variables */
char one[1]= {'1'};
char zero[1]= {'0'};
char rx_data[3];
char buffer[6];
char buffer2[4];
char *eptr;
int temp0[16];
uint16_t temp1[samples];
int temp5[8];
int temp6[8*samples];
int temp9[16*samples];
int temp10[16];
int temp11[16];
int temp12[128*samples];
int RX[128*samples];
int hold1[16];
int hold2[16];
int hold3;
int table;
int state;
int Out_Data;
int Out_Data2[samples-1];
uint16_t TO_Decoder[3];
int Conv_output[64*samples];
int error;
/* Private functions */
void GPIO_Configuration(void);
void USART_Config(void);
void USART_PutChar(char c);
void To_String(char* _buffer, unsigned int data);
void To_String2(char* _buffer, unsigned int data);
int bin_to_dec(int *arr,int in_size);
unsigned int SIZE_V ;

int Output_Data[16*samples+1];
int Output_Data2[16*samples];
void LCD_display(int *input, int size,int position,int x);
static void SPI_Config(void);
int position[4] ={60,100,150,200};
/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
	// LED configuration
 	GPIO_Configuration();
    // Call USART1 configuration
    USART_Config();
    /* SPI1 configuration ---------------------------------------*/
    SPI_Config();
	//Initialize ILI9341
	TM_ILI9341_Init();
	//Rotate LCD for 90 degrees
	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);

	int j=0,k=0,s=0,p=0,f=0,o=0,jj=0,v=0;

//	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));  //transmit buffer empty?
//	SPI_I2S_SendData(SPI1, 0xA5);

 	while(1)
 	{

	// SPI RECEIVE

		for(j =0;j<16*samples;++j)
		{
			while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)); //data received?
			Output_Data2[j]=SPI_I2S_ReceiveData(SPI1);
		}
		
		for(j =0;j<128*samples;++j)
		{
			while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)); //data received?
			RX[j]=SPI_I2S_ReceiveData(SPI1);
			if(RX[j]==255){RX[j]=-1;}
			else{RX[j]=1;}
		}


		NRZ(RX, 128*samples,temp12);
		 //**===================================================================================================================
		//           CHANNEL            CHANNEL              CHANNEL              CHANNEL              CHANNEL
		 //**===================================================================================================================
 		
		 //	TM_ILI9341_Puts(40, 10, "EFMPlus Encoder 2  ", &TM_Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
 		//	TM_ILI9341_Puts(10, 36, "Input          :        Output", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
 		//	LCD_display(temp11, 16,10*v,160);
 		//	LCD_display(temp5, 8,10*v,10);

 		while((k+1) < 8*samples)
 		{
			for(p =0;p< 16;++p)
			{
				hold1[p] = temp12[16*k+p];
				temp10[15-p]=hold1[p];
				hold2[p] = temp12[16*k+p+16];
				temp11[15-p]=hold2[p];
			}

			state = State_Detector(temp10) ;
			table = Table_Detector(temp10,temp11) ;
			hold3=bin_to_dec(hold1,16);
			//**************EFMPlus Decoder 2**********************
			Out_Data = EFM_Decoder(state, table, hold3);
			if (Out_Data ==545){Out_Data=255;}
			int_to_bin_digit(Out_Data,8, temp5);

			for(o =0;o<8;++o){Conv_output[k*8+o]  =temp5[o];}
			k=k+1;
 		} // WHILE LOOP

		//**************Viterbi Decoder**********************
		 SIZE_V = sizeof(Conv_output)/sizeof(int);
		 Viterbi(SIZE_V , Conv_output,Output_Data );
		 
		 for(v =0;v<16*samples;++v)
		 {
		 	if(Output_Data[v+1]!=Output_Data2[v]){error=error+1;}		
		 }

		 if(error >40){
		 for(v =0;v<16*samples;++v)
		 {
			 Output_Data2[v]=Output_Data[v+1];
		 }}

		for(jj =0;jj<samples-1;++jj)
		{
			for(p =0;p< 16;++p)
			{
				hold1[p] = Output_Data2[16*jj+p];
				temp10[15-p]=hold1[p];
				hold2[p] = Output_Data2[16*jj+p+16];
				temp11[15-p]=hold2[p];
			}

			 state = State_Detector(temp10) ;
			 table = Table_Detector(temp10,temp11);
			 hold3=bin_to_dec(hold1,16);
			//**************EFMPlus Decoder 1**********************
			 Out_Data2[jj] = EFM_Decoder(state, table, hold3);

			 To_String(buffer2, Out_Data2[jj]);
			 USART_PutString(buffer2);

		}// end for loop

		  //  To_String(buffer2, error);
		 	//TM_ILI9341_Puts(40, 10, buffer, &TM_Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
		//	TM_ILI9341_Puts(10, 36, "Input          :        Output", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
		//	LCD_display(temp11, 16,10*v,160);
		//	LCD_display(temp5, 8,10*v,10);

  	} // LARGE WHILE

}// END OF MAIN




/**===========================================================================
           FUNCTIONS
/*********************************************************************************/

void GPIO_Configuration(void)
{    // Enable clock for GPIOD (for orange LED)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
    // Initialization of GPIOD (for orange LED)
    GPIO_InitTypeDef GPIO_InitDef;
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &GPIO_InitDef);
}

/**************************************************************************************/
void USART_Config(void)
{
	// Enable clock for GPIOA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	// Enable clock for USART1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	// Connect PA9 to USART1_Tx
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	// Connect PA10 to USART1_Rx
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	// Initialization of GPIOA
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	// Initialization of USART1
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStruct);
	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // enable IRQ on RX
	//NVIC_EnableIRQ(USART1_IRQn);   // Enable IRQ for USART1 in NVIC
	// Enable USART1
	USART_Cmd(USART1, ENABLE);
}
/**************************************************************************************/
static void SPI_Config(void)
{
 GPIO_InitTypeDef GPIO_InitStructure;
 SPI_InitTypeDef SPI_InitStructure;
 /* Enable the SPI clock */
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
 /* Enable the GPIOA clock */
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
 /* Connect PA5 to SPI1_SCK */
 GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
 /* Connect PA6 to SPI1_MISO */
 GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
 /* Connect PA7 to SPI1_MOSI */
 GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
 /* Configure SPI1 pins as alternate function (No need to
 configure PA4 since NSS will be managed by software) */
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
 GPIO_Init(GPIOA, &GPIO_InitStructure);
 /* SPI configuration *****************************************/

 SPI_InitStructure.SPI_Direction =
 SPI_Direction_2Lines_FullDuplex;
 SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
 SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
 SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
 SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
 SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
 SPI_InitStructure.SPI_BaudRatePrescaler =
 SPI_BaudRatePrescaler_256;
 SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
 SPI_InitStructure.SPI_CRCPolynomial = 7;
 SPI_Init(SPI1, &SPI_InitStructure);
 SPI_Cmd(SPI1, ENABLE);
}

/**************************************************************************************/
void USART_PutChar(char c)
{
    // Wait until transmit data register is empty
    while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
    // Send a char using USART1
    USART_SendData(USART1, c);
}
/**************************************************************************************/
void USART_PutString(char *s)
{
    // Send a string
    while (*s)
    {
        USART_PutChar(*s++);
    }
}
/**************************************************************************************/
uint16_t USART_GetChar()
{
    // Wait until data is received
    while (!USART_GetFlagStatus(USART1, USART_FLAG_RXNE));
    // Read received char
    return USART_ReceiveData(USART1);
}
/**************************************************************************************/

void To_String(char* _buffer, unsigned int data)
{
  // we make our string assuming all hex digits are 0 to 9
  // string will be of the form 0xabcd
  // where a,b,c,d are the individual hex digits
  _buffer[0] = '0';
  _buffer[1] = 'x';
 // _buffer[2] = ( (data>>12) & 0x0F) + '0';
 // _buffer[3] = ( (data>>8)  & 0x0F) + '0';
  _buffer[2] = ( (data>>4)  & 0x0F) + '0';
  _buffer[3] = ( (data)     & 0x0F) + '0';
 // _buffer[6] = 0;

  // now we correct for the case where a digit
  // is A to F:
  if (_buffer[2] > '9') _buffer[2] += 7;
  if (_buffer[3] > '9') _buffer[3] += 7;
//  if (_buffer[4] > '9') _buffer[4] += 7;
//  if (_buffer[5] > '9') _buffer[5] += 7;

}

void To_String2(char* _buffer, unsigned int data)
{
  // we make our string assuming all hex digits are 0 to 9
  // string will be of the form 0xabcd
  // where a,b,c,d are the individual hex digits
  _buffer[0] = ( (data>>12) & 0x0F) + '0';
  _buffer[1] = ( (data>>8)  & 0x0F) + '0';
  _buffer[2] = ( (data>>4)  & 0x0F) + '0';
  _buffer[3] = ( (data)     & 0x0F) + '0';
  _buffer[4] = 0;

  // now we correct for the case where a digit
  // is A to F:
  if (_buffer[0] > '9') _buffer[2] += 7;
  if (_buffer[1] > '9') _buffer[3] += 7;
  if (_buffer[2] > '9') _buffer[4] += 7;
  if (_buffer[3] > '9') _buffer[5] += 7;

}

int bin_to_dec(int *arr,int in_size)
{
   int bin=0,i;

 	for ( i = 0; i < in_size; ++i )
	{
    	bin *= 2;
    	bin = bin + arr[i];
	}
	return bin;
}

void LCD_display(int *input, int size,int position,int x)
{
	int i,down =55;
		for(i =0;i< size;++i)
		{
			if (input[i] ==0)
			{
				TM_ILI9341_Puts((x+6*i), position+down, zero , &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
			}
			else if (input[i] ==1)
			{
				TM_ILI9341_Puts((x+6*i), position+down, one , &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
			}

			TM_ILI9341_Puts(100, position+down,"--->" , &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
		}
}
