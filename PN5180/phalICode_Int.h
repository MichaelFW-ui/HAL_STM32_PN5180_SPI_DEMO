/*
 *         Copyright (c), NXP Semiconductors Bangalore / India
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
 * Internal functions of both Software and SamNonX implementation of ICode (R) application layer.
 * $Author: nxp99556 $
 * $Revision: 2536 $ (v05.22.00)
 * $Date: 2017-01-02 12:00:04 +0530 (Mon, 02 Jan 2017) $
 *
 * History:
 *  CHu: Generated 02. January 2017
 *
 */

#ifndef PHALICODE_INT_H
#define PHALICODE_INT_H

/** ICode product's command codes. */
#define PHAL_ICODE_CMD_INVENTORY                                    0x01U    /**< 盘存 */
#define PHAL_ICODE_CMD_STAY_QUIET                                   0x02U    /**< 使激活的标签进入静默模式 */
#define PHAL_ICODE_CMD_SELECT                                       0x25U    /**< 多盘存时用于选中一个标签（选中后才能够进行读写快，单盘存不需要此命令）*/

/* 0X03~0X1F 期间的值为保留命令未使用 */

#define PHAL_ICODE_CMD_READ_SINGLE_BLOCK                            0x20U    /**< ICode command code for ReadSingleBlock command. */
#define PHAL_ICODE_CMD_WRITE_SINGLE_BLOCK                           0x21U    /**< ICode command code for WriteSingleBlock command. */
#define PHAL_ICODE_CMD_LOCK_BLOCK                                   0x22U    /**< ICode command code for LockBlock command. */
#define PHAL_ICODE_CMD_READ_MULTIPLE_BLOCKS                         0x23U    /**< ICode command code for ReadMultipleBlock command. */
#define PHAL_ICODE_CMD_WRITE_AFI                                    0x27U    /**< ICode command code for WriteAFI command. */
#define PHAL_ICODE_CMD_LOCK_AFI                                     0x28U    /**< ICode command code for LockAFI command. */
#define PHAL_ICODE_CMD_WRITE_DSFID                                  0x29U    /**< ICode command code for WriteDSFID command. */
#define PHAL_ICODE_CMD_LOCK_DSFID                                   0x2AU    /**< ICode command code for LockDSFID command. */
#define PHAL_ICODE_CMD_GET_SYSTEM_INFORMATION                       0x2BU    /**< ICode command code for GetSystemInformation command. */
#define PHAL_ICODE_CMD_GET_MULTIPLE_BLOCK_SECURITY_STATUS           0x2CU    /**< ICode command code for GetMultipleBlockSecurityStatus command. */
#define PHAL_ICODE_CMD_FAST_READ_MULTIPLE_BLOCKS                    0x2DU    /**< ICODE command code for FastReadMultipleBlocks command. */
#define PHAL_ICODE_CMD_EXTENDED_READ_SINGLE_BLOCK                   0x30U    /**< ICode command code for ExtendedReadSingleBlock command. */
#define PHAL_ICODE_CMD_EXTENDED_WRITE_SINGLE_BLOCK                  0x31U    /**< ICode command code for ExtendedWriteSingleBlock command. */
#define PHAL_ICODE_CMD_EXTENDED_LOCK_BLOCK                          0x32U    /**< ICode command code for ExtendedLockSingleBlock command. */
#define PHAL_ICODE_CMD_EXTENDED_READ_MULTIPLE_BLOCKS                0x33U    /**< ICode command code for ExtendedReadMultipleBlock command. */
#define PHAL_ICODE_CMD_AUTHENTICATE                                 0x35U    /**< ICODE command code for Authenticate command. */
#define PHAL_ICODE_CMD_CHALLENGE                                    0x39U    /**< ICODE command code for Challenge command. */
#define PHAL_ICODE_CMD_READ_BUFFER                                  0x3AU    /**< ICODE command code for Read Buffer command. */
#define PHAL_ICODE_CMD_EXTENDED_GET_SYSTEM_INFORMATION              0x3BU    /**< ICODE command code for ExtendedGetSystemInformation command. */
#define PHAL_ICODE_CMD_EXTENDED_GET_MULTIPLE_BLOCK_SECURITY_STATUS  0x3CU    /**< ICODE command code for ExtendedGetMultipleBlockSecurityStatus command. */
#define PHAL_ICODE_CMD_EXTENDED_FAST_READ_MULTIPLE_BLOCKS           0x3DU    /**< ICODE command code for ExtendedFastReadMultipleBlocks command. */
#define PHAL_ICODE_CMD_SET_EAS                                      0xA2U    /**< ICode command code for SetEAS command. */
#define PHAL_ICODE_CMD_RESET_EAS                                    0xA3U    /**< ICode command code for ResetEAS command. */
#define PHAL_ICODE_CMD_LOCK_EAS                                     0xA4U    /**< ICode command code for LockEAS command. */
#define PHAL_ICODE_CMD_EAS_ALARM                                    0xA5U    /**< ICode command code for EASAlarm command. */
#define PHAL_ICODE_CMD_PASSWORD_PROTECT_EAS_AFI                     0xA6U    /**< ICode command code for PasswordProtectEAS command. */
#define PHAL_ICODE_CMD_WRITE_EAS_ID                                 0xA7U    /**< ICode command code for WriteEASID command. */
#define PHAL_ICODE_CMD_READ_EPC                                     0xA8U    /**< ICode command code for ReadEPC command. */
#define PHAL_ICODE_CMD_GET_NXP_SYSTEM_INFORMATION                   0xABU    /**< ICode command code for GetNXPSystemInformation command. */
#define PHAL_ICODE_CMD_GET_RANDOM_NUMBER                            0xB2U    /**< ICode command code for GetRandomNumber command. */
#define PHAL_ICODE_CMD_SET_PASSWORD                                 0xB3U    /**< ICode command code for SetPassword command. */
#define PHAL_ICODE_CMD_WRITE_PASSWORD                               0xB4U    /**< ICode command code for WritePassword command. */
#define PHAL_ICODE_CMD_LOCK_PASSWORD                                0xB5U    /**< ICode command code for LockPassword command. */
#define PHAL_ICODE_CMD_PROTECT_PAGE                                 0xB6U    /**< ICode command code for ProtectPage command. */
#define PHAL_ICODE_CMD_LOCK_PAGE_PROTECTION_CONDITION               0xB7U    /**< ICode command code for LockPageProtectionCondition command. */
#define PHAL_ICODE_CMD_GET_MULTIPLE_BLOCK_PROTECTION_STATUS         0xB8U    /**< ICode command code for GetMultipleBlockProtectionStatus command. */
#define PHAL_ICODE_CMD_DESTROY                                      0xB9U    /**< ICode command code for Destroy command. */
#define PHAL_ICODE_CMD_ENABLE_PRIVACY                               0xBAU    /**< ICode command code for EnablePrivacy command. */
#define PHAL_ICODE_CMD_64_BIT_PASSWORD_PROTECTION                   0xBBU    /**< ICode command code for 64-BitPasswordProtection command. */
#define PHAL_ICODE_CMD_READ_SIGNATURE                               0xBDU    /**< ICode command code for ReadSignature command. */
#define PHAL_ICODE_CMD_READ_CONFIG                                  0xC0U    /**< ICODE command code for Read Config command. */
#define PHAL_ICODE_CMD_WRITE_CONFIG                                 0xC1U    /**< ICODE command code for Write Config command. */
#define PHAL_ICODE_CMD_PICK_RANDOM_ID                               0xC2U    /**< ICODE command code for Pick Random Id command. */
#define PHAL_ICODE_RANDOM_NUMBER_SIZE                               0x0AU   /**< Authenticate and Challenge Random number size. */
#define PHAL_ICODE_BLOCK_SIZE                                       4U      /**< Bytes available in one block. */
#define PHAL_ICODE_MAX_BLOCKS                                       256U    /**< Maximum blocks supported by I15693 specification. */
#define PHAL_ICODE_MAX_BLOCKS_EXTENDED                              512U    /**< Maximum blocks supported by I15693 specification for Extended operations. */
#define PHAL_ICODE_MAX_BLOCKS_CM1_OPTION_FLAG_NOT_SET               60U     /**< Maimum block data that can be read using CM1 reader when Option flag is not set. */
#define PHAL_ICODE_MAX_BLOCKS_CM1_OPTION_FLAG_SET                   40U     /**< Maimum block data that can be read using CM1 reader when Option flag is set. */

