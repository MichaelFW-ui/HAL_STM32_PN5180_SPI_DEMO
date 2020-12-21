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
* Internal functions for MIFARE Classic contactless IC (R) application layer.
* $Author$
* $Revision$ (v05.22.00)
* $Date$
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PHALMFC_INT_H
#define PHALMFC_INT_H

#define PHAL_MFC_RESP_ACK       0x0AU    /**< MIFARE Classic ACK response code */
#define PHAL_MFC_RESP_NAK0      0x00U    /**< MIFARE Classic NAK0 response code */
#define PHAL_MFC_RESP_NAK1      0x01U    /**< MIFARE Classic NAK1 response code */
#define PHAL_MFC_RESP_NAK4      0x04U    /**< MIFARE Classic NAK4 response code */
#define PHAL_MFC_RESP_NAK5      0x05U    /**< MIFARE Classic NAK5 response code */

#define PHAL_MFC_CMD_RESTORE    0xC2U    /**< MIFARE Classic Restore command byte */
#define PHAL_MFC_CMD_INCREMENT  0xC1U    /**< MIFARE Classic Increment command byte */
#define PHAL_MFC_CMD_DECREMENT  0xC0U    /**< MIFARE Classic Decrement command byte */
#define PHAL_MFC_CMD_TRANSFER   0xB0U    /**< MIFARE Classic Transfer command byte */
#define PHAL_MFC_CMD_READ       0x30U    /**< MIFARE Classic Read command byte */
#define PHAL_MFC_CMD_WRITE      0xA0U    /**< MIFARE Classic Write command byte */
#define PHAL_MFC_CMD_AUTHA      0x60U    /**< MIFARE Classic Authenticate A command byte */
#define PHAL_MFC_CMD_AUTHB      0x61U    /**< MIFARE Classic Authenticate B command byte */
#define PHAL_MFC_CMD_PERSOUID   0x40U    /**< MIFARE Classic Personalize UID command */
#define PHAL_MFC_CMD_GETVERSION 0x62U    /**< MIFARE Classic GET VERSION command */
#define PHAL_MFC_VERSION_LENGTH 0x08U    /**< Length of a Version MIFARE(R) Classic data block */

#endif /* PHALMFC_INT_H */
