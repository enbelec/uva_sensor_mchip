/* 
 * File:   mide.h
 * Author: JUANPCR5
 *
 * Created on September 21, 2021, 9:32 AM
 */

#ifndef MIDE_H
#define	MIDE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define NUM_DATOS_SENS 100 //numero de medidas a guardar enla cpu, no se usa

    typedef union{
        char todo[47];
        struct{
            char sens[6];
            char O2[9];
            char temp[8];
            char presion[7];
            char O2r[9];
            char error[8];
        }datos;
    }DATOS_SENS;
    
    extern DATOS_SENS datosSens[NUM_DATOS_SENS];
    extern uint16_t puntDatos;

    extern uint8_t numSens; //numero de sensor que mide
    extern uint8_t arrSens[MAX_SENS];
    
    extern bool FrespM;
    
    extern void mide(void);
    extern void inicializaMedir(void);
    extern void finMedir (void);
    extern bool escaneando (void);
    extern bool poneModoPool(void);
    extern void poneRespuestaM(bool resp);
    extern void poneContadorTiempoTotal (uint16_t tiempo);
    
#ifdef	__cplusplus
}
#endif

#endif	/* MIDE_H */

