#include "os.h"

volatile int it = 0;
volatile int ct = 0;
tcb_t tcb[10];

volatile long long os_time = 0;

cpu_t stk_idle[128];

void idle(void){
  for(;;);  
}

void install_task(task_t task, cpu_t *stk, int stk_size, int prio){
  tcb[it].stk = prepare_stk(task, stk, stk_size);  
  // Define priority and ready or not.
  tcb[it].ready = 1;
  tcb[it].prio = (cpu_t)prio;  
  // Next task
  it++;
}

void start_os(void){
  install_task(idle, stk_idle, sizeof(stk_idle), 0);
  init_timer(); 
  stk_os = tcb[0].stk;
  dispatcher(); 
}

void delay(long long time_t){
  tcb[ct].timeout = time_t + os_time;
  tcb[ct].ready = 0;
  yield();
}

cpu_t os_inc_and_compare(void){
   cpu_t i = 0;
   cpu_t ready_t = 0;
   os_time++;
   
   while(i < it){
      if(os_time == tcb[i].timeout){
          ready_t = 1;
          tcb[i].ready = 1; 
      }
      i++;
   }
   return ready_t;
}

cpu_t *scheduler(void){
    cpu_t i = 0;
    cpu_t hi_prio = 0;
    cpu_t st = 0;
    //cpu_t *aux;

    for(i=0;i<it;i++){
        if(tcb[i].ready && (tcb[i].prio > hi_prio)){
           hi_prio=tcb[i].prio;
           st = i;
        } 
    }
    ct=st;
    return tcb[ct].stk;
}



