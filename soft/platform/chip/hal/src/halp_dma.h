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



#ifndef  _HALP_DMA_H_
#define  _HALP_DMA_H_


#include "cs_types.h"

// =============================================================================
//  FUNCTIONS
// =============================================================================



// =============================================================================
//
// -----------------------------------------------------------------------------
// =============================================================================

// =============================================================================
// hal_DmaIrqHandler
// -----------------------------------------------------------------------------
/// DMA module IRQ handler
/// Clear IRQ and call the IRQ handler user function.
// =============================================================================
PROTECTED VOID hal_DmaIrqHandler(UINT8 dmaIrqId);




#endif //  _HAL_DMA_H_

