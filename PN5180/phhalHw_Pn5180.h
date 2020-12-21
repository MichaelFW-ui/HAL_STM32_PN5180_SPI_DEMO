/*
*         Copyright (c), NXP Semiconductors Gratkorn / Austria
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

/** \file
* PN5180 generic HAL interface.
* $Author$
* $Revision$ (v05.22.00)
* $Date$
*/

#ifndef PHHALHW_PN5180_H
#define PHHALHW_PN5180_H


/*#define PHHAL_HW_PN5180_FIFOSIZE         255U             < Size of PN517 internal FiFo buffer */
#define PHHAL_HW_ERR_EMD_ERROR              0x0011U      /**< An EMD error (noise received). */
#define ACTIVE_MODE_HAL_PN5180              0xFF00U
#define A_MODE                              0x01U
#define B_MODE                              0x02U
#define F_MODE                              0x04U

#define ACTIVE_A_MODE                       0x0100U
#define ACTIVE_B_MODE                       0x0200U
#define ACTIVE_F_MODE                       0x0400U
#define UNSUPPORTED_MODES                   0xF8F8U

#define PHHAL_HW_PN5180_BIT_TYPEB                 0x03U   /**< Activates Type B communication mode. */
#define PHHAL_HW_PN5180_BIT_FELICA                0x02U   /**< Activates FeliCa communication mode. */
#define PHHAL_HW_PN5180_BIT_ISO18092              0x01U   /**< Activates ISO18092(with Sync Byte = 0xF0) communication mode. */
#define PHHAL_HW_PN5180_BIT_MIFARE                0x00U   /**< Activates ISO/IEC 14443 type A communication mode. */
#define PHHAL_HW_PN5180_I18092MT_START_BYTE       0xF0U   /**< Start Byte to be added to the protocol header in case protocol ISO18092. */
#define PHHAL_HW_PN5180_SIGPRO_GENERAL_MAPPING    0x04U
#define PHHAL_HW_PN5180_EXCHANGE_HEADER_SIZE      0x02U    /**< Size Tx exchange header.*/
#define PHHAL_HW_PN5180_ACTIVE_ERR_CAUSE4         0x44U


/**
Tranceive States
*/
#define PHHAL_HW_PN5180_TRANCEIVE_STATE_IDLE                 0U
#define PHHAL_HW_PN5180_TRANCEIVE_STATE_WAITTRANSMIT         1U
#define PHHAL_HW_PN5180_TRANCEIVE_STATE_TRANSMITTING         2U
#define PHHAL_HW_PN5180_TRANCEIVE_STATE_WAITRECEIVE          3U
#define PHHAL_HW_PN5180_TRANCEIVE_STATE_WAITFORDATA          4U
#define PHHAL_HW_PN5180_TRANCEIVE_STATE_RECEIVING            5U
#define PHHAL_HW_PN5180_TRANCEIVE_STATE_LOOPBACK             6U

/**
System Commands-  hold the command bit
*/
#define PHHAL_HW_PN5180_SYSTEM_IDLE_CMD                 0x00U   /*stops all ongoing communication and set the CLIF to IDLE mode*/
#define PHHAL_HW_PN5180_SYSTEM_TRANSMIT_CMD             0x01U  /*starts a transmission immediately*/
#define PHHAL_HW_PN5180_SYSTEM_RECEIVE_CMD              0x02U  /*enables the receiver. After end of reception the bits are clear and IDLE*/
#define PHHAL_HW_PN5180_SYSTEM_TRANSEIVE_CMD            0x03U  /*Transceive command; initiates a transceive cycle. Note: Depending on the value of the Initiator bit a transmission is started or the receiver is enabled Note: The transceive command does not finish automatically. It stays in the transceive cycle until stopped via the IDLE/StopCom command */
#define PHHAL_HW_PN5180_SYSTEM_KEEP_CMD                 0x04U  /*This command does not change the content of the command register and might be used in case other bits in the register are to be changed*/
#define PHHAL_HW_PN5180_SYSTEM_LOOPBACK_CMD             0x05U  /*This command is for test purposes only. It starts a transmission and at the same enables the receiver*/


#define PHHAL_HW_PN5180_TR_RX_PRESCALAR                 0x7FU  /* Tx and Rx Prescaler to 0x7F with 1 Etu ref*/
/**
Set Listen Parameter Constants
*/
#define PHHAL_HW_PN5180_SET_LISTEN_LEN              24U
#define PHHAL_HW_PN5180_SET_LISTEN_EEPROM_ADDR      0x40U
#define PHHAL_HW_PN5180_SET_LISTEN_SENRES_LEN       2U
#define PHHAL_HW_PN5180_SET_LISTEN_NFCID1_LEN       3U
#define PHHAL_HW_PN5180_SET_LISTEN_SELRES_LEN       1U
#define PHHAL_HW_PN5180_SET_LISTEN_POLLRES_LEN      18U
#define PHHAL_HW_PN5180_SET_LISTEN_NFCID3_LEN       1U

#define PHHAL_HW_PN5180_DIGITAL_DELAY_CONFIG_ADDR   0xE8U
#define PHHAL_HW_PN5180_DIGITAL_DELAY_CONFIG_LEN    0x01U
#define PHHAL_HW_PN5180_DIGITAL_DELAY_ENABLE        0x01U

