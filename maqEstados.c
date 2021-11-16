
#include "includes.h"
#include "maqEstados.h"
#include <stdio.h>

ESTADOS_PRIN estPrin;
ESTADOS_PRIN estSolicitado;
int8_t contTiempo;

void maqEstados (void){
   
   uint8_t f,g;
   
   switch (estPrin){
      case EST_INIT:
         estPrin = EST_REPOSO;
         break;
      case EST_REPOSO:
         contTiempo = 0;
         if (estSolicitado == EST_MEDIR) estPrin = EST_MEDIR;
         if (estSolicitado == EST_VACIAR) estPrin = EST_VACIAR;
         if (estSolicitado == EST_FIN) error = 0;
         estSolicitado = EST_REPOSO;
         break;
      case EST_MEDIR: //alimenta sensores
         if (contTiempo == 0){
            ponePower(); //prepara medicion
            mandaSpi();
         }
         if (veTiempo.F100ms){
            if (contTiempo ++ == 10){ //espera 1 segundos
               estPrin = EST_MEDIR_1;
               vaciaBufferInSens(); //vacia buffer de entrada
               contTiempo = 0;
            }
         }
         break;
      case EST_MEDIR_1: //los pone en modo pool
         if (poneModoPool() == true){ // ha terminado
            estPrin =EST_MEDIR_2;
            poneContadorTiempoTotal(0); //resetea contador de tiempo total de medicion
         }
         break;
      case EST_MEDIR_2: //pasa 2 veces para asegurarse
         if (poneModoPool() == true){ // ha terminado
            estPrin =EST_MEDIR_3;
            sprintf(bufferOut, "M 1\r\n"); //INICIO MEDIR
            Ftransmite = true;
            poneContadorTiempoTotal(0); //resetea contador de tiempo total de medicion
         }
         break;
      case EST_MEDIR_3:
         if (estSolicitado == EST_FIN || estSolicitado == EST_FIN_MEDIR){
            estPrin = EST_FIN_MEDIR;
            break;
         }
         mide();
         break;
      case EST_FIN_MEDIR:
         finMedir();
         sprintf(bufferOut, "F \r\n");
         Ftransmite = true;
         estPrin = EST_FIN;
         break;
      case EST_VACIAR:
         if (contTiempo == 0){
            ponePower(); //prepara medicion
            mandaSpi();
         }
         if (veTiempo.F100ms){
            if (contTiempo ++ == 10){ //espera 1 segundos
               estPrin = EST_VACIAR_1;
               vaciaBufferInSens(); //vacia buffe de entrada
               contTiempo = 0;
            }
         }
         break;
      case EST_VACIAR_1:
         if (poneModoPool() == true){ // ha terminado
            estPrin =EST_VACIAR_2;
            poneContadorTiempoTotal(0); //resetea contador de tiempo total de medicion
         }
         break;
      case EST_VACIAR_2:
         if (poneModoPool() == true){ // ha terminado
            g = 0;
            for (f = 0; f < MAX_SENS; f++){
               if (arrSens[f] == '1') g =1;
            }
            if (g == 1){
               estPrin =EST_VACIAR_3;
               sprintf(bufferOut, "W 1\r\n"); //INICIO VACIADO
               Ftransmite = true;
               poneContadorTiempoTotal(0); //resetea contador de tiempo total de medicion
            }
            else{ //si no hay nadapara medir da error
               estPrin =EST_FIN;
               finVaciar();
               sprintf(bufferOut, "W 3\r\n"); //error VACIADO
               Ftransmite = true;
               poneContadorTiempoTotal(0); //resetea contador de tiempo total de medicion
            
            }
         }
         break;
      case EST_VACIAR_3:
         if (estSolicitado == EST_FIN || estSolicitado == EST_FIN_VACIAR){
            estPrin = EST_FIN_VACIAR;
            break;
         }
         vaciar(); //va a la rutina de vaciar
         break;
      case EST_FIN_VACIAR:
         if (veTiempo.F100ms){
            finVaciar();
            sprintf(bufferOut, "W 2\r\n"); //VACIADO OK
            Ftransmite = true;
            estPrin = EST_FIN;
         }
         break;
      case EST_FIN:
         estPrin = EST_REPOSO;
         break;
   }
   
}

//***********************
void cambiaEstado(ESTADOS_PRIN estado){
   estSolicitado = estado; //pone el estado al que cambiar
}

ESTADOS_PRIN leeEstadoMaquina (void){
   
   return estPrin;
}