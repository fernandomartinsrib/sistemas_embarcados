#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#ifdef __cplusplus
 extern "C"
#endif
void MCU_init(void); /* Device initialization function declaration */

#include "os.h"

cpu_t stk1[128];
cpu_t stk2[128];
cpu_t stk_idle[128];

void task1(void){
    int i = 0;
    //i++;
    for(;;){ 
      i++;
      delay(15);
      //yield();
    }
}

void task2(void){
    int i = 0;
    //i++;
    for(;;){ 
      i++;
      delay(10);
      //yield();
    }
}

void idle(void){
  for(;;);  
}


void main(void) {
  MCU_init(); /* call Device Initialization */

  
  /* include your code here */
  install_task(idle, stk_idle, sizeof(stk_idle), 0);
  install_task(task1, stk1, sizeof(stk1),2);
  install_task(task2, stk2, sizeof(stk2),5);
  //stk_os = tcb[0].stk;
  start_os();
  //dispatcher();
  
  for(;;) {
    /* __RESET_WATCHDOG(); by default, COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}