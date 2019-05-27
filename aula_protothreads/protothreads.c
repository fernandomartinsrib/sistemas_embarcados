#include "pt.h"
#include "lc.h"
#include <stdio.h>

int proto1(struct pt *pt){
	static int i = 0;
	PT_BEGIN(pt);
	while(i <= 100){
		i++;
		printf("%d\n", i);
		PT_YIELD(pt);
	}
	PT_END(pt);
}

int proto2(struct pt *pt){
	static int i = 100;
	PT_BEGIN(pt);
	while(i >= 0){
		i--;
		printf("%d\n", i);
		PT_YIELD(pt);
	}
	PT_END(pt);
}

struct pt pt1, pt2;

int main(void){
	PT_INIT(&pt1);
	PT_INIT(&pt2);

	while(1){
		proto1(&pt1);
		proto2(&pt2);
	}
}
