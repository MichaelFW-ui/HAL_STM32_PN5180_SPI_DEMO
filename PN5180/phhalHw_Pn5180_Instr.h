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
* PN5180 HAL Instruction Layer.
** $Author:nxp62726 $
* $Revision$ (v05.22.00)
* $Date$
*/

#ifndef PHHALHW_PN5180_INSTR_H
#define PHHALHW_PN5180_INSTR_H

/**
 * \name PN5180 Instruction Codes.
 * To be used with #phhalHw_Pn5180_Instr_Execute
 */
/*@{*/
#define PHHAL_HW_PN5180_SET_INSTR_WRITE_REGISTER                               0x00U  /**< Write 32 bit value to a register. */
#define PHHAL_HW_PN5180_SET_INSTR_WRITE_REGISTER_OR_MASK                       0x01U  /**< Perform a logical OR operation on a register using provided mask. */
#define PHHAL_HW_PN5180_SET_INSTR_WRITE_REGISTER_AND_MASK                      0x02U  /**< Perform a logical AND operation on a register using provided mask. */
#define PHHAL_HW_PN5180_SET_INSTR_WRITE_REGISTER_MULTIPLE                      0x03U  /**< Perform a write register operation using a set of Register-Value pairs. */
#define PHHAL_HW_PN5180_GET_INSTR_READ_REGISTER                                0x04U  /**< Read back content of a register. */
#define PHHAL_HW_PN5180_GET_INSTR_READ_REGISTER_MULTIPLE                       0x05U  /**< Perform a read register operation on a set of registers. */
#define PHHAL_HW_PN5180_SET_INSTR_WRITE_E2PROM                                 0x06U  /**< Write given values sequentially to E2PROM. */
#define PHHAL_HW_PN5180_GET_INSTR_READ_E2PROM                                  0x07U  /**< Read out values from E2PROM sequentially. */
#define PHHAL_HW_PN5180_SET_INSTR_WRITE_TX_DATA                                0x08U  /**< Write Tx data to internal CLIF transmission buffer. */
#define PHHAL_HW_PN5180_SET_INSTR_SEND_DATA                                    0x09U  /**< Write Tx data to internal RF transmission buffer and starts transmission using transceive command. */
#define PHHAL_HW_PN5180_GET_INSTR_RETRIEVE_RX_DATA                             0x0AU  /**< Read Rx data from internal RF reception buffer. */
#define PHHAL_HW_PN5180_SET_INSTR_SWITCH_MODE                                  0x0BU  /**< Switch operation mode. Possible modes are: Normal, LPCD, Autocoll, Standby. */
#define PHHAL_HW_PN5180_GET_INSTR_MFC_AUTHENTICATE                             0x0CU  /**< Perform authentication on an activated MIFARE Classic contactless IC card. */
#define PHHAL_HW_PN5180_SET_INSTR_EPC_GEN2_INVENTORY                           0x0DU  /**< Perform an ISO 18000-3M3 Inventory. */
#define PHHAL_HW_PN5180_SET_INSTR_EPC_GEN2_RESUME_INVENTORY                    0x0EU  /**< Resume ISO18000-3M3 Inventory. */
#define PHHAL_HW_PN5180_GET_INSTR_EPC_GEN2_RETRIEVE_INVENTORY_RESULT_SIZE      0x0FU  /**< Retrieve the size of a pending EPC GEN2 inventory result. */
#define PHHAL_HW_PN5180_GET_INSTR_EPC_GEN2_RETRIEVE_INVENTORY_RESULT           0x10U  /**< Return the result of inventory. */
#define PHHAL_HW_PN5180_SET_INSTR_LOAD_RF_CONFIGURATION                        0x11U  /**< Load RF Tx and Rx settings from E2PROM. */
#define PHHAL_HW_PN5180_SET_INSTR_UPDATE_RF_CONFIGURATION                      0x12U  /**< Update the RF configuration. */
#define PHHAL_HW_PN5180_GET_INSTR_RETRIEVE_RF_CONFIGURATION_SIZE               0x13U  /**< Retrieve the number of register-value pairs of the RF configuration. */
#define PHHAL_HW_PN5180_GET_INSTR_RETRIEVE_RF_CONFIGURATION                    0x14U  /**< Retrieve the RF configuration. */
#define PHHAL_HW_PN5180_SET_INSTR_CONFIGURE_TESTBUS_RFU                        0x15U  /**< Retrieve the RF configuration. */
#define PHHAL_HW_PN5180_GET_INSTR_FIELD_ON                                     0x16U  /**< RF Field ON. */
#define PHHAL_HW_PN5180_GET_INSTR_FIELD_OFF                                    0x17U  /**< RF field OFF.*/
#define PHHAL_HW_PN5180_SET_INSTR_CONFIGURE_TESTBUS_DIGITAL                    0x18U  /**< Digital Testbus.*/
#define PHHAL_HW_PN5180_SET_INSTR_CONFIGURE_TESTBUS_ANALOG                     0x19U  /**< Analog Testbus*/


