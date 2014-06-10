/* 
 * File:   UART.h
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 20:55
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

    #define     resetUART       _UARTEN = 0; _UARTEN = 1;

    extern void OpenUART(void);
    extern void WriteUART(unsigned int);
    extern void putsUART(char *buffer);
    extern unsigned int getsUART(unsigned int length,unsigned int *buffer, unsigned int uart_data_wait);
    extern unsigned int ReadUART(void);

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

