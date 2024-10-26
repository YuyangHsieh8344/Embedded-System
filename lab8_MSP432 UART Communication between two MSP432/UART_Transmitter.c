#include "msp.h"
#include<stdint.h>
#include<stdbool.h>

void sendString(char *str);
void sendChar(char s);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer

    // Enable UART0 Pins
    // P1.2->RX
    // P1.3->TX
    P1->SEL0 |= BIT2 | BIT3;
    P1->SEL1 &= ~(BIT2 | BIT3);

    // UART0 Configuration
    EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SWRST; // Clear previous configuration of UART
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK; // Use SMCLK as clock source (3MHz)
    //N = clock source / baud rate = 3000000 / 9600 / 16 = 19
    EUSCI_A0->BRW = 19; // Baud Rate 9600

    //19.53125 - 19 = 0.53125 * 16 = 8.5, round up to 9
    EUSCI_A0->MCTLW = (9 << EUSCI_A_MCTLW_BRF_OFS | EUSCI_A_MCTLW_OS16);

    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Release reset
    EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG; // Clear interrupt flag
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE; // Enable RX interrupt

    // Enable UART2 Pins
    // P3.2->RX
    // P3.3->TX
    P3->SEL0 |= BIT2 | BIT3;
    P3->SEL1 &= ~(BIT2 | BIT3);

    // UART2 Configuration
    EUSCI_A2->CTLW0 = EUSCI_A_CTLW0_SWRST; // Clear previous configuration of UART
    EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK; // Use SMCLK as clock source
    EUSCI_A2->BRW = 19; // Baud Rate 9600

    //19.53125 - 19 = 0.53125 * 16 = 8.5, round up to 9
    EUSCI_A2->MCTLW = (9 << EUSCI_A_MCTLW_BRF_OFS | EUSCI_A_MCTLW_OS16);
    EUSCI_A2->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Release reset

    EUSCI_A2->IFG &= ~EUSCI_A_IFG_RXIFG; // Clear interrupt flag
    EUSCI_A2->IE |= EUSCI_A_IE_RXIE; // Enable RX interrupt

    // Enable NVIC for UART0
    NVIC->ISER[0] = 1 << (EUSCIA0_IRQn & 31);
    // Enable global interrupts
    __enable_irq();

    sendString("Enter r for red, g for green, b for blue!\r\n"); // send message

    while (1)
    {
        // do nothing
    }
}

void EUSCIA0_IRQHandler(void)
{
    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG) // receive interrupt
    {
        char c = EUSCI_A0->RXBUF; // store data into character buffer, and clear flag
        sendString(&c);
        sendChar(c);              // display character through the SERIAL port
    }
}

void sendString(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        while (!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG)); // Wait until TXBUF is empty
        EUSCI_A0->TXBUF = str[i]; // Send character through buffer
        i++;
    }
}

void sendChar(char s)
{
    while (!(EUSCI_A2->IFG & EUSCI_A_IFG_TXIFG)); // Wait until TXBUF is empty
        EUSCI_A2->TXBUF = s; // Send character through buffer
}
