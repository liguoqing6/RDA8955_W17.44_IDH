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

























#ifndef SINREF_H
#define SINREF_H


#include "cs_types.h"



/* -------------------------------------------------- */
/* ----- Number of reference samples. */

#define SINREF_SIZE         250 /* Samples */
#define SINREF_F            8   /* Hz */



/* -------------------------------------------------- */
/* ----- The samples of:
 *
 *              sinref(n) = 2^16 * sin(2 * Pi * n / 1000)
 */

CONST UINT16 sinRef[SINREF_SIZE] =
{
    0x0,
    0xCD,
    0x19B,
    0x269,
    0x337,
    0x405,
    0x4D3,
    0x5A0,
    0x66E,
    0x73B,
    0x809,
    0x8D6,
    0x9A4,
    0xA71,
    0xB3E,
    0xC0B,
    0xCD8,
    0xDA5,
    0xE72,
    0xF3E,
    0x100A,
    0x10D7,
    0x11A3,
    0x126E,
    0x133A,
    0x1406,
    0x14D1,
    0x159C,
    0x1667,
    0x1731,
    0x17FC,
    0x18C6,
    0x1990,
    0x1A59,
    0x1B23,
    0x1BEC,
    0x1CB4,
    0x1D7D,
    0x1E45,
    0x1F0D,
    0x1FD5,
    0x209C,
    0x2163,
    0x2229,
    0x22F0,
    0x23B5,
    0x247B,
    0x2540,
    0x2605,
    0x26C9,
    0x278D,
    0x2851,
    0x2914,
    0x29D7,
    0x2A99,
    0x2B5B,
    0x2C1D,
    0x2CDE,
    0x2D9E,
    0x2E5F,
    0x2F1E,
    0x2FDD,
    0x309C,
    0x315A,
    0x3218,
    0x32D5,
    0x3392,
    0x344E,
    0x350A,
    0x35C5,
    0x367F,
    0x3739,
    0x37F3,
    0x38AC,
    0x3964,
    0x3A1C,
    0x3AD3,
    0x3B8A,
    0x3C40,
    0x3CF5,
    0x3DAA,
    0x3E5E,
    0x3F11,
    0x3FC4,
    0x4076,
    0x4128,
    0x41D9,
    0x4289,
    0x4338,
    0x43E7,
    0x4495,
    0x4543,
    0x45F0,
    0x469C,
    0x4747,
    0x47F2,
    0x489C,
    0x4945,
    0x49ED,
    0x4A95,
    0x4B3C,
    0x4BE2,
    0x4C88,
    0x4D2C,
    0x4DD0,
    0x4E73,
    0x4F16,
    0x4FB7,
    0x5058,
    0x50F8,
    0x5197,
    0x5235,
    0x52D2,
    0x536F,
    0x540B,
    0x54A5,
    0x553F,
    0x55D9,
    0x5671,
    0x5708,
    0x579F,
    0x5834,
    0x58C9,
    0x595D,
    0x59F0,
    0x5A82,
    0x5B13,
    0x5BA3,
    0x5C33,
    0x5CC1,
    0x5D4E,
    0x5DDB,
    0x5E66,
    0x5EF1,
    0x5F7A,
    0x6003,
    0x608B,
    0x6112,
    0x6197,
    0x621C,
    0x62A0,
    0x6322,
    0x63A4,
    0x6425,
    0x64A5,
    0x6523,
    0x65A1,
    0x661E,
    0x6699,
    0x6714,
    0x678D,
    0x6806,
    0x687D,
    0x68F4,
    0x6969,
    0x69DD,
    0x6A50,
    0x6AC3,
    0x6B34,
    0x6BA4,
    0x6C12,
    0x6C80,
    0x6CED,
    0x6D58,
    0x6DC3,
    0x6E2C,
    0x6E95,
    0x6EFC,
    0x6F62,
    0x6FC7,
    0x702A,
    0x708D,
    0x70EE,
    0x714F,
    0x71AE,
    0x720C,
    0x7269,
    0x72C5,
    0x731F,
    0x7379,
    0x73D1,
    0x7428,
    0x747E,
    0x74D3,
    0x7526,
    0x7578,
    0x75CA,
    0x761A,
    0x7668,
    0x76B6,
    0x7702,
    0x774E,
    0x7798,
    0x77E0,
    0x7828,
    0x786E,
    0x78B3,
    0x78F7,
    0x793A,
    0x797B,
    0x79BC,
    0x79FB,
    0x7A39,
    0x7A75,
    0x7AB0,
    0x7AEA,
    0x7B23,
    0x7B5B,
    0x7B91,
    0x7BC6,
    0x7BFA,
    0x7C2D,
    0x7C5E,
    0x7C8E,
    0x7CBD,
    0x7CEA,
    0x7D17,
    0x7D42,
    0x7D6B,
    0x7D94,
    0x7DBB,
    0x7DE1,
    0x7E06,
    0x7E29,
    0x7E4B,
    0x7E6C,
    0x7E8C,
    0x7EAA,
    0x7EC7,
    0x7EE3,
    0x7EFD,
    0x7F16,
    0x7F2E,
    0x7F45,
    0x7F5A,
    0x7F6E,
    0x7F81,
    0x7F92,
    0x7FA2,
    0x7FB1,
    0x7FBF,
    0x7FCB,
    0x7FD6,
    0x7FE0,
    0x7FE8,
    0x7FEF,
    0x7FF5,
    0x7FFA,
    0x7FFD,
    0x7FFF
};



#endif /* SINREF_H */

