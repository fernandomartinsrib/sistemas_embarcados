#include "os.h"
//#include "port.h"

void sc(void){
    SAVE_PC();
    tcb[ct].stk = stk_os;

    //ct++;
    //if(ct>=it) ct=0;

    //stk_os = tcb[ct].stk;
    stk_os = scheduler();
    RESTORE_SP();
}

cpu_t *stk_os;

cpu_t *prepare_stk(void *task, cpu_t *stk, int stk_size){
  cpu_t *stk_tmp = (cpu_t*)((int)stk + stk_size - sizeof(cpu_t));

  *--stk_tmp = (cpu_t)INITIAL_XPSR;
  *--stk_tmp = (cpu_t)task; // ADDRES task

  *--stk_tmp = 0; //
  *--stk_tmp = (cpu_t)0x12121212u;
  *--stk_tmp = (cpu_t)0x03030303u;
  *--stk_tmp = (cpu_t)0x02020202u;
  *--stk_tmp = (cpu_t)0x010101012;
  *--stk_tmp = (cpu_t)0;
  *--stk_tmp = (cpu_t)0xfffffffdu;
  *--stk_tmp = (cpu_t)0x11111111u;
  *--stk_tmp = (cpu_t)0x10101010u;
  *--stk_tmp = (cpu_t)0x09090909u;
  *--stk_tmp = (cpu_t)0x08080808u;
  *--stk_tmp = (cpu_t)0x07070707u;
  *--stk_tmp = (cpu_t)0x06060606u;
  *--stk_tmp = (cpu_t)0x05050505u;
  *--stk_tmp = (cpu_t)0x04040404u;

  return(stk_tmp);
}

__attribute__((naked)) void SwitchContextToFirstTask(void){
    /* Make PendSV and SysTick the lowest priority interrupts. */
    *(NVIC_SYSPRI3) |= NVIC_PENDSV_PRI;
    *(NVIC_SYSPRI3) |= NVIC_SYSTICK_PRI;
    RESTORE_SP();
    RESTORE_CONTEXT();
}

void init_timer(void){
    uint32_t module = 120000000/(uint32_t)1000;
    *(NVIC_SYSTICK_CTRL) = 0; /* Disable SysTick timer */
    *(NVIC_SYSTICK_LOAD) = module - 1u;
    *(NVIC_SYSTICK_CTRL) = NVIC_SYSTICK_CLK | NVIC_SYSTICK_ENABLE | NVIC_SYSTICK_INT;
}

void ticktimer(void){
  if(os_inc_and_compare()){
    SAVE_PC();
    tcb[ct].stk = stk_os;

    stk_os = scheduler();
    RESTORE_SP();
  }
}
