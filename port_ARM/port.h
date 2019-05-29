//#include "derivative.h"

/* Constants required to set up the initial stack. */
#define INITIAL_XPSR                    0x01000000

/* Cortex-M specific definitions. */
#define PRIO_BITS                       4                           // 15 priority levels
#define LOWEST_INTERRUPT_PRIORITY       0xF
#define KERNEL_INTERRUPT_PRIORITY       (LOWEST_INTERRUPT_PRIORITY << (8 - PRIO_BITS) )

/* Constants required to manipulate the NVIC PendSV */
#define NVIC_PENDSVSET                  0x10000000                  // Value to trigger PendSV exception.
#define NVIC_PENDSVCLR                  0x08000000                  // Value to clear PendSV exception.

// Constants required to manipulate the NVIC SysTick
#define NVIC_SYSTICK_CLK                0x00000004
#define NVIC_SYSTICK_INT                0x00000002
#define NVIC_SYSTICK_ENABLE             0x00000001

// ARM Cortex-Mx registers
#define NVIC_SYSTICK_CTRL               ( ( volatile unsigned long *) 0xe000e010 )
#define NVIC_SYSTICK_LOAD               ( ( volatile unsigned long *) 0xe000e014 )
#define NVIC_INT_CTRL                   ( ( volatile unsigned long *) 0xe000ed04 )
#define FPU_FPCCR                       ( ( volatile unsigned long *) 0xE000EF34 )
#define NVIC_SYSPRI3                    ( ( volatile unsigned long *) 0xe000ed20 )

// Kernel interrupt priorities
#define NVIC_PENDSV_PRI                 ( ( ( unsigned long ) KERNEL_INTERRUPT_PRIORITY ) << 16 )
#define NVIC_SYSTICK_PRI                ( ( ( unsigned long ) KERNEL_INTERRUPT_PRIORITY ) << 24 )

/// Define MCU FPU hardware support
#define FPU_SUPPORT         1

#include <stdint.h>

typedef uint32_t cpu_t;

extern cpu_t *stk_os;

cpu_t *prepare_stk(void *, cpu_t *, int);
void init_timer(void);

#define SAVE_PC()\

#define RESTORE_SP() __asm("LDR R1, =stk_os    \n"     \
                           "LDR R0,[R1]         \n"     \
                          )
#define RESTORE_CONTEXT() __asm(                                    \
                                "LDMIA  R0!, {R4-R11, R14}  \n"     \
                                "TST    R14, #0x10          \n"     \
                                "IT     EQ                  \n"     \
                                "VLDMIAEQ R0!, {S16-S31}    \n"     \
                                "MSR    PSP, R0             \n"     \
                                "ORR    LR, LR, #0x04       \n"     \
                                "CPSIE  I                   \n"     \
                                "BX     LR                  \n"     \
                                )

#define yield()\


#define dispatcher() __asm( /* Call SVC to start the first task */ \
                            "svc 0              \n"                \
                            )

