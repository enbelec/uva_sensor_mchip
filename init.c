
#include "includes.h"

void inicializa(void){
   
   uint32_t f;
   
   I2COpen();
   
   if (LeeIntE2prom(E2P_CHECK) != 0x55AA){
      //inicializa
      EscribeIntE2prom(E2P_CHECK, 0x55AA);
      EscribeByteE2prom(E2P_NUM_SENSORES, 16);
      EscribeByteE2prom(E2P_NUM_PLACAS, 2);
      EscribeByteE2prom(E2P_T_ENTRE_MEDIDAS, 1); //1 segundos entre medidas
      EscribeIntE2prom(E2P_T_MEDICION, 120); //100 segundos
   }
   
   numSensores = LeeByteE2prom(E2P_NUM_SENSORES);
   numplacas = LeeByteE2prom(E2P_NUM_PLACAS);
   tEntreMedidas = LeeByteE2prom(E2P_T_ENTRE_MEDIDAS);
   tMedicion = LeeIntE2prom(E2P_T_MEDICION);
 
   puntDatos = 0;
   
   Bm280Reset();
   for(f=0;f<100000; f++); //espera 20ms
   Bm280LeeCalibracion();
   
}