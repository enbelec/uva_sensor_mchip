/* 
 * File:   EjecSerie.h
 * Author: JUANPCR5
 *
 * Created on September 20, 2021, 5:41 PM
 */

#ifndef EJECSERIE_H
#define	EJECSERIE_H

#ifdef	__cplusplus
extern "C" {
#endif

    extern bool Ftransmite;
    extern char bufferOut[]; //buffer de salida

    extern void InicializaSeriePC(void);
    extern void EntradaSeriePC(void);
    extern void ProcesoSeriePC(void);
    extern void salidaSeriePC(void);


#ifdef	__cplusplus
}
#endif

#endif	/* EJECSERIE_H */

