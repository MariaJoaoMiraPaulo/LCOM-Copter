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

#define SCROLL_ON 1  //use to ativate scroll  1= 2⁰

#define NUM_ON 2   //use to ativate num 2=2¹

#define CAPS_ON 4  //use to ativate caps 4=2²

///////////////////////////		 MOUSE		\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#define MOUSE_IRQ 12

#define IBF BIT(1)			//use to test if input buffer is full

#define OBF BIT(0)			//use to test if output buffer is full

#define FIRST_BYTE BIT(3)     //use to test if is the first byte of the packet

#define ENABLE_MOUSE 0xA8

#define MOUSE_COMMAND 0xD4

#define ENABLE_DATA_PACKETS 0xF4

#define DISABLE_STREAM_MODE 0xF5

#define CONFIG_FIRST_BYTE (BIT(3)|BIT(7))

#define CONFIG_SECOND_BYTE (BIT(2) | BIT(3) | BIT(4) | BIT(5) | BIT(6)| BIT(7))

#define STATUS_REQUEST 0xE9

#define SET_RESOLUTION (BIT(0) | BIT(1))

#define STREAM_MOD 0xEA

#define RIGHT_BUTTON BIT(1)

#endif /* _LCOM_KBD_H */
