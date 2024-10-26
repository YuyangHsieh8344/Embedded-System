#include "msp.h"

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer

    // Error LEDs
    P1->DIR |= BIT0;    // set BIT0 as OUTPUT
    P1->OUT &= ~(BIT0); // set BIT0 as LOW
    P1->SEL0 &= ~(BIT0);
    P1->SEL1 &= ~(BIT0);

    // RGB LEDs
    P2->DIR |= BIT0 | BIT1 | BIT2;    // set BIT0,1,2 as OUTPUTs
    P2->OUT &= ~(BIT0 | BIT1 | BIT2); // set BIT0,1,2 as LOW
    P2->SEL0 &= ~(BIT0 | BIT1 | BIT2);
    P2->SEL1 &= ~(BIT0 | BIT1 | BIT2);

    // Enable UART2 Pins (P3.2->RX, P3.3->TX)
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

    // Enable NVIC for UART2
    NVIC->ISER[0] = 1 << (EUSCIA2_IRQn & 31);

    // Enable global interrupts
    __enable_irq();

    while (1); // Infinite loop
}

void EUSCIA2_IRQHandler(void)
{
    if (EUSCI_A2->IFG & EUSCI_A_IFG_RXIFG) // receive interrupt
    {
        char c = EUSCI_A2->RXBUF; // read the received character
        int i, j; // Declare variables outside the loops

        switch (c)
        {
        case 'r':
            P2->OUT &= ~(BIT0); // set BIT0 as LOW
            P2->OUT &= ~(BIT1); // set BIT0 as LOW
            P2->OUT &= ~(BIT2); // set BIT0 as LOW
            P2->OUT ^= BIT0; // Toggle Red LED (P2.0)
            break;
        case 'g':
            P2->OUT &= ~(BIT0); // set BIT0 as LOW
            P2->OUT &= ~(BIT1); // set BIT0 as LOW
            P2->OUT &= ~(BIT2); // set BIT0 as LOW
            P2->OUT ^= BIT1; // Toggle Green LED (P2.1)

            break;
        case 'b':
            P2->OUT &= ~(BIT0); // set BIT0 as LOW
            P2->OUT &= ~(BIT1); // set BIT0 as LOW
            P2->OUT &= ~(BIT2); // set BIT0 as LOW
            P2->OUT ^= BIT2; // Toggle Blue LED (P2.2)

            break;


        default:
            // Blink Error LED (P1.0) twice
            for (i = 0; i < 2; i++)
            {
                P1->OUT ^= BIT0; // Toggle Error LED (P1.0)
                for (j = 0; j < 100000; j++); // Simple delay
                P1->OUT ^= BIT0; // Toggle Error LED off
                for (j = 0; j < 100000; j++); // Simple delay
            }
            break;
        }

        EUSCI_A2->IFG &= ~EUSCI_A_IFG_RXIFG; // Clear the receive interrupt flag
    }
}
