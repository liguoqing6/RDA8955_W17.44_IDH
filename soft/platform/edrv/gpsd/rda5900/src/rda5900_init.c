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

#include "sxr_ops.h"
#include "sxs_io.h"
#include "cs_types.h"
#include "sxr_tls.h"
#include "gpsddp_debug.h"
#include "gpsd_config.h"
#include "gpsd_m.h"
#include "tgt_gpsd_cfg.h"
#include "hal_host.h"
// ============================================================================
// LOCAL DEFINITIONS
// ============================================================================


// =============================================================================
//  GLOBAL VARIABLES
// =============================================================================



// =============================================================================
//  FUNCTIONS
// =============================================================================

/*
regAddr
regVal
delay after operate
*/

CONST UINT16 rdagps_rf_init[][3] = 
{	
    {0x61,0x0,300},// reset
	{0x61,0x8001,300},// ldo_on
	{0x63,0x87C9,0},// setting 1.8v
	{0x64,0x84CD,0},// setting 1.2v 0x848D
	{0x02,0x783F,0},
	{0x01,0x67FE,300},
	{0x02,0x782F,0},
	{0x01,0x77FF,0},
	{0x19,0x90C0,0},// setting 26mhz crystal 
	{0x1D,0x1800,0},// pll count time
	{0x10,0x8986,0},// pll count time
	{0x0F,0xF886,0},// pll presc regulator
	{0x0F,0x8886,0},// pll count time
	{0x13,0x3C98,0},// 
	{0x14,0xC680,0},// 
	{0x15,0x07A0,0},//
	{0x1D,0x1B27,0},//
	{0x08,0x0CFF,0},//
	{0x0A,0xF0FA,0},//
	{0x09,0x01FF,0},//
	{0x0E,0xFEEF,0},//
	{0x02,0x782E,300},//  
	{0x02,0x782F,0},//
	{0x13,0x0F26,0},// 
	{0x14,0x31A0,0},//
	{0x06,0xF200,0},//sleep
	{0x07,0x5515,0},//sleep 
	{0x17,0x5E28,0},//sleep
	{0x01,0x57FF,0},
	{0x37,0x186A,0},

};	


CONST UINT32 rdagps_pskey_rf[][3] =
{ 
	{0xA1730004,0,100},
	{0x81C1E028,0x28650028,0},
	{0x81C1E02C,0x3c0c81e1,0},
	{0x81C1E030,0x358dab30,0},
	{0x81C1E034,0x01a00008,0},
	{0x81C1E038,0x00000000,0},
	{0xA1400008,0x81e1ab2c,0},
	{0xA1400048,0x81c1e028,0},	
	{0x81C1E014,0x2843000A,0},
	{0x81C1E018,0x3c0c81e1,0},
	{0x81C1E01C,0x358daae0,0},
	{0x81C1E020,0x01a00008,0},
	{0x81C1E024,0x00000000,0},
	{0xA1400004,0x81e1aadc,0},
	{0xA1400044,0x81c1e014,0},
	
};

CONST UINT32 rdagps_sleep[][3] =
{
	{0xA1600000,0x22,0}, 
	{0xA173004c,0x8,0}, 
};


