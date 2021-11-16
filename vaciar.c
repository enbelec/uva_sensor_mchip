
#include "includes.h"
#include "EjecSerieSens.h"
#include <stdio.h>

EST_VAC estVaciar;
CIERRES arrCierres[MAX_SENS];

uint8_t numSensVac; //numero de vaciado de sensores
uint16_t contEspera; //contador espera contestacion
bool FrecVaciar;
bool FVaciando;     //flag de que ha acabado de vaciar

void vaciar(void){

   uint8_t f;
   uint16_t tmpInt;
   static bool Fmidiendo;

   char str[30];
   
   switch (estVaciar)   {
      case EST_VAC_REPOSO:
         estVaciar = EST_VAC_ABRE_SALIR;
         numSensVac = 0;
         break;
      case EST_VAC_ABRE_SALIR:
         if (veTiempo.F100ms){
            for (f =0; f< MAX_PLACAS; f++){
               salidaSpi[f].ev1_8.byte_ev1_8 = 0;
               if (arrSens[f *8] == '1') salidaSpi[f].ev1_8.bits_ev1_8.ev1 = 1;
               if (arrSens[(f *8) + 1] == '1') salidaSpi[f].ev1_8.bits_ev1_8.ev2 = 1;
               if (arrSens[(f *8) + 2] == '1') salidaSpi[f].ev1_8.bits_ev1_8.ev3 = 1;
               if (arrSens[(f *8) + 3] == '1') salidaSpi[f].ev1_8.bits_ev1_8.ev4 = 1;
               if (arrSens[(f *8) + 4] == '1') salidaSpi[f].ev1_8.bits_ev1_8.ev5 = 1;
               if (arrSens[(f *8) + 5] == '1') salidaSpi[f].ev1_8.bits_ev1_8.ev6 = 1;
               if (arrSens[(f *8) + 6] == '1') salidaSpi[f].ev1_8.bits_ev1_8.ev7 = 1;
               if (arrSens[(f *8) + 7] == '1') salidaSpi[f].ev1_8.bits_ev1_8.ev8 = 1;
               salidaSpi[f].ev9_16.byte_ev9_16 = 0x00;
            }
            mandaSpi();
            estVaciar = EST_VAC_ABRE_ENTRAR;
            FVaciando = true;
         }
         break;
      case EST_VAC_ABRE_ENTRAR:
         if (veTiempo.F100ms){
            for (f =0; f< MAX_PLACAS; f++){
               salidaSpi[f].ev1_8.byte_ev1_8 = 0;
               if (arrSens[f *8] == '1') salidaSpi[f].ev1_8.bits_ev1_8.ev1 = 1;
               if (arrSens[(f *8) + 1] == '1') salidaSpi[f].ev1_8.bits_ev1_8.ev2 = 1;
               if (arrSens[(f *8) + 2] == '1') salidaSpi[f].ev1_8.bits_ev1_8.ev3 = 1;
               if (arrSens[(f *8) + 3] == '1') salidaSpi[f].ev1_8.bits_ev1_8.ev4 = 1;
               if (arrSens[(f *8) + 4] == '1') salidaSpi[f].ev1_8.bits_ev1_8.ev5 = 1;
               if (arrSens[(f *8) + 5] == '1') salidaSpi[f].ev1_8.bits_ev1_8.ev6 = 1;
               if (arrSens[(f *8) + 6] == '1') salidaSpi[f].ev1_8.bits_ev1_8.ev7 = 1;
               if (arrSens[(f *8) + 7] == '1') salidaSpi[f].ev1_8.bits_ev1_8.ev8 = 1;
               salidaSpi[f].ev9_16.byte_ev9_16 = 0x00;
               if (arrSens[(f * 8) + 0] == '1') salidaSpi[f].ev9_16.bits_ev9_16.ev9 = 1;
               if (arrSens[(f * 8) + 1] == '1') salidaSpi[f].ev9_16.bits_ev9_16.ev10 = 1;
               if (arrSens[(f * 8) + 2] == '1') salidaSpi[f].ev9_16.bits_ev9_16.ev11 = 1;
               if (arrSens[(f * 8) + 3] == '1') salidaSpi[f].ev9_16.bits_ev9_16.ev12 = 1;
               if (arrSens[(f * 8) + 4] == '1') salidaSpi[f].ev9_16.bits_ev9_16.ev13 = 1;
               if (arrSens[(f * 8) + 5] == '1') salidaSpi[f].ev9_16.bits_ev9_16.ev14 = 1;
               if (arrSens[(f * 8) + 6] == '1') salidaSpi[f].ev9_16.bits_ev9_16.ev15 = 1;
               if (arrSens[(f * 8) + 7] == '1') salidaSpi[f].ev9_16.bits_ev9_16.ev16 = 1;
            }
            mandaSpi();
            numSensVac = 0;
            estVaciar = EST_VAC_MIDE;
         }
         break;
      case EST_VAC_MIDE:
         if (Fmidiendo){ //espera que llegue comando
            if (FrecVaciar){ //ha recibido dato
               FrecVaciar = false;
               str[0] = bufferProcSens[2];
               str[1] = bufferProcSens[3];
               str[2] = bufferProcSens[4];
               str[3] = bufferProcSens[5];
               str[4] = bufferProcSens[7];
               str[5] = NULL;
               tmpInt = atoi(str);
               if (tmpInt < limiteO2){ //manda cerrar valvulas
                  arrCierres[numSensVac].Fcerrar = 1;
               }
               //saca a serie
               sprintf(bufferOut, "O %03d O xxxx,x\r\n", numSensVac +1); //internamente trabaja de 0 a 63 pero manda de 1 a 64
               bufferOut[8] = str[0];
               bufferOut[9] = str[1];
               bufferOut[10] = str[2];
               bufferOut[11] = str[3];
               bufferOut[13] = str[4];
               Ftransmite = true;
               Fmidiendo = false;
               numSensVac ++;
            }
            else{ //espera
               if (veTiempo.F10ms){
                  if (++contEspera > T_ESPERA_COMS){
                     Fmidiendo = false;
                     sprintf(bufferOut, "E 02 S %03d\r\n", numSens + 1);
                     arrSens[numSensVac] = '0';
                     numSens = numSensVac; //para que pinte losled rojos
                     poneLeds(1);
                     mandaSpi();
                     Ftransmite = true;
                     numSensVac ++;
                     error = 2; //pone error 2 alguno ha dejado de funcionar
                  }
               }
            }
         }
         else{ //manda siguiente sensor
            if (veTiempo.F10ms == 0) break; //entra cada 10ms
            while(arrSens[numSensVac] == '0'){
               numSensVac ++;
               if (numSensVac > MAX_SENS - 1)break; //si ha mirado todos sale
            }
            
            // TODO si no hay sensores que salga
            //_____________________________________
            
            if (numSensVac > MAX_SENS - 1){
               numSensVac = 0;
               break;
            }
            else{  //manda medir
               numSens = numSensVac; //para que pinte losled rojos
               poneLeds(1);
               poneMpx(numSensVac); //aqui manda SPI
               mandaComASensor(SENS_MIDE_O2);
               Fmidiendo = true;
               contEspera = 0;
            }
         }
         if (cerrarValvulas()){
            estVaciar = EST_VAC_FIN_VACIAR;
         }
         break;
      case EST_VAC_FIN_VACIAR:
         FVaciando = false;
         estVaciar = EST_VAC_REPOSO;
         cambiaEstado(EST_FIN_VACIAR);
         break;
   }
}

