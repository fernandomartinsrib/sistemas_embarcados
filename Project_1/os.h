#include "port.h"

typedef void (*task_t)(void);

typedef struct tcb_t{
  cpu_t *stk;
  cpu_t prio;
  cpu_t ready;
  long long timeout;
}tcb_t;


void install_task(task_t task, cpu_t *stk, int stk_size, int prio);
cpu_t *scheduler(void);
void delay(long long);
cpu_t os_inc_and_compare(void);
void start_os(void);

extern tcb_t tcb[10];
extern volatile int it;
extern volatile int ct;
extern volatile long long os_time;