CONST UINT32 rdagps_patch_rel3[][3] =
{
	{0x81C1E040,0x00000000,0},
	{0x81C1E044,0x00001021,0},
	{0x81C1E048,0x03e00008,0},
	{0x81C1E04C,0x00000000,0},
	{0xA1400008,0x81e0c610,0},
	{0xA1400048,0x81c1e040,0},
	{0x81C1E050,0x8c850000,0},
	{0x81C1E054,0x3c063fc0,0},
	{0x81C1E058,0x00a61824,0},
	{0x81C1E05C,0x3c0222c0,0},
	{0x81C1E060,0x1462000b,0},
	{0x81C1E064,0x00000000,0},
	{0x81C1E068,0x8c880004,0},
	{0x81C1E06C,0x00000000,0},
	{0x81C1E070,0x31070003,0},
	{0x81C1E074,0x14e00006,0},
	{0x81C1E078,0x00000000,0},
	{0x81C1E07C,0x8c890024,0},
	{0x81C1E080,0x00000000,0},
	{0x81C1E084,0x31240003,0},
	{0x81C1E088,0x03e00008,0},
	{0x81C1E08C,0x0004102b,0},
	{0x81C1E090,0x03e00008,0},
	{0x81C1E094,0x24020001,0},
	{0x81C1E098,0x00000000,0},
	{0xA140000C,0x81e0c658,0},
	{0xA140004C,0x81c1e050,0},
	{0x81C1E0B4,0xadf30004,0},
	{0x81C1E0B8,0x00026202,0},
	{0x81C1E0BC,0x318d0007,0},
	{0x81C1E0C0,0xa20d0016,0},
	{0x81C1E0C4,0x00000000,0},
	{0x81C1E0C8,0x3c0c81e0,0},
	{0x81C1E0CC,0x358dcbe4,0},
	{0x81C1E0D0,0x01A00008,0},
	{0x81C1E0D4,0x00000000,0},
	{0xA1400014,0x81e0cbe0,0},
	{0xA1400054,0x81c1e0b4,0},
	{0x81C1E0D8,0x2c430013,0},
	{0x81C1E0DC,0x3c0c81e0,0},
	{0x81C1E0E0,0x358bc9e8,0},
	{0x81C1E0E4,0x01600008,0},
	{0x81C1E0E8,0x00000000,0},
	{0xA1400018,0x81e0c9e4,0},
	{0xA1400058,0x81c1e0d8,0},
	{0x81C1E0EC,0x2f380013,0},
	{0x81C1E0F0,0x3c0c81e0,0},
	{0x81C1E0F4,0x358bdb2c,0},
	{0x81C1E0F8,0x01600008,0},
	{0x81C1E0FC,0x00000000,0},
	{0xA140001C,0x81e0db28,0},
	{0xA140005C,0x81c1e0ec,0},
	{0x81C1E100,0x2dac0013,0},
	{0x81C1E104,0x3c0a81e1,0},
	{0x81C1E108,0x35484170,0},
	{0x81C1E10C,0x01000008,0},
	{0x81C1E110,0x00000000,0},
	{0xA1400020,0x81e1416c,0},
	{0xA1400060,0x81c1e100,0},
	{0x81C1E114,0x2dcb0013,0},
	{0x81C1E118,0x3c0a81e1,0},
	{0x81C1E11C,0x354841cc,0},
	{0x81C1E120,0x01000008,0},
	{0x81C1E124,0x00000000,0},
	{0xA1400024,0x81e141c8,0},
	{0xA1400064,0x81c1e114,0},
	{0x81C1E128,0x2cd50013,0},
	{0x81C1E12C,0x3c0a81e1,0},
	{0x81C1E130,0x35488fd4,0},
	{0x81C1E134,0x01000008,0},
	{0x81C1E138,0x00000000,0},
	{0xA1400028,0x81e18fd0,0},
	{0xA1400068,0x81c1e128,0},
	{0x81C1E13C,0x2ddf0013,0},
	{0x81C1E140,0x3c0a81e1,0},
	{0x81C1E144,0x3548905c,0},
	{0x81C1E148,0x01000008,0},
	{0x81C1E14C,0x00000000,0},
	{0xA140002C,0x81e19058,0},
	{0xA140006C,0x81c1e13c,0},
	{0x81C1E150,0x2f170015,0},
	{0x81C1E154,0x3c0a81e0,0},
	{0x81C1E158,0x3548d8d4,0},
	{0x81C1E15C,0x01000008,0},
	{0x81C1E160,0x00000000,0},
	{0xA1400030,0x81e0d8d0,0},
	{0xA1400070,0x81c1e150,0},
	{0x81C1E164,0x2c850015,0},
	{0x81C1E168,0x3c0a81e0,0},
	{0x81C1E16C,0x3548e4e4,0},
	{0x81C1E170,0x01000008,0},
	{0x81C1E174,0x00000000,0},
	{0xA1400034,0x81e0e4e0,0},
	{0xA1400074,0x81c1e164,0},
	{0x81C1E178,0x24040004,0},
	{0x81C1E17C,0xa204000d,0},
	{0x81C1E180,0x8fbf002c,0},
	{0x81C1E184,0x3c0a81e0,0},
	{0x81C1E188,0x3548ccf4,0},
	{0x81C1E18C,0x01000008,0},
	{0x81C1E190,0x00000000,0},
	{0xA1400038,0x81e0ccf0,0},
	{0xA1400078,0x81c1e178,0},
	{0x81C1E194,0x1440fffA,0},
	{0x81C1E198,0x3c0c81e0,0},
	{0x81C1E19C,0x358bcb34,0},
	{0x81C1E1A0,0x01600008,0},
	{0x81C1E1A4,0x00000000,0},
	{0xA140003C,0x81e0cb30,0},
	{0xA140007C,0x81c1e194,0},
	{0x81C1E1A8,0x3411ef24,0},
	{0x81C1E1AC,0x240e1122,0},
	{0x81C1E1B0,0x3c0a81e1,0},
	{0x81C1E1B4,0x3548b128,0},
	{0x81C1E1B8,0x01000008,0},
	{0x81C1E1BC,0x00000000,0},
	{0xA1400010,0x81e1b120,0},
	{0xA1400050,0x81c1e1a8,0},
	{0x81C1E1C0,0x24020080,0},
	{0x81C1E1C4,0x3c0c81e1,0},
	{0x81C1E1C8,0x358bb2d0,0},
	{0x81C1E1CC,0x01600008,0},
	{0x81C1E1D0,0x00000000,0},
	{0xA1400040,0x81e1b2cc,0},
	{0xA1400080,0x81c1e1c0,0},
	{0x81C1E1D4,0x3c0800ff,0},
	{0x81C1E1D8,0x3509ffff,0},
	{0x81C1E1DC,0x00492824,0},
	{0x81C1E1E0,0x3c0c81e1,0},
	{0x81C1E1E4,0x358b6368,0},
	{0x81C1E1E8,0x01600008,0},
	{0x81C1E1EC,0x00000000,0},
	{0xA1400004,0x81e16364,0},
	{0xA1400044,0x81c1e1d4,0},
	{0xA1400000,0x0000ffff,0},
};

