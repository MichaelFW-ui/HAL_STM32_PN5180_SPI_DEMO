/**
 * @filename: iso14443.c
 *
 * @brief Create by lakun@qq.com on 2020/11/14
 */

#include <string.h>
#include "dbg.h"
#include "delay.h"
#include "spi.h"
#include "pn5180.h"
#include "phhalHw.h"
#include "phhalHw_Pn5180.h"
#include "phhalHw_Pn5180_Reg.h"
#include "phhalHw_Pn5180_Instr.h"
#include "phalICode_Int.h"
#include "phalMfc_Int.h"
#include "iso14443.h"


//
// Mifare简介及说明
//
// Mifare是NXP公司生产的一系列遵守ISO14443A标准的射频卡，
// 包括Mifare S50、Mifare S70、Mifare UltraLight、Mifare Pro、Mifare Desfire等。
// Mifare S50的容量为1K字节，常被称为Mifare Standard，又被叫做Mifare 1，
// 是遵守ISO14443A标准的卡片中应用最为广泛、影响力最大的的一员。
// S50的卡类型(ATQA)是0004H。
//


static int ISO14443_CommandSendAndRecvData(const uint8_t* CmdFrame, uint8_t CmdFrameLength, uint8_t* RxBuffer, uint16_t* RxLength);


/**
 * 发送REQA(对睡眠的卡不起作用)命令并接收ATQA。
 *
 * 通常情况下，各个卡类型的ATQA为：
 * Mifare S50        : 0X0004
 * Mifare S70        : 0X0002
 * Mifare UltraLight : 0x0044
 * Mifare Light      : 0X0010
 * Mifare Desfire    : 0X0344
 *
 * 我自己测试时候读取的公交卡的ATQA是0X0008
 *
 * @return 返回接收到的ATQA，如果为0那么查询失败了。
 */
uint16_t ISO14443_SendREQAAndReadATQA(void)
{
    uint16_t ATQA = 0;
    uint16_t Length = 0;
    uint8_t Buffer[32];
    uint8_t Command[3];

    /* Sends REQA(REQuest command,Type A) command */
    Command[0] = PHHAL_HW_PN5180_SET_INSTR_SEND_DATA;
    Command[1] = 0X07;  /* LSB先发，只发送0X26的7bits */
    Command[2] = 0X26;  /* REQA Command */

    if (ISO14443_CommandSendAndRecvData(Command, sizeof(Command), Buffer, &Length) == 0)
    {
        if (Length == 2) /* 正确则返回2字节的ATQA */
        {
            ATQA = (Buffer[1] << 8) | Buffer[0];
        }
    }

    return ATQA;
}

/**
 * 发送REQA(对所有卡起作用)命令并接收ATQA。
 *
 * 通常情况下，各个卡类型的ATQA为：
 * Mifare S50        : 0X0004
 * Mifare S70        : 0X0002
 * Mifare UltraLight : 0x0044
 * Mifare Light      : 0X0010
 * Mifare Desfire    : 0X0344
 *
 * 我自己测试时候读取的公交卡的ATQA是0X0008
 *
 * @return 返回接收到的ATQA，如果为0那么查询失败了。
 */
uint16_t ISO14443_SendWakeUpTypeAAndReadATQA(void)
{
    uint16_t ATQA = 0;
    uint16_t Length = 0;
    uint8_t Buffer[32];
    uint8_t Command[3];

    /* Sends WAKE-UP(Wake-UP command,Type A) command */
    Command[0] = PHHAL_HW_PN5180_SET_INSTR_SEND_DATA;
    Command[1] = 0X07;  /* LSB先发，只发送0X52的7bits */
    Command[2] = 0X52;

    if (ISO14443_CommandSendAndRecvData(Command, sizeof(Command), Buffer, &Length) == 0)
    {
        if (Length == 2) /* 正确则返回2字节的ATQA */
        {
            ATQA = (Buffer[1] << 8) | Buffer[0];
        }
    }

    return ATQA;
}

