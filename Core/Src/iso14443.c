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
// Mifare��鼰˵��
//
// Mifare��NXP��˾������һϵ������ISO14443A��׼����Ƶ����
// ����Mifare S50��Mifare S70��Mifare UltraLight��Mifare Pro��Mifare Desfire�ȡ�
// Mifare S50������Ϊ1K�ֽڣ�������ΪMifare Standard���ֱ�����Mifare 1��
// ������ISO14443A��׼�Ŀ�Ƭ��Ӧ����Ϊ�㷺��Ӱ�������ĵ�һԱ��
// S50�Ŀ�����(ATQA)��0004H��
//


static int ISO14443_CommandSendAndRecvData(const uint8_t* CmdFrame, uint8_t CmdFrameLength, uint8_t* RxBuffer, uint16_t* RxLength);


/**
 * ����REQA(��˯�ߵĿ���������)�������ATQA��
 *
 * ͨ������£����������͵�ATQAΪ��
 * Mifare S50        : 0X0004
 * Mifare S70        : 0X0002
 * Mifare UltraLight : 0x0044
 * Mifare Light      : 0X0010
 * Mifare Desfire    : 0X0344
 *
 * ���Լ�����ʱ���ȡ�Ĺ�������ATQA��0X0008
 *
 * @return ���ؽ��յ���ATQA�����Ϊ0��ô��ѯʧ���ˡ�
 */
uint16_t ISO14443_SendREQAAndReadATQA(void)
{
    uint16_t ATQA = 0;
    uint16_t Length = 0;
    uint8_t Buffer[32];
    uint8_t Command[3];

    /* Sends REQA(REQuest command,Type A) command */
    Command[0] = PHHAL_HW_PN5180_SET_INSTR_SEND_DATA;
    Command[1] = 0X07;  /* LSB�ȷ���ֻ����0X26��7bits */
    Command[2] = 0X26;  /* REQA Command */

    if (ISO14443_CommandSendAndRecvData(Command, sizeof(Command), Buffer, &Length) == 0)
    {
        if (Length == 2) /* ��ȷ�򷵻�2�ֽڵ�ATQA */
        {
            ATQA = (Buffer[1] << 8) | Buffer[0];
        }
    }

    return ATQA;
}

/**
 * ����REQA(�����п�������)�������ATQA��
 *
 * ͨ������£����������͵�ATQAΪ��
 * Mifare S50        : 0X0004
 * Mifare S70        : 0X0002
 * Mifare UltraLight : 0x0044
 * Mifare Light      : 0X0010
 * Mifare Desfire    : 0X0344
 *
 * ���Լ�����ʱ���ȡ�Ĺ�������ATQA��0X0008
 *
 * @return ���ؽ��յ���ATQA�����Ϊ0��ô��ѯʧ���ˡ�
 */
uint16_t ISO14443_SendWakeUpTypeAAndReadATQA(void)
{
    uint16_t ATQA = 0;
    uint16_t Length = 0;
    uint8_t Buffer[32];
    uint8_t Command[3];

    /* Sends WAKE-UP(Wake-UP command,Type A) command */
    Command[0] = PHHAL_HW_PN5180_SET_INSTR_SEND_DATA;
    Command[1] = 0X07;  /* LSB�ȷ���ֻ����0X52��7bits */
    Command[2] = 0X52;

    if (ISO14443_CommandSendAndRecvData(Command, sizeof(Command), Buffer, &Length) == 0)
    {
        if (Length == 2) /* ��ȷ�򷵻�2�ֽڵ�ATQA */
        {
            ATQA = (Buffer[1] << 8) | Buffer[0];
        }
    }

    return ATQA;
}

//
// Mifareϵ�п���֤
//
// ����˵����
// UID:����
// KEY:�ֽڵ�KEYA����KEYB
// KeyType=0X60��֤KEYA,KeyType=0X61��֤KEYB
// BlockNo:Ҫ�����Ŀ��ַ
//
// ����ֵ��
// =0����֤�ɹ�
// =1��ʧ��
// =2����ʱ����Ƭ�����ڣ�
// =3~0XFF��δ���壬δ֪����
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

    // ��������
    PN5180_WriteBytes(Command, sizeof(Command));

    // ����״̬��
    PN5180_ReadBytes(&Status, 1);

    return Status;
}

/**
 * Mifareϵ�п�����ײ�������ų�ײ��ѡ�п�������
 * @param  UID ���տ�UID
 * @return     =0���ɹ�  =other��ʧ��
 *
 * ������SAK������ֵ��
 * 0X08:M1��
 * 0X20:CPU��
 * 0X28:MF1��(CPUģ��M1��)
 * 0X18:S70����ADEL�������������ڸ��ֺ�̩�Ƶ�ȣ�
 */
