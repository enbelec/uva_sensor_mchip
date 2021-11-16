
#include "mandaSpi.h"
#include "variables.h"
#include "mcc_generated_files/spi1.h"
#include "mcc_generated_files/pin_manager.h"


SALIDA_SPI salidaSpi[MAX_PLACAS];


//***********************************
// manda SPI manda los datos que stan en el array salidaSpi, 
// tarda 33us por array
//***********************************

void mandaSpi(void){
   
   uint8_t f;
   uint8_t cont_placas; 
   
   
   cont_placas = numplacas;
   
   do {
      cont_placas --;
      SPI1_Exchange8bit(salidaSpi[cont_placas].ev9_16.byte_ev9_16);
      SPI1_Exchange8bit(salidaSpi[cont_placas].ev1_8.byte_ev1_8);
      SPI1_Exchange8bit(salidaSpi[cont_placas].power.byte_pow);
      SPI1_Exchange8bit(salidaSpi[cont_placas].mpx.mpxu.byteMpx);
      SPI1_Exchange8bit(salidaSpi[cont_placas].leds5_8.byte5_8);
      SPI1_Exchange8bit(salidaSpi[cont_placas].leds1_4.byte1_4);
   }while (cont_placas > 0);
   
   while (SPI1STATbits.SRMPT == false); //espera
   SS1_SetHigh();
   for (f = 0;f < 5; f++){
     Nop();
   }
   SS1_SetLow();
   
}

void inicializaSpi(void){

   uint8_t f;
   
   for (f = 0; f < MAX_PLACAS; f++){
      salidaSpi[f].ev1_8.byte_ev1_8 = 0;
      salidaSpi[f].ev9_16.byte_ev9_16 =0;
      salidaSpi[f].leds1_4.byte1_4 = 0;
      salidaSpi[f].leds5_8.byte5_8 = 0;
      salidaSpi[f].mpx.mpxu.byteMpx = 0;
      salidaSpi[f].power.byte_pow = 0;
   }
   mandaSpi();
   
}