//
// Mifare系列卡认证
//
// 参数说明：
// UID:卡号
// KEY:字节的KEYA或者KEYB
// KeyType=0X60验证KEYA,KeyType=0X61验证KEYB
// BlockNo:要操作的块地址
//
// 返回值：
// =0：认证成功
// =1：失败
// =2：超时（卡片不存在）
// =3~0XFF：未定义，未知错误
//
uint8_t ISO14443_MifareAuthenticate(const uint8_t UID[4], const uint8_t KEY[6], uint8_t KeyType, uint8_t BlockNo)
{
    uint8_t Status = 0;

    uint8_t Command[13] =
    {
        PHHAL_HW_PN5180_GET_INSTR_MFC_AUTHENTICATE,
        KEY[0],
        KEY[1],
        KEY[2],
        KEY[3],
        KEY[4],
        KEY[5],
        KeyType,
        BlockNo,
        UID[0],
        UID[1],
        UID[2],
        UID[3]
    };

    // 发送命令
    PN5180_WriteBytes(Command, sizeof(Command));

    // 接收状态码
    PN5180_ReadBytes(&Status, 1);

    return Status;
}

/**
 * Mifare系列卡防冲撞，包括放冲撞和选中卡两步骤
 * @param  UID 接收卡UID
 * @return     =0：成功  =other：失败
 *
 * 常见的SAK有以下值：
 * 0X08:M1卡
 * 0X20:CPU卡
 * 0X28:MF1卡(CPU模拟M1卡)
 * 0X18:S70卡（ADEL门锁卡，常见于格林豪泰酒店等）
 */
