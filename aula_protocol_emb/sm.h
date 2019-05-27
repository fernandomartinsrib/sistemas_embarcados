#ifndef _sm_h
#define _sm_h

/*
 * Tipos de dados armazenados:
 * STX: 1 byte Inicio de transmissao($)
 * ADDR: 2 bytes
 * QTD_DADOS: 1 byte -> Quantidade de dados transmitidos
 * DADOS: N Bytes -> Dados ate 128 bytes.
 * CHK: 1 Byte --> Checksum da transmissao.
 * ETX: 1 Byte --> Fim da tranmissao (#).
 */

#include <stdint.h>

typedef enum{

	st_stx, st_addr, st_qtd, st_dados, st_chk, st_etx, st_end, st_max


}state_t;

typedef void (*action_t)(void *,unsigned char);
typedef void (*handle_t)( unsigned char *);


typedef struct sm_state{
	
	state_t state;
	action_t action[st_end];


	uint16_t my_addr;
	uint16_t my_addr_receive;
	unsigned char pack[128];
	unsigned char qtd_dados;
	unsigned char qtd_receive;
	unsigned char chk;
	unsigned char chk_receive;
	unsigned char etx;

	handle_t handlePk;	

}sm_t;


void initSM(sm_t *sm, uint16_t addr, handle_t handle);
void execSM(sm_t *sm, unsigned char data);
void execPROG(sm_t *sm, unsigned char *data, int size);

#endif
