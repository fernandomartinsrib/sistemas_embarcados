#include "derivative.h"

typedef unsigned char cpu_t;

extern cpu_t *stk_os;

cpu_t *prepare_stk(void *, cpu_t *, int);
void init_timer(void);

#define SAVE_PC()\
      asm("TSX");\
      asm("STHX stk_os")

#define RESTORE_SP()\
      asm("LDHX stk_os");\
      asm("TXS")

#define yield()\
        asm("SWI")

#define dispatcher()\
        asm("LDHX stk_os");\
        asm("TXS");\
        asm("PULH");\
        asm("RTI")