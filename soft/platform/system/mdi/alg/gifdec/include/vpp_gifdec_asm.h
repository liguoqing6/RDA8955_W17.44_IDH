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
















#include "cs_types.h"

#ifndef CS_PLATFORM_SIMU

// avoid double declaration in simulation
#define RAM_X_BEGIN_ADDR               0x0000
#define RAM_Y_BEGIN_ADDR               0x4000

#endif

#define TO32(lo,hi)                    ((lo & 0xffff) | ((hi &0xffff) << 16))

#define VPP_GIFDEC_MAIN_SIZE               g_vppGifDecCommonCodeSize
#define VPP_GIFDEC_MAIN_ENTRY              0
#define VPP_GIFDEC_CRITICAL_SECTION_MIN    0
#define VPP_GIFDEC_CRITICAL_SECTION_MAX    0

// ******************************
//            COMMON
// ******************************
EXPORT INT32 g_vppGifDecCommonCode[];
EXPORT CONST INT32 g_vppGifDecCommonCodeSize;


