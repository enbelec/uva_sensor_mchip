/* 
 * File:   strcut.h
 * Author: JUANPCR5
 *
 * Created on 20 de septiembre de 2021, 15:16
 */



#ifndef STRCUT_H
#define	STRCUT_H

#ifdef	__cplusplus
extern "C" {
#endif

#define byte uint8_t

 typedef union bflags {
  byte Byte;
  struct {
    byte BIT0    :1;
    byte BIT1    :1;
    byte BIT2    :1;
    byte BIT3    :1;
    byte BIT4    :1;
    byte BIT5    :1;
    byte BIT6    :1;
    byte BIT7    :1;
  } Bits;
} BYTESTR;


/*
typedef union unionbyte {
  uint16_t allByte;
  struct {
    byte LowByte     :8;
    byte HighByte    :8;
  } uByte;
} intByte;
*/


#ifdef	__cplusplus
}
#endif

#endif	/* STRCUT_H */

