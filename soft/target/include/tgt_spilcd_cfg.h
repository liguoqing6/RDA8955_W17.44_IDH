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



#ifndef _TGT_SPILCD_CFG_H_
#define _TGT_SPILCD_CFG_H_

#include "cs_types.h"

#ifdef __PRJ_WITH_SPILCD__
// =============================================================================
// tgt_GetSpiLcdConfig
// -----------------------------------------------------------------------------
/// This function is used by SPILCD to get access to its configuration structure.
/// This is the only way SPILCD can get this information.
// =============================================================================
PUBLIC CONST SPILCD_CONFIG_STRUCT_T* tgt_GetSpiLcdConfig(VOID);
#endif //__PRJ_WITH_SPILCD__
#endif //