/*@}*/


/**
 * \name PN5180 Write multiple register operation type.
 * To be used with #phhalHw_Pn5180_Instr_WriteRegisterMultiple.
 */
/*@{*/
#define PHHAL_HW_PN5180_WRITE_MULTIPLE_TYPE_WRITE                             0x01U  /**< Write register operation requested. */
#define PHHAL_HW_PN5180_WRITE_MULTIPLE_TYPE_WRITE_OR_MASK                     0x02U  /**< Write register OR mask operation requested. */
#define PHHAL_HW_PN5180_WRITE_MULTIPLE_TYPE_WRITE_AND_MASK                    0x03U  /**< Write register AND mask operation requested. */
/*@}*/

/**
 * \name PN5180 wakeup control bitmask defintion
 */
/*@{*/
#define PHHAL_HW_PN5180_WAKEUP_CONTROL_MASK_WUP_ON_COUNTER                    0x01U  /**< Wake up from standby on wakeup counter expire. */
#define PHHAL_HW_PN5180_WAKEUP_CONTROL_MASK_WUP_ON_EXT_FIELD                  0x02U  /**< Wake up from standby due to external RF field. */
#define PHHAL_HW_PN5180_WAKEUP_CONTROL_MASK_ASSERT_GPO                        0x04U  /**< Assert GPO when leaving standby. */
/*@}*/

/**
 * \name PN5180 autocoll RF technology bitmask definition
 */
/*@{*/
#define PHHAL_HW_PN5180_AUTOCOLL_RF_TECHNOLOGY_MASK_NFC_A                    0x01U  /**< Autocoll for NFC-A (ISO14443 mode A) enabled. */
#define PHHAL_HW_PN5180_AUTOCOLL_RF_TECHNOLOGY_MASK_NFC_F                    0x02U  /**< Autocoll for NFC-F (FeliCa) enabled. */
#define PHHAL_HW_PN5180_AUTOCOLL_RF_TECHNOLOGY_MASK_ISO18092_ACTIVE          0x04U  /**< Autocoll for ISO18092 target mode active enabled. */
#define PHHAL_HW_PN5180_AUTOCOLL_RF_TECHNOLOGY_MASK_NFC_F_ACTIVE             0x08U  /**< Autocoll for NFC_F target mode active enabled. */
/*@}*/

/**
 * \name PN5180 autocoll operation mode
 */
/*@{*/
#define PHHAL_HW_PN5180_AUTOCOLL_MODE_TERMINATE_ON_RF_OFF                 0x00U  /**< Autocoll terminates when external field vanishes. */
#define PHHAL_HW_PN5180_AUTOCOLL_MODE_AUTONOMOUS_WITH_STANDBY             0x01U  /**< Autocoll terminates only upon successful activation. When external field vanishes, PN5180 enters standby. PN5180 wakes up again once external field is detected again. */
#define PHHAL_HW_PN5180_AUTOCOLL_MODE_AUTONOMOUS_WITHOUT_STANDBY          0x02U  /**< Autocoll terminates only upon successful activation. PN5180 does use standby mode. */
/*@}*/

/**
 * \name PN5180 Timeslot processing behavior.
 */
