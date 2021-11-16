/* 
 * File:   BM280.h
 * Author: JUANPCR5
 *
 * Created on November 16, 2021, 8:47 AM
 */

#ifndef BM280_H
#define	BM280_H

#ifdef	__cplusplus
extern "C" {
#endif

#define BM280_ADD_WR 0xEC
#define BM280_ADD_RD 0xED    

#define BM280_ADD_RESET 0xE0
#define BM280_VALOR_RESET 0xB6
#define BM280_ADD_CAL1 0x88
#define BM280_ADD_CAL2 0xE1
#define BM280_ADD_STATUS 0xF3
#define BM280_ADD_SENS_PRES 0xF7    
#define BM280_ADD_SENS_TEMP 0xFA    
#define BM280_ADD_SENS_HUM 0xFD    
    
    
    typedef struct bm280_calibracion{
        uint16_t dig_T1;
        int16_t dig_T2;
        int16_t dig_T3;
        uint16_t dig_P1;
        int16_t dig_P2;
        int16_t dig_P3;
        int16_t dig_P4;
        int16_t dig_P5;
        int16_t dig_P6;
        int16_t dig_P7;
        int16_t dig_P8;
        int16_t dig_P9;
        uint16_t dig_H1;
        int16_t dig_H2;
        uint16_t dig_H3;
        int16_t dig_H4;
        int16_t dig_H5;
    }BM280_CALIBRACION;
    
    extern BM280_CALIBRACION Bm280Calibracion;
    
    extern bool Bm280Reset(void);
    extern void Bm280LeeCalibracion(void);
    extern void Bm280LeeSensores(int32_t *temp, uint32_t *Presion, uint32_t *humedad);
    extern uint8_t BM280LeeStatus(void);
    extern void Bm280PoneModo(uint8_t t_sb, uint8_t filter, uint8_t osrs_t,
        uint8_t osrs_p, uint8_t osrs_h, uint8_t mode);
    
    void Bm280CompensaSensores(void);



#ifdef	__cplusplus
}
#endif

#endif	/* BM280_H */