int ISO14443_MifareAnticollision(uint8_t UID[4], uint8_t* SAK)
{
    int ret = -1;
    uint16_t RxLength = 0, TxLength = 0;
    uint8_t RxBuffer[16];
    uint8_t TxBuffer[16];

    // 防冲撞命令帧
    TxLength = 0;
    TxBuffer[TxLength++] = PHHAL_HW_PN5180_SET_INSTR_SEND_DATA;
    TxBuffer[TxLength++] = 0X00;
    TxBuffer[TxLength++] = 0X93;  // SEL
    TxBuffer[TxLength++] = 0X20;  // NVB,0X20为首次防冲撞命令

__loops:

    if (ISO14443_CommandSendAndRecvData(TxBuffer, TxLength, RxBuffer, &RxLength) == 0)
    {
        //
        // 不需要防冲撞或者防冲撞成功则返回5字节，RxBuffer前4个字节是UID，第五个字节是前面4字节UID的异或
        //
        if (RxLength == 5)
        {
            // 拷贝出UID
            *((uint32_t *)UID) = *(uint32_t *)RxBuffer;

            // 选卡命令帧
            TxLength = 0;
            TxBuffer[TxLength++] = PHHAL_HW_PN5180_SET_INSTR_SEND_DATA;
            TxBuffer[TxLength++] = 0X00;
            TxBuffer[TxLength++] = 0X93;    // SEL
            TxBuffer[TxLength++] = 0X70;    // NVB,0X70为选卡命令
            TxBuffer[TxLength++] = UID[0];
            TxBuffer[TxLength++] = UID[1];
            TxBuffer[TxLength++] = UID[2];
            TxBuffer[TxLength++] = UID[3];
            TxBuffer[TxLength++] = UID[0] ^ UID[1] ^ UID[2] ^ UID[3];     // BCC
//            iso14443a_crc(&TxBuffer[2], 7, &TxBuffer[9], &TxBuffer[10]);  // CRC_A
//            TxLength += 2;

            /* Switches the CRC extension on in Tx direction */
            PN5180_WriteRegisterOrMask(CRC_TX_CONFIG, CRC_TX_CONFIG_TX_CRC_ENABLE_MASK);

            /* Switches the CRC extension on in Rx direction */
            PN5180_WriteRegisterOrMask(CRC_RX_CONFIG, CRC_RX_CONFIG_RX_CRC_ENABLE_MASK);

            // 发送命令帧，成功则返回3字节：1字节SAK+2字节CRC_A
            if (ISO14443_CommandSendAndRecvData(TxBuffer, TxLength, RxBuffer, &RxLength) == 0 && RxLength != 0)
            {
                *SAK = RxBuffer[0];  // 拷贝出SAK
                ret = 0;
            }
            else
            {
                ret = -2;
            }

            /* Switches the CRC extension off in Tx direction */
            PN5180_WriteRegisterAndMask(CRC_TX_CONFIG, ~((uint32_t)CRC_TX_CONFIG_TX_CRC_ENABLE_MASK));

            /* Switches the CRC extension off in Rx direction */
            PN5180_WriteRegisterAndMask(CRC_RX_CONFIG, ~((uint32_t)CRC_RX_CONFIG_RX_CRC_ENABLE_MASK));
        }

        //
        // 需要进行防冲撞
        //
        else
        {
            // 防冲撞命令帧
            TxLength = 0;
            TxBuffer[TxLength++] = PHHAL_HW_PN5180_SET_INSTR_SEND_DATA;
            TxBuffer[TxLength++] = 0X00;
            TxBuffer[TxLength++] = 0X93;                // SEL

            switch(RxLength)
            {
            //
            // 接收到的数据长度为1，表示多个卡的UID从UID0的位置开始出现不一致
            // RxBuffer[0]为冲突的比特位置
            //
            case 1:
            {
                TxBuffer[TxLength++] = 0X20 + RxBuffer[0];  // NVB = 0X20 + 出现冲突的比特位置
                TxBuffer[TxLength++] = RxBuffer[0];         // 后跟发生冲突的比特位置
                goto __loops;
            }

            //
            // 接收到的数据长度为2，表示多个卡的UID从UID1的位置开始出现不一致，
            // RxBuffer[0]为UID0
            // RxBuffer[1]为冲突的比特位置
            //
            case 2:
            {
                TxBuffer[TxLength++] = 0X30 + RxBuffer[1];
                TxBuffer[TxLength++] = RxBuffer[0];
                TxBuffer[TxLength++] = RxBuffer[1];
                goto __loops;
            }
            default:
                break;
            }
        }
    }

    return ret;
}



int ISO14443_ReadBlock(uint16_t BlockNo, uint8_t* BlockData)
{
    int ret = 0;
    uint8_t Buffer[32];
    uint8_t Command[2] = {PHAL_MFC_CMD_READ, BlockNo};
    uint32_t TempLength = 0;

    // 发送命令
    PN5180_WriteBytes(Command, sizeof(Command));

    // 等待2ms的命令响应处理时间
    delay_ms(2);

    // 检查否有数据收到
    if ((TempLength = PN5180_GetRxStatus() & 0X1FFU) == 0)
    {
        ret = -1;
        goto __exit;
    }

    // 发送读取数据命令
    Command[0] = PHHAL_HW_PN5180_GET_INSTR_RETRIEVE_RX_DATA;
    Command[1] = 0X00;
    PN5180_WriteBytes(Command, 2);

    // 读取数据
    PN5180_ReadBytes((uint8_t *)Buffer, TempLength);

__exit:
    return ret;
}

int ISO14443_WriteBlock(uint16_t BlockNo, const uint8_t BlockData[16])
{
    int ret = 0;
    uint16_t Buffer[32];
    uint8_t Command[2] = {PHAL_MFC_CMD_WRITE, BlockNo};
    uint32_t TempLength = 0;

    // 发送命令
    PN5180_WriteBytes(Command, sizeof(Command));

    // 等待2ms的命令响应处理时间
    delay_ms(2);

    // 检查否有数据收到
    if ((TempLength = PN5180_GetRxStatus() & 0X1FFU) == 0)
    {
        ret = -1;
        goto __exit;
    }

    // 发送读取数据命令
    Command[0] = PHHAL_HW_PN5180_GET_INSTR_RETRIEVE_RX_DATA;
    Command[1] = 0X00;
    PN5180_WriteBytes(Command, 2);

    // 读取数据
    PN5180_ReadBytes((uint8_t *)Buffer, TempLength);

__exit:
    PN5180_ClearIRQStatus(PHHAL_HW_PN5180_IRQ_SET_CLEAR_ALL_MASK);
    return ret;
}