CONST UINT32 rdagps_patch_rel4[][3] =
{
	{0x81C1E014,0x3c0c81e0,0},	
	{0x81C1E018,0x358d2e44,0},	
	{0x81C1E01C,0x01a00008,0},	
	{0x81C1E020,0x00000000,0},	
	{0xA1400004,0x81e02e28,0},	 
	{0xA1400044,0x81c1e014,0},																						 
	{0x81C1E024,0x087855c1,0},	
	{0x81C1E028,0x00000000,0},	
	{0x81C1E02C,0x3c0c81e1,0},	
	{0x81C1E030,0x358d56b4,0},	
	{0x81C1E034,0x01a00008,0},	
	{0x81C1E038,0x00000000,0},	
	{0xA1400008,0x81e156ac,0},	 
	{0xA1400048,0x81c1e024,0},
	{0x81C1E03C,0x10800003,0},
	{0x81C1E040,0x24020001,0},	
	{0x81C1E044,0x10800002,0}, 
	{0x81C1E048,0x00000000,0},	
	{0x81C1E04C,0x24020000,0},
	{0x81C1E050,0x3c0c81e1,0},	
	{0x81C1E054,0x358d2270,0},	
	{0x81C1E058,0x01a00008,0},	
	{0x81C1E05C,0x00000000,0},	
	{0xA140000C,0x81e12268,0},	
	{0xA140004C,0x81c1e03c,0},
	{0x81C1E060,0x93840063,0},	
	{0x81C1E064,0x2484ffff,0},	
	{0x81C1E068,0x10800006,0},	
	{0x81C1E06C,0x00000000,0},	
	{0x81C1E070,0x8c69aa18,0}, 
	{0x81C1E074,0x3c0c81e1,0},	
	{0x81C1E078,0x358d5198,0},	
	{0x81C1E07C,0x01a00008,0},	
	{0x81C1E080,0x00000000,0},	
	{0x81C1E084,0x00a61025,0},
	{0x81C1E088,0xafa20050,0},
	{0x81C1E08C,0x3c0c81e1,0},
	{0x81C1E090,0x358d51ac,0},	
	{0x81C1E094,0x01a00008,0},	
	{0x81C1E098,0x00000000,0},	
	{0xA1400010,0x81e15194,0},	
	{0xA1400050,0x81c1e060,0},
	{0x81C1E09C,0x240d0001,0}, 
	{0x81C1E0A0,0x920a001b,0}, 
	{0x81C1E0A4,0x00000000,0},	
	{0x81C1E0A8,0x154D0002,0},
	{0x81C1E0AC,0x00000000,0},	
	{0x81C1E0B0,0x38a50001,0},
	{0x81C1E0B4,0x920b000a,0}, 
	{0x81C1E0B8,0x00000000,0},	
	{0x81C1E0BC,0x156d000f,0},
	{0x81C1E0C0,0x00000000,0},	
	{0x81C1E0C4,0x240c001c,0}, 
	{0x81C1E0C8,0x920b0013,0}, 
	{0x81C1E0CC,0x00000000,0},	
	{0x81C1E0D0,0x156c000a,0},
	{0x81C1E0D4,0x00000000,0},	
	{0x81C1E0D8,0x240c0009,0}, 
	{0x81C1E0DC,0x920b0014,0},	
	{0x81C1E0E0,0x00000000,0},	
	{0x81C1E0E4,0x156c0005,0},
	{0x81C1E0E8,0x00000000,0},	
	{0x81C1E0EC,0x10a00003,0},
	{0x81C1E0F0,0x00000000,0},	
	{0x81C1E0F4,0x394A0001,0},
	{0x81C1E0F8,0x24050000,0},
	{0x81C1E0FC,0x920b000a,0},	
	{0x81C1E100,0x00000000,0},	
	{0x81C1E104,0x156d000c,0},
	{0x81C1E108,0x00000000,0},	
	{0x81C1E10C,0x240c001d,0}, 
	{0x81C1E110,0x920b0013,0}, 
	{0x81C1E114,0x00000000,0},	
	{0x81C1E118,0x156c0007,0},
	{0x81C1E11C,0x00000000,0},	
	{0x81C1E120,0x240c0009,0}, 
	{0x81C1E124,0x920b0014,0},	
	{0x81C1E128,0x00000000,0},	
	{0x81C1E12C,0x156c0002,0},
	{0x81C1E130,0x00000000,0},	
	{0x81C1E134,0x24050000,0},
	{0x81C1E138,0xa20a001b,0},
	{0x81C1E13C,0x8e0c008c,0}, 
	{0x81C1E140,0x3c0b81e1,0},	
	{0x81C1E144,0x356d0ea4,0},	
	{0x81C1E148,0x01a00008,0},	
	{0x81C1E14C,0x00000000,0},	
	{0xA1400014,0x81e10ea0,0},	
	{0xA1400054,0x81c1e09c,0},
	{0x81C1E150,0x8e02008c,0}, 
	{0x81C1E154,0x920b0014,0},	
	{0x81C1E158,0x00000000,0},	
	{0x81C1E15C,0x11600005,0},
	{0x81C1E160,0x00000000,0},	
	{0x81C1E164,0x3c0c81e1,0},	
	{0x81C1E168,0x358d1568,0},	
	{0x81C1E16C,0x01a00008,0},	
	{0x81C1E170,0x00000000,0},
	{0x81C1E174,0x3c0c81e1,0},	
	{0x81C1E178,0x358d1584,0},	
	{0x81C1E17C,0x01a00008,0},	
	{0x81C1E180,0x00000000,0},	
	{0xA1400018,0x81e11564,0},	
	{0xA1400058,0x81c1e150,0},
	{0x81C1E1C4,0x3c0b81e0,0},	
	{0x81C1E1C8,0x356d2dc4,0},	
	{0x81C1E1CC,0x01a00008,0},	
	{0x81C1E1D0,0x00000000,0},	
	{0xA1400020,0x81e02dc0,0},	
	{0xA1400060,0x81c1e1c4,0},
	{0x81C1E1D4,0x3c0b81e0,0},	
	{0x81C1E1D8,0x356d2f20,0},	
	{0x81C1E1DC,0x01a00008,0},	
	{0x81C1E1E0,0x00000000,0},	
	{0xA1400024,0x81e02f1c,0},	
	{0xA1400064,0x81c1e1d4,0},
	{0x81C1E1E4,0x2fc7000d,0},
	{0x81C1E1E8,0x14e0000e,0},
	{0x81C1E1EC,0x3c0c81c0,0},	
	{0x81C1E1F0,0x938efe87,0},
	{0x81C1E1F4,0x240d0001,0},	
	{0x81C1E1F8,0x11cd0006,0}, 
	{0x81C1E1FC,0x00000000,0},	
	{0x81C1E200,0x2fcb0017,0},
	{0x81C1E204,0x15600007,0},
	{0x81C1E208,0x00000000,0},	
	{0x81C1E20C,0x15c00005,0},
	{0x81C1E210,0x00000000,0},	
	{0x81C1E214,0x3c0b81e2,0},	
	{0x81C1E218,0x356da54c,0},	
	{0x81C1E21C,0x01a00008,0},	
	{0x81C1E220,0x00000000,0},	
	{0x81C1E224,0x3c0b81e2,0},	
	{0x81C1E228,0x356db358,0},	
	{0x81C1E22C,0x01a00008,0},	
	{0x81C1E230,0x00000000,0},	
	{0xA1400028,0x81e2a540,0},	
	{0xA1400068,0x81c1e1e4,0},
	{0x81C1E234,0x3c0c81e3,0},	
	{0x81C1E238,0x358db320,0},	
	{0x81C1E23C,0x01a00008,0},	
	{0x81C1E240,0x00000000,0},	
	{0xA140002C,0x81e3b31c,0},	 
	{0xA140006C,0x81c1e234,0},
	{0x81C1E24C,0x2d040002,0},	
	{0x81C1E250,0x3c0b81e2,0},	
	{0x81C1E254,0x356d4d50,0},	
	{0x81C1E258,0x01a00008,0},	
	{0x81C1E25C,0x00000000,0},	
	{0xA1400030,0x81e24d4c,0},	
	{0xA1400070,0x81c1e24c,0},
	{0x81C1E260,0x2c8a0002,0},	
	{0x81C1E264,0x3c0b81e2,0},	
	{0x81C1E268,0x356db9bc,0},	
	{0x81C1E26C,0x01a00008,0},	
	{0x81C1E270,0x00000000,0},	
	{0xA1400034,0x81e2b9b8,0},	
	{0xA1400074,0x81c1e260,0},
	{0x81C1E274,0x2ef30002,0},	
	{0x81C1E278,0x16600012,0}, 
	{0x81C1E27C,0x00000000,0},	
	{0x81C1E280,0x92040063,0},	
	{0x81C1E284,0x00000000,0},	
	{0x81C1E288,0x2c920002,0},	
	{0x81C1E28C,0x1640000d,0}, 
	{0x81C1E290,0x00000000,0},	
	{0x81C1E294,0x921800c3,0},	
	{0x81C1E298,0x00000000,0},	
	{0x81C1E29C,0x2f050002,0},	
	{0x81C1E2A0,0x14a00008,0}, 
	{0x81C1E2A4,0x00000000,0},	
	{0x81C1E2A8,0x92130123,0},	
	{0x81C1E2AC,0x00000000,0},	
	{0x81C1E2B0,0x2e700002,0},	
	{0x81C1E2B4,0x3c0b81e2,0},	
	{0x81C1E2B8,0x356dbbc4,0},	
	{0x81C1E2BC,0x01a00008,0},	
	{0x81C1E2C0,0x00000000,0},	
	{0x81C1E2C4,0x3c0b81e2,0},	
	{0x81C1E2C8,0x356dbbcc,0},	
	{0x81C1E2CC,0x01a00008,0},	
	{0x81C1E2D0,0x00000000,0},	
	{0xA1400038,0x81e2bb84,0},	
	{0xA1400078,0x81c1e274,0},
	{0x81C1E2D4,0x2c8a0002,0},	
	{0x81C1E2D8,0x15400012,0}, 
	{0x81C1E2DC,0x00000000,0},	
	{0x81C1E2E0,0x92130063,0},	
	{0x81C1E2E4,0x00000000,0},	
	{0x81C1E2E8,0x2e650002,0},	
	{0x81C1E2EC,0x14a0000d,0}, 
	{0x81C1E2F0,0x00000000,0},	
	{0x81C1E2F4,0x920300c3,0},	
	{0x81C1E2F8,0x00000000,0},	
	{0x81C1E2FC,0x2c6c0002,0},	
	{0x81C1E300,0x15800008,0}, 
	{0x81C1E304,0x00000000,0},	
	{0x81C1E308,0x920f0123,0},	
	{0x81C1E30C,0x00000000,0},	
	{0x81C1E310,0x2df00002,0},	
	{0x81C1E314,0x3c0b81e2,0},	
	{0x81C1E318,0x356dbce8,0},	
	{0x81C1E31C,0x01a00008,0},	
	{0x81C1E320,0x00000000,0},	
	{0x81C1E324,0x3c0b81e2,0},	
	{0x81C1E328,0x356dbd24,0},	
	{0x81C1E32C,0x01a00008,0},	
	{0x81C1E330,0x00000000,0},	
	{0xA140003C,0x81e2bca8,0},	
	{0xA140007C,0x81c1e2d4,0},
	{0x81C1E360,0x24050001,0}, 
	{0x81C1E364,0x0c7835da,0},	
	{0x81C1E368,0x02202021,0}, 
	{0x81C1E36C,0x92180002,0},	
	{0x81C1E370,0x3c0c81e1,0},	
	{0x81C1E374,0x358dace4,0},	
	{0x81C1E378,0x01A00008,0},	
	{0x81C1E37C,0x00000000,0},	
	{0xA1400040,0x81e1acdc,0},	
	{0xA1400080,0x81c1e360,0},	
	{0x81C1E348,0xafac0020,0}, 
	{0x81C1E34C,0x24140001,0}, 
	{0x81C1E350,0x3c0c81e1,0},	
	{0x81C1E354,0x358da390,0},	
	{0x81C1E358,0x01A00008,0},	
	{0x81C1E35C,0x00000000,0},	
	{0xA140001C,0x81e1a38c,0},	 
	{0xA140005C,0x81c1e348,0},	 

};

