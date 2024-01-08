/*!
    \file    gd32f10x_it.c
    \brief   interrupt service routines

    \version 2014-12-26, V1.0.0, firmware for GD32F10x
    \version 2017-06-20, V2.0.0, firmware for GD32F10x
    \version 2018-07-31, V2.1.0, firmware for GD32F10x
    \version 2020-09-30, V2.2.0, firmware for GD32F10x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/
#include "gd32f10x_it.h"
#include "main.h"
#include "systick.h"

extern uint8_t result[12];
extern uint8_t state_mode;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;

extern FlagStatus receive_flag;
extern can_receive_message_struct receive_message;

/*codes for freertos*/
volatile unsigned long long FreeRTOSRunTimeTicks = 0;
void xPortSysTickHandler( void );

/*!
    \brief      this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_Handler(void)
{
}

/*!
    \brief      this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void HardFault_Handler(void)
{
    /* if Hard Fault exception occurs, go to infinite loop */
    while (1)
    {
        // printf("HardFault_Handler\r\n");
    }
}

/*!
    \brief      this function handles MemManage exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void MemManage_Handler(void)
{
    /* if Memory Manage exception occurs, go to infinite loop */
    while (1)
    {
    }
}

/*!
    \brief      this function handles BusFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void BusFault_Handler(void)
{
    /* if Bus Fault exception occurs, go to infinite loop */
    while (1)
    {
    }
}

/*!
    \brief      this function handles UsageFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void UsageFault_Handler(void)
{
    /* if Usage Fault exception occurs, go to infinite loop */
    while (1)
    {
    }
}

/*!
    \brief      this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
/*
void SVC_Handler(void)
{
}
*/
/*!
    \brief      this function handles DebugMon exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void DebugMon_Handler(void)
{
}

/*!
    \brief      this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
/*
void PendSV_Handler(void)
{
}
*/
/*!
    \brief      this function handles SysTick exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SysTick_Handler(void)
{
    // led_spark();
    delay_decrement();

    HAL_SYSTICK_Callback();
	xPortSysTickHandler();		

}

/*!
    \brief      this function handles USART RBNE interrupt request and TBE interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void USART0_IRQHandler(void)
{
    if (RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE))
    {
        /* receive data */

        if (huart1.pRxBuffPtr != NULL)
        {
            huart1.pRxBuffPtr[huart1.RxXferCount++] = usart_data_receive(USART0);
            if (huart1.RxXferCount >= huart1.RxXferSize)
                huart1.RxXferCount = 0;
        }

        // }
    }
    if (RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_TBE))
    {
        /* transmit data */
        // usart_data_transmit(USART0, txbuffer[txcount++]);
        // if(txcount == tx_size){
        //    usart_interrupt_disable(USART0, USART_INT_TBE);
        // }
    }
}

void USART1_IRQHandler(void)
{
    if (RESET != usart_interrupt_flag_get(USART1, USART_INT_FLAG_RBNE))
    {
        /* receive data */

        if (huart2.pRxBuffPtr != NULL)
        {
            huart2.pRxBuffPtr[huart2.RxXferCount++] = usart_data_receive(USART1);
            if (huart2.RxXferCount >= huart2.RxXferSize)
                huart2.RxXferCount = 0;
        }
        else
            usart_data_receive(USART1);
        // }
    }
    if (RESET != usart_interrupt_flag_get(USART1, USART_INT_FLAG_TBE))
    {
        /* transmit data */
        // usart_data_transmit(USART0, txbuffer[txcount++]);
        // if(txcount == tx_size){
        //     usart_interrupt_disable(USART0, USART_INT_TBE);
        //  }
    }
}

void USART2_IRQHandler(void)
{
    if (RESET != usart_interrupt_flag_get(USART2, USART_INT_FLAG_RBNE))
    {
        /* receive data */

        if (huart3.pRxBuffPtr != NULL)
        {
            huart3.pRxBuffPtr[huart3.RxXferCount++] = usart_data_receive(USART2);
            if (huart3.RxXferCount >= huart3.RxXferSize)
                huart3.RxXferCount = 0;
        }
        else
            usart_data_receive(USART2);
        // }
    }
    if (RESET != usart_interrupt_flag_get(USART2, USART_INT_FLAG_TBE))
    {
        /* transmit data */
        //  usart_data_transmit(USART0, txbuffer[txcount++]);
        //  if(txcount == tx_size){
        //      usart_interrupt_disable(USART0, USART_INT_TBE);
        //   }
    }
}

