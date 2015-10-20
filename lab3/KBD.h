#ifndef _LCOM_KBD_H_
#define _LCOM_KBD_H_

/*
 * @{
 *
 * Constants for programming the Keyboard. Needs to be completed.
 */

#define BIT(n) (0x01<<(n))

#define KBD_IRQ  1  // keyboard IRQ line

#define KBD_OUT_BUF 0x60 //keyboard controller output buffer

#define DELAY_US 20000   //20 ms, time waiting for the keyboard

#define PARITY BIT(7)   //Put 1 ate bit 7, Parity Error

#define TIMEOUT BIT(6) //Put 1 ate bit 6, Time-Out Error

#define STAT_REG 0x64 //Keyboard controller status register

#define TWO_BYTE 0xE0  //scan code with 2 bytes

#define MSB 0x80 //MSB at 1

#define BREAK_ESC 0x81 //break code of key esc

#define STATUS_READY_OUT 0x01 //status controller that indicates that we have something to read

#define OK 0 //to make the code easier to ready

#endif /* _LCOM_KBD_H */
