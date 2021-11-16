
#include "includes.h"
#include "mcc_generated_files/pin_manager.h"

uint8_t errI2c;

void I2CIdle(void)
{
  Nop();
  Nop();
  Nop();
  Nop();
}

void I2COpen(void)
{
   SCL_SetDigitalOutput();
   SDA_SetDigitalOutput();
   SCL_SetHigh();
   SDA_SetHigh();
	I2CIdle();
}

/*
void I2CClose(void)
{
   SCL_TRIS = OUTPUT;
   SDA_TRIS = OUTPUT;
   SCL_LAT = 0;
   SDA_LAT = 0;
}
*/

unsigned char I2CWrite(unsigned char I2C_DATA)
{

	unsigned char ndata;

	ndata=8;
	
	SDA_SetDigitalOutput();
	do{
      SCL_SetLow();
      if (I2C_DATA & 0x80) SDA_SetHigh();
      else SDA_SetLow();
      I2CIdle();
      SCL_SetHigh();
      I2C_DATA = I2C_DATA << 1;
      I2CIdle();
/*
      SCL_TRIS = OUTPUT;   //SCL_LAT = 0;
		if ( (I2C_DATA & 0x80) == 0x80) SDA_TRIS = INPUT; //SDA_LAT = 1;
		else SDA_TRIS = OUTPUT; //SDA_LAT = 0;
		I2CIdle();
		SCL_TRIS = INPUT;  //SCL_LAT = 1;
		I2C_DATA = I2C_DATA << 1;		
		I2CIdle();		
 */
	}while(--ndata);
	
   SCL_SetLow();
   SDA_SetLow();
//	SCL_TRIS = OUTPUT;   //SCL_LAT = 0;
//	SDA_TRIS = OUTPUT;   //SDA_LAT = 0;
	I2CIdle();

	ndata=0;
	
   SDA_SetDigitalInput();
   I2CIdle();
   SCL_SetHigh();
   I2CIdle();
   if (SDA_GetValue()) ndata = 1;
   else ndata = 0;
   SCL_SetLow();
   I2CIdle();
   SDA_SetDigitalOutput();
   
/* SDA_TRIS = INPUT;
	I2CIdle();
	SCL_TRIS = INPUT;    //SCL_LAT = 1;
	I2CIdle();
	if (SDA_PORT==1) ndata=1;
	SCL_TRIS = OUTPUT;   //SCL_LAT = 0;
   I2CIdle();
	SDA_TRIS = OUTPUT;
//	SDA_LAT = 0;
	*/
	return ndata;
}

unsigned char I2CRead(uint8_t ack){

	unsigned char ndata;
  unsigned char I2C_DATA;

	ndata=8;
	I2C_DATA=0x00;
	
   SDA_SetDigitalInput();
   I2CIdle();
   do{
      SCL_SetLow();
      I2C_DATA = I2C_DATA << 1;
      I2CIdle();
      SCL_SetHigh();
      if (SDA_GetValue()) I2C_DATA = (I2C_DATA |0x01);
      I2CIdle();
   }while (--ndata);
   SCL_SetLow();
   SDA_SetDigitalOutput();
   
   if (ack) I2CAck();
   else I2CNotAck();
   
   
/*	SDA_TRIS = INPUT;
	I2CIdle();
	
	do{
 	  SCL_TRIS = OUTPUT;    //SCL_LAT = 0;
 	  I2C_DATA = I2C_DATA << 1;
		I2CIdle();
		SCL_TRIS = INPUT;    //SCL_LAT = 1;
    if (SDA_PORT==1) I2C_DATA = (I2C_DATA | 0x01) ;
		I2CIdle();    
	}while(--ndata);
	
	SCL_TRIS = OUTPUT;   //SCL_LAT = 0;
	SDA_TRIS = OUTPUT;
//	SDA_LAT = 0;
*/		
	return I2C_DATA;
}

void I2CAck(void){

   I2CIdle();
   SCL_SetLow();
   SDA_SetLow();
   I2CIdle();
   SCL_SetHigh();
   I2CIdle();
   SCL_SetLow();
   I2CIdle();
   
/*	I2CIdle();
   SCL_TRIS = OUTPUT;
   SDA_TRIS = OUTPUT;
   I2CIdle();
   SCL_TRIS = INPUT;
   I2CIdle();
   SCL_TRIS = OUTPUT;
   I2CIdle();
*/
/*
	I2CIdle();
	SCL_LAT = 0;
	SDA_LAT = 0;
	I2CIdle();
	SCL_LAT = 1;
	I2CIdle();
	SCL_LAT = 0;
	I2CIdle();
*/	
}

void I2CNotAck(void){

   I2CIdle();
   SCL_SetLow();
   SDA_SetHigh();
   I2CIdle();
   SCL_SetHigh();
   I2CIdle();
   SCL_SetLow();
   I2CIdle();

/*	I2CIdle();
   SCL_TRIS = OUTPUT;
   SDA_TRIS = INPUT;
   I2CIdle();
   SCL_TRIS = INPUT;
   I2CIdle();
   SCL_TRIS = OUTPUT;
   I2CIdle();
   SDA_TRIS = OUTPUT;
   I2CIdle();
*/   
/*   
   I2CIdle();	
	SCL_LAT = 0;
	SDA_LAT = 1;
	I2CIdle();
	SCL_LAT = 1;
	I2CIdle();
	SCL_LAT = 0;
	I2CIdle();	
	SDA_LAT = 0;
*/	
}

void I2CStop(void){

   SDA_SetLow();
   I2CIdle();
   SCL_SetLow();
   I2CIdle();
   SCL_SetHigh();
   I2CIdle();
   SDA_SetHigh();
   I2CIdle();
   
/*   SDA_TRIS = OUTPUT;
   I2CIdle();
   SCL_TRIS = OUTPUT;
   I2CIdle();
   SCL_TRIS = INPUT;
   I2CIdle();
   SDA_TRIS = INPUT;
   I2CIdle();
 */
/*
  SCL_TRIS = OUTPUT;
  SDA_TRIS = OUTPUT;

	SDA_LAT = 0;
	I2CIdle(); 
 	SCL_LAT = 0;
	I2CIdle();
	SCL_LAT = 1;
	I2CIdle();
	SDA_LAT = 1;	
	I2CIdle();	
 */
}


void I2CStart(void){

   SDA_SetDigitalOutput();
   SDA_SetHigh();
   I2CIdle();
   SCL_SetHigh();
   I2CIdle();
   SDA_SetLow();
   I2CIdle();
   SCL_SetLow();
   I2CIdle();
   
/*   SDA_TRIS = INPUT;
   I2CIdle();
   SCL_TRIS = INPUT;
   I2CIdle();
   SDA_TRIS = OUTPUT;
   I2CIdle();
   SCL_TRIS = OUTPUT;
   I2CIdle();
*/   
/*   
   SCL_TRIS = OUTPUT;
   SDA_TRIS = OUTPUT;
  
	SDA_LAT = 1;
	I2CIdle();
	SCL_LAT = 1;
	I2CIdle();
	SDA_LAT = 0;
	I2CIdle();
	SCL_LAT = 0;
	I2CIdle();		
 */
}
