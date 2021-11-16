
#include "includes.h"
#include "EjecSerieSens.h"
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/pin_manager.h"
#include <string.h>
#include <stdio.h>

DATOS_SENS datosSens[NUM_DATOS_SENS];
uint16_t puntDatos; //puntero de datos para guardarlo
uint8_t numSens; //numero de sensor que mide
uint8_t contTentreMedidas ; //contador de tiempo entre medidas
uint16_t contTMedicion; //contador total de la medicion
uint16_t contMinutos; //contador de minutos de medicion

uint8_t arrSens[MAX_SENS];
bool Fscaneo;
bool Fmidiendo;

bool FrespM;

void mide(void){
   
   char str[200];

   static uint16_t contSalida;

   
   //------ control tiempo medicion total --------
   // lo dejamos para que lo controle el PC
/*
   if (veTiempo.F1seg){
      if (++ contsegundos > 59){
         contsegundos = 0;
         contMinutos ++;
         if (contMinutos >= contTMedicion){ // se acabo
            cambiaEstado(EST_FIN_MEDIR);
            return;
         }
      }
   }
*/   
   // -------- control tiempo entre muestras ------------
   
   if (veTiempo.F1seg){  //espera a que pase el tiempo de medir
      if (-- contTentreMedidas == 0){
         contTentreMedidas = tEntreMedidas;
         Fscaneo = true;
         numSens = 0;
      }
   }
   
   //----------------------------------------
   if (Fscaneo){
      if (Fmidiendo){ //espera resultado sensor
         if (FrespM && !Ftransmite){ //ha recibida del sensor y ha terminado la transmision anterior al PC
            FrespM = false;
            sprintf(str, "D %03d ", numSens + 1); //internamente trabaja de 0 a 63 pero manda de 1 a 64
            bufferProcSens[6] = 0x2c; //pone , en vez de .
            bufferProcSens[14] = 0x2c;
            bufferProcSens[29] = 0x2c;
            strcat(str, bufferProcSens);
/*
            // esto es para guardar datos dentro de la cpu
            //de momento no se usa
 
            strcpy(datosSens[puntDatos].todo, str);
            puntDatos ++;
            if (puntDatos > NUM_DATOS_SENS - 1){
               puntDatos = 0;
            }
*/
            strcpy (bufferOut, str);
            Ftransmite = true; //manda sacar datos
            Fmidiendo = false;
            numSens ++;
         }
         else{ //no llega, cuenta para salir con error
            if (veTiempo.F10ms){
               if (++contSalida > T_ESPERA_COMS){ //espera 1 segundo
                  Fmidiendo = false;
                  sprintf(bufferOut, "E 02 S %03d\r\n", numSens);
                  arrSens[numSens] = '0';
                  poneLeds(1);
                  mandaSpi();
                  Ftransmite = true;
                  numSens ++;
                  error = 2; //pone error 2 alguno ha dejado de funcionar
               }
            }
         }
      }
      else{ //mira siguiente a medir
         if (veTiempo.F10ms == 0) return;//mira un sensor cada 10 ms para no atragantar las comunicaciones
         while(arrSens[numSens] == '0'){
            numSens ++;
            if (numSens > MAX_SENS - 1)break; //si ha mirado todos sale
         }
         if (numSens > MAX_SENS - 1){
            numSens = 0;
            Fscaneo = false; //se acabo el medir
            strcpy (bufferOut, "S\r\n"); //pone fin de sacneo
            Ftransmite = true; //manda sacar datos
         }
         else{  //manda medir
            poneLeds(1);
            poneMpx(numSens); //aqui manda SPI
//            mandaSpi();
            mandaComASensor(SENS_MIDE_TODO);
            Fmidiendo = true;
            contSalida = 0;
         }
      }
   }
   
}

//*******************************
void finMedir (void){
   // quita la alimentacion a los sensores
   uint8_t f;
   
   for (f = 0 ; f < MAX_PLACAS ; f++){  //apaga todo
      salidaSpi[f].power.byte_pow = 0;
      salidaSpi[f].ev1_8.byte_ev1_8 = 0;
      salidaSpi[f].ev9_16.byte_ev9_16 = 0;
      salidaSpi[f].leds1_4.byte1_4 = 0;
      salidaSpi[f].leds5_8.byte5_8 = 0;
   }
   mandaSpi();
   numSens = 0;

}
//***************************

void inicializaMedir(void){
   
   uint8_t f;
   
   puntDatos = 0;
   numSens = 0;
   contTentreMedidas = tEntreMedidas;
   contTMedicion = 0;
   for (f =0 ; f<100 ; f++){
      strcpy(datosSens[f].todo, "                            ");
   }
   ponePower();
   poneLeds(0);
   mandaSpi();
   
   FrespM = false;
}

//***************************************
bool escaneando (void){
   return Fscaneo;
}

//***************************************
bool poneModoPool(void){
   
   static bool FesperaResp;
   static int contEspera;
   static int vecesRep; //veces deintento de comunicacion
   
#ifdef _TEST
   LED2_Toggle();
#endif
   
   if (FesperaResp){ //espera a que contesten
      if (FrespM){
         FrespM = false;
         FesperaResp = false;
         vecesRep = 0;
         numSens++;
      }
      else{ //no responde cuenta de seguridad
         if (veTiempo.F10ms){
            if (++contEspera > T_ESPERA_COMS){ //espera 1 segundo
               if (++vecesRep > 2){
                  arrSens[numSens] = '0';
                  sprintf(bufferOut, "E 01 S %03d\r\n", numSens);
                  Ftransmite = true;
                  vecesRep = 0;
                  numSens ++;
               }
               FesperaResp = false;
               FrespM = false;
               error = 1; //pone error 1
            }
         }
      }
   }
   else{ //manda pool
      if (Ftransmite) return false; //si esta transmitiendo sale
      while(arrSens[numSens] != '1'){
         vecesRep = 0;
         numSens++;
         if (numSens > MAX_SENS -1) break;
      }
      if (numSens > MAX_SENS -1){
         numSens = 0;
         poneLeds(1);
         mandaSpi();
         error = 0; //quita errores
         return true; //pone que ha acabado
      }
      poneLeds(1);
      poneMpx(numSens);
      vaciaBufferInSens();  //vacia buffer para coger solo la respuesta
      mandaComASensor(SENS_MODO_POOL);
      FesperaResp = 1;
      contEspera = 0;
   }
   return false; //no ha terminado
}

//***************************************
void poneRespuestaM(bool resp){
   FrespM = resp;
}

//***************************************
void poneContadorTiempoTotal (uint16_t tiempo){
   contTMedicion = tiempo;
}