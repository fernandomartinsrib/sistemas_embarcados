#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "sm.h"

void printRes(unsigned char* string){
	printf("String: %s\n", string);
}

sm_t sm_teste;

int main(void){
	sm_t sm;
	unsigned char data[] = {'$', 0x0A, 0x00, 3,'f', 'e', 'r',0x4a, '#'};

	initSM(&sm_teste, 10, printRes);
	execPROG(&sm_teste, data, 9);
}
