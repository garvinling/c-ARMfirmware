#include <LPC21xx.H>                     /* LPC21xx definitions               */
#include "Serial.h"

int uart1_getkey (void)  {                     /* Read character from Serial Port   */

  while (!(U1LSR & 0x01));
		return (U1RBR);
}

int uart0_getkey (void)  {                     /* Read character from Serial Port   */

  while (!(U0LSR & 0x01));
		return (U0RBR);
}

void uart0_init(void)
{
  /* initialize the serial interface   */
  PINSEL0 = 0x00050005;           /* Enable RxD1 and TxD1                     */
  U0LCR = 0x83;                   /* 8 bits, no Parity, 1 Stop bit            */
  U0DLL = 97;                     /* 9600 Baud Rate @ 15MHz VPB Clock         */
  //U1DLM = 1;
  U0LCR = 0x03;                   /* DLAB = 0                                 */
}

void uart1_init(void)
{
  /* initialize the serial interface   */
  //PINSEL0 = 0x00050005;           /* Enable RxD1 and TxD1                     */
  U1LCR = 0x83;                   /* 8 bits, no Parity, 1 Stop bit            */
  U1DLL = 97;                     /* 9600 Baud Rate @ 15MHz VPB Clock         */
  //U1DLM = 1;
  U1LCR = 0x03;                   /* DLAB = 0                                 */
}

void uart0_putc(char c)
{
	while(!(U0LSR & 0x20));
		U0THR = c;  // Send character
}

void uart1_putc(char c)
{
	while(!(U1LSR & 0x20));
		U1THR = c;  // Send character
}

void uart0_puts(char *p)
{
	while(*p) // Point to character
	{
		uart0_putc(*p++);   // Send character then point to next character
	}
}

void uart1_puts(char *p)
{
	while(*p) // Point to character
	{
		uart1_putc(*p++);   // Send character then point to next character
	}
}
