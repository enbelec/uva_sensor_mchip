
#include "includes.h"
#include "mcc_generated_files/pin_manager.h"

// pone potencia de los sensores a medir
void ponePower(void){
   uint8_t f, g;
   
   for (f = 0; f< MAX_PLACAS; f++){ //borra todos los power
      salidaSpi[f].power.byte_pow = 0;
   }
   for (f = 0 ; f< MAX_SENS; f++){
      if (arrSens[f] == '1'){
         g = f / MAX_PLACAS; //g = numero de placa
         switch (f % MAX_PLACAS){
            case 0:
               salidaSpi[g].power.bits_pow.pow8 = 1;
               break;
            case 1:
               salidaSpi[g].power.bits_pow.pow7 = 1;
               break;
            case 2:
               salidaSpi[g].power.bits_pow.pow6 = 1;
               break;
            case 3:
               salidaSpi[g].power.bits_pow.pow5 = 1;
               break;
            case 4:
               salidaSpi[g].power.bits_pow.pow4 = 1;
               break;
            case 5:
               salidaSpi[g].power.bits_pow.pow3 = 1;
               break;
            case 6:
               salidaSpi[g].power.bits_pow.pow2 = 1;
               break;
            case 7:
               salidaSpi[g].power.bits_pow.pow1 = 1;
               break;
         }
      }
   }
   
}

// pone leds de los sensores a medir
void poneLeds(bool FledRojos){
   uint8_t f, g, h;
   
   for (f = 0; f< MAX_PLACAS; f++){ //borralos led
      salidaSpi[f].leds1_4.byte1_4 = 0;
      salidaSpi[f].leds5_8.byte5_8 = 0;
   }
   for (f = 0 ; f< MAX_SENS; f++){
      if (arrSens[f] == '1'){  //pone leds de los que van a medir
         g = f / MAX_PLACAS; //g = numero de placa
         switch (f % MAX_PLACAS){
            case 0:
               salidaSpi[g].leds1_4.bits1_4.led1_rojo = 1;
               break;
            case 1:
               salidaSpi[g].leds1_4.bits1_4.led2_rojo = 1;
               break;
            case 2:
               salidaSpi[g].leds1_4.bits1_4.led3_rojo = 1;
               break;
            case 3:
               salidaSpi[g].leds1_4.bits1_4.led4_rojo = 1;
               break;
            case 4:
               salidaSpi[g].leds5_8.bits5_8.led5_rojo = 1;
               break;
            case 5:
               salidaSpi[g].leds5_8.bits5_8.led6_rojo = 1;
               break;
            case 6:
               salidaSpi[g].leds5_8.bits5_8.led7_rojo = 1;
               break;
            case 7:
               salidaSpi[g].leds5_8.bits5_8.led8_rojo = 1;
               break;
         }
      }
   }
   
   //pone el numero de sensor que mide
   g = numSens / MAX_PLACAS; //en G esta el numero de placa que mide
   h = numSens % MAX_PLACAS; // en h esta el numero de sensor que mide en la placa
   if (FledRojos){
      switch (h){
         case 0:
            salidaSpi[g].leds1_4.bits1_4.led1_verde = 1;
            break;
         case 1:
            salidaSpi[g].leds1_4.bits1_4.led2_verde = 1;
            break;
         case 2:
            salidaSpi[g].leds1_4.bits1_4.led3_verde = 1;
            break;
         case 3:
            salidaSpi[g].leds1_4.bits1_4.led4_verde = 1;
            break;
         case 4:
            salidaSpi[g].leds5_8.bits5_8.led5_verde = 1;
            break;
         case 5:
            salidaSpi[g].leds5_8.bits5_8.led6_verde = 1;
            break;
         case 6:
            salidaSpi[g].leds5_8.bits5_8.led7_verde = 1;
            break;
         case 7:
            salidaSpi[g].leds5_8.bits5_8.led8_verde = 1;
            break;
      }
   }
}

void poneLedCpu(void){
   //pone los led segun el estado de la maquina de estados
   //reposo led verde fijo
   //mide led verde parpadea 1 seg
   //vacia led verde parpadea 100ms
   //error led rojo parpadea 1 seg.
   static uint8_t ct1;
   
   ESTADOS_PRIN est;
   est = leeEstadoMaquina();
   
   switch (est){ //led verde
      case EST_REPOSO:
         if (veTiempo.F100ms){
            if (++ct1 > 20) ct1 = 0;
         }
         if (ct1 == 0)  LED1_SetLow();
         else LED1_SetHigh();
         break;
      case EST_MEDIR:
      case EST_MEDIR_1:
      case EST_MEDIR_2:
      case EST_MEDIR_3:
         if (veTiempo.F100ms_5) LED1_Toggle();
         break;
      case EST_VACIAR:
      case EST_VACIAR_1:
      case EST_VACIAR_2:
      case EST_VACIAR_3:
         if (veTiempo.F100ms) LED1_Toggle();
         break;
      default:
         LED1_SetLow();
   }

#ifndef _TEST   //si estamos en test el led rojo es para testear
   switch (error){
      case 0:
         LED2_SetLow();
         break;
      case 1:
         if (veTiempo.F1seg) LED2_Toggle();
         break;
      case 2:
         if (veTiempo.F100ms_5) LED2_Toggle();
         break;
      case 3:
         if (veTiempo.F100ms) LED2_Toggle();
         break;
      default:
         LED2_SetHigh();
         break;
   }
#endif
   
}

// pone el multplexor enel sensor que le llega
void poneMpx(int8_t sensor){
   
   uint8_t f,g,h;
   
   g = sensor / MAX_PLACAS; //coge el num de placa
   h = sensor % MAX_PLACAS; //num sensor en placa
   
   for (f = 0; f < MAX_PLACAS; f++){
      salidaSpi[f].mpx.mpxu.bits.mpx = 7;
      salidaSpi[f].mpx.mpxu.bits.mpx_enh = 1;
      salidaSpi[f].mpx.mpxu.bits.mpxrx = 0;
   }
   salidaSpi[g].mpx.mpxu.bits.mpx = ~h;
   salidaSpi[g].mpx.mpxu.bits.mpx_enh = 0; //activa el mpx
   salidaSpi[g].mpx.mpxu.bits.mpxrx = 1; //deja pasar datos de Rx
   
   mandaSpi();
}
