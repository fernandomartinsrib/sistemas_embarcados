#ifdef __cplusplus
 extern "C"
#endif

#include "os.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"

cpu_t stk1[128];
cpu_t stk2[128];
cpu_t stk3[128];
cpu_t stk4[128];
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

void task3(void){
    int i = 0;
    //i++;
    for(;;){
      i++;
      delay(15);
      //yield();
    }
}

void task4(void){
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


int main(void) {

    // Set the system clock to run at 120Mhz off PLL with external crystal as
        // reference.
        //
        // Make sure the main oscillator is enabled because this is required by
        // the PHY.  The system must have a 25MHz crystal attached to the OSC
        // pins. The SYSCTL_MOSC_HIGHFREQ parameter is used when the crystal
        // frequency is 10MHz or higher.
        MAP_SysCtlMOSCConfigSet(SYSCTL_MOSC_HIGHFREQ);

        // Run from the PLL at 120 MHz.
        (void)MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                    SYSCTL_OSC_MAIN |
                    SYSCTL_USE_PLL |
                    SYSCTL_CFG_VCO_480), 120000000);

        // Enable stacking for interrupt handlers.  This allows floating-point
        // instructions to be used within interrupt handlers, but at the expense of
        // extra stack usage.
        MAP_FPUEnable();
        MAP_FPULazyStackingEnable();



  /* include your code here */
  install_task(idle, stk_idle, sizeof(stk_idle), 0);
  install_task(task1, stk1, sizeof(stk1),2);
  install_task(task2, stk2, sizeof(stk2),5);
  install_task(task3, stk3, sizeof(stk3),6);
  install_task(task4, stk4, sizeof(stk4),7);
  //stk_os = tcb[0].stk;
  start_os();
  //dispatcher();

  for(;;) {
    /* __RESET_WATCHDOG(); by default, COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}