/*@{*/
#define PHHAL_HW_PN5180_EPC_GEN2_TIMESLOT_FILL_BUFFER                     0x00U  /**< EPC GEN2 inventory processes timeslots until buffer is full. */
#define PHHAL_HW_PN5180_EPC_GEN2_TIMESLOT_SINGLE                          0x01U  /**< EPC GEN2 inventory processes one timeslot only. */
#define PHHAL_HW_PN5180_EPC_GEN2_TIMESLOT_SINGLE_SELECT_TAG               0x02U  /**< EPC GEN2 inventory processes one timeslot only. If timeslot contains a valid tag response, the tag is also selected. */
/*@}*/


/**
   * \name PN5180 Switch Mode Type type.
   */
/*@{*/
#define PHHAL_HW_PN5180_SWITCH_MODE_STANDBY                               0x00U  /**< PN5180 is in standby/sleep state to save power. */
#define PHHAL_HW_PN5180_SWITCH_MODE_LPCD                                  0x01U  /**< PN5180 is in low power card detection mode. */
#define PHHAL_HW_PN5180_SWITCH_MODE_AUTOCOLL                              0x02U  /**< PN5180 is acting as RF listener, performing target mode activation autonomously. */
#define PHHAL_HW_PN5180_SWITCH_MODE_NORMAL                                0x03U  /**< PN5180 is in Normal modes. */

/*@}*/


/**
* \name PN5180 register, EEPROM & TX/RX buffer custom definitions.
* To be used with
* #phhalHw_Pn5180_Instr_WriteRegister,
* #phhalHw_Pn5180_Instr_WriteRegisterOrMask,
* #phhalHw_Pn5180_Instr_WriteRegisterAndMask,
* #phhalHw_Pn5180_Instr_WriteRegisterMultiple,
* #phhalHw_Pn5180_Instr_ReadRegister,
* #phhalHw_Pn5180_Instr_ReadRegisterMultiple,
* #phhalHw_Pn5180_Instr_WriteE2Prom,
* #phhalHw_Pn5180_Instr_ReadE2Prom,
* #phhalHw_Pn5180_Instr_WriteTxData,
* #phhalHw_Pn5180_Instr_SendData,
* #phhalHw_Pn5180_Instr_RetrieveRxData.
 */
/*@{*/
#define PHHAL_HW_PN5180_MAX_REGISTER_TYPE_VALUE_SET                       0x102U /**< Size of the buffer holding the register-type-value sets. Maximum size supported is 258 = 43 sets. */
#define PHHAL_HW_PN5180_MIN_REGISTER_TYPE_VALUE_SET                        0x06U /**< Size of the buffer holding the register-type-value sets. Minimum size supported is 6 = 1 set. */

#define PHHAL_HW_PN5180_E2PROM_MAX_DATA_LENGTH                             0x41U /**< The E2PROM maximum payload length is 254 byte. */
#define PHHAL_HW_PN5180_E2PROM_MIN_DATA_LENGTH                             0x01U /**< The E2PROM minimum payload length is 1 byte. */
#define PHHAL_HW_PN5180_E2PROM_MAX_ADDESS                                  0xFDU /**< The E2PROM maximum Address is 0x93. */
#define PHHAL_HW_PN5180_E2PROM_MIN_ADDESS                                  0x16U  /**< The E2PROM minimum Address 0. */

#define PHHAL_HW_PN5180_TX_DATA_MAX_LENGTH                                 0x104U/**< The Transmission maximum payload length is 260 byte. */
#define PHHAL_HW_PN5180_TX_DATA_MIN_LENGTH                                 0x01U /**< The Transmission minimum payload length is 1 byte. */

#define PHHAL_HW_PN5180_RX_DATA_MAX_LENGTH                                 0x200U/**< The Retrieved Maximum data length is 512 byte. */
#define PHHAL_HW_PN5180_RX_DATA_MIN_LENGTH                                 0x01U /**< The Retrieved Minimum data length is 1 byte. */

#define PHHAL_HW_PN5180_INSTR_DATA_MIN_VALUE                               0x01U /**< The Minimum data value 01. */

