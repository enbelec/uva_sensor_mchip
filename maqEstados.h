/* 
 * File:   maqEstados.h
 * Author: JUANPCR5
 *
 * Created on September 20, 2021, 5:11 PM
 */

#ifndef MAQESTADOS_H
#define	MAQESTADOS_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum{
        EST_INIT = 0,
        EST_REPOSO,
        EST_MEDIR,
        EST_MEDIR_1,
        EST_MEDIR_2,
        EST_MEDIR_3,
        EST_FIN_MEDIR,
        EST_VACIAR,
        EST_VACIAR_1,
        EST_VACIAR_2,
        EST_VACIAR_3,
        EST_FIN_VACIAR,
        EST_FIN,
    }ESTADOS_PRIN;
    
    extern ESTADOS_PRIN estPrin;

    extern void maqEstados(void);
    extern void cambiaEstado(ESTADOS_PRIN estado);
    extern ESTADOS_PRIN leeEstadoMaquina (void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* MAQESTADOS_H */

