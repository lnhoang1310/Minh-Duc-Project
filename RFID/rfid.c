#include "rfid.h"
#include "Flash.h"
#include <string.h>

uint8_t Master_Card[UID_SIZE] = {0x23, 0x3E, 0x4A, 0x06, 0x51};
uint8_t Member_Card[MEMBER_CARD_NUM][UID_SIZE];
uint8_t member_card_index = 0;
RFID_Mode status = RFID_CHECK_CARD;

uint8_t isMaster_Card(uint8_t* uid)
{
    return memcmp(uid, Master_Card, UID_SIZE) == 0;
}

uint8_t isMember_Card(uint8_t* uid)
{
    for(uint8_t i = 0; i < member_card_index; i++){
        if(memcmp(uid, Member_Card[i], UID_SIZE) == 0)
            return 1;
    }
    return 0;
}

uint8_t add_new_card(uint8_t* uid)
{
    if(member_card_index >= MEMBER_CARD_NUM)
        return 0;

    if(isMember_Card(uid))
        return 2;

    memcpy(Member_Card[member_card_index], uid, UID_SIZE);
    member_card_index++;

    Flash_Write_Matrix(ADDRESS_FLASH_MEMBER_CARD, Member_Card, MEMBER_CARD_NUM * UID_SIZE);
    Flash_Write(ADDRESS_FLASH_MEMBER_INDEX, member_card_index);
    return 1;
}

uint8_t remove_card(uint8_t* uid)
{
    for(uint8_t i = 0; i < member_card_index; i++)
    {
        if(memcmp(uid, Member_Card[i], UID_SIZE) == 0)
        {
            for(uint8_t k = i; k < member_card_index - 1; k++){
                memcpy(Member_Card[k], Member_Card[k+1], UID_SIZE);
            }

            member_card_index--;
            Flash_Write_Matrix(ADDRESS_FLASH_MEMBER_CARD, Member_Card, MEMBER_CARD_NUM * UID_SIZE);
            Flash_Write(ADDRESS_FLASH_MEMBER_INDEX, member_card_index);
            return 1;
        }
    }
    return 0;
}

Handle_State RFID_Handle(uint8_t* uid)
{
    if(isMaster_Card(uid))
    {
        if(status == RFID_ADD_CARD)
            status = RFID_CHECK_CARD;
        else if(status == RFID_CHECK_CARD)
            status = RFID_REMOVE_CARD;
        else
            status = RFID_ADD_CARD;
        return CHECK_NO_CARD;
    }

    switch(status)
    {
        case RFID_ADD_CARD:
            if(add_new_card(uid) == 1) return ADD_CARD_OK;
            else return ADD_CARD_ERROR;

        case RFID_CHECK_CARD:
            if(isMember_Card(uid)) return CHECK_CARD_VALID;
            else return CHECK_CARD_INVALID;

        case RFID_REMOVE_CARD:
            if(remove_card(uid)) return REMOVE_CARD_OK;
            else return REMOVE_CARD_ERROR;
    }

    return CHECK_NO_CARD;
}

void RFID_Init(void)
{
    Flash_Read(ADDRESS_FLASH_MEMBER_INDEX, &member_card_index);
	if(member_card_index > MEMBER_CARD_NUM)
        member_card_index = 0;
	else Flash_Read_Matrix(ADDRESS_FLASH_MEMBER_CARD, Member_Card, MEMBER_CARD_NUM * UID_SIZE);	
}