#define PHHAL_HW_PN5180_INVALID_REG_START_ADDRESS                          0x44U /**< Regs from 0x45 to 0x7F are not implemented Update everytime regmap changes due to reg addition.*/
#define PHHAL_HW_PN5180_INVALID_REG_END_ADDRESS                            0x7FU /**< Regs from 0x45 to 0x7F are not implemented Update everytime regmap changes due to reg addition.*/



#define PHHAL_HW_PN5180_MAX_REGISTERS_READ_MULTIPLE                        18U /**< Maximum registers for multiple Read*/
#define PHHAL_HW_PN5180_BYTES_PER_REGISTER                                 4U
#define PHHAL_HW_PN5180_SEND_DATA_FIXED_CMD_BYTES                          2U
#define PHHAL_HW_PN5180_WRITE_TX_DATA_FIXED_CMD_BYTES                      1U
/*@}*/

/**
 * \name PN5180 Execute instruction custom definitions.
 * To be used with
 * #phhalHw_Pn5180_Instr_Execute.
 */
/*@{*/
#define PHHAL_HW_PN5180_MAX_INSTRUCTION_CODE                               PHHAL_HW_PN5180_GET_INSTR_RETRIEVE_RF_CONFIGURATION            /**< Maximum value of the instruction code. */
#define PHHAL_HW_PN5180_MIN_PAYLOAD_LENGTH                                 1U                                                             /**< Minimum payload length for the instruction. */
#define PHHAL_HW_PN5180_MAX_PAYLOAD_LENGTH                                 261U                                                           /**< Maximum payload length for the instruction. */
#define PHHAL_HW_PN5180_MAX_INSTRUCTION_LENGTH                             (1U + PHHAL_HW_PN5180_MAX_PAYLOAD_LENGTH)                      /**< Maximum length for the instruction. 1 byte is for the instruction code */
#define PHHAL_HW_PN5180_MAX_INST_RESPONSE_LENGTH                           (0x200U)                                                       /**< Maximum length for the instruction response */


/*@}*/

/**
 * \name PN5180 standby custom definitions.
 * To be used with
 * #phhalHw_Pn5180_Instr_SwitchModeStandby.
 */
/*@{*/
#define PHHAL_HW_PN5180_WAKEUP_CONTROL_MASK                                (PHHAL_HW_PN5180_WAKEUP_CONTROL_MASK_WUP_ON_COUNTER \
                                                                           | PHHAL_HW_PN5180_WAKEUP_CONTROL_MASK_WUP_ON_EXT_FIELD \
                                                                           | PHHAL_HW_PN5180_WAKEUP_CONTROL_MASK_ASSERT_GPO)                /**< Mask value for wakeup control. */

#define PHHAL_HW_PN5180_MAX_WAKEUP_COUNTER                                 (2690U)                                                            /**< Maximum value for wakeup counter in msecs. */

/*@}*/

/**
 * \name PN5180 Autocoll custom definitions.
 * To be used with
 * #phhalHw_Pn5180_Instr_SwitchModeAutocoll.
 */
/*@{*/
#define PHHAL_HW_PN5180_MAX_AUTOCOLL_MODE                                  PHHAL_HW_PN5180_WAKEUP_CONTROL_MASK_ASSERT_GPO                 /**< Maximum value for Autocoll mode. */
#define PHHAL_HW_PN5180_AUTOCOLL_MODE_MASK                                 (PHHAL_HW_PN5180_AUTOCOLL_MODE_TERMINATE_ON_RF_OFF  \
                                                                           | PHHAL_HW_PN5180_AUTOCOLL_MODE_AUTONOMOUS_WITH_STANDBY \
                                                                           | PHHAL_HW_PN5180_AUTOCOLL_MODE_AUTONOMOUS_WITHOUT_STANDBY)      /**< Mask value for RF technology. */

#define PHHAL_HW_PN5180_MAX_AUTOCOLL_RF_TECHNOLOGY                         PHHAL_HW_PN5180_AUTOCOLL_RF_TECHNOLOGY_MASK_ISO18092_ACTIVE    /**< Maximum value for RF technology. */

