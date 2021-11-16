/* 
 * File:   EjecSerieSens.h
 * Author: JUANPCR5
 *
 * Created on September 20, 2021, 7:18 PM
 */

#ifndef EJECSERIESENS_H
#define	EJECSERIESENS_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum {
        SENS_MODO_STREAM = 0,
        SENS_MODO_POOL,
        SENS_MODO_OFF,
        SENS_MIDE_O2,
        SENS_MIDE_TODO,
        SENS_PIDE_INFO_DIA,
        SENS_PIDE_INFO_NUM_SERIE,
        SENS_PIDE_INFO_SOFT,
    }SENS_COMS;
    
    extern bool FdatoRecibido;
    extern char bufferProcSens[]; //buffer proceso

    extern void InicializaSerieSens(void);
    extern void EntradaSerieSens(void);
    extern void ProcesoSerieSens(void);
    extern void salidaSerieSens(void);
    extern void mandaComASensor(SENS_COMS comando);
    extern void vaciaBufferInSens(void);

#ifdef	__cplusplus
}
#endif

#endif	/* EJECSERIESENS_H */

