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

#define KBD_IN_BUF  0x60 //keyboard controller input buffer

#define SET_LED 0xED //command that warns the keyboard which is going to change the led

#define DELAY_US 20000   //20 ms, time waiting for the keyboard

#define PARITY BIT(7)   //Put 1 ate bit 7, Parity Error

#define TIMEOUT BIT(6) //Put 1 ate bit 6, Time-Out Error

#define STAT_REG 0x64 //Keyboard controller status register

#define TWO_BYTE 0xE0  //scan code with 2 bytes

#define MSB 0x80 //MSB at 1

#define BREAK_ESC 0x81 //break code of key Esc

#define STATUS_READY_OUT 0x01 //status controller that indicates that we have something to read

#define OK 0 //to make the code easier to ready

#define REPEAT 1 // error!!

#define ACK 0xFA //Tells everything went well

#define RESEND 0xFE // Founded a error inside the function

#define ERROR 0xFC //Error, must do the function all over again

#define SCROLL_ON 1

#define NUM_ON 2

#define CAPS_ON 4

#endif /* _LCOM_KBD_H */