#define PHHAL_HW_PN5180_AUTOCOLL_RF_TECHNOLOGY_MASK                        (PHHAL_HW_PN5180_AUTOCOLL_RF_TECHNOLOGY_MASK_NFC_A \
                                                                           | PHHAL_HW_PN5180_AUTOCOLL_RF_TECHNOLOGY_MASK_NFC_F \
                                                                           | PHHAL_HW_PN5180_AUTOCOLL_RF_TECHNOLOGY_MASK_ISO18092_ACTIVE \
                                                                           | PHHAL_HW_PN5180_AUTOCOLL_RF_TECHNOLOGY_MASK_NFC_F_ACTIVE)   /**< Mask value for RF technology. */
/*@}*/

/**
* \name PN5180 EPC GEN2 custom definitions.
* To be used with
* #phhalHw_Pn5180_Instr_EpcGen2Inventory,
* #phhalHw_Pn5180_Instr_EpcGen2RetrieveResultSize,
* #phhalHw_Pn5180_Instr_EpcGen2RetrieveResult,
* #phhalHw_Pn5180_Instr_EpcGen2ResumeInventory.
*/
/*@{*/
#define PHHAL_HW_PN5180_MIN_SELECT_COMMAND_LENGTH                          1U    /**< Minimum length of Select command. */
#define PHHAL_HW_PN5180_MAX_SELECT_COMMAND_LENGTH                          39U   /**< Maximum length of Select command. */
#define PHHAL_HW_PN5180_BEGIN_COMMAND_LENGTH                               03U   /**< length of Begin command. */

#define PHHAL_HW_PN5180_MAX_NUM_OF_BITS_FOR_LAST_BYTE                      7U    /**< Maximum number of bits to be transmitted in the last byte of \p pSelectCommand. 0 in case all bits shall be transmitted, otherwise 1-7. */
#define PHHAL_HW_PN5180_MAX_EPC_GEN2_TIMESLOT                              (PHHAL_HW_PN5180_EPC_GEN2_TIMESLOT_SINGLE_SELECT_TAG) /**< Maximum EPC GEN2 TIMESLOT parameter. */
/*@}*/

/**
 * \name PN5180 RF configuration custom definitions.
 * To be used with
 * #phhalHw_Pn5180_Instr_LoadRfConfiguration,
 * #phhalHw_Pn5180_Instr_UpdateRfConfiguration,
 * #phhalHw_Pn5180_Instr_RetrieveRfConfigurationSize,
 * #phhalHw_Pn5180_Instr_RetrieveRfConfiguration.
 */
/*@{*/
#define PHHAL_HW_PN5180_MIN_RF_TX_CONFIGURATION_INDEX                      0x00U  /**< Minimum RF configuration index for TX. */
#define PHHAL_HW_PN5180_MAX_RF_TX_CONFIGURATION_INDEX                      0x1CU  /**< Maximum RF configuration index for TX. */
#define PHHAL_HW_PN5180_MIN_RF_RX_CONFIGURATION_INDEX                      0x80U  /**< Minimum RF configuration index for RX. */
#define PHHAL_HW_PN5180_MAX_RF_RX_CONFIGURATION_INDEX                      0x9DU  /**< Maximum RF configuration index for RX. */
#define PHHAL_HW_PN5180_MAX_RF_CONFIGURATION_INDEX                         PHHAL_HW_PN5180_MAX_RF_RX_CONFIGURATION_INDEX   /**< Maximum RF configuration index. */
#define PHHAL_HW_PN5180_CURRENT_RF_CONFIGURATION_INDEX                     0xFFU  /**< Current RF configuration index for TX/RX. */
#define PHHAL_HW_PN5180_RF_CONFIGURATION_SIZE                              6U    /**< Size of a single RF configuration
                                                                                      1 Byte Rx or Tx configuration index
                                                                                      1 Byte Register address within the RF configuration
                                                                                      4 Bytes value to be written into the register. */
#define PHHAL_HW_PN5180_RETRIEVE_RF_EACH_CONFIGURATION                     5U    /**< Size of a single RF configuration
                                                                                      1 Byte Register address within the RF configuration
                                                                                      4 Bytes value of the register. */

