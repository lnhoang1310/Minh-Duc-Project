#ifndef __RFID_H
#define __RFID_H

#include "stm32f1xx_hal.h"
#include <stdint.h>

#define UID_SIZE            5
#define MEMBER_CARD_NUM     10

#define ADDRESS_FLASH_MEMBER_CARD   0x0801F000
#define ADDRESS_FLASH_MEMBER_INDEX  0x0801F400

typedef enum {
    RFID_ADD_CARD = 0,
    RFID_CHECK_CARD,
    RFID_REMOVE_CARD
} RFID_Mode;

typedef enum{
	ADD_CARD_OK,
	ADD_CARD_ERROR,
	CHECK_NO_CARD,
	CHECK_CARD_VALID,
	CHECK_CARD_INVALID,
	REMOVE_CARD_OK,
	REMOVE_CARD_ERROR
}Handle_State;

extern uint8_t Master_Card[UID_SIZE];
extern uint8_t Member_Card[MEMBER_CARD_NUM][UID_SIZE];
extern uint8_t member_card_index;
extern RFID_Mode status;


void RFID_Init(void);
Handle_State RFID_Handle(uint8_t* uid);
#endif