bool vaciando(void){
   return FVaciando;
}

bool cerrarValvulas(void){
   
   uint8_t f,g,h;
   
   if (veTiempo.F100ms){ //entra cada 100ms
      for (f = 0; f < MAX_SENS; f++){
         g = f / MAX_PLACAS; //numero de placa  
         h = f % MAX_PLACAS; //sensor dentro de la placa

         //cierra valvulas de salida, mas tarde
         if (arrCierres[f].Fcerrando){
            arrCierres[f].Fcerrado = 1;
            switch (h){
               case 0:
                  salidaSpi[g].ev9_16.bits_ev9_16.ev9 = 0;
                  break;
               case 1:
                  salidaSpi[g].ev9_16.bits_ev9_16.ev10 = 0;
                  break;
               case 2:
                  salidaSpi[g].ev9_16.bits_ev9_16.ev11 = 0;
                  break;
               case 3:
                  salidaSpi[g].ev9_16.bits_ev9_16.ev12 = 0;
                  break;
               case 4:
                  salidaSpi[g].ev9_16.bits_ev9_16.ev13 = 0;
                  break;
               case 5:
                  salidaSpi[g].ev9_16.bits_ev9_16.ev14 = 0;
                  break;
               case 6:
                  salidaSpi[g].ev9_16.bits_ev9_16.ev15 = 0;
                  break;
               case 7:
                  salidaSpi[g].ev9_16.bits_ev9_16.ev16 = 0;
                  break;
            }
         }

         //cierra valvulas de entrada
         if (arrCierres[f].Fcerrar){
            arrCierres[f].Fcerrando = 1;
            switch (h){
               case 0:
                  salidaSpi[g].ev1_8.bits_ev1_8.ev1 = 0;
                  break;
               case 1:
                  salidaSpi[g].ev1_8.bits_ev1_8.ev2 = 0;
                  break;
               case 2:
                  salidaSpi[g].ev1_8.bits_ev1_8.ev3 = 0;
                  break;
               case 3:
                  salidaSpi[g].ev1_8.bits_ev1_8.ev4 = 0;
                  break;
               case 4:
                  salidaSpi[g].ev1_8.bits_ev1_8.ev5 = 0;
                  break;
               case 5:
                  salidaSpi[g].ev1_8.bits_ev1_8.ev6 = 0;
                  break;
               case 6:
                  salidaSpi[g].ev1_8.bits_ev1_8.ev7 = 0;
                  break;
               case 7:
                  salidaSpi[g].ev1_8.bits_ev1_8.ev8 = 0;
                  break;
            }
         }
         
         if (arrSens[f] != '1'){ //si no esta activo quita las valvulas
            switch (h){
               case 0:
                  salidaSpi[g].ev1_8.bits_ev1_8.ev1 = 0;
                  salidaSpi[g].ev9_16.bits_ev9_16.ev9 = 0;
                  break;
               case 1:
                  salidaSpi[g].ev1_8.bits_ev1_8.ev2 = 0;
                  salidaSpi[g].ev9_16.bits_ev9_16.ev10 = 0;
                  break;
               case 2:
                  salidaSpi[g].ev1_8.bits_ev1_8.ev3 = 0;
                  salidaSpi[g].ev9_16.bits_ev9_16.ev11 = 0;
                  break;
               case 3:
                  salidaSpi[g].ev1_8.bits_ev1_8.ev4 = 0;
                  salidaSpi[g].ev9_16.bits_ev9_16.ev12 = 0;
                  break;
               case 4:
                  salidaSpi[g].ev1_8.bits_ev1_8.ev5 = 0;
                  salidaSpi[g].ev9_16.bits_ev9_16.ev13 = 0;
                  break;
               case 5:
                  salidaSpi[g].ev1_8.bits_ev1_8.ev6 = 0;
                  salidaSpi[g].ev9_16.bits_ev9_16.ev14 = 0;
                  break;
               case 6:
                  salidaSpi[g].ev1_8.bits_ev1_8.ev7 = 0;
                  salidaSpi[g].ev9_16.bits_ev9_16.ev15 = 0;
                  break;
               case 7:
                  salidaSpi[g].ev1_8.bits_ev1_8.ev8 = 0;
                  salidaSpi[g].ev9_16.bits_ev9_16.ev16 = 0;
                  break;
            }
         }
      }
      
      //mira si esta todo cerrado
      g = 0;
      for (f = 0 ; f< MAX_SENS; f++){
         if (arrSens[f] == '1'){
            if (arrCierres[f].Fcerrado == 0) g = 1;
         }
      }
      if (g == 0){ //si eta en 0 hemos terminado
         return true; //pone fin de todos vaciados
      }
   }
   return false;
}

void finVaciar(void){
   // quita la alimentacion a los sensores
   uint8_t f;
   
   for (f = 0 ; f < MAX_PLACAS ; f++){ //apaga todo
      salidaSpi[f].power.byte_pow = 0;
      salidaSpi[f].ev1_8.byte_ev1_8 = 0;
      salidaSpi[f].ev9_16.byte_ev9_16 = 0;
      salidaSpi[f].leds1_4.byte1_4 = 0;
      salidaSpi[f].leds5_8.byte5_8 = 0;
      
      arrCierres[f].Fcerrado =0;
      arrCierres[f].Fcerrando =0;
      arrCierres[f].Fcerrar =0;
   }
   mandaSpi();
}

void poneRespuestaVac(bool resp){
   FrecVaciar = resp;
}