/* 
 * File:   i2c_hard.h
 * Author: JUANPCR5
 *
 * Created on 20 de septiembre de 2021, 15:31
 */

#ifndef I2C_HARD_H
#define	I2C_HARD_H

#ifdef	__cplusplus
extern "C" {
#endif

#define I2C_ACK	1
#define I2C_NO_ACK 0
	
	extern uint8_t errI2c;

void I2COpen(void);
void I2CClose(void);  
void I2CIdle(void);							
unsigned char I2CWrite(unsigned char I2C_DATA);																
unsigned char I2CRead(uint8_t ack);			
void I2CAck(void);				
void I2CNotAck(void);		
void I2CStop(void);				
void I2CStart(void);				




#ifdef	__cplusplus
}
#endif

#endif	/* I2C_HARD_H */

