/**
 * @filename: iso15693.h
 *
 * @brief Create by lakun@qq.com on 2020/11/14
 */
 
#ifndef IOS_15693_H__
#define IOS_15693_H__

#include <stdint.h>

typedef struct
{
    uint8_t Flags;
    uint8_t BlkSize;
    uint8_t BlkNum;
    uint8_t DSFID;
    uint8_t AFI;
    uint8_t ICreference;
    uint16_t ViccMemSize;
} ISO15693CardInfo_Typedef;

int ISO15693_GetSysInfo(const uint8_t UID[8], ISO15693CardInfo_Typedef* CardInfo);
int ISO15693_ReadSingleBlock(const uint8_t UID[8], uint8_t blockData[4], uint8_t blockNo);
int ISO15693_WriteSingleBlock(const uint8_t UID[8], const uint8_t blockData[4], uint8_t blockNo);
int ISO15693_ReadMultiBlock(const uint8_t UID[8], uint8_t FirstBlockNumber, uint8_t NumBlocksToRead, uint8_t* BlocksData);

void ISO15693_SingleInventoryDemo(void);
void ISO15693_MultiInventoryDemo(void);

int ISO15693_InventorySingleSlot(uint8_t UID[8]);
uint16_t ISO15693_Inventory16Slots(uint8_t* UID);

#endif
