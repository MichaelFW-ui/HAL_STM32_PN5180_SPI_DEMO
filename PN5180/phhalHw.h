/*
*         Copyright (c), NXP Semiconductors Gratkorn / Austria
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
* particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

/** \file
* Generic HAL component of Reader Library Framework.
* $Author$
* $Revision$ (v05.22.00)
* $Date$
*
* History:
*  SA: Generated 10. July 2015
*
*/

#ifndef PHHALHW_H
#define PHHALHW_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \defgroup phhalHw_Pn5180 component : Pn5180
 * \brief Pn5180 HAL component
 *
 * @{
 */
#define PHHAL_HW_PN5180_ID                          0x0EU        /**< ID for PN5180 HAL component */
#define PHHAL_HW_PN5180_DEFAULT_TIMEOUT             150U         /**< Default timeout in microseconds. */
#define PHHAL_HW_PN5180_DEFAULT_TIMEOUT_MILLI       50U          /**< Default timeout in milliseconds */
#define PHHAL_HW_PN5180_SHADOW_COUNT                0x10U        /**< Pn5180 Shadow Register count */
#define INSTR_BUFFER_SIZE                           262U         /**< Used to form commands 259-Max buf size in writeregmultiple */
#define PHHAL_HW_PN5180_DEFAULT_FELICA_EMD_REGISTER 0x00FF0019U  /**< FeliCa EMD Control register default value */


/** \defgroup phhalHw Hardware Abstraction Layer
* \brief These are the components which are used to abstract the
* functionality of the physical reader device to a generic interface.
*
* HAL API usage in common use cases are described in the sequence diagrams below
*
* <strong>Reader mode:</strong> This sequence diagram describes the usage of HAL APIs to
* implement a simple reader mode application.
* \image html HAL_ReaderMode.png
*
* <strong>Passive initiator mode:</strong> This sequence diagram describes the usage of HAL APIs to
* implement a simple ISO 18092 Initiator in \n
* passive communication mode.
* \image html HAL_PassiveInitiator.png
*
* <strong>Card mode:</strong> This sequence diagram describes the usage of HAL APIs to
* implement a ISO 14443-3A PICC / ISO 18092 passive target.
* \image html HAL_CardMode.png
*
* <strong>Active initiator:</strong> This sequence diagram describes the usage of HAL APIs to
* implement ISO 18092 initiator in active communication mode.
* \image html HAL_ActiveInitiator.png
*
* <strong>Active target:</strong> This sequence diagram describes the usage of HAL APIs to
* implement ISO 18092 target in active communication mode.
* \image html HAL_ActiveTarget.png
*
* <strong>Low power card detection(LPCD):</strong> This sequence diagram describes the usage of HAL APIs to
* implement a simple ISO/IEC 14443-3a \n
* reader that uses LPCD functionality of reader IC.
* \image html HAL_Lpcd.png
*
* <strong>ISO 18000P3M3 Inventory:</strong> This sequence diagram describes the usage of HAL APIs to
* implement a simple application that \n
* inventories and activates an ISO 18000p3m3 tag.
* \image html HAL_I18000p3m3Inventory.png
*
* <strong>ISO 18000P3M3 Resume Inventory:</strong> This sequence diagram describes the usage of HAL APIs to
* implement a simple application that \n
* inventories and activates an ISO 18000p3m3 tag.\n
* In this specific diagram, it is shown how to use \ref phhalHw_I18000p3m3ResumeInventory() API.
* \image html HAL_I18000p3m3Resume.png
*
* <strong>OSAL usage in HAL:</strong> This sequence diagram describes the usage of OS event
* from within the HAL. \n
* HAL uses OSAL call to wait for a CLIF event that is triggered by a CLIF interrupt.\n
* \image html HAL_Osal.png
*
* @{
*/

/**
* \name Communication configuration parameters \n
*  These parameters are used to configure hardware/HAL
*  in a particular manner before performing an operation.
*/
/*@{*/

/**
 * Enable (#PH_ON) or Disable (#PH_OFF) Parity.\n
 *
 * */
#define PHHAL_HW_CONFIG_PARITY                    0x0000U

/**
 * Enable (#PH_ON) or disable (#PH_OFF) transmit CRC.\n
 *
 * */
#define PHHAL_HW_CONFIG_TXCRC                     0x0001U

/**
 * Enable (#PH_ON) or disable (#PH_OFF) receive CRC.\n
 *
 *
 * */
#define PHHAL_HW_CONFIG_RXCRC                     0x0002U

/**
 * Set number of valid bits for the last transmitted byte.
 * Valid range is 1 to 7
 * */
#define PHHAL_HW_CONFIG_TXLASTBITS                0x0003U

/**
 * Get number of valid bits of last received byte.
 * Valid range is 0 to 7
 * */
#define PHHAL_HW_CONFIG_RXLASTBITS                0x0004U

/**
 * Set Rx-Aligned Bits. Used for reception of bit oriented frames.
 * RxAlign defines the bit position for the first bit received to be stored in the FIFO.
 * Further received bits are stored at the following bit positions.
 * Used only for bitwise anti-collision at 106kbps. For all other modes it is set to logic 0.
 * */
#define PHHAL_HW_CONFIG_RXALIGN                   0x0005U

/**
 * Configure receiver deaf-time (time after a send where every reception is ignored) in microseconds.
 * This is the time for which the IC cannot receive any data after transmit.
 * */
#define PHHAL_HW_CONFIG_RXWAIT_US                 0x0006U

/**
 * Set Tx wait time (time between last RxIrq and Tx of succeeding frame) in microseconds.\n
 *
 * */
#define PHHAL_HW_CONFIG_TXWAIT_US                 0x0007U

/**
 * Configure data-rate and framing for transmission.\n
 * Use LSB for data-rate and MSB to specify framing.\n
 * MSB values can be #PHHAL_HW_RF_TYPE_A_FRAMING, #PHHAL_HW_RF_TYPE_B_FRAMING, #PHHAL_HW_RF_TYPE_F_FRAMING\n
 * LSB values can be #PHHAL_HW_RF_DATARATE_106, #PHHAL_HW_RF_DATARATE_212, #PHHAL_HW_RF_DATARATE_424, #PHHAL_HW_RF_DATARATE_848\n
 *
 * */
#define PHHAL_HW_CONFIG_TXDATARATE_FRAMING        0x0009U

/**
 * Enable or disable clearing of bits after collision.
 * Deprecated. Not used anymore.
 * */
#define PHHAL_HW_CONFIG_CLEARBITSAFTERCOLL        0x0008U

/**
 * Configure data-rate and framing for reception.
 * Use LSB for data-rate and MSB to specify framing.\n
 * MSB values can be #PHHAL_HW_RF_TYPE_A_FRAMING, #PHHAL_HW_RF_TYPE_B_FRAMING, #PHHAL_HW_RF_TYPE_F_FRAMING\n
 * LSB values can be #PHHAL_HW_RF_DATARATE_106, #PHHAL_HW_RF_DATARATE_212, #PHHAL_HW_RF_DATARATE_424, #PHHAL_HW_RF_DATARATE_848\n
 * */
#define PHHAL_HW_CONFIG_RXDATARATE_FRAMING        0x000AU

/**
 * Set modulation index (unit and value are hardware-dependent).\n
 *
 * Example values are \n
 * \li #PHHAL_HW_RC663_MODINDEX_I14443B \n
 * \li #PHHAL_HW_RC663_MODINDEX_I15693  \n
 * \li #PHHAL_HW_RC663_MODINDEX_EPCUID  \n
 * \li #PHHAL_HW_RC663_MODINDEX_I18000P3M3\n
 *
 *
 * */
#define PHHAL_HW_CONFIG_MODINDEX                  0x000BU

/**
 * Enable (#PH_ON) or disable (#PH_OFF) 100% modulation.\n
 *
 * */
#define PHHAL_HW_CONFIG_ASK100                    0x000CU

/**
 * Set RC timeout (in [us]).\n
 *
 * Note: Timers will be configured as FWT/FDT timers only after phhalHw_ApplyProtocolSettings() API is called.
 * */
#define PHHAL_HW_CONFIG_TIMEOUT_VALUE_US          0x000DU

/**
 * Set RC timeout (in [ms]).\n
 *
 * Note: Timers will be configured as FWT/FDT timers only after phhalHw_ApplyProtocolSettings() API is called.
 * */
#define PHHAL_HW_CONFIG_TIMEOUT_VALUE_MS          0x000EU

/**
 * Sub-carrier setting for ISO 15693.
 * Possible values are\n
 *     #PHHAL_HW_SUBCARRIER_SINGLE,\n
 *     #PHHAL_HW_SUBCARRIER_DUAL,\n
 *     #PHHAL_HW_SUBCARRIER_QUAD\n
 * */
#define PHHAL_HW_CONFIG_SUBCARRIER                0x000FU

/**
 * Set the field off time for field-reset ([ms]); \b Note: A value of \c 0 is not allowed.\n
 * Default value is #PHHAL_HW_FIELD_OFF_DEFAULT
 * */
#define PHHAL_HW_CONFIG_FIELD_OFF_TIME            0x0013U

/**
 * Set the field recovery time for field-reset ([ms]); \b Note: For ISO15693 operation, this should be at least set to \c 1ms.\n
 * Default value is #PHHAL_HW_FIELD_RECOVERY_DEFAULT
 * */
#define PHHAL_HW_CONFIG_FIELD_RECOVERY_TIME       0x0014U

/**
 * Disable / Set the SOF symbol of a frame.
 * Sets the start of frame symbol for a frame for ICODE EPIC UID, ISO 15693, ISO 18000p3m3. The values can be one of:\n
 * \li #PH_OFF - Disable SoF\n
 * \li #PHHAL_HW_SYMBOL_ICODEEPCUID_SSOF - Short start of frame\n
 * \li #PHHAL_HW_SYMBOL_ICODEEPCUID_LSOF - Long start of frame\n
 * \li #PHHAL_HW_SYMBOL_ICODEEPCUID_CS - Close slot\n
 * \li #PHHAL_HW_SYMBOL_I15693_SOF - SOF for ISO 15693. Automatically chosen between 1/256 and 1/4\n
 * \li #PHHAL_HW_SYMBOL_I18000P3M3_PREAMBLE - ISO 18000p3m3 Preamble\n
 * \li #PHHAL_HW_SYMBOL_I18000P3M3_FSYNC - ISO 18000p3m3 Frame Sync
 *
 * */
#define PHHAL_HW_CONFIG_SYMBOL_START              0x0015U

/**
 * Disable / Set the EOF symbol of a frame.
 * Sets the end of frame symbol for a frame for ICODE EPIC UID protocol.\n
 * #PH_OFF - Disable EoF\n
 * #PHHAL_HW_SYMBOL_ICODEEPCUID_CEOF - Common end of frame\n
 *
 * */
#define PHHAL_HW_CONFIG_SYMBOL_END                0x0016U

/**
 * Sets the CRC type for Tx(#PHHAL_HW_CONFIG_TXCRC) and Rx(#PHHAL_HW_CONFIG_RXCRC).
 * Values can be one of\n
 * #PHHAL_HW_CRCTYPE_CRC5,\n
 * #PHHAL_HW_CRCTYPE_CRC16\n
 * optionally combined with the following inversion option.\n
 * #PHHAL_HW_CRCOPTION_INVERTED.
 *
 * */
#define PHHAL_HW_CONFIG_CRCTYPE                   0x0017U

/**
 * Set TxWait (time between last RxIrq and transmit start of succeeding frame) in milliseconds.\n
 *
 * */
#define PHHAL_HW_CONFIG_TXWAIT_MS                 0x0018U

/**
 * Set the #PH_ON/#PH_OFF Jewel exchange mode.
 * This should be done by user before T1T/Jewel functions are called.
 * */
#define PHHAL_HW_CONFIG_JEWEL_MODE                0x0020U

/**
 * Get config to get the card type.
 * */
#define PHHAL_HW_CONFIG_CARD_TYPE                   0x0021U

/**
 * Disable MIFARE(R) Classic Crypto1.\n
 * Disables the MIFARE Classic Crypto 1 in the IC. Only value PH_OFF is allowed.\n
 * The MIFARE Classic Crypto 1 will be enabled by the MFAuthent command. This bit cannot be set by software.
 * */
#define PHHAL_HW_CONFIG_DISABLE_MF_CRYPTO1        0x002EU

/**
 * Set/Get an offset value\n
 * A value at this offset on HAL Tx Buffer can be read or written by using\n
 * Get/Set(#PHHAL_HW_CONFIG_TXBUFFER) once the offset is set using this parameter.\n
 * Used by Protocol components.
 * */
#define PHHAL_HW_CONFIG_TXBUFFER_OFFSET           0x002FU

/**
 * Set/Get start position of RX buffer to be used (never changed by HAL).\n
 *
 * */
#define PHHAL_HW_CONFIG_RXBUFFER_STARTPOS         0x0030U

/**
 * Get size of Rx buffer set at HAL initialization. This is read-only parameter.\n
 * Used by protocols to know the Rx buffer size for chaining purposes.
 * */
#define PHHAL_HW_CONFIG_RXBUFFER_BUFSIZE          0x0031U

/**
 * Get size of TX buffer set at HAL initialization. This is read-only parameter.\n
 * Used by protocols to know the TxBuffer size.
 * */
#define PHHAL_HW_CONFIG_TXBUFFER_BUFSIZE          0x0032U

/**
 * Set/Get the amount of valid bytes in Tx buffer. \n
 *
 * */
#define PHHAL_HW_CONFIG_TXBUFFER_LENGTH           0x0033U

/**
 * Access the transmit buffer(TxBuffer) at the byte offset defined by #PHHAL_HW_CONFIG_TXBUFFER_OFFSET.\n
 * Used to get or set two bytes from/to a particular position in TxBuffer.\n
 * The position in transmit buffer is defined by setting TXBUFFER_OFFSET.\n
 * Used by protocol components.
 * */
#define PHHAL_HW_CONFIG_TXBUFFER                  0x0034U

/**
 * Sets, configures and start the guard time to send Poll commands. When SetConfig with this Key is performed timer is started
 * but will not wait till timer to expire. Exchange or I18000p3m3Inventory API should wait till this timer is expired before
 * transmitting Poll Frame. Also exchange API should stop this timer if there is any error in exchange API.
 *
 * NOTE: \ref phhalHw_Wait API should not be executed after configuring the poll guard time but can be used once again after
 * phhalHw_Exchange() or phhalHw_I18000p3m3Inventory() API is executed.
 * */
#define PHHAL_HW_CONFIG_POLL_GUARD_TIME_US        0x0035U

/**
 * Set/Reset minimum FDT (only for proximity check).\n
 * Used to set minimum frame delay time (timeout) in microseconds as required for proximity check\n
 * command of MIFARE Plus contactless IC.
 *
 * */
#define PHHAL_HW_CONFIG_SETMINFDT                 0x0051U

/**
 * Get the status of external RF field. Returned values are #PH_ON or #PH_OFF.
 * Deprecated.
 * */
#define PHHAL_HW_CONFIG_EXT_RF_ON                 0x0052U

/**
 * Enable (#PH_ON) or disable (#PH_OFF) multiple reception.\n
 * Please refer to phpalFelica.h and phpalFelica_ReqC function documentation to know the
 * frame format in which the data is returned.
 * */
#define PHHAL_HW_CONFIG_RXMULTIPLE                0x0053U

/**
 * Get the status if active communication mode is #PH_ON / #PH_OFF.\n
 * Used by protocols to know the mode.
 *
 * */
#define PHHAL_HW_CONFIG_ACTIVEMODE                0x0054U

/**
 * Set/Reset MFHalted bit in MifNFCReg.\n
 *
 * When set, this indicates that the IC is set to HALT mode in card operation mode at 106 kBit.\n
 * Once set, when \ref phhalHw_Autocoll API is called in card/target mode, will only accept WUPA/ALL_REQ command to respond.
 *
 * */
#define PHHAL_HW_CONFIG_MFHALTED                  0x0055U

/**
 * Enable/disable RF collision avoidance for passive communication mode. (#PH_ON or #PH_OFF).\n
 * This parameter should be set before \ref phhalHw_FieldOn to perform Initial RFCA.
 * By default after IC HAL initialization, this should be set to #PH_ON
 * */
#define PHHAL_HW_CONFIG_RFCA                      0x0056U

/**
 * Enable RF-ON interrupt\n
 *
 * This is typically used in card/target mode. When there is no external RF, this configuration is set in the HAL\n
 * and the controller can go into a wait state for the external RF-ON interrupt to occur.
 *
 * */
#define PHHAL_HW_CONFIG_RFON_INTERRUPT            0x0057U

/**
 * Get the framing and speed at which target is operating.\n
 * Read-only parameter.
 * RF data rate values in the LSB and framing in the MSB are returned.\n
 * MSB values can be #PHHAL_HW_RF_TYPE_A_FRAMING, #PHHAL_HW_RF_TYPE_B_FRAMING, #PHHAL_HW_RF_TYPE_F_FRAMING\n
 * LSB values can be #PHHAL_HW_RF_DATARATE_106, #PHHAL_HW_RF_DATARATE_212, #PHHAL_HW_RF_DATARATE_424\n
 *
 * */
#define PHHAL_HW_CONFIG_TARGET_DATARATE_FRAMING   0x0059U

/**
 * Configure operation mode for this Layer.\n
 * Values can be #RD_LIB_MODE_NFC or #RD_LIB_MODE_EMVCO
 *
 * */
#define PHHAL_HW_CONFIG_OPE_MODE                  0x005AU

/**
 * Enable/Disable handling start byte at 106kbps in NFCIP Mode of communication.\n
 * This is to tell the HAL to prepend the start byte as required for passive\n
 * communication mode at 106kbps.
 *
 * */
#define PHHAL_HW_CONFIG_NFCIP_STARTBYTE           0x005CU

/**
 * Enable symbol send (#PH_ON).\n
 * ISO/IEC 18000p3m3 protocol will use data send (#PH_OFF).
 *
 * */
#define PHHAL_HW_CONFIG_SET_SYMBOL_SEND           0x005DU

/**
 * Enable (#PH_ON) or Disable (#PH_OFF) EMD error check for Emvco.\n
 * The EMD check should be enabled only after ISO 14443A/B layer 3\n
 * activation.
 *
 * */
#define PHHAL_HW_CONFIG_SET_EMD                   0x005EU

/**
 * Get the status of internal RF field. Returned values are #PH_ON or #PH_OFF.
 *
 * */
#define PHHAL_HW_CONFIG_INT_RF_ON                 0x005FU

/*@}*/

/**
* \name IC specific configuration parameters
* These are not applicable to all ICs and
* are not mandatory to be implemented to
* comply with this HAL specification.
*/
/*@{*/

/**
 * Sets the exchange time measurement mode in the IC. The values can be one of:\n
 * #PHHAL_HW_TIMING_MODE_OFF - Time measurement disabled\n
 * #PHHAL_HW_TIMING_MODE_FDT - Frame delay time to be measured\n
 * #PHHAL_HW_TIMING_MODE_COMM - Overall time to be measured\n
 * #PHHAL_HW_TIMING_MODE_OPTION_MASK - Additional option-mask for time measurement.\n
 * #PHHAL_HW_TIMING_MODE_OPTION_DEFAULT - The timing value is accumulated on each exchange until it gets retrieved by phhalHw_GetConfig.\n
 * #PHHAL_HW_TIMING_MODE_OPTION_AUTOCLEAR - Automatically resets the current timing value prior to any communication.
 *
 * */
#define PHHAL_HW_CONFIG_TIMING_MODE               0x8010U

/**
 * Retrieve elapsed time of receive timer ([us]).\n
 *
 * */
#define PHHAL_HW_CONFIG_TIMING_US                 0x8011U

/**
 * Retrieve elapsed time of receive timer ([ms]).\n
 *
 * */
#define PHHAL_HW_CONFIG_TIMING_MS                 0x8012U

/**
 * Enable (#PH_ON) or Disable (#PH_OFF) EMD error check for FeliCa.\n
 *
 * Note1: Before Setting FELICA_EMD bit, OpeMode need to be configured to \ref RD_LIB_MODE_FELICA.\n
 * Note2: FeliCa EMD is available from FW V04.01 and these configurations shall not be used with
 *        PN5180 FW less than V04.00.
 * */
#define PHHAL_HW_PN5180_CONFIG_SET_FELICA_EMD                        0x8025U

/**
 * Enable (#PH_ON) or Disable (#PH_OFF) FeliCa EMD Length check based
 * on Maximum and Minimum Length configuration using \ref PHHAL_HW_PN5180_CONFIG_SET_FELICA_EMD_LEN_BYTE_MAX
 * and \ref PHHAL_HW_PN5180_CONFIG_SET_FELICA_EMD_LEN_BYTE_MIN respectively.\n
 *
 * Note: FeliCa EMD is available from FW V04.01 and these configurations shall not be used with
 *       PN5180 FW less than V04.00.
 * */
#define PHHAL_HW_PN5180_CONFIG_SET_FELICA_EMD_LEN_CHECK              0x8026U

/**
 * Enable (#PH_ON) or Disable (#PH_OFF) FeliCa EMD Response Code check based
 * on Response code that can be configured using \ref PHHAL_HW_PN5180_CONFIG_SET_FELICA_EMD_RC_BYTE_VAL.\n
 *
 * Note: FeliCa EMD is available from FW V04.01 and these configurations shall not be used with
 *       PN5180 FW less than V04.00.
 * */
#define PHHAL_HW_PN5180_CONFIG_SET_FELICA_EMD_RC_CHECK               0x8027U

/**
 * Enable (#PH_ON) or Disable (#PH_OFF) FeliCa EMD Protocol error check.\n
 *
 * Note: FeliCa EMD is available from FW V04.01 and these configurations shall not be used with
 *       PN5180 FW less than V04.00.
 * */
#define PHHAL_HW_PN5180_CONFIG_SET_FELICA_EMD_PROTOCOL_ERR_CHECK     0x8028U

/**
 * Enable (#PH_ON) or Disable (#PH_OFF) FeliCa EMD Integrity error check.\n
 *
 * Note: FeliCa EMD is available from FW V04.01 and these configurations shall not be used with
 *       PN5180 FW less than V04.00.
 * */
#define PHHAL_HW_PN5180_CONFIG_SET_FELICA_EMD_INTEGRITY_ERR_CHECK    0x8029U

/**
 * Configure the Minimum Length Byte value that shall be used by the Reader IC
 * to receive under FeliCa EMD. Response containing Length Byte value lesser than the
 * configured value is treated as EMD error.\n
 *
 * Note: FeliCa EMD is available from FW V04.01 and these configurations shall not be used with
 *       PN5180 FW less than V04.00.
 * */
#define PHHAL_HW_PN5180_CONFIG_SET_FELICA_EMD_LEN_BYTE_MIN           0x802AU

/**
 * Configure the Maximum Length Byte value that shall be used by the Reader IC
 * to receive under FeliCa EMD. Response containing Length Byte value greater than the
 * configured value is treated as EMD error.\n
 *
 * Note: FeliCa EMD is available from FW V04.01 and these configurations shall not be used with
 *       PN5180 FW less than V04.00.
 * */
#define PHHAL_HW_PN5180_CONFIG_SET_FELICA_EMD_LEN_BYTE_MAX           0x802BU

/**
 * Configure the RC Byte value that shall be compared to the received RC byte value in
 * the received FeliCa Response, if comparison fails then Reader IC shall consider
 * the response as EMD error.\n
 *
 * Note: FeliCa EMD is available from FW V04.1 and these configurations shall not be used with
 *       PN5180 FW version less than V04.1.
 * */
#define PHHAL_HW_PN5180_CONFIG_SET_FELICA_EMD_RC_BYTE_VAL            0x802CU

/**
 * Configures the max. number of bytes which are pre-cached prior to command execution.\n
 * Bytes up to the maximum pre-cache limit can be written into the FIFO before the command is started.\n
 * The maximum pre-cache limit depends upon the FIFO size of the IC.\n
 * This will ensure faster transmission in comparison to starting the command and then writing the\n
 * parameters + data to the FIFO. Rc523(Pn512) and Rc663 HALs provide such a functionality.\n
 *
 * */
#define PHHAL_HW_CONFIG_MAX_PRECACHED_BYTES       0x8035U

/**
 * Set the BAL connection type. The default value is always #PHHAL_HW_BAL_CONNECTION_RS232.\n
 * Other supported values are\n
 * #PHHAL_HW_BAL_CONNECTION_SPI\n
 * #PHHAL_HW_BAL_CONNECTION_I2C\n
 * */
#define PHHAL_HW_CONFIG_BAL_CONNECTION            0x8040U

/**
 * Bit rate for serial UART communication for Rc523, CLRC663\n
 * valid values range from - #PHHAL_HW_RS232_BITRATE_9600 to\n
 * #PHHAL_HW_RS232_BITRATE_460800
 * */
#define PHHAL_HW_CONFIG_SERIAL_BITRATE            0x8041U


/**
 * Perform an RF-reset in case of a timeout (only for \ref phhalHw_Exchange)\n
 * Valid values are #PH_ON, #PH_OFF
 * */
#define PHHAL_HW_CONFIG_RFRESET_ON_TIMEOUT        0x8050U

/**
 * Get any additional information that the HAL might provide
 * For example any specific error information.
 *
 * */
#define PHHAL_HW_CONFIG_ADDITIONAL_INFO           0x802FU

/*@}*/


/**
* \name Card Configuration
*/
/*@{*/
#define PHHAL_HW_CARDTYPE_CURRENT               0x0000U /**< Re-Apply settings for current communication mode. */
#define PHHAL_HW_CARDTYPE_ISO14443A             0x0001U /**< ISO/IEC 14443A mode. */
#define PHHAL_HW_CARDTYPE_ISO14443B             0x0002U /**< ISO/IEC 14443B mode. */
#define PHHAL_HW_CARDTYPE_FELICA_212            0x0003U /**< FeliCa (JIS X 6319) mode. */
#define PHHAL_HW_CARDTYPE_ISO15693              0x0004U /**< ISO/IEC 15693 mode. */
#define PHHAL_HW_CARDTYPE_ICODEEPCUID           0x0005U /**< NXP I-Code EPC/UID mode. */
#define PHHAL_HW_CARDTYPE_I18000P3M3            0x0006U /**< ISO/IEC 18000-3 mode3. */
#define PHHAL_HW_CARDTYPE_I18092M_ACTIVE_106    0x0007U /**< ISO/IEC ISO18092 (NFC) initiator mode at 106 baud. */
#define PHHAL_HW_CARDTYPE_I18092M_ACTIVE_212    0x0008U /**< ISO/IEC ISO18092 (NFC) initiator mode at 212 baud. */
#define PHHAL_HW_CARDTYPE_I18092M_ACTIVE_424    0x0009U /**< ISO/IEC ISO18092 (NFC) initiator mode at 424 baud. */
#define PHHAL_HW_CARDTYPE_FELICA_424            0x000AU /**< FeliCa mode at 424 baud. */
#define PHHAL_HW_CARDTYPE_UNKNOWN               0x00FFU /**< Unknown card type. */
/*@}*/

/**
* \name CRC Values
*/
/*@{*/
#define PHHAL_HW_CRCTYPE_CRC5               0x0001U /**< 5 bit length, polynomial x^5+x^3+1U, preset value 01001b, residue 00000b. */
#define PHHAL_HW_CRCTYPE_CRC16              0x0002U /**< ISO/IEC 13239, 16 bit length, polynomial x^16+x^12+x^5+1U, preset value 0xFFFF, residue 0x1D0F. */
#define PHHAL_HW_CRCOPTION_INVERTED         0x0100U /**< To indicate that the CRC generated should be inverted. This should be ORed with the CRCTYPEs above. */
/*@}*/

/**
* \name RF Data rate values
*/
/*@{*/
#define PHHAL_HW_RF_DATARATE_106                0x0000U /**< Data rate setting for 106 kBit/s. */
#define PHHAL_HW_RF_DATARATE_212                0x0001U /**< Data rate setting for 212 kBit/s. */
#define PHHAL_HW_RF_DATARATE_424                0x0002U /**< Data rate setting for 424 kBit/s. */
#define PHHAL_HW_RF_DATARATE_848                0x0003U /**< Data rate setting for 848 kBit/s. */

#define PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_256    0x000AU /**< Data rate setting for ISO15693 '1 out of 256' mode. */
#define PHHAL_HW_RF_TX_DATARATE_1_OUT_OF_4      0x000BU /**< Data rate setting for ISO15693 '1 out of 4' mode. */
#define PHHAL_HW_RF_RX_DATARATE_LOW             0x000CU /**< Data rate setting for ISO15693 low data rate. */
#define PHHAL_HW_RF_RX_DATARATE_HIGH            0x000DU /**< Data rate setting for ISO15693 high data rate. */
#define PHHAL_HW_RF_RX_DATARATE_FAST_LOW        0x000EU /**< Data rate setting for ISO15693 fast (low*2U) data rate (FAST INVENTORY (PAGE) READ). */
#define PHHAL_HW_RF_RX_DATARATE_FAST_HIGH       0x000FU /**< Data rate setting for ISO15693 fast (high*2U) data rate (FAST INVENTORY (PAGE) READ). */
#define PHHAL_HW_RF_I15693_53KBPS_DATARATE      0x001BU /**< Data rate setting for 53 kbps. Used for Testing */
#define PHHAL_HW_RF_DATARATE_EPCUID             0x0010U /**< Data rate setting for EPC/UID. */
#define PHHAL_HW_RF_TX_DATARATE_I18000P3M3      0x0011U    /**< Tx data rate setting for ISO18000-3 mode3. TARI Value = 9.44us*/
#define PHHAL_HW_RF_TX_DATARATE_I18000P3M3_TARI1888      0x0012U    /**< Tx data rate setting for ISO18000-3 mode3. TARI Value = 18.88 us*/

#define PHHAL_HW_RX_I18000P3M3_FL_423_MAN2    0x0013U /**< ICode ISO18000-3 Mode3 424 kBit/s (M=2). */
#define PHHAL_HW_RX_I18000P3M3_FL_847_MAN2    0x0014U /**< ICode ISO18000-3 Mode3 847 kBit/s (M=2). */
#define PHHAL_HW_RX_I18000P3M3_FL_423_MAN4    0x0015U /**< ICode ISO18000-3 Mode3 424 kBit/s (M=4). */
#define PHHAL_HW_RX_I18000P3M3_FL_847_MAN4    0x0016U /**< ICode ISO18000-3 Mode3 847 kBit/s (M=4). */
/*@}*/

/**
* \name RF Framing Mode Values
*/
/*@{*/
#define PHHAL_HW_RF_TYPE_A_FRAMING              0x0100U /**< Data rate setting for 106 kBit/s. */
#define PHHAL_HW_RF_TYPE_B_FRAMING              0x0200U /**< Data rate setting for 212 kBit/s. */
#define PHHAL_HW_RF_TYPE_F_FRAMING              0x0300U /**< Data rate setting for 424 kBit/s. */
#define PHHAL_HW_RF_TYPE_ACTIVE_FRAMING         0x0400U /**< Data rate setting for 848 kBit/s. */

#define PHHAL_HW_RF_DATARATE_OPTION_MASK        0x00FFU /**< Option-mask for data rate. */
#define PHHAL_HW_RF_FRAMING_OPTION_MASK         0xFF00U /**< Option-mask for framing. */
#define PHHAL_HW_RF_TYPE_A_START_BYTE           0xF0U   /**< Start byte used at passive 106kbps. */
/*@}*/

/**
* \name Helper macros used for \ref phhalHw_Autocoll.
* Used to extract data rate and framing values.
*/
/*@{*/
#define PHHAL_HW_GETFRAMING( protParams ) ((protParams) >> 8U)
#define PHHAL_HW_GETBITRATE( protParams ) ((protParams) & 0x00FFU)
/*@}*/

/**
* \name RF sub carrier Values
*/
/*@{*/
#define PHHAL_HW_SUBCARRIER_SINGLE  0x0000U /**< Sub carrier setting for ISO15693 single sub carrier. */
#define PHHAL_HW_SUBCARRIER_DUAL    0x0001U /**< Sub carrier setting for ISO15693 / EPC V2 dual sub carrier. */
#define PHHAL_HW_SUBCARRIER_QUAD    0x0002U /**< Sub carrier setting for EPC V2 quad sub carrier. */
/*@}*/

/**
* \name Time units
*/
/*@{*/
#define PHHAL_HW_TIME_MICROSECONDS  0x0000U /**< Time in microseconds (us). */
#define PHHAL_HW_TIME_MILLISECONDS  0x0001U /**< Time in milliseconds (ms). */
/*@}*/

/**
* \name Timing mode settings
*/
/*@{*/
#define PHHAL_HW_TIMING_MODE_OFF                0x0000U /**< Time measurement disabled. */
#define PHHAL_HW_TIMING_MODE_FDT                0x0001U /**< Measures time from Tx-end until Rx-begin. */
#define PHHAL_HW_TIMING_MODE_COMM               0x0002U /**< Measures the duration of the complete communication. */
#define PHHAL_HW_TIMING_MODE_OPTION_MASK        0xFF00U /**< Additional option-mask for time measurement. */
#define PHHAL_HW_TIMING_MODE_OPTION_DEFAULT     0x0000U /**< The timing value is accumulated on each exchange until it gets retrieved by \ref phhalHw_GetConfig. */
#define PHHAL_HW_TIMING_MODE_OPTION_AUTOCLEAR   0x0100U /**< Automatically resets the current timing value prior to any communication. */
/*@}*/

/**
* \name Field reset default times
*/
/*@{*/
#define PHHAL_HW_FIELD_OFF_DEFAULT          0x0005U     /**< Default field-off time. */
#define PHHAL_HW_FIELD_RECOVERY_DEFAULT     0x0005U     /**< Default field-recovery time. */
/*@}*/

/**
* \name Frame Symbols (use #PH_OFF to disable)
*/
/*@{*/
#define PHHAL_HW_SYMBOL_ICODEEPCUID_SSOF    0x0001U /**< ICode EPC/UID short start of frame. */
#define PHHAL_HW_SYMBOL_ICODEEPCUID_LSOF    0x0002U /**< ICode EPC/UID long start of frame. */
#define PHHAL_HW_SYMBOL_ICODEEPCUID_CEOF    0x0003U /**< ICode EPC/UID common end of frame. */
#define PHHAL_HW_SYMBOL_ICODEEPCUID_CS      0x0004U /**< ICode EPC/UID close slot. */
#define PHHAL_HW_SYMBOL_I15693_SOF          0x0005U /**< ISO15693 SOF (automatically chosen between 1/256 and 1/4). */
#define PHHAL_HW_SYMBOL_I18000P3M3_PREAMBLE 0x0006U /**< ISO18000-3 mode3 preamble. */
#define PHHAL_HW_SYMBOL_I18000P3M3_FSYNC    0x0007U /**< ISO18000-3 mode3 frame-sync. */
/*@}*/

/**
* \name MIFARE Classic authenticate options
*/
/*@{*/
#define PHHAL_HW_MFC_KEYA               0x0AU   /**< MIFARE Classic key type A. */
#define PHHAL_HW_MFC_KEYB               0x0BU   /**< MIFARE Classic key type B. */
#define PHHAL_HW_MFC_KEY_LENGTH         0x06U   /**< Length of a MIFARE Classic key (for completeness). */
/*@}*/

/**
* \name BAL Connection types
*/
/*@{*/
#define PHHAL_HW_BAL_CONNECTION_RS232   0x0000U     /**< Reader IC is connected via RS232. */
#define PHHAL_HW_BAL_CONNECTION_SPI     0x0001U     /**< Reader IC is connected via SPI. */
#define PHHAL_HW_BAL_CONNECTION_I2C     0x0002U     /**< Reader IC is connected via I2C. */
/*@}*/

/**
* \name RS232 Bitrate Values
*/
/*@{*/
#define PHHAL_HW_RS232_BITRATE_7200     0x0000U     /**< 7.200 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_9600     0x0001U     /**< 9.600 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_14400    0x0002U     /**< 14.400 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_19200    0x0003U     /**< 19.200 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_38400    0x0004U     /**< 38.400 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_57600    0x0005U     /**< 57.500 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_115200   0x0006U     /**< 115.200 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_128000   0x0007U     /**< 128.000 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_230400   0x0008U     /**< 230.400 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_460800   0x0009U     /**< 460.800 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_921600   0x000AU     /**< 921.600 kBit/s. */
#define PHHAL_HW_RS232_BITRATE_1228800  0x000BU     /**< 1.228.800 kBit/s. */
/*@}*/

/**
* \name Min FDT values
*/
/*@{*/
#define PHHAL_HW_MINFDT_106_US        91+10         /**< (n * 128 + 84U) / 13.56; n = 9. */
#define PHHAL_HW_MINFDT_212_US        87+40         /**< (n * 128 + 148U) / 13.56; n = 8. */
#define PHHAL_HW_MINFDT_424_US        84+35         /**< (n * 128 + 116U) / 13.56; n = 8. */
#define PHHAL_HW_MINFDT_848_US        83+45         /**< (n * 128 + 100U) / 13.56; n = 8. */
/*@}*/

/**
 * \name Framing mode values
 */
/*@{*/
#define PHHAL_HW_I14443A_106_FRAMING        0x00U    /**< ISO/IEC 14443A and passive communication mode 106 kBit. */
#define PHHAL_HW_ACTIVE_MODE_FRAMING        0x01U    /**< Active communication mode. */
#define PHHAL_HW_FELICA_FRAMING             0x02U    /**< FeliCa and passive communication mode 212 and 424 kBit. */
#define PHHAL_HW_I14443B_FRAMING            0x03U    /**< ISO/IEC 14443B. */
/*@}*/

/**
* \name Target Bit Coding
*/
/*@{*/
#define PHHAL_HW_EMULATE_TYPE_A_TARGET      0x0001U /**< Bit setting to emulate Type A target. */
#define PHHAL_HW_EMULATE_TYPE_B_TARGET      0x0002U /**< Bit setting to emulate Type B target. */
#define PHHAL_HW_EMULATE_TYPE_F_TARGET      0x0004U /**< Bit setting to emulate Type F target. */
/*@}*/

/**
 * \name FeliCa Response Frame Coding \n
 * Applicable when \ref PHHAL_HW_CONFIG_RXMULTIPLE is enable
 */
/*@{*/
#define PHHAL_HW_REQC_MIN_LEN                        19U  /**< Minimum length of valid ReqC response when multiple reception is enabled. */
#define PHHAL_HW_RESP_FRAME_SIZE                     32U  /**< Frame size of one FeliCa response when multiple reception is enable. */
#define PHHAL_HW_STATUS_FRAME_LEN_BYTE_POS           28U  /**< Byte position where length information in FeliCa response frame. */
#define PHHAL_HW_STATUS_FRAME_ERR_BYTE_POS           29U  /**< Byte position where error information in FeliCa response frame. */

#define PHHAL_HW_STATUS_FRAME_CL_ERR_POS        (1U << 0U)  /**< Bit position for contact less Error in FeliCa response frame. */
#define PHHAL_HW_STATUS_FRAME_DATA_ERR_POS      (1U << 1U)  /**< Bit position for data(CRC or Parity) error in FeliCa response frame. */
#define PHHAL_HW_STATUS_FRAME_PROT_ERR_POS      (1U << 2U)  /**< Bit position for protocol error in FeliCa response frame. */
#define PHHAL_HW_STATUS_FRAME_COLL_ERR_POS      (1U << 3U)  /**< Bit position for collision error in FeliCa response frame. */
#define PHHAL_HW_STATUS_FRAME_LEN_ERR_POS       (1U << 4U)  /**< Bit position for length error in FeliCa response frame. */

#define PHHAL_HW_STATUS_FRAME_ERR_MASK             0x1FU  /**< Bit mask for error byte in FeliCa response frame. */
#define PHHAL_HW_STATUS_FRAME_LEN_MASK             0x1FU  /**< Bit mask for Length byte in FeliCa response frame. */
/*@}*/

/**
 * \name Parameter values for ISO/IEC 18000p3m3 HAL APIs \n
 *
 */
/*@{*/
#define PHHAL_HW_I18000P3M3_GET_MAX_RESPS             0U          /**< Gets responses from more than one slots limited by the RX buffer size and number of slots. */
#define PHHAL_HW_I18000P3M3_ONE_TS_ONLY               1U          /**< Gets response for only one time slot */
#define PHHAL_HW_I18000P3M3_GET_TAG_HANDLE            2U          /**< Gets response for only one time slot. Also sends a ReqRN to get the tag handle for this slot. */
#define PHHAL_HW_I18000P3M3_PERFORM_RESIZE            3U          /**< Perform Resize Round */
#define PHHAL_HW_I18000P3M3_SESSION_S0               0x00U       /**< Session S0. */
#define PHHAL_HW_I18000P3M3_SESSION_S2               0x02U       /**< Session S2. */
#define PHHAL_HW_I18000P3M3_TARGET_INVENTORIED_S0    0x00U       /**< INVENTORIED_S0 target. */
#define PHHAL_HW_I18000P3M3_TARGET_INVENTORIED_S2    0x02U       /**< INVENTORIED_S2 target. */
#define PHHAL_HW_I18000P3M3_TARGET_SL                0x04U       /**< SL target. */

#define PHHAL_HW_I18000P3M3_UPDN_INCREMENT           0x06U   /**< Increment Q. */
#define PHHAL_HW_I18000P3M3_UPDN_NOCHANGE            0x00U   /**< Do not change Q. */
#define PHHAL_HW_I18000P3M3_UPDN_DECREMENT           0x03U   /**< Decrement Q. */
#define PHHAL_HW_I18000P3M3_CMD_RESIZE_ROUND         0x09U    /**< ResizeRound command code. */
/*@}*/


#ifdef __cplusplus
} /* Extern C */
#endif

#endif /* PHHALHW_H */
