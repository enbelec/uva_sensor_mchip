/* 
 * File:   tiempo.h
 * Author: JUANPCR5
 *
 * Created on September 20, 2021, 12:07 PM
 */

#include "mcc_generated_files/system.h"

#ifndef TIEMPO_H
#define	TIEMPO_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct {
    
	uint8_t Fi1ms	:1;	//dispar enla interupcion para tenerlo en cuenta en el main
	uint8_t F1ms	:1;
	uint8_t F10ms	:1;
	uint8_t F10ms_5	:1;	//cada 10 ms pero alternativo a F10ms
	uint8_t F100ms	:1;
    uint8_t F100ms_5 :1; //cada 500ms
	uint8_t F1seg	:1;
	uint8_t F10seg	:1;
	uint8_t contms;
	uint8_t contdms;
	uint8_t contcms;
	uint8_t contSeg;
	uint8_t contMin;
	uint8_t contHoras;
}VE_TIEMPO;

extern VE_TIEMPO	veTiempo;

extern void contadorTiempo(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TIEMPO_H */

