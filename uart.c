#include "gpio.h"

#define UART ((NRF_UART_REG*)0x40002000)

typedef struct {
    volatile uint32_t STARTRX;
    volatile uint32_t STOPRX;
    volatile uint32_t STARTTX;
    volatile uint32_t STOPTX;
    volatile uint32_t RESERVED1[3];
    volatile uint32_t SUSPEND;
    volatile uint32_t RESERVED2[56];

    volatile uint32_t CTS;
    volatile uint32_t NCTS;
    volatile uint32_t RXDRDY;
    volatile uint32_t RESERVED3[4];
    volatile uint32_t TXDRDY;
    volatile uint32_t RESERVED4[1];
    volatile uint32_t ERROR;
    volatile uint32_t RESERVED5[7];
    volatile uint32_t RXTO;
    volatile uint32_t RESERVED6[46];

    volatile uint32_t SHORTS;
    volatile uint32_t RESERVED7[64];
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED8[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED9[31];
    volatile uint32_t ENABLE;

    volatile uint32_t RESERVED10[1];
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;

    volatile uint32_t RTS;
    volatile uint32_t TXD;
    volatile uint32_t RXD;
    volatile uint32_t RESERVED11[1];
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVED12[17];
    volatile uint32_t CONFIG;

} NRF_UART_REG;


void uart_init(){
    GPIO1->PIN_CNF[8] = 1; //TXD - output
    GPIO0->PIN_CNF[6] = 0; //RXD - input

    UART->PSELTXD = 8;
    UART->PSELRXD = 6;

    UART->BAUDRATE = 0x0075F000;
    UART->PSELRTS = 0xFFFFFFFF; //disconnect = 1
    UART->PSELCTS = 0xFFFFFFFF;

    UART->ENABLE = 4; //enable = 4
    UART->STARTRX = 1; //trigger = 1

}

void uart_send(char letter){
    UART->STARTTX = 1;

    UART->TXD = letter;

    while(UART->TXDRDY){
    }

    UART->TXDRDY = 0;
    UART->STOPTX = 1;

}

char uart_read(){
    UART->STARTRX = 1;

    if(UART->RXDRDY){
        UART->RXDRDY = 0;
        char letter = UART->RXD;
        return letter;
    }
    else{
        return '\0';
    }

}