void RDAGPS_I2C_DIG_Read(UINT32 i2c_adder,UINT32 *data)
{
	gpsd_i2c_read_core_data(i2c_adder,data,1);
}

void RDAGPS_I2C_DIG_Write(UINT32 i2c_adder,UINT32 data)
{
	gpsd_i2c_write_core_data(i2c_adder,&data,1);
}

void RDAGPS_I2C_Read(UINT32 i2c_adder,UINT32 *data)
{
	gpsd_i2c_read_rf_data(i2c_adder,data,1);
}

void RDAGPS_I2C_Write(UINT32 i2c_adder,UINT32 data)
{
	gpsd_i2c_write_rf_data(i2c_adder,&data,1);
}

UINT16 g_RDAGPS_chipID = 0xffff;

void RDAGPS_read_chipID(void)
{
	UINT16 temp = 0;
	gpsd_i2c_read_rf_data(0x60,&temp,1);
	g_RDAGPS_chipID = temp;
}

UINT16 Get_RDAGPS_chipID(void)
{
	return g_RDAGPS_chipID;
}

void RDAGPS_rf_Intialization(void)
{
	UINT8 i=0;
	UINT16 temp = 0;
	for(i =0;i<sizeof(rdagps_rf_init)/sizeof(rdagps_rf_init[0]); i++)
	{
		gpsd_i2c_write_rf_data(rdagps_rf_init[i][0],&rdagps_rf_init[i][1],1);
		RDAGPS_DELAY(rdagps_rf_init[i][2]);
	}

	
	for(i =0;i<sizeof(rdagps_rf_init)/sizeof(rdagps_rf_init[0]); i++)
	{
		gpsd_i2c_read_rf_data(rdagps_rf_init[i][0],&temp,1);
		hal_HstSendEvent(rdagps_rf_init[i][0]);
		hal_HstSendEvent(temp);
	}

	gpsd_i2c_read_rf_data(0x60,&temp,1);
	if(0x5903 != temp)
	{
		hal_HstSendEvent(0x59030000+temp);
		hal_DbgAssert(0);
	}
	
	RDAGPS_read_chipID();
}

