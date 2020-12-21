
#ifndef ISO14443_H__
#define ISO14443_H__

#include "main.h"

/** ReqA Command code */
#define PHPAL_I14443P3A_REQUEST_CMD         0x26U

/** WupA Command code */
#define PHPAL_I14443P3A_WAKEUP_CMD          0x52U

/** HltA Command code */
#define PHPAL_I14443P3A_HALT_CMD            0x50U

/** Cascade Tag (CT) value */
#define PHPAL_I14443P3A_CASCADE_TAG         0x88U

/** Length of AtqA */
#define PHPAL_I14443P3A_ATQA_LENGTH         2U

/** Wait time for selection command in microseconds */
#define PHPAL_I14443P3A_SELECTION_TIME_US   85U

/** Wait time for halt command in microseconds */
#define PHPAL_I14443P3A_HALT_TIME_US        1100U

/** Time extension in microseconds for all commands.  */
#define PHPAL_I14443P3A_EXT_TIME_US         60U


void iso14443b_crc(const uint8_t *pbtData, size_t szLen, uint8_t *pbtCrcLow, uint8_t *pbtCrcHigh);
void iso14443a_crc(const uint8_t *pbtData, size_t szLen, uint8_t *pbtCrcLow, uint8_t *pbtCrcHigh);

void ISO14443_Init(void);

#endif
