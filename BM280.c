
#include "includes.h"
#include <stdio.h>

BM280_CALIBRACION Bm280Calibracion;

uint32_t presionBruto, tempBruto, humedadBruto;

bool Bm280Reset(){
   uint8_t temp, cont;
   uint16_t tempint;
   
   cont =0;
   do{
      I2CStart();
      temp = I2CWrite(BM280_ADD_WR);
      if (temp) I2CStop();
      for (tempint = 0; tempint < 25000; tempint ++){}; //espera 5ms
      cont++;
      if (cont > 10){
         return false; //no responde el BM280
      }
   }while (temp);
   I2CWrite(BM280_ADD_RESET);
   I2CWrite(BM280_VALOR_RESET);
   I2CStop();
   
   return true; //retorna que esta todo ok
  
}

void Bm280LeeCalibracion(void){
   
   uint8_t t1, t2;
      
   I2CStart();
   I2CWrite(BM280_ADD_WR);
   I2CWrite(BM280_ADD_CAL1);
   I2CStart();
   I2CWrite(BM280_ADD_RD);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   Bm280Calibracion.dig_T1 = t1 + (t2 << 8);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   Bm280Calibracion.dig_T2 = t1 + (t2 << 8);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   Bm280Calibracion.dig_T3 = t1 + (t2 << 8);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   Bm280Calibracion.dig_P1 = t1 + (t2 << 8);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   Bm280Calibracion.dig_P2 = t1 + (t2 << 8);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   Bm280Calibracion.dig_P3 = t1 + (t2 << 8);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   Bm280Calibracion.dig_P4 = t1 + (t2 << 8);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   Bm280Calibracion.dig_P5 = t1 + (t2 << 8);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   Bm280Calibracion.dig_P6 = t1 + (t2 << 8);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   Bm280Calibracion.dig_P7 = t1 + (t2 << 8);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   Bm280Calibracion.dig_P8 = t1 + (t2 << 8);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   Bm280Calibracion.dig_P9 = t1 + (t2 << 8);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   Bm280Calibracion.dig_H1 = t2;
   I2CStop();

   I2CStart();
   I2CWrite(BM280_ADD_WR);
   I2CWrite(BM280_ADD_CAL2);
   I2CStart();
   I2CWrite(BM280_ADD_RD);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   Bm280Calibracion.dig_H2 = t1 + (t2 << 8);
   t1 = I2CRead(1);
   Bm280Calibracion.dig_H3 = t1;
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   Bm280Calibracion.dig_H4 = t1 + (t2 << 8);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   Bm280Calibracion.dig_H5 = t1 + (t2 << 8);
   I2CStop();

}
  
uint8_t BM280LeeStatus(void){
   
   uint8_t f;
   
   I2CStart();
   I2CWrite(BM280_ADD_WR);
   I2CWrite(BM280_ADD_STATUS);
   I2CStart();
   I2CWrite(BM280_ADD_RD);
   f = I2CRead(1);
   I2CStop();
   
   return f;
}
   
void Bm280LeeSensores(int32_t *temp, uint32_t *Presion, uint32_t *humedad){
   
   uint8_t t1, t2, t3;
   
   I2CStart();
   I2CWrite(BM280_ADD_WR);
   I2CWrite(BM280_ADD_SENS_PRES);
   I2CStart();
   I2CWrite(BM280_ADD_RD);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   t3 = I2CRead(1);
   presionBruto = t3 + (t2 << 8) + (t1 << 16);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   t3 = I2CRead(1);
   tempBruto = t3 + (t2 << 8) + (t1 << 16);
   t1 = I2CRead(1);
   t2 = I2CRead(1);
   humedadBruto = t2 + (t1 << 8);
   I2CStop();
   
   *temp = tempBruto;
   *Presion = presionBruto;
   *humedad = humedadBruto;
   
   
}
