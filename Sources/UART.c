/*
 * File:   ADC.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 18:33
 */

#include <xc.h>
#include <Generic.h>
#include <uart.h>
#include <pps.h>
#include <timer.h>
#include <stdio.h>
#include "../Headers/Interpreter.h"

#define FCY 40000000
#define BAUDRATE 115200
#define BRGVAL ((FCY/BAUDRATE)/4)-1
#define DELAY_87500ns asm volatile ("REPEAT, #3500"); Nop(); // 8750ns delay

void OpenUART(void)
{
    OpenUART1(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_UEN_00
            & UART_EN_WAKE & UART_DIS_LOOPBACK & UART_DIS_ABAUD & UART_UXRX_IDLE_ONE
            & UART_BRGH_FOUR & UART_NO_PAR_8BIT & UART_1STOPBIT,
            UART_SYNC_BREAK_DISABLED & UART_IrDA_POL_INV_ZERO
            & UART_INT_TX_BUF_EMPTY & UART_TX_ENABLE & UART_TX_BUF_NOT_FUL & UART_ADR_DETECT_DIS
            & UART_INT_RX_CHAR & UART_RX_OVERRUN_CLEAR,
            BRGVAL);
    ConfigIntUART1(UART_RX_INT_EN & UART_RX_INT_PR3 & UART_TX_INT_DIS & UART_TX_INT_PR0);

    _PCFG4 = 1;
    _PCFG5 = 1;
    PPSInput(IN_FN_PPS_U1RX,IN_PIN_PPS_RP3);        // Assign U1Rx To Pin RP3
    PPSOutput(OUT_FN_PPS_U1TX,OUT_PIN_PPS_RP2);     // Assign U1Tx To Pin RP2
}

void WriteUART(unsigned char data)
{
    U1TXREG = data;
    DELAY_87500ns;
}

void putsUART(unsigned char *buffer)
{
    while(*buffer != '\0')
        WriteUART(*(buffer++));
}

char ReadUART(void)
{
    return (char) (U1RXREG & 0xFF);
}


void __attribute__((interrupt,no_auto_psv)) _U1RXInterrupt(void)
{
    _U1RXIE = 0;
    _OERR = 0;
    while(DataRdyUART1())
        interpreteData(ReadUART());

    _U1RXIE = 1;
    
    IFS0bits.U1RXIF = 0; // Clear RX Interrupt flag
}

void __attribute__((interrupt,no_auto_psv)) _U1TXInterrupt(void)
{
    IFS0bits.U1TXIF = 0; // Clear TX Interrupt flag
}