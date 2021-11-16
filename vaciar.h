/* 
 * File:   vaciar.h
 * Author: JUANPCR5
 *
 * Created on 23 de septiembre de 2021, 8:16
 */

#ifndef VACIAR_H
#define	VACIAR_H

#include "mide.h"


#ifdef	__cplusplus
extern "C" {
#endif

   
    typedef enum{
        EST_VAC_REPOSO,
        EST_VAC_ABRE_SALIR,
        EST_VAC_ABRE_ENTRAR,
        EST_VAC_MIDE,
        EST_VAC_FIN_VACIAR,
    }EST_VAC;
    
    typedef struct{
        uint8_t Fcerrar : 1; //manda cerrar
        uint8_t Fcerrando : 1; //ha cerrado entrada
        uint8_t Fcerrado :1;    //ha cerrado todo
    }CIERRES;
    
    extern EST_VAC estVaciar;
    
    extern CIERRES arrCierres[MAX_SENS]; //array de como estan los cierres de electrovalvulas

    extern void vaciar(void);
    extern bool cerrarValvulas(void);
    extern void finVaciar(void);
    extern void poneRespuestaVac(bool resp);
    extern bool vaciando(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* VACIAR_H */

