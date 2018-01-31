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



#define EHF_MASK 0x0008 /* Encoder Homing Frame pattern */

/* Function Prototypes */

INT16 encoder_homing_frame_test (INT16 input_frame[]);

void encoder_reset (void);

void reset_enc (void);