int ISO14443_MifareAnticollision(uint8_t UID[4], uint8_t* SAK)
{
    int ret = -1;
    uint16_t RxLength = 0, TxLength = 0;
    uint8_t RxBuffer[16];
    uint8_t TxBuffer[16];

    // ����ײ����֡
    TxLength = 0;
    TxBuffer[TxLength++] = PHHAL_HW_PN5180_SET_INSTR_SEND_DATA;
    TxBuffer[TxLength++] = 0X00;
    TxBuffer[TxLength++] = 0X93;  // SEL
    TxBuffer[TxLength++] = 0X20;  // NVB,0X20Ϊ�״η���ײ����

__loops:

    if (ISO14443_CommandSendAndRecvData(TxBuffer, TxLength, RxBuffer, &RxLength) == 0)
    {
        //
        // ����Ҫ����ײ���߷���ײ�ɹ��򷵻�5�ֽڣ�RxBufferǰ4���ֽ���UID��������ֽ���ǰ��4�ֽ�UID�����
        //
        if (RxLength == 5)
        {
            // ������UID
            *((uint32_t *)UID) = *(uint32_t *)RxBuffer;

            // ѡ������֡
            TxLength = 0;
            TxBuffer[TxLength++] = PHHAL_HW_PN5180_SET_INSTR_SEND_DATA;
            TxBuffer[TxLength++] = 0X00;
            TxBuffer[TxLength++] = 0X93;    // SEL
            TxBuffer[TxLength++] = 0X70;    // NVB,0X70Ϊѡ������
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

            // ��������֡���ɹ��򷵻�3�ֽڣ�1�ֽ�SAK+2�ֽ�CRC_A
            if (ISO14443_CommandSendAndRecvData(TxBuffer, TxLength, RxBuffer, &RxLength) == 0 && RxLength != 0)
            {
                *SAK = RxBuffer[0];  // ������SAK
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
        // ��Ҫ���з���ײ
        //
        else
        {
            // ����ײ����֡
            TxLength = 0;
            TxBuffer[TxLength++] = PHHAL_HW_PN5180_SET_INSTR_SEND_DATA;
            TxBuffer[TxLength++] = 0X00;
            TxBuffer[TxLength++] = 0X93;                // SEL

            switch(RxLength)
            {
            //
            // ���յ������ݳ���Ϊ1����ʾ�������UID��UID0��λ�ÿ�ʼ���ֲ�һ��
            // RxBuffer[0]Ϊ��ͻ�ı���λ��
            //
            case 1:
            {
                TxBuffer[TxLength++] = 0X20 + RxBuffer[0];  // NVB = 0X20 + ���ֳ�ͻ�ı���λ��
                TxBuffer[TxLength++] = RxBuffer[0];         // ���������ͻ�ı���λ��
                goto __loops;
            }

            //
            // ���յ������ݳ���Ϊ2����ʾ�������UID��UID1��λ�ÿ�ʼ���ֲ�һ�£�
            // RxBuffer[0]ΪUID0
            // RxBuffer[1]Ϊ��ͻ�ı���λ��
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

    // ��������
    PN5180_WriteBytes(Command, sizeof(Command));

    // �ȴ�2ms��������Ӧ����ʱ��
    delay_ms(2);

    // �����������յ�
    if ((TempLength = PN5180_GetRxStatus() & 0X1FFU) == 0)
    {
        ret = -1;
        goto __exit;
    }

    // ���Ͷ�ȡ��������
    Command[0] = PHHAL_HW_PN5180_GET_INSTR_RETRIEVE_RX_DATA;
    Command[1] = 0X00;
    PN5180_WriteBytes(Command, 2);

    // ��ȡ����
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

    // ��������
    PN5180_WriteBytes(Command, sizeof(Command));

    // �ȴ�2ms��������Ӧ����ʱ��
    delay_ms(2);

    // �����������յ�
    if ((TempLength = PN5180_GetRxStatus() & 0X1FFU) == 0)
    {
        ret = -1;
        goto __exit;
    }

    // ���Ͷ�ȡ��������
    Command[0] = PHHAL_HW_PN5180_GET_INSTR_RETRIEVE_RX_DATA;
    Command[1] = 0X00;
    PN5180_WriteBytes(Command, 2);

    // ��ȡ����
    PN5180_ReadBytes((uint8_t *)Buffer, TempLength);

__exit:
    PN5180_ClearIRQStatus(PHHAL_HW_PN5180_IRQ_SET_CLEAR_ALL_MASK);
    return ret;
}

int ISO14443_GetVersion(void)
{
    uint8_t Buffer[32];

    uint8_t Command[] = {PHAL_MFC_CMD_GETVERSION};

    // ��������
    PN5180_WriteBytes(Command, sizeof(Command));

    // ��������
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

    // Ѱ��
    if ((ATQA = ISO14443_SendWakeUpTypeAAndReadATQA()) == 0)
    //if ((ATQA = ISO14443_SendREQAAndReadATQA()) == 0)
    {
        debug(" RequestA Failed!\r\n");
        goto __exit;
    }

    debug(" ATQA:%04X\r\n", ATQA);

    // ����ײ
    if ((ret = ISO14443_MifareAnticollision(UID, &SAK)) != 0)
    {
        debug(" Mifare Anticollision Failed,ErrCode:%d\r\n", ret);
        goto __exit;
    }

    debug(" UID :%02X%02X%02X%02X    \r\n SAK :%02X    \r\n", UID[0], UID[1], UID[2], UID[3], SAK);

    // ��֤
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

    // ��0
    *RxLength = 0;

    // ��������
    PN5180_WriteBytes(CmdFrame, CmdFrameLength);

    // �ȴ�10ms��������Ӧ
    delay_ms(10);

    // ����Ƿ��⵽��Ƭ
    if ((PN5180_GetIRQStatus() & IRQ_STATUS_RX_SOF_DET_IRQ_MASK) == 0)
    {
        ret = -1;
        goto __exit;
    }

    // �ȴ�10ms��������Ӧ����ʱ��
    delay_ms(10);

    // �����������յ�
    if ((TempLength = PN5180_GetRxStatus() & 0X1FFU) == 0)
    {
        ret = -2;
        goto __exit;
    }

    // ���Ͷ�ȡ��������
    TxBuffer[0] = PHHAL_HW_PN5180_GET_INSTR_RETRIEVE_RX_DATA;
    TxBuffer[1] = 0X00;
    PN5180_WriteBytes(TxBuffer, 2);

    // ��ȡ����
    PN5180_ReadBytes((uint8_t *)RxBuffer, TempLength);

    // ��ֵ���ݳ���
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