void RDAGPS_Pskey_Write(void)
{
   UINT32 i;
   UINT32 temp =0;
   
   for(i=0;i<sizeof(rdagps_pskey_rf)/sizeof(rdagps_pskey_rf[0]);i++)
   {
      gpsd_i2c_write_core_data(rdagps_pskey_rf[i][0],&rdagps_pskey_rf[i][1],1);
      RDAGPS_DELAY(rdagps_pskey_rf[i][2]);
   }


	RDAGPS_DELAY(10); 
}

void RDAGPS_Sleep_Write(void)
{
   UINT32 i;
   UINT32 temp =0;
   for(i=0;i<sizeof(rdagps_sleep)/sizeof(rdagps_sleep[0]);i++)
   {
      gpsd_i2c_write_core_data(rdagps_sleep[i][0],&rdagps_sleep[i][1],1);
      RDAGPS_DELAY(rdagps_sleep[i][2]);
   }
}

void RDAGPS_Patch_Write(void)
{
   UINT32 i;
   UINT32 temp =0;
	/*��λоƬ*/
   RDAGPS_Pskey_Write();
}

void RDAGPS_Intialization(void)
{
#ifndef I2C_BASED_ON_GPIO
	UINT16 reg = 0; 
	gpsd_i2c_read_rf_data(0,&reg,1);
#endif

    RDAGPS_DELAY(10); //wait for digi running
    RDAGPS_rf_Intialization();
    RDAGPS_DELAY(200); //wait for digi running
	RDAGPS_Patch_Write();  
	RDAGPS_DELAY(200); //wait for patch running
	gpsd_sleep_init();
}

void RDAGPS_test(void)
{
	UINT16 temp = 0;
	UINT32 temp32 =0;

	temp = 0x7628;
	gpsd_i2c_write_rf_data(0x17,&temp,1);

	gpsd_i2c_read_rf_data(0x17,&temp,1);
	hal_HstSendEvent(0x17);
	hal_HstSendEvent(temp);
	
	gpsd_i2c_read_rf_data(0x02,&temp,1);
	hal_HstSendEvent(0x02);
	hal_HstSendEvent(temp);

	
	gpsd_i2c_read_core_data(0xA1730040,&temp32,1);
	hal_HstSendEvent(0xA1730040);
	hal_HstSendEvent(temp32);
}