#define PHHAL_HW_PN5180_FDT_TIMER_USED              0x01U     /* As Timer 1 is used for FWT/FDT in HAL 5180, configure timer 1 for digital delay calculation in FW. */
#define PHHAL_HW_PN5180_FDT_TIMER_USED_MASK         0x06U

#define PHHAL_HW_PN5180_DELAY_TO_CHECK_TESTBUS      2U
#define PHHAL_HW_PN5180_RESET_DELAY_MILLI_SECS      2U

/**
Set EMD Modes
*/
#define PHHAL_HW_PN5180_NO_EMD      0U   /* .. no EMD    */
#define PHHAL_HW_PN5180_EMD_2P3     0x185U   /*EMVCO 2.3.1*/
#define PHHAL_HW_PN5180_EMD_2P5     0x107U   /*EMVCO 2.5 and 2.6*/


/**
Switch Protocol Type
*/
#define HHAL_HW_PN5180_PROTOCOL_ISO14443 1
#define HHAL_HW_PN5180_PROTOCOL_ISO15693 2
#define HHAL_HW_PN5180_PROTOCOL_ISO18000 3

/**
ICODE Type

+------------------------------------------------------------------------------------------------+
|   MSB     |   LSB     |           |                                                |   LSB     |
|-----------+-----------+-----------+-----------+====================================+-----------+
|   64:57   |   56:49   |   48:41   |                           40:1
|-----------+-----------+-----------+-----------+====================================+-----------|
|   "E0"    |   "04"    |   "01"    |               IC manufacturer serial number                |
|-----------+-----------+-----------+-----------+====================================+-----------|
|   UID 7   |   UID 6   |   UID 5   |   UID 4   |   UID 3   |   UID 2   |   UID 1    |   UID 0   |
+------------------------------------------------------------------------------------------------+


----------------------------------------
Bit37        Bit36        ICODE Type
----------------------------------------
  0            0           ICODE SLI
----------------------------------------
  1            0           ICODE SLIX
----------------------------------------
  0            1           ICODE SLIX2
----------------------------------------
  1            1           RFU
----------------------------------------

*/

#define HHAL_HW_PN5180_ICODE_SLI   0X00
#define HHAL_HW_PN5180_ICODE_SLIX  0X01
#define HHAL_HW_PN5180_ICODE_SLIX2 0X02

/**
FIRMWARE_VERSION address in E2PROM
*/
#define PHHAL_HW_PN5180_FIRMWARE_VERSION_ADDR         0x12U

/**
TESTBUS_MODE address in E2PROM
*/
#define PHHAL_HW_PN5180_TESTBUS_ENABLE_ADDR           0x17U

/**
LPCD_REFERENCE_VALUE address in E2PROM
*/
#define PHHAL_HW_PN5180_LPCD_REFERENCE_VALUE_ADDR     0x34U

/**
OCPROT_CONTROL address in E2PROM
*/
#define PHHAL_HW_PN5180_OCPROT_CONTROL_ADDR           0x59U

/**
LPCD_GPO_REFVAL_CONTROL address in E2PROM
*/
#define PHHAL_HW_PN5180_LPCD_GPO_REFVAL_CONTROL_ADDR  0x38U

/**
LPCD_REFERENCE_VALUE Mask to get the mode
*/
#define     LPCD_REFVAL_CONTROL_MASK                  0x03U

/**
Clear all INTERUPT MASK
*/
#define PHHAL_HW_PN5180_IRQ_SET_CLEAR_ALL_MASK        0xFFFFFU

/**
Prescalar for Millisec
*/
#define PHHAL_HW_PN5180_MS_TIMEOUT_PRESCALAR          0x3CU

/** \name Modulation indices
*/
/*@{*/
#define PHHAL_HW_PN5180_MODINDEX_I14443B     0xCCU   /**< Default modulation index for ISO14443B. */
#define PHHAL_HW_PN5180_MODINDEX_FELICA      0x17U   /**< Default modulation index for FeliCa. */
#define PHHAL_HW_PN5180_MODINDEX_I15693      0x10U   /**< Default modulation index for ISO15693.  */
#define PHHAL_HW_PN5180_MODINDEX_EPCUID      0x10U   /**< Default modulation index for EPC/UID. */
#define PHHAL_HW_PN5180_MODINDEX_I18000P3M3  0x10U   /**< Default modulation index for ISO18000-3 Mode3. */
/*@}*/

/**
* \brief PN5180 implementation of write register
* This function writes given 32-bit value to the given address.
* This function makes use of the SetRegister command and Pn5180 expects the
* command and the data in the following format.
*
*  +-------+-------+-------+-------+-------+-------+
*  |       |       |       |       |       |       |
*  | 0x00  |  Addr | LSB1  | LSB2  | MSB1  | MSB2  |
*  +-------+-------+-------+-------+-------+-------+
*     0        1       2      3       4       5
*
*  In response to this command, we are going to receive a three byte response
*
*   +-------+
*   |       |
*   | Status|
*   +-------+
*      0        1       2
*
*   status byte indicates the error condition or absence of it.
*
*/

#endif  /* PHHALHW_PN5180_H */
