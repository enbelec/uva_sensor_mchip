/* 
 * File:   mandaSpi.h
 * Author: JUANPCR5
 *
 * Created on September 20, 2021, 12:30 PM
 */

#ifndef MANDASPI_H
#define	MANDASPI_H

#include "mcc_generated_files/dma.h"
#include "variables.h"


#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct salida_Spi{
        union {
            uint8_t byte1_4;
            struct{
                uint8_t led1_verde :1;
                uint8_t led1_rojo :1;
                uint8_t led2_verde :1;
                uint8_t led2_rojo :1;
                uint8_t led3_verde :1;
                uint8_t led3_rojo :1;
                uint8_t led4_verde :1;
                uint8_t led4_rojo :1;
            }bits1_4;
        }leds1_4;

        union {
            uint8_t byte5_8;
            struct{
                uint8_t led5_verde :1;
                uint8_t led5_rojo :1;
                uint8_t led6_verde :1;
                uint8_t led6_rojo :1;
                uint8_t led7_verde :1;
                uint8_t led7_rojo :1;
                uint8_t led8_verde :1;
                uint8_t led8_rojo :1;
            }bits5_8;
        }leds5_8;
        
        struct {
            union{
                uint8_t byteMpx;
                struct{
                    uint8_t mpx :3;
                    uint8_t mpx_enh :1;
                    uint8_t mpxrx :1;
                }bits;
            }mpxu;
        }mpx;
        
        union{
            uint8_t byte_pow;
            struct{
                uint8_t pow1 :1;
                uint8_t pow2 :1;
                uint8_t pow3 :1;
                uint8_t pow4 :1;
                uint8_t pow5 :1;
                uint8_t pow6 :1;
                uint8_t pow7 :1;
                uint8_t pow8 :1;
            }bits_pow;
        }power;
        
        union{
            uint8_t byte_ev1_8;  //Ev salida de gas
            struct{
                uint8_t ev1 :1;
                uint8_t ev2 :1;
                uint8_t ev3 :1;
                uint8_t ev4 :1;
                uint8_t ev5 :1;
                uint8_t ev6 :1;
                uint8_t ev7 :1;
                uint8_t ev8 :1;
            }bits_ev1_8;
        }ev1_8;

        union{
            uint8_t byte_ev9_16; //entrada de nitrogeno
            struct{
                uint8_t ev9 :1;
                uint8_t ev10 :1;
                uint8_t ev11 :1;
                uint8_t ev12 :1;
                uint8_t ev13 :1;
                uint8_t ev14 :1;
                uint8_t ev15 :1;
                uint8_t ev16 :1;
            }bits_ev9_16;
        }ev9_16;

    }SALIDA_SPI;

    extern SALIDA_SPI salidaSpi[]; //8 salidas para 4cajas 64 sensores

    extern void mandaSpi(void);
    extern void inicializaSpi(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* MANDASPI_H */

