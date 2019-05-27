#include "os.h"
//#include "port.h"

interrupt void sc(void){
    SAVE_PC();
    tcb[ct].stk = stk_os;
    
    ct++;
    if(ct>=it) ct=0;
    
    stk_os = tcb[ct].stk;
    //stk_os = scheduler();
    RESTORE_SP();
}

// testando git.

cpu_t *stk_os;

cpu_t *prepare_stk(void *task, cpu_t *stk, int stk_size){
  cpu_t *stk_tmp = (cpu_t*)((int)stk + stk_size - sizeof(cpu_t));
  
  *stk_tmp-- = (cpu_t)((int)(task)&0xFF);
  *stk_tmp-- = (cpu_t)((int)(task) >> 8);
  
  *stk_tmp-- = 0;
  *stk_tmp-- = 0;
  *stk_tmp-- = 0;
  *stk_tmp = 0;
  
  return(stk_tmp);  
}

void init_timer(void){
  TPM1SC = 0;
  TPM1MOD = 19999;
  TPM1SC = 0x48;
}

interrupt void ticktimer(void){
  TPM1SC_TOF = 0;
  if(os_inc_and_compare()){
    SAVE_PC();
    tcb[ct].stk = stk_os;
    
    //ct++;
    //if(ct>=it) ct=0;
    
    //stk_os = tcb[ct].stk;
    stk_os = scheduler();
    RESTORE_SP();
  }
}


