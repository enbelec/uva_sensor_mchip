/* 
 * File:   hardware.h
 * Author: JUANPCR5
 *
 * Created on 22 de septiembre de 2021, 7:27
 */

#ifndef HARDWARE_H
#define	HARDWARE_H

#ifdef	__cplusplus
extern "C" {
#endif



    
    extern void ponePower(void);
    extern void poneLeds(bool FledRojos);
    extern void poneLedCpu(void);
    extern void poneMpx(int8_t sensor);
    
#ifdef	__cplusplus
}
#endif

#endif	/* HARDWARE_H */

