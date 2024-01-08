/*
 * FreeRTOS V202212.01
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/*
	BASIC INTERRUPT DRIVEN SERIAL PORT DRIVER FOR UART0.
*/

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

/* Library includes. */
// #include "stm32f10x_lib.h"
#include "gd32f10x.h"
#include "gd32f10x_eval.h"

/* Demo application includes. */
#include "serial.h"
/*-----------------------------------------------------------*/

/* Misc defines. */
#define serINVALID_QUEUE				( ( QueueHandle_t ) 0 )
#define serNO_BLOCK						( ( TickType_t ) 0 )
#define serTX_BLOCK_TIME				( 40 / portTICK_PERIOD_MS )

/*-----------------------------------------------------------*/

/* The queue used to hold received characters. */
static QueueHandle_t xRxedChars;
static QueueHandle_t xCharsForTx;

/*-----------------------------------------------------------*/

/* UART interrupt handler. */
void vUARTInterruptHandler( void );

/*-----------------------------------------------------------*/

/*
 * See the serial2.h header file.
 */
xComPortHandle xSerialPortInitMinimal( unsigned long ulWantedBaud, unsigned portBASE_TYPE uxQueueLength )
{
xComPortHandle xReturn;
// USART_InitTypeDef USART_InitStructure;
// NVIC_InitTypeDef NVIC_InitStructure;
// GPIO_InitTypeDef GPIO_InitStructure;

	/* Create the queues used to hold Rx/Tx characters. */
	xRxedChars = xQueueCreate( uxQueueLength, ( unsigned portBASE_TYPE ) sizeof( signed char ) );
	xCharsForTx = xQueueCreate( uxQueueLength + 1, ( unsigned portBASE_TYPE ) sizeof( signed char ) );

	/* If the queue/semaphore was created correctly then setup the serial port
	hardware. */
	if( ( xRxedChars != serINVALID_QUEUE ) && ( xCharsForTx != serINVALID_QUEUE ) )
	{
		// printf("the queue/semaphore was created correctly\n");
		/* clear all UART4 FLAG */
		// usart_flag_clear(UART4, USART_FLAG_RBNE);
		// usart_flag_clear(UART4, USART_FLAG_TBE);

		// usart_interrupt_enable(UART4, USART_INT_RBNE);		
		//printf all flags
		// printf("USART_FLAG_RBNE: %d\n", usart_flag_get(UART4,USART_FLAG_RBNE));
		// printf("USART_FLAG_TBE: %d\n", usart_flag_get(UART4,USART_FLAG_TBE));
		// printf("USART_INT_RBNE: %d\n", usart_interrupt_flag_get(UART4,USART_INT_FLAG_RBNE));
		// printf("USART_INT_TBE: %d\n", usart_interrupt_flag_get(UART4,USART_INT_FLAG_TBE));

		// /* Enable UART4 clock */
		// RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE );

		// /* Configure UART4 Rx (PA10) as input floating */
		// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		// GPIO_Init( GPIOA, &GPIO_InitStructure );

		// /* Configure UART4 Tx (PA9) as alternate function push-pull */
		// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		// GPIO_Init( GPIOA, &GPIO_InitStructure );

		// USART_InitStructure.USART_BaudRate = ulWantedBaud;
		// USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		// USART_InitStructure.USART_StopBits = USART_StopBits_1;
		// USART_InitStructure.USART_Parity = USART_Parity_No ;
		// USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		// USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		// USART_InitStructure.USART_Clock = USART_Clock_Disable;
		// USART_InitStructure.USART_CPOL = USART_CPOL_Low;
		// USART_InitStructure.USART_CPHA = USART_CPHA_2Edge;
		// USART_InitStructure.USART_LastBit = USART_LastBit_Disable;

		// USART_Init( UART4, &USART_InitStructure );

		// USART_ITConfig( UART4, USART_IT_RXNE, ENABLE );

		// NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
		// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = configLIBRARY_KERNEL_INTERRUPT_PRIORITY;
		// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		// NVIC_Init( &NVIC_InitStructure );

		// USART_Cmd( UART4, ENABLE );
	}
	else
	{
		printf("the queue/semaphore was created failed\n");
		xReturn = ( xComPortHandle ) 0;
	}

	/* This demo file only supports a single port but we have to return
	something to comply with the standard demo header file. */
	return xReturn;
}
/*-----------------------------------------------------------*/