/** Authenticate constants for Tag and mutual authentication. */
#define PHAL_ICODE_CONST_TAM1                                       0x96C5U /**< Macro value for Tag authentication 1 constant value. */
#define PHAL_ICODE_CONST_MAM1                                       0xDA83U /**< Macro value for Mutual authentication 1 constant value. */
#define PHAL_ICODE_CONST_MAM2                                       0xDA80U /**< Macro value for Mutual authentication 2 constant value. */

#define PHAL_ICODE_AUTHPROC_TAM                                     0x00U   /**< Macro value for authentication option as Tag Authentication. */
#define PHAL_ICODE_AUTHPROC_MAM                                     0x02U   /**< Macro value for authentication option as Mutual Authentication. */
#define PHAL_ICODE_CSI                                              0x00U   /**< Macro to represent the value of the CSI (AES Crypto Suite). */
#define PHAL_ICODE_TAM_CUSTOMDATA_CLEAR                             0x00U   /**< Macro to represent the custom data value for Tag authentication cleared. */
#define PHAL_ICODE_TAM_CUSTOMDATA_SET                               0x01U   /**< Macro to represent the custom data value for Tag authentication set. */
#define PHAL_ICODE_MAM1_STEP                                        0x00U   /**< Macro to represent the first step value for Mutual authentication. */
#define PHAL_ICODE_MAM2_STEP                                        0x04U   /**< Macro to represent the first second value for Mutual authentication. */

#endif
