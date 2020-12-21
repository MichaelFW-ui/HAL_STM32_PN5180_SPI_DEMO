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
* Cards identification.
* $Author: Kiran Kumar Makam Nataraja (nxp69453) $
* $Revision: 4423 $ (v05.22.00)
* $Date: 2016-04-22 11:50:54 +0530 (Fri, 22 Apr 2016) $
*
* History:
*
*
*/

#ifndef PHAPP_INIT_H
#define PHAPP_INIT_H

/* Status header */
#include <ph_Status.h>

/* NFCLIB Header */
#include <phNfcLib.h>

/* Check for LPC1769 controller based boards. */
#if defined(PHDRIVER_LPC1769PN5180_BOARD) || defined(PHDRIVER_LPC1769RC663_BOARD)
#define PHDRIVER_LPC1769
#endif

#include <stdio.h>

#define  DEBUG_PRINTF(...) printf(__VA_ARGS__); fflush(stdout)

/*******************************************************************************
**   Global Variable Declaration
*******************************************************************************/

#define PH_NFCRDLIB_EXAMPLE_LPCD_GUARDTIME      100           /* LPCD Guard time(T4) in milli-seconds configured by application for Rc663. */
#define PH_NFCRDLIB_EXAMPLE_LPCD_RFON_TIME      56            /* LPCD RFON time(T3) in micro-seconds configured by application for Rc663. */

/* HAL & BAL declarations */

extern phhalHw_Pn5180_DataParams_t   * pHal;

/**************************************************Prints if error is detected**************************************************************/
/* Enable(1) / Disable(0) printing error/info */
#define DETECT_ERROR 0

#if DETECT_ERROR
#define DEBUG_ERROR_PRINT(x) x
#define PRINT_INFO(...) DEBUG_PRINTF(__VA_ARGS__)
#else
#define DEBUG_ERROR_PRINT(x)
#define PRINT_INFO(...)
#endif

#define CHECK_STATUS(x)                                      \
    if ((x) != PH_ERR_SUCCESS)                               \
{                                                            \
    DEBUG_PRINTF("Line: %d   Error - (0x%04X) has occurred : 0xCCEE CC-Component ID, EE-Error code. Refer-ph_Status.h\n", __LINE__, (x));    \
}

/* prints if error is detected */
#define CHECK_SUCCESS(x)              \
    if ((x) != PH_ERR_SUCCESS)        \
{                                     \
    DEBUG_PRINTF("\nLine: %d   Error - (0x%04X) has occurred : 0xCCEE CC-Component ID, EE-Error code. Refer-ph_Status.h\n ", __LINE__, (x)); \
    return (x);                       \
}

/* prints if error is detected */
#define CHECK_NFCLIB_STATUS(x)                               \
    if ((x) != PH_NFCLIB_STATUS_SUCCESS)                     \
{                                                            \
    DEBUG_PRINTF("\nLine: %d   Error - (0x%04X) has occurred in NFCLIB\n ", __LINE__, (x)); \
}


/*********************************************************************************************************************************************/

/*******************************************************************************
**   Function Declarations
*******************************************************************************/
extern void phApp_CPU_Init(void);
extern phStatus_t phApp_Comp_Init(void * pDiscLoopParams);
extern phStatus_t phApp_HALConfigAutoColl(void);
extern phStatus_t phApp_ConfigureLPCD(void);
extern void phApp_PrintTagInfo(phacDiscLoop_Sw_DataParams_t *pDataParams, uint16_t wNumberOfTags, uint16_t wTagsDetected);
extern void phApp_PrintTech(uint8_t TechType);
extern void phApp_Print_Buff(uint8_t *pBuff, uint8_t num);
extern void PrintErrorInfo(phStatus_t wStatus);

#endif /* PHAPP_INIT_H */
