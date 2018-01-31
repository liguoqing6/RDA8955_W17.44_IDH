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


#include "fixed.h"
/*
 * NAME:    fixed->abs()
 * DESCRIPTION: return absolute value of a fixed-point number
 */
mad_fixed_t mad_f_abs(mad_fixed_t x)
{
    return x < 0 ? -x : x;
}

