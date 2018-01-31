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



#include "hal_debug.h"
#include "sxs_io.h"
//#include "imgs_profile_codes.h"

#ifndef _IMGSP_DEBUG_H_
#define _IMGSP_DEBUG_H_



// =============================================================================
//  TRACE
// -----------------------------------------------------------------------------
/// Trace macro to use to send a trace. The parameter \c format is a string
/// containing parameters in the "print fashion", but limited for trace to 6
/// parameters. The parameter \c tstmap defines which parameter is a string.
/// (Leave it to 0, if you don't use %s in fmt);
/// @todo implement, replacing level by _HAL or something
// =============================================================================
#ifndef IMGS_NO_PRINTF
#define IMGS_TRACE(level, tsmap, format, ...)  hal_DbgTrace(level,tsmap,format, ##__VA_ARGS__)
#else
#define IMGS_TRACE(level, tsmap, fmt, ...)
#endif



#ifdef IMGS_NO_ASSERT
#define IMGS_ASSERT(BOOL, format, ...)
#else
// =============================================================================
//  ASSERT
// -----------------------------------------------------------------------------
/// Assert: If the boolean condition (first parameter) is false,
/// raise an assert and print the decorated string passed in the other
/// parameter.
// =============================================================================
#define IMGS_ASSERT(BOOL, format, ...)                   \
    if (!(BOOL)) {            \
        hal_DbgAssert(format, ##__VA_ARGS__);                             \
    }
#endif



// =============================================================================
//  PROFILING
// -----------------------------------------------------------------------------
/// Those are the macros to use for profiling
/// @todo Implement them with hal_DbgProfilingEnter etc instead of this :
// =============================================================================
#ifdef IMGS_PROFILING


// =============================================================================
//  IMGS_PROFILE_PULSE
// -----------------------------------------------------------------------------
/// Use this macro to generate a profiling pulse.
// =============================================================================
#define IMGS_PROFILE_PULSE(pulseName)  \
        hal_DbgPxtsProfilePulse(HAL_DBG_PXTS_SVC, (CP_ ## pulseName))


// =============================================================================
//  IMGS_PROFILE_FUNCTION_ENTER
// -----------------------------------------------------------------------------
/// Use this macro at the begining of a profiled function or window.
// =============================================================================
#define IMGS_PROFILE_FUNCTION_ENTER(eventName) \
        hal_DbgPxtsProfileFunctionEnter(HAL_DBG_PXTS_SVC, (CP_ ## eventName))


// =============================================================================
//  IMGS_PROFILE_FUNCTION_EXIT
// -----------------------------------------------------------------------------
/// Use this macro at the end of a profiled function or window.
// =============================================================================
#define IMGS_PROFILE_FUNCTION_EXIT(eventName) \
        hal_DbgPxtsProfileFunctionExit(HAL_DBG_PXTS_SVC, (CP_ ## eventName))


// =============================================================================
//  IMGS_PROFILE_WINDOW_ENTER
// -----------------------------------------------------------------------------
/// Use this macro at the begining of a profiled function or window.
// =============================================================================
#define IMGS_PROFILE_WINDOW_ENTER(eventName) \
        hal_DbgPxtsProfileWindowEnter(HAL_DBG_PXTS_SVC, (CP_ ## eventName))


// =============================================================================
//  IMGS_PROFILE_WINDOW_EXIT
// -----------------------------------------------------------------------------
/// Use this macro at the end of a profiled function or window.
// =============================================================================
#define IMGS_PROFILE_WINDOW_EXIT(eventName) \
        hal_DbgPxtsProfileWindowExit(HAL_DBG_PXTS_SVC, (CP_ ## eventName))


#else // IMGS_PROFILING

#define IMGS_PROFILE_FUNCTION_ENTER(eventName)
#define IMGS_PROFILE_FUNCTION_EXIT(eventName)
#define IMGS_PROFILE_WINDOW_ENTER(eventName)
#define IMGS_PROFILE_WINDOW_EXIT(eventName)
#define IMGS_PROFILE_PULSE(pulseName)

#endif // IMGS_PROFILING



#endif // _IMGSP_DEBUG_H_