int ISO14443_GetVersion(void)
{
    uint8_t Buffer[32];

    uint8_t Command[] = {PHAL_MFC_CMD_GETVERSION};

    // 发送命令
    PN5180_WriteBytes(Command, sizeof(Command));

    // 接收数据
    PN5180_ReadBytes(Buffer, 32);

    return 0;
}

void ISO14443_Init(void)
{
    int i = 0;
    int ret = 0;
    uint8_t RxBuffer[32] = {0};
    uint8_t UID[4] = {0};
    uint8_t KEY[6] = {0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF};
    uint8_t BlockNo = 5;

    uint16_t ATQA = 0;
    uint8_t  SAK = 0;

    /* Reset Hardware */
    PN5180_Reset();

__REQA:

    debug("\r\n\r\n");

    /* Loads the ISO 14443 protocol into the RF registers */
    PN5180_LoadRFConfiguration(HHAL_HW_PN5180_PROTOCOL_ISO14443);

    /* Switches the RF field ON. */
    PN5180_FieleOn();

    /* Crypto ON */
    PN5180_WriteRegisterOrMask(SYSTEM_CONFIG, SYSTEM_CONFIG_MFC_CRYPTO_ON_MASK);

    /* Crypto OFF */
    PN5180_WriteRegisterAndMask(SYSTEM_CONFIG, ~((uint32_t)SYSTEM_CONFIG_MFC_CRYPTO_ON_MASK));

    /* Switches the CRC extension off in Tx direction */
    PN5180_WriteRegisterAndMask(CRC_TX_CONFIG, ~((uint32_t)CRC_TX_CONFIG_TX_CRC_ENABLE_MASK));

    /* Switches the CRC extension off in Rx direction */
    PN5180_WriteRegisterAndMask(CRC_RX_CONFIG, ~((uint32_t)CRC_RX_CONFIG_RX_CRC_ENABLE_MASK));

    /* Clears the interrupt register IRQ_STATUS */
    PN5180_ClearIRQStatus(PHHAL_HW_PN5180_IRQ_SET_CLEAR_ALL_MASK);

    /* Sets the PN5180 into IDLE state */
    PN5180_WriteRegisterAndMask(SYSTEM_CONFIG, (uint32_t)~SYSTEM_CONFIG_COMMAND_MASK);

    /* Activates TRANSCEIVE routine */
    PN5180_WriteRegisterOrMask(SYSTEM_CONFIG, SYSTEM_CONFIG_START_SEND_POS);

    // 寻卡
    if ((ATQA = ISO14443_SendWakeUpTypeAAndReadATQA()) == 0)
    //if ((ATQA = ISO14443_SendREQAAndReadATQA()) == 0)
    {
        debug(" RequestA Failed!\r\n");
        goto __exit;
    }

    debug(" ATQA:%04X\r\n", ATQA);

    // 防冲撞
    if ((ret = ISO14443_MifareAnticollision(UID, &SAK)) != 0)
    {
        debug(" Mifare Anticollision Failed,ErrCode:%d\r\n", ret);
        goto __exit;
    }

    debug(" UID :%02X%02X%02X%02X    \r\n SAK :%02X    \r\n", UID[0], UID[1], UID[2], UID[3], SAK);

    // 认证
    if ((ret = ISO14443_MifareAuthenticate(UID, KEY, PHAL_MFC_CMD_AUTHA, BlockNo)) != 0)
    {
        debug(" Mifare Authenticate Failed,ErrorCode:%d\r\n", ret);
        goto __exit;
    }

    debug(" Mifare Authenticate OK.\r\n");

    if((ret = ISO14443_ReadBlock(BlockNo, RxBuffer)) != 0)
    {
        debug(" Read Block Failed,ErrCode:%d\r\n", ret);
        goto __exit;
    }

    debug("BLOCK:");
    for(i = 0; i < 16; i++)  debug("%02X", RxBuffer[i]);
    debug("\r\n");

__exit:

    PN5180_FieleOff();

    delay_ms(1000);

    goto __REQA;
}

