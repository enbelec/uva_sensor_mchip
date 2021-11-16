#include "includes.h"
#include "mcc_generated_files/uart1.h"
#include "EjecSerieSens.h"
#include <string.h>
    
#define NUM_DATOS_SERIE_SENS 100

char bufferInSens[NUM_DATOS_SERIE_SENS]; //buffer entrada
char bufferProcSens[NUM_DATOS_SERIE_SENS]; //buffer proceso
char bufferOutSens[NUM_DATOS_SERIE_SENS]; //buffer de salida

bool FrecepOkSens;
bool FtransmiteSens;
//bool FdatoRecibido;
uint8_t contBytesInSens;
   
//*********************** mira que entran daots serie
void InicializaSerieSens(void){
   
   FrecepOkSens = false;
   contBytesInSens = 0;
}

//******************************* entrada serie 
void EntradaSerieSens(void){
   
   uint8_t datoSerie;
   uint8_t f;
   
   if (UART1_IsRxReady()){
      datoSerie = UART1_Read();
      if (datoSerie == 0x0A){ //llega fin de carro, procesa comando
         bufferInSens[contBytesInSens] = datoSerie;
         bufferInSens[contBytesInSens +1] = NULL;
         if (bufferInSens[0] == NULL){
            for (f = 0 ;f < contBytesInSens ; f++){
               bufferInSens[f] = bufferInSens[f+1];
            }
            bufferInSens[f] = NULL; // pone nulo al final
         }
         bufferInSens[contBytesInSens +1] = NULL; //por si habia algo en el buffer
         strcpy(bufferProcSens, bufferInSens);
//         for (f = 0; f < contBytesInSens ; f++ ) {
//            bufferProcSens[f] = bufferInSens[f];
//         }
         FrecepOkSens = true;
         contBytesInSens = 0; //resetea puntero del buffer
      }
      else{ //edntran datos
         if (datoSerie != NULL){
            bufferInSens[contBytesInSens] = datoSerie;
            contBytesInSens ++;
            if (contBytesInSens > NUM_DATOS_SERIE_SENS - 1){ //se sale del buffer
               contBytesInSens = 0; //inicializa puntero
            }
            bufferInSens[contBytesInSens] = NULL;
         }
      }
   }
}

//********************** porcesa datos
void ProcesoSerieSens(void){
   
   uint8_t cont;
   
   if (FrecepOkSens){ //se ha recibido comunicacion
      switch (bufferProcSens[0]){
         case 'M': //modo funcionamiento
            poneRespuestaM(true);
            break;
         case 'O':   //oxigeno
             if (bufferProcSens[8] == 0x0D){ //solo manda oxigeno
                poneRespuestaVac(true); //si esta vaciando marca que ha llegado el dato
             }
             else{ //manda todo
                poneRespuestaM(true); //pone que ha recibido dato
             }
            break;
         case '%':   //oxigeno en %
            
            break;
         case 'T':   //Temperatura
            
            break;
         case 'P':   //presion
            
            break;
         case 'e':   //error
            break;
         case '#':   //info
             if (bufferProcSens[7] == 0x0D){ //devuelve revison soft
                 
             }
             else if(bufferProcSens[11] == 0x0D){ //devuelve numero serie
                 
             }
             else if (bufferProcSens[13] == 0x0D){ //devuelve dia de fabricacion
                 
             }
            break;
      }
      FrecepOkSens = false;
   }
   else{
      cont = 0;
   }
}

//**************************** salida serie
void salidaSerieSens(void){
   
   static bool FinitSens;
   static uint8_t contOutSens;
   
   if (FtransmiteSens){
      if (FinitSens == true){
         FinitSens = false;
         contOutSens = 0;
      }
      if (UART1_IsTxReady()){
         UART1_Write(bufferOutSens[contOutSens]);
         if (bufferOutSens[contOutSens] == 0x0A){ //fin de trama
            FtransmiteSens = false;
            contOutSens = 0;
         }
         else{
            contOutSens ++;
         }
      }
   }
   else{
      FinitSens = true;
   }
}

//*************************** MANDA COMANDO AL SENSOR
void mandaComASensor(SENS_COMS comando){
   
   switch (comando){
      case SENS_MODO_STREAM:
         bufferOutSens[0] = 'M';
         bufferOutSens[1] = ' ';
         bufferOutSens[2] = '0';
         bufferOutSens[3] = 0x0D;
         bufferOutSens[4] = 0x0A;
         FtransmiteSens = true;
         break;
      case SENS_MODO_POOL:
         bufferOutSens[0] = 'M';
         bufferOutSens[1] = ' ';
         bufferOutSens[2] = '1';
         bufferOutSens[3] = 0x0D;
         bufferOutSens[4] = 0x0A;
         FtransmiteSens = true;
         break;
      case SENS_MODO_OFF:
         bufferOutSens[0] = 'M';
         bufferOutSens[1] = ' ';
         bufferOutSens[2] = '2';
         bufferOutSens[3] = 0x0D;
         bufferOutSens[4] = 0x0A;
         FtransmiteSens = true;
         break;
      case SENS_MIDE_O2:
         bufferOutSens[0] = 'O';
         bufferOutSens[1] = 0x0D;
         bufferOutSens[2] = 0x0A;
         FtransmiteSens = true;
         break;
      case SENS_MIDE_TODO:
         bufferOutSens[0] = 'A';
         bufferOutSens[1] = 0x0D;
         bufferOutSens[2] = 0x0A;
         FtransmiteSens = true;
         break;
      case SENS_PIDE_INFO_DIA:
         bufferOutSens[0] = '#';
         bufferOutSens[1] = ' ';
         bufferOutSens[3] = '0';
         bufferOutSens[4] = 0x0D;
         bufferOutSens[5] = 0x0A;
         FtransmiteSens = true;
         break;
      case SENS_PIDE_INFO_NUM_SERIE:
         bufferOutSens[0] = '#';
         bufferOutSens[1] = ' ';
         bufferOutSens[2] = '1';
         bufferOutSens[3] = 0x0D;
         bufferOutSens[4] = 0x0A;
         FtransmiteSens = true;
         break;
      case SENS_PIDE_INFO_SOFT:
         bufferOutSens[0] = '#';
         bufferOutSens[1] = ' ';
         bufferOutSens[2] = '2';
         bufferOutSens[3] = 0x0D;
         bufferOutSens[4] = 0x0A;
         FtransmiteSens = true;
         break;
   }

}

//***************************
void vaciaBufferInSens(void){
   int f;
   
   contBytesInSens = 0; //pone puntero a 0
   
   for (f = 0; f< MAX_SENS - 1; f++){
      bufferInSens[f] = NULL;
   }
}