void UART3_IRQHandler(void)
{
    if (RESET != usart_interrupt_flag_get(UART3, USART_INT_FLAG_RBNE))
    {
        /* receive data */
        if (huart4.pRxBuffPtr != NULL)
        {
            huart4.pRxBuffPtr[huart4.RxXferCount++] = usart_data_receive(UART3);
            if (huart4.RxXferCount >= huart4.RxXferSize)
                huart4.RxXferCount = 0;
        }
        else
            usart_data_receive(UART3);
    }
    if (RESET != usart_interrupt_flag_get(UART3, USART_INT_FLAG_TBE))
    {
        /* transmit data */
        //  usart_data_transmit(USART0, txbuffer[txcount++]);
        //  if(txcount == tx_size){
        //       usart_interrupt_disable(USART0, USART_INT_TBE);
        //}
    }
}

void UART4_IRQHandler(void)
{
    if (RESET != usart_interrupt_flag_get(UART4, USART_INT_FLAG_RBNE))
    {
        /* receive data */
        if (huart5.pRxBuffPtr != NULL)
        {
            huart5.pRxBuffPtr[huart5.RxXferCount++] = usart_data_receive(UART4);
            if (huart5.RxXferCount >= huart5.RxXferSize)
                huart5.RxXferCount = 0;
        }
        else
            usart_data_receive(UART4);
    }
    if (RESET != usart_interrupt_flag_get(UART4, USART_INT_FLAG_TBE))
    {
        /* transmit data */
        // usart_data_transmit(USART0, txbuffer[txcount++]);
        // if(txcount == tx_size){
        //    usart_interrupt_disable(USART0, USART_INT_TBE);
        //  }
    }
}

void USBD_LP_CAN0_RX0_IRQHandler(void)
{
    /* check the receive message */
    can_message_receive(CAN0, CAN_FIFO0, &receive_message);
    /* if((0x321 == receive_message.rx_sfid)&&(CAN_FF_STANDARD == receive_message.rx_ff) && (1 == receive_message.rx_dlen))
     {
         receive_flag = SET;
     }*/
    //mcu
    if(  (0x001806E600 == receive_message.rx_efid
		||0x001806E601 == receive_message.rx_efid
		||0x001806E602 == receive_message.rx_efid
		||0x001806E502 == receive_message.rx_efid
		||0x001806E503 == receive_message.rx_efid)
		&&(CAN_FF_EXTENDED == receive_message.rx_ff))
	{
       CanMcuParse(receive_message.rx_efid,receive_message.rx_data,receive_message.rx_dlen);
    }
	else if((0x001806E610 == receive_message.rx_efid
			||0x001806E611 == receive_message.rx_efid
			||0x001806E612 == receive_message.rx_efid
			||0x001806E613 == receive_message.rx_efid
			||0x001806E614 == receive_message.rx_efid
			||0x001806E615 == receive_message.rx_efid
			||0x001806E616 == receive_message.rx_efid
			||0x001806E617 == receive_message.rx_efid
			||0x001806E618 == receive_message.rx_efid
			||0x001806E620 == receive_message.rx_efid
			||0x001806E516 == receive_message.rx_efid)
			&&(CAN_FF_EXTENDED == receive_message.rx_ff))
	{
       CanBmsParse(receive_message.rx_efid,receive_message.rx_data,receive_message.rx_dlen);
    }
}

void EXTI0_IRQHandler(void)
{
    if (RESET != exti_interrupt_flag_get(EXTI_0))
    {
        // gd_eval_led_toggle(LED3);
        HAL_GPIO_EXTI_Callback(EXTI_0);
        exti_interrupt_flag_clear(EXTI_0);
    }
}

void TIMER1_IRQHandler(void)
{
    if (timer_interrupt_flag_get(TIMER1, TIMER_INT_FLAG_UP) == SET) // 获取TIMERx 中断标志 函数成功获取返回SET,否则RESET�?
    {
				displayInit();
        if (result[0] != 0)
        {
            sif_send_data_handle(state_mode);
        }
        timer_interrupt_flag_clear(TIMER1, TIMER_INT_FLAG_UP);// 清除中断位标�?
                                                              // 下面实现自己的函数�?
    }
}

void TIMER2_IRQHandler(void)
{
    if(SET == timer_interrupt_flag_get(TIMER2, TIMER_INT_FLAG_UP)){
        /* clear channel 0 interrupt bit */
       timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_UP);
			// if(FreeRTOSRunTimeTicks%1000==0)
			// {
			// 	printf("TIMER2_IRQHandler");
			// }
			  FreeRTOSRunTimeTicks++;
    }
		//timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_UP);// 清除中断位标�?

}