static int ISO14443_CommandSendAndRecvData(const uint8_t* CmdFrame, uint8_t CmdFrameLength, uint8_t* RxBuffer, uint16_t* RxLength)
{
    int ret = 0;
    uint16_t TempLength = 0;
    uint8_t TxBuffer[2];

    // 置0
    *RxLength = 0;

    // 发送命令
    PN5180_WriteBytes(CmdFrame, CmdFrameLength);

    // 等待10ms的数据响应
    delay_ms(10);

    // 检查是否检测到卡片
    if ((PN5180_GetIRQStatus() & IRQ_STATUS_RX_SOF_DET_IRQ_MASK) == 0)
    {
        ret = -1;
        goto __exit;
    }

    // 等待10ms的命令响应处理时间
    delay_ms(10);

    // 检查否有数据收到
    if ((TempLength = PN5180_GetRxStatus() & 0X1FFU) == 0)
    {
        ret = -2;
        goto __exit;
    }

    // 发送读取数据命令
    TxBuffer[0] = PHHAL_HW_PN5180_GET_INSTR_RETRIEVE_RX_DATA;
    TxBuffer[1] = 0X00;
    PN5180_WriteBytes(TxBuffer, 2);

    // 读取数据
    PN5180_ReadBytes((uint8_t *)RxBuffer, TempLength);

    // 赋值数据长度
    *RxLength = TempLength;

__exit:
    PN5180_ClearIRQStatus(PHHAL_HW_PN5180_IRQ_SET_CLEAR_ALL_MASK);
    return ret;
}

/**
 * @brief CRC_A
 *
 */
void iso14443a_crc(const uint8_t *pbtData, size_t szLen, uint8_t *pbtCrcLow, uint8_t *pbtCrcHigh)
{
    uint32_t wCrc = 0x6363;
    uint8_t  bt;
    do
    {

        bt = *pbtData++;
        bt = (bt ^ (uint8_t)(wCrc & 0x00FF));
        bt = (bt ^ (bt << 4));
        wCrc = (wCrc >> 8) ^ ((uint32_t) bt << 8) ^ ((uint32_t) bt << 3) ^ ((uint32_t) bt >> 4);
    }
    while (--szLen);
    *pbtCrcLow  = (uint8_t)(wCrc & 0xFF);
    *pbtCrcHigh = (uint8_t)((wCrc >> 8) & 0xFF);
}

/**
 * @brief CRC_B
 *
 */
void iso14443b_crc(const uint8_t *pbtData, size_t szLen, uint8_t *pbtCrcLow, uint8_t *pbtCrcHigh)
{
    uint32_t wCrc = 0xFFFF;
    uint8_t  bt;
    do
    {

        bt = *pbtData++;
        bt = (bt ^ (uint8_t)(wCrc & 0x00FF));
        bt = (bt ^ (bt << 4));
        wCrc = (wCrc >> 8) ^ ((uint32_t) bt << 8) ^ ((uint32_t) bt << 3) ^ ((uint32_t) bt >> 4);
    }
    while (--szLen);
    wCrc = ~wCrc;
    *pbtCrcLow  = (uint8_t)(wCrc & 0xFF);
    *pbtCrcHigh = (uint8_t)((wCrc >> 8) & 0xFF);
}
