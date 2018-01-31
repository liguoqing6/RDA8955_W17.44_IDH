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

#include "hal_map_engine.h"

#include "btd_map.h"
#include "tgt_m.h"



// =============================================================================
//  MACROS
// =============================================================================

#define BTD_VERSION_STRING "BTD for " STRINGIFY_VALUE(BTD_BT_MODEL)
#define BTD_VERSION_NUMBER 1
#include "btdp_version.h"



// =============================================================================
//  GLOBAL VARIABLES
// =============================================================================


// =============================================================================
// g_btdMapVersion
// -----------------------------------------------------------------------------
/// Contains the version of the module.
/// The macro used is generated by the make process.
// =============================================================================
PROTECTED HAL_MAP_VERSION_T HAL_MAP_VER_LOC g_btdMapVersion = BTD_VERSION_STRUCT;


#ifdef FACTORY_VERSION
// =============================================================================
// g_btdMapAccess
// -----------------------------------------------------------------------------
/// Contains the addresses of the structures of the module that will be
/// accessible from a remote PC (e.g. through CoolWatcher).
// =============================================================================
PROTECTED BTD_MAP_ACCESS_T HAL_MAP_ACCESS_LOC g_btdMapAccess =
{
    .flashInfo = FACT_SETTINGS_BASE + offsetof(FACTORY_BLOCK_T, btInfo)
};

#else
// =============================================================================
// g_btdMapAccess
// -----------------------------------------------------------------------------
/// Contains the addresses of the structures of the module that will be
/// accessible from a remote PC (e.g. through CoolWatcher).
// =============================================================================
PROTECTED BTD_MAP_ACCESS_T HAL_MAP_ACCESS_LOC g_btdMapAccess =
{
    .flashInfo = FACT_SETTINGS_BASE + offsetof(TGT_FACTORY_SETTINGS_T, btInfo)
};
#endif


// =============================================================================
//  FUNCTIONS
// =============================================================================


// =============================================================================
// btd_RegisterYourself
// -----------------------------------------------------------------------------
/// This function registers the module itself to HAL so that the version and
/// the map accessor are filled. Then, the CSW get version function and the
/// CoolWatcher get version command will work.
// =============================================================================
PUBLIC VOID btd_RegisterYourself(VOID)
{
    hal_MapEngineRegisterModule(HAL_MAP_ID_BTD, &g_btdMapVersion, &g_btdMapAccess);
}
