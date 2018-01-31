/* Copyright (C) 2016 RDA Technologies Limited and/or its affiliates("RDA").
* All rights reserved.
*
* This software is supplied "AS IS" without any warranties.
* RDA assumes no responsibility or liability for the use of the software,
* conveys no license or title under any patent, copyright, or mask work
* right to the product. RDA reserves the right to make changes in the
* software without notification.  RDA also make no representation or
* warranty that such application will be suitable for the specified use
* without further testing or modification.
*/


#ifndef _BOOTP_HOST_H_
#define _BOOTP_HOST_H_

#include "cs_types.h"
#include "boot.h"

// =============================================================================
// MACROS
// =============================================================================


// =============================================================================
// TYPES
// =============================================================================


// =============================================================================
// GLOBAL VARIABLES
// =============================================================================


// =============================================================================
// FUNCTIONS
// =============================================================================

PROTECTED VOID mon_Event(UINT32 evt);

PROTECTED VOID boot_HstMonitorX(VOID);

PROTECTED BOOT_MONITOR_OP_STATUS_T boot_HstMonitor(VOID);

#endif // _BOOTP_HOST_H_
