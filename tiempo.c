
#include "tiempo.h"
#include "mcc_generated_files/tmr1.h"

VE_TIEMPO veTiempo;

void contadorTiempo(void){
   
   veTiempo.F1ms = 0;
   veTiempo.F10ms = 0;
	veTiempo.F10ms_5 = 0;
   veTiempo.F100ms = 0;
   veTiempo.F100ms_5 = 0;
   veTiempo.F1seg = 0;
   
   if (veTiempo.Fi1ms) { //aqui son 10ms
      veTiempo.Fi1ms = 0;
//      veTiempo.F1ms = 1;
//      veTiempo.contms++;
//		if (veTiempo.contms == 5) veTiempo.F10ms_5 = 1;
//      if (veTiempo.contms > 9) {
//         veTiempo.contms = 0;
         veTiempo.F10ms = 1;
         veTiempo.contdms++;
         if (veTiempo.contdms > 9) {
            veTiempo.contdms = 0;
            veTiempo.F100ms = 1;
            veTiempo.contcms++;
            if (veTiempo.contcms == 5) veTiempo.F100ms_5 = 1;
            if (veTiempo.contcms > 9){
               veTiempo.contcms = 0;
               veTiempo.F1seg = 1;
               veTiempo.contSeg++;
               if (veTiempo.contSeg > 59) {
                  veTiempo.contSeg = 0;
                  veTiempo.contMin++;
                  if (veTiempo.contMin > 59) {
                     veTiempo.contMin = 0;
                     veTiempo.contHoras++;
                  }
               }
            }
         }
//      }
   }
   
}