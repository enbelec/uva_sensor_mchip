/* 
 * File:   variables.h
 * Author: JUANPCR5
 *
 * Created on 20 de septiembre de 2021, 15:23
 */

#ifndef VARIABLES_H
#define	VARIABLES_H

#ifdef	__cplusplus
extern "C" {
#endif

//#define _TEST // para probar cosas, salida por led rojo
    
#define MAX_SENS 64  //numero maximo de sensores
#define MAX_PLACAS 8 //numero maximo de placas
#define T_ESPERA_COMS 30 //tiempode espera respuesta de comunicaciones cada unidad son 10ms
    
typedef union int_byte{
    uint16_t allByte;
    struct{
        uint8_t LowByte;
        uint8_t Highbyte;
    }uByte;
}INT_BYTE;


extern uint8_t numSensores;
extern uint8_t numplacas;
extern uint8_t tEntreMedidas;
extern uint16_t tMedicion;
extern uint8_t error; //hay error cuanto el numero mas granded mayor error
extern uint16_t limiteO2; //limite o2 para cerrar valvulas

//************************ E2PROM

#define E2P_CHECK				0X00
#define E2P_NUM_SENSORES		0X02    //
#define E2P_NUM_PLACAS          0X04    // cada placa 8 sensores
#define E2P_T_ENTRE_MEDIDAS     0X06    // tiempo en segundos
#define E2P_T_MEDICION          0X08    // tiempo enminutos



#ifdef	__cplusplus
}
#endif

#endif	/* VARIABLES_H */

