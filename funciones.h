/* 
 * File:   funciones.h
 * Author: JUANPCR5
 *
 * Created on 20 de septiembre de 2021, 15:29
 */

#ifndef FUNCIONES_H
#define	FUNCIONES_H

#include "struct.h"


#ifdef	__cplusplus
extern "C" {
#endif

#define E2P_ADDR_WR 0xA0
#define E2P_ADDR_RD 0xA1	

uint8_t  EscribeByteE2prom( uint8_t direccion, uint8_t dato);
uint8_t LeeByteE2prom(uint8_t direccion);
uint8_t  EscribeIntE2prom( uint8_t direccion, uint16_t dato);
uint16_t LeeIntE2prom(uint8_t direccion);
INT_BYTE pasaHexaDec(int datoHex);
uint8_t pasaBinaHex(uint8_t entrada);



#ifdef	__cplusplus
}
#endif

#endif	/* FUNCIONES_H */

