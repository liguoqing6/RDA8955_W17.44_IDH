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


#ifndef _UCTLSP_DEBUG_H_
#define _UCTLSP_DEBUG_H_

#include "cs_types.h"

#include "hal_debug.h"

#include "sxs_io.h"

//#include "uctls_profile_codes.h"
#include "svcp_debug.h"

// =============================================================================
// MACROS
// =============================================================================

// =============================================================================
//  TRACE Level mapping
// -----------------------------------------------------------------------------
/// Important trace that can be enabled all the time (low rate)
// =============================================================================
#define UCTLS_WARN_TRC   SVC_WARN_TRC

/// Informational trace interesting for AVRS only
#define UCTLS_INFO_TRC   SVC_UCTLS_TRC

/// reserved for debug (can be very verbose, but should probably not stay in code)
#define UCTLS_DBG_TRC    SVC_DBG_TRC



// =============================================================================
//  TRACE
// -----------------------------------------------------------------------------
/// Trace macro to use to send a trace. The parameter \c format is a string
/// containing parameters in the "print fashion", but limited for trace to 6
/// parameters. The parameter \c tstmap defines which parameter is a string.
/// (Leave it to 0, if you don't use %s in fmt);
// =============================================================================
#ifndef UCTLS_NO_PRINTF
#define UCTLS_TRACE(level, tsmap, format, ...)   SVC_TRACE(level,tsmap,format, ##__VA_ARGS__)
#else
#define UCTLS_TRACE(level, tsmap, fmt, ...)
#endif


#ifdef UCTLS_NO_ASSERT
#define UCTLS_ASSERT(BOOL, format, ...)
#else
// =============================================================================
//  ASSERT
// -----------------------------------------------------------------------------
/// Assert: If the boolean condition (first parameter) is false,
/// raise an assert and print the decorated string passed in the other
/// parameter.
// =============================================================================
#define UCTLS_ASSERT(BOOL, format, ...)                   \
    if (!(BOOL)) {            \
        hal_DbgAssert(format, ##__VA_ARGS__);                             \
    }
#endif

#ifdef UCTLS_PROFILING

// =============================================================================
//  UCTLS_PROFILE_FUNCTION_ENTER
// -----------------------------------------------------------------------------
/// Use this macro at the begining of a profiled function or window.
// =============================================================================
#define UCTLS_PROFILE_FUNCTION_ENTER(eventName) \
        hal_DbgPxtsProfileFunctionEnter(HAL_DBG_PXTS_SVC, (CP_ ## eventName))

// =============================================================================
//  UCTLS_PROFILE_FUNCTION_EXIT
// -----------------------------------------------------------------------------
/// Use this macro at the end of a profiled function or window.
// =============================================================================
#define UCTLS_PROFILE_FUNCTION_EXIT(eventName) \
        hal_DbgPxtsProfileFunctionExit(HAL_DBG_PXTS_SVC, (CP_ ## eventName))

// =============================================================================
//  UCTLS_PROFILE_PULSE
// -----------------------------------------------------------------------------
/// Use this macro to generate a profiling pulse.
// =============================================================================
#define UCTLS_PROFILE_PULSE(pulseName)  \
        hal_DbgPxtsProfilePulse(HAL_DBG_PXTS_SVC, (CP_ ## pulseName))

#else

#define UCTLS_PROFILE_FUNCTION_ENTER(eventName)
#define UCTLS_PROFILE_FUNCTION_EXIT(eventName)
#define UCTLS_PROFILE_PULSE(pulseName)

#endif /* UCTLS_PROFILING */

// =============================================================================
// TYPES
// =============================================================================


// =============================================================================
// GLOBAL VARIABLES
// =============================================================================


// =============================================================================
// FUNCTIONS
// =============================================================================

#endif // _UCTLSP_DEBUG_H_