signed portBASE_TYPE xSerialGetChar( xComPortHandle pxPort, signed char *pcRxedChar, TickType_t xBlockTime )
{
	/* The port handle is not required as this driver only supports one port. */
	( void ) pxPort;

	/* Get the next character from the buffer.  Return false if no characters
	are available, or arrive before xBlockTime expires. */
	if( xQueueReceive( xRxedChars, pcRxedChar, xBlockTime ) )
	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	}
}
/*-----------------------------------------------------------*/

void vSerialPutString( xComPortHandle pxPort, const signed char * const pcString, unsigned short usStringLength )
{
signed char *pxNext;

	/* A couple of parameters that this port does not use. */
	( void ) usStringLength;
	( void ) pxPort;

	/* NOTE: This implementation does not handle the queue being full as no
	block time is used! */

	/* The port handle is not required as this driver only supports UART1. */
	( void ) pxPort;

	/* Send each character in the string, one at a time. */
	pxNext = ( signed char * ) pcString;
	while( *pxNext )
	{
		xSerialPutChar( pxPort, *pxNext, serNO_BLOCK );
		pxNext++;
	}
}
/*-----------------------------------------------------------*/

signed portBASE_TYPE xSerialPutChar( xComPortHandle pxPort, signed char cOutChar, TickType_t xBlockTime )
{
signed portBASE_TYPE xReturn;

	if( xQueueSend( xCharsForTx, &cOutChar, xBlockTime ) == pdPASS )
	{
		xReturn = pdPASS;
		// USART_ITConfig( UART4, USART_IT_TXE, ENABLE );
		usart_interrupt_enable(UART4, USART_INT_TBE);
	}
	else
	{
		xReturn = pdFAIL;
	}

	return xReturn;
}
/*-----------------------------------------------------------*/

void vSerialClose( xComPortHandle xPort )
{
	/* Not supported as not required by the demo application. */
}
/*-----------------------------------------------------------*/

// check xTaskGetCurrentTaskHandle
void vUARTInterruptHandler( void )
{
portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
char cChar;
TaskHandle_t xCurrentTaskHandle = xTaskGetCurrentTaskHandle();
const char *pcTaskName;

// char InfoBuffer[200];

if (xCurrentTaskHandle != NULL) 
    pcTaskName = pcTaskGetName(xCurrentTaskHandle);

// printf("vUARTInterruptHandler\n"); 
// vTaskList(InfoBuffer);
// printf("%s\r\n",InfoBuffer);


// if(pcTaskName != NULL && strcmp(pcTaskName, "CLI") == 0)
// {

	// if( USART_GetITStatus( UART4, USART_IT_TXE ) == SET )
	if(usart_flag_get(UART4, USART_FLAG_TBE) == SET)
	{
		// printf("vUARTInterruptHandler0: %c\n", cChar);
		/* The interrupt was caused by the THR becoming empty.  Are there any
		more characters to transmit? */
		if(xQueueReceiveFromISR( xCharsForTx, &cChar, &xHigherPriorityTaskWoken ) == pdTRUE)
		{
			// printf("vUARTInterruptHandler1: %c\n", cChar);
			/* A character was retrieved from the queue so can be sent to the
			THR now. */
			// USART_SendData( UART4, cChar );
			usart_data_transmit(UART4, cChar);
			
		}
		else
		{
			// printf("vUARTInterruptHandler2: %c\n", cChar);
			// USART_ITConfig( UART4, USART_IT_TXE, DISABLE );
			usart_interrupt_disable(UART4, USART_INT_TBE);
		}
	}
// }
	// if( USART_GetITStatus( UART4, USART_IT_RXNE ) == SET )
	if(usart_flag_get(UART4, USART_FLAG_RBNE) == SET)
	{

		// cChar = USART_ReceiveData( UART4 );
		cChar = usart_data_receive(UART4);
		// printf("vUARTInterruptHandler3: %c\n", cChar);		
		xQueueSendFromISR( xRxedChars, &cChar, &xHigherPriorityTaskWoken );
	}
	//printf all flags
	// printf("USART_INT_FLAG_RBNE: %d\n", usart_interrupt_flag_get(UART4,USART_FLAG_RBNE));
	// printf("USART_INT_FLAG_TBE: %d\n", usart_interrupt_flag_get(UART4,USART_FLAG_TBE));


	// printf("USART_INT_RBNE: %d\n", usart_interrupt_flag_get(UART4,USART_INT_RBNE));
	// printf("USART_INT_TBE: %d\n", usart_interrupt_flag_get(UART4,USART_INT_TBE));


	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );

}