#define PHHAL_HW_PN5180_RETRIEVE_RF_CONFIGURATION_SIZE_RESPONSE             1U
#define PHHAL_HW_PN5180_MAX_RF_CONFIGURATION_SIZE                          252U  /**< Maximum size of the RF configurations. It must be a multiple of #PHHAL_HW_PN5180_RF_CONFIGURATION_SIZE. */
#define PHHAL_HW_PN5180_MAX_RF_REGS                                        0x43U  /**< Max RF config regs- Not in Spec-Discussed with JP. */
#define PHHAL_HW_PN5180_UPDATE_RF_CONFIG_FIXED_CMD_BYTES                   2U

/*@}*/

/**
* \name PN5180 Load Configuration for Tx and Rx baudrates/reg values.
* To be used with
* #phhalHw_Pn5180_ApplyProtocolSettings.
* #phhalHw_Pn5180_SetCardMode.
*/
/*@{*/
#define PHHAL_HW_PN5180_RF_TX_ISO14443A_106_MILLER                      0U      /**< Type A baud rate @ 106 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_ISO14443A_212_MILLER                      1U      /**< Type A baud rate @ 212 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_ISO14443A_424_MILLER                      2U      /**< Type A baud rate @ 424 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_ISO14443A_848_MILLER                      3U      /**< Type A baud rate @ 848 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_ISO14443B_106_NRZ                         4U      /**< Type B baud rate @ 106 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_ISO14443B_212_NRZ                         5U      /**< Type B baud rate @ 212 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_ISO14443B_424_NRZ                         6U      /**< Type B baud rate @ 424 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_ISO14443B_848_NRZ                         7U      /**< Type B baud rate @ 848 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_FELICA_212                                8U      /**< Type F baud rate @ 212 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_FELICA_424                                9U      /**< Type F baud rate @ 484 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_NFC_AI_106_106                            0x0AU   /**< Active Initiator baud rate @ 106 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_NFC_AI_212_212                            0x0BU   /**< Active Initiator baud rate @ 212 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_NFC_AI_424_424                            0x0CU   /**< Active Initiator baud rate @ 424 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_ISO15693_26_1OF4_ASK100                   0x0DU   /**< Type V (ISO 15693 ) load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_ISO15693_26_1OF4_ASK10                    0x0EU   /**< Type V (ISO 15693 ) load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_ISO180003M3_TARI_18_88_ASK                0x0FU   /**< ISO 18000P3M3 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_ISO180003M3_TARI_9_44_ASK                 0x10U   /**< ISO 18000P3M3 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_ISO14443A_PICC_106_MANCH_SUBC             0x13U   /**< Type A Card mode baud rate @ 106 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_ISO14443A_PICC_212_BPSK                   0x14U   /**< Type A Card mode baud rate @ 212 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_ISO14443A_PICC_424_BPSK                   0x15U   /**< Type A Card mode baud rate @ 424 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_ISO14443A_PICC_848_BPSK                   0x16U   /**< Type A Card mode baud rate @ 848 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_NFC_PT_212                                0x17U   /**< Passive Target baud rate @ 212 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_NFC_PT_424                                0x18U   /**< Passive Target baud rate @ 424 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_NFC_AT_106                                0x19U   /**< Active Target baud rate @ 106 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_NFC_AT_212                                0x1AU   /**< Active Target baud rate @ 212 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_NFC_AT_424                                0x1BU   /**< Active Target baud rate @ 424 load configurations TX Value.*/
#define PHHAL_HW_PN5180_RF_TX_GTM_All_Al                                0x1CU   /**< General Target Mode configuration.*/


