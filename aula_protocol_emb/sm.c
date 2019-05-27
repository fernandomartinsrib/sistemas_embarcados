#include "sm.h"
#include <stdint.h>
#include <stdio.h>

static void fnSTX(sm_t  *sm, unsigned char data){
	printf("aqui stx\n");
	if(data == '$'){
		sm->my_addr_receive = 0;
		sm->chk_receive = 0;
		sm->qtd_receive = 0;
		sm->state = st_addr;
	}
}

static void fnADDR(sm_t *sm, unsigned char data){
	printf("aqui addr\n");

	if(sm->my_addr_receive == 0){
		printf("aqui addr receive\n");
		sm->my_addr_receive = data;
	}
	else{
		printf("entrou no else addr\n");
		sm->my_addr_receive |= (((uint16_t) data)<<8);
		sm->chk_receive += data;
			printf("Valor sm->chk_receive: %x\n", sm->chk_receive);
		printf("Endereço obtido: %x\n", sm->my_addr_receive);
		printf("Enredeço compardo: %x\n", sm->my_addr);
		if(sm->my_addr_receive == sm->my_addr){
			sm->state = st_qtd;
		}
		else{
			sm->state = st_stx;
		}
	}
	sm->chk_receive += data;
	printf("Valor sm->chk_receive: %x\n", sm->chk_receive);
}

static void fnQTD(sm_t *sm, unsigned char data){
	printf("aqui qtd\n");
	sm->qtd_dados = data;
	sm->chk_receive += data;
		printf("Valor sm->chk_receive: %x\n", sm->chk_receive);
	sm->state = st_dados;
}

static void fnDADOS(sm_t *sm, unsigned char data){
	printf("aqui1 fndados\n");
	printf("sm->qtd_receive %d e sm->qtd_dados:%d\n",sm->qtd_receive, sm->qtd_dados );
	if(sm->qtd_receive < sm->qtd_dados){
		sm->pack[sm->qtd_receive] = data;
		sm->qtd_receive++;
		sm->chk_receive += data;
			printf("Valor sm->chk_receive: %x\n", sm->chk_receive);
		if(sm->qtd_receive == sm->qtd_dados){
			sm->pack[sm->qtd_receive] = '\0';
			printf("here\n");
			sm->state = st_chk;
		}
	}

}

static void fnCHK(sm_t *sm, unsigned char data){
	printf("aqui chk\n");
	printf("Valor sm->chk_receive: %x\n", sm->chk_receive);
	sm->chk = data;
	if(sm->chk == sm->chk_receive){
		printf("SUCESSO\n");
	}else{
		printf("ERROR\n");
	}
	sm->state = st_etx;

}

static void fnETX(sm_t *sm, unsigned char data){
	printf("aqui etx\n");
	if(data == '#'){
		sm->state = st_end;
		sm->handlePk(sm->pack);
	}
}


void initSM(sm_t *sm, uint16_t addr, handle_t handle){
	printf("aqui init\n");
	printf("ADDR: %x\n", addr);

	sm->state = st_stx;
	sm->my_addr = addr;
	sm->handlePk = handle;
	
	sm->my_addr = addr;
	printf("ADDR: %x\n", sm->my_addr);
	sm->my_addr_receive = 0;
	sm->chk = 0;
	sm->chk_receive = 0;
	sm->qtd_dados = 0;
	sm->qtd_receive = 0;


	sm->action[st_stx] =(action_t) fnSTX;
	sm->action[st_addr] = (action_t)fnADDR;
	sm->action[st_qtd] = (action_t)fnQTD;
	sm->action[st_dados] = (action_t)fnDADOS;
	sm->action[st_chk] = (action_t)fnCHK;
	sm->action[st_etx] = (action_t)fnETX; 
	//sm->action[st_end] = fnSTX;
	printf("saiu init\n");
}


void execSM(sm_t *sm,unsigned char data){
	sm->action[sm->state](sm, data);
}

void execPROG(sm_t *sm,unsigned char *data, int size){
	printf("aqui exec\n");
	for(int i=0;i < size; i++){
		execSM(sm, data[i]);	
	}
}
