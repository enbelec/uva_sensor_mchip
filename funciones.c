
#include "includes.h"

uint8_t  EscribeByteE2prom( uint8_t direccion, uint8_t dato){
   
   uint8_t temp;
   uint16_t tempint;
   
   do{
      I2CStart();
      temp = I2CWrite(E2P_ADDR_WR);
      if (temp) I2CStop();
      for (tempint = 0; tempint < 25000; tempint ++){}; //espera 5ms
   }while (temp);
   I2CWrite(direccion);
   I2CWrite(dato);
   I2CStop();
   
   return 0;
}

uint8_t LeeByteE2prom(uint8_t direccion){
   
   uint8_t temp;
   I2CStart();
   temp = I2CWrite(E2P_ADDR_WR);
   I2CWrite(direccion);
   I2CStop();
   I2CStart();
   temp = I2CWrite(E2P_ADDR_RD);
   temp = I2CRead(I2C_NO_ACK);
   I2CStop();
   
   return temp;
}

uint8_t  EscribeIntE2prom( uint8_t direccion, uint16_t dato){
   
   INT_BYTE temp;
   
   temp.allByte = dato;
   
   EscribeByteE2prom(direccion , temp.uByte.Highbyte);
   EscribeByteE2prom(direccion + 1, temp.uByte.LowByte);
   
/*   
   do{
      I2CStart();
      temp.uByte.LowByte = I2CWrite(E2P_ADDR_WR);
      if (temp.uByte.LowByte) I2CStop();
   }while (temp.uByte.LowByte);
   if (temp.uByte.LowByte) return 1;
   I2CWrite(direccion);
   temp.allByte = dato;
   I2CWrite(temp.uByte.Highbyte);
   I2CWrite(temp.uByte.LowByte);
   I2CStop();
*/   
   return 0;
}

uint16_t LeeIntE2prom(uint8_t direccion){
   
   INT_BYTE  temp;
   
   I2CStart();
   I2CWrite(E2P_ADDR_WR);
   I2CWrite(direccion) ;
   I2CStop();
   I2CStart();
   I2CWrite(E2P_ADDR_RD);
   temp.uByte.Highbyte = I2CRead(I2C_ACK);
   temp.uByte.LowByte = I2CRead(I2C_NO_ACK);
   I2CStop();
   
   return temp.allByte;
}

//**************************** hex a dec
//conversion de 16bits, devuelve solo 4 digitos, hasta el 9999
INT_BYTE pasaHexaDec(int datoHex){
BYTESTR alto, bajo;
uint8_t tmp, tmp2;
INT_BYTE tmpResultado, tmpr2;
	
	tmpResultado.allByte = datoHex;
	alto.Byte = 0;
	bajo.Byte= 0;
	tmp = 16;
   tmpr2.allByte = 0;
   
	do{
      tmpr2.uByte.LowByte += 0x03;
      if (!(tmpr2.uByte.LowByte & 0x08)) tmpr2.uByte.LowByte -= 0x03;
      tmpr2.uByte.LowByte += 0x30;
      if (!(tmpr2.uByte.LowByte & 0x80)) tmpr2.uByte.LowByte -= 0x30;
      tmpr2.uByte.Highbyte += 0x03;
      if (!(tmpr2.uByte.Highbyte & 0x08)) tmpr2.uByte.Highbyte -= 0x03;
      tmpr2.uByte.Highbyte += 0x30;
      if (!(tmpr2.uByte.Highbyte & 0x80)) tmpr2.uByte.Highbyte -= 0x30;
      
      if (tmpResultado.allByte & 0x8000) tmp2 = 1;
      else tmp2 = 0;
      tmpResultado.allByte = tmpResultado.allByte << 1;
      tmpr2.allByte = tmpr2.allByte << 1;
      if (tmp2) tmpr2.allByte |= 0x0001;
      
/*		bajo.Byte += (uint8_t)0x03;
		if (!bajo.Bits.BIT3) bajo.Byte -= (uint8_t) 0x03;
		bajo.Byte += (uint8_t)0x30;
		if (!bajo.Bits.BIT7) bajo.Byte -= (uint8_t) 0x30;
		alto.Byte += (uint8_t)0x03;
		if (!alto.Bits.BIT3) alto.Byte -= (uint8_t) 0x03;
		alto.Byte += (uint8_t)0x30;
		if (!alto.Bits.BIT7) alto.Byte -= (uint8_t) 0x30;
		asm CLC;
		asm ROL tmpResultado.uByte.LowByte;		
		asm ROL tmpResultado.uByte.HighByte;
		asm ROL bajo.Byte;		
		asm ROL alto.Byte;
 */
	}while(--tmp);
//	tmpResultado.uByte.HighByte = alto.Byte;
//	tmpResultado.uByte.LowByte = bajo.Byte;
	return(tmpr2);
}
//************************ bin a hex *****************
//entra u nnumero en binario ysale en bcd
uint8_t pasaBinaHex(uint8_t entrada){
uint8_t temp;

	temp = entrada >> 4; //deja solo la parte alta
	temp = temp * 10;
	temp = temp + (entrada & 0x0f);
	return(temp);	
		
}


