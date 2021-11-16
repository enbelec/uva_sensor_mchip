
#include "includes.h"
#include "mcc_generated_files/uart2.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_DATOS_SERIE 200

char bufferIn[NUM_DATOS_SERIE]; //buffer entrada
char bufferProc[NUM_DATOS_SERIE]; //buffer proceso
char bufferOut[NUM_DATOS_SERIE]; //buffer de salida

bool FrecepOk;
bool Ftransmite;
uint8_t contBytesIn;


//*********************** mira que entran daots serie
void InicializaSeriePC(void){
   
   FrecepOk = false;
   contBytesIn = 0;
}

//******************************* entrada serie 
void EntradaSeriePC(void){
   
   uint8_t datoSerie;
   uint8_t f;
   
   if (UART2_IsRxReady()){
      datoSerie = UART2_Read();
      if (datoSerie == 0x0A){ //llega fin de carro, procesa comando
         for (f = 0; f < contBytesIn ; f++ ) {
            bufferProc[f] = bufferIn[f];
         }
         FrecepOk = true;
         bufferProc[contBytesIn] = 0x0D; //lo pone por si acaso no ha llegado el suyo
         contBytesIn = 0; //resetea puntero del buffer
      }
      else{ //edntran datos
         bufferIn[contBytesIn] = datoSerie;
         contBytesIn ++;
         if (contBytesIn > NUM_DATOS_SERIE - 1){ //se sale del buffer
            contBytesIn = 0; //inicializa puntero
         }
      }
   }
}

//********************** porcesa datos
void ProcesoSeriePC(void){
   
   uint8_t cont, dat, f;
   uint16_t  dat2;
   char str[30];
   
   if (FrecepOk){ //se ha recibido comunicacion
      switch (bufferProc[0]){
         case 'L':
//            bufferOut[0] = 'L';
//            bufferOut[1] = 0x0D;
//            bufferOut[2] = 0x0A;
            sprintf(bufferOut,"L\r\n");
            Ftransmite = true;
            break;
         case 'O':   //ok
            break;
         case 'N':   //numero de sensores
            dat = (bufferProc[2] - '0') * 2; //resta del 0 que viene en ascii
            EscribeByteE2prom(E2P_NUM_PLACAS,dat); //llega el numero de cajas, cada caja tiene 2 placas
            EscribeByteE2prom(E2P_NUM_SENSORES, dat * 8);
            numplacas = dat;
            numSensores = dat * 8;
            sprintf(bufferOut,"OK\r\n");
            Ftransmite = true;
            break;
         case 'T':   //tiempo de medida
            dat = (bufferProc[2] - '0') * 10;
            dat = dat + (bufferProc[3] - '0');
            EscribeByteE2prom(E2P_T_ENTRE_MEDIDAS, dat);
            tEntreMedidas = dat;
            dat2 = ((bufferProc[7] - '0') * 1000);
            dat2 = dat2 + ((bufferProc[8] - '0') * 100);
            dat2 = dat2 + ((bufferProc[9] - '0') * 10);
            dat2 = dat2 + (bufferProc[10] -'0');
            EscribeIntE2prom(E2P_T_MEDICION, dat2);
            tMedicion = dat2;
            sprintf(bufferOut,"OK\r\n");
            Ftransmite = true;
            break;
         case 'V':   //vacia
            cambiaEstado(EST_VACIAR);
            sprintf(bufferOut,"OK\r\n");
            Ftransmite = true;
            break;
         case 'M':   //mide
            cambiaEstado(EST_MEDIR);
            sprintf(bufferOut,"OK\r\n");
            Ftransmite = true;
            break;
         case 'F':   //fin de medir
            cambiaEstado(EST_FIN);
            sprintf(bufferOut,"OK\r\n");
            Ftransmite = true;
            break;
         case 'A':  //array de sensores
            for (f = 0 ; f< MAX_SENS; f++){
               if (bufferProc[f+2] == 0x0D){
                  break; //si esta el retorno de carro sale
               }
               arrSens[f] = bufferProc[f+2];
            }
            poneLeds(0);
            sprintf(bufferOut,"OK\r\n");
            Ftransmite = true;
            break;
         case 'K': //limite de oxigeno 
            str[0] = bufferProc[2];
            str[1] = bufferProc[3];
            str[2] = bufferProc[4];
            str[3] = bufferProc[5];
            str[4] = bufferProc[7];
            str[5] = NULL;
            limiteO2 = atoi(str);
            sprintf(bufferOut,"OK\r\n");
            Ftransmite = true;
            break;
      }
      FrecepOk = false;
   }
   else{
      cont = 0;
   }
   
}

//**************************** salida serie
void salidaSeriePC(void){
   
   static bool Finit;
   static uint8_t contOut;
   
   if (Ftransmite){
      if (Finit == true){
         Finit = false;
         contOut = 0;
      }
      if (UART2_IsTxReady()){
         UART2_Write(bufferOut[contOut]);
         if (bufferOut[contOut] == 0x0A){ //fin de trama
            Ftransmite = false;
            contOut = 0;
         }
         else{
            contOut ++;
         }
      }
   }
   else{
      Finit = true;
   }
   
}