#define PHHAL_HW_PN5180_RF_RX_ISO14443A_106_MANCH_SUBC                  0x80U   /**< Type A baud rate @ 106 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO14443A_212_BPSK                        0x81U   /**< Type A baud rate @ 212 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO14443A_424_BPSK                        0x82U   /**< Type A baud rate @ 424 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO14443A_848_BPSK                        0x83U   /**< Type A baud rate @ 848 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO14443B_106_BPSK                        0x84U   /**< Type B baud rate @ 106 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO14443B_212_BPSK                        0x85U   /**< Type B baud rate @ 212 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO14443B_424_BPSK                        0x86U   /**< Type B baud rate @ 424 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO14443B_848_BPSK                        0x87U   /**< Type B baud rate @ 848 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_FELICA_212                                0x88U   /**< Type F baud rate @ 212 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_FELICA_424                                0x89U   /**< Type F baud rate @ 424 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_NFC_AI_106                                0x8AU   /**< Active Initiator @ baud rate 106 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_NFC_AI_212                                0x8BU   /**< Active Initiator @ baud rate 212 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_NFC_AI_424                                0x8CU   /**< Active Initiator @ baud rate 424 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO15693_26_1OF4_SC                       0x8DU   /**< Type V (ISO 15693 ) load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO15693_53_1OF4_SC                       0x8EU   /**< Type V (ISO 15693 ) load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO180003M3_MANCH424_4_PERIOD             0x8FU   /**< ISO 18000P3M3 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO180003M3_MANCH424_2_PERIOD             0x90U   /**< ISO 18000P3M3 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO180003M3_MANCH848_4_PERIOD             0x91U   /**< ISO 18000P3M3 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO180003M3_MANCH848_2_PERIOD             0x92U   /**< ISO 18000P3M3 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO14443A_PICC_106_MILLER                 0x93U   /**< Type A Card mode baud rate @ 106 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO14443A_PICC_212_MILLER                 0x94U   /**< Type A Card mode baud rate @ 212 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO14443A_PICC_424_MILLER                 0x95U   /**< Type A Card mode baud rate @ 424 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_ISO14443A_PICC_848_MILLER                 0x96U   /**< Type A Card mode baud rate @ 848 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_NFC_PT_212                                0x97U   /**< Passive Target baud rate @ 212 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_NFC_PT_424                                0x98U   /**< Passive Target baud rate @ 424 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_NFC_AT_106                                0x99U   /**< Active Initiator baud rate @ 106 load configurations RX Value. */
#define PHHAL_HW_PN5180_RF_RX_NFC_AT_212                                0x9AU   /**< Active Initiator baud rate @ 212 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_NFC_AT_424                                0x9BU   /**< Active Initiator baud rate @ 424 load configurations RX Value.*/
#define PHHAL_HW_PN5180_RF_RX_GTM_All_All                               0x9CU   /**< General Target Mode configuration.*/
/*@}*/


/**
  * \name PN5180 EEPROM custom definitions.
  * To be used with
  * #phhalHw_Pn5180_Instr_WriteE2Prom.
  */
/*@{*/
#define PHHAL_HW_PN5180_WRITE_E2PROM_FIXED_CMD_BYTES                       3U
/*@}*/

/**
    * \name PN5180 ConfigureTestBus custom definitions.
    * To be used with
    * #phhalHw_Pn5180_Instr_ConfigureTestBusDigital.
    */
/*@{*/
#define PHHAL_HW_PN5180_CONFIGURE_TESTBUS_DIGITAL_FIXED_CMD_BYTES                       2U
#define PHHAL_HW_PN5180_CONFIGURE_TESTBUS_ANALOG_CMD_BYTES                              3U
/*@}*/


/**
* \name LPCD configuration
*/
/*@{*/

#define PHHAL_HW_CONFIG_SET_LPCD_WAKEUPTIME_MS  0x0070U     /**< Used value for wakeup counter in msecs, i.e. after this amount of time IC will wakes up from standby. */
#define PHHAL_HW_CONFIG_LPCD_MODE               0x0071U     /**< Used to set options  PHHAL_HW_PN5180_LPCD_MODE_DEFAULT or PHHAL_HW_PN5180_LPCD_MODE_POWERDOWN */
#define PHHAL_HW_CONFIG_LPCD_REF                0x0072U     /**< Used to set or get LPCD Ref */

/*@}*/

/**
* \name LPCD modes
*/
/*@{*/
#define PHHAL_HW_PN5180_LPCD_MODE_DEFAULT            0x00U  /**< Default mode. Try LPCD until timeout is reached. */
#define PHHAL_HW_PN5180_LPCD_MODE_POWERDOWN          0x01U  /**< Powers down the IC for a certain amount of time and performs LPC after wakeup.
                                                                 If no card is found the IC is powered down again and the procedure is restarted.
                                                                 If a card is found the function returns and the IC remains powered up. */
/*@}*/

#endif  /* PHHALHW_PN5180_INSTR_H */
