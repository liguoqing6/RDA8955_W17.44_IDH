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


#ifndef SHEEN_VC_DEBUG
#include "global.h"
#endif
#ifdef MP4_3GP_SUPPORT

#ifndef _QUANT_H_
#define _QUANT_H_

#include "portab.h"

/*****************************************************************************
 * Common API for Intra (de)Quant functions
 ****************************************************************************/

typedef uint32_t (quant_intraFunc) (int16_t * data,
                                    const int16_t * coeff,
                                    const uint16_t quant,
                                    const uint8_t dcscalar,
                                    const uint16_t * mpeg_quant_matrices);

typedef quant_intraFunc *quant_intraFuncPtr;

/* Global function pointers */
extern quant_intraFuncPtr dequant_h263_intra;
extern quant_intraFuncPtr dequant_mpeg_intra;


/*****************************************************************************
 * Known implementation of Intra (de)Quant functions
 ****************************************************************************/

/* DeQuant functions */
quant_intraFunc dequant_h263_intra_c;
quant_intraFunc dequant_mpeg_intra_c;

/*****************************************************************************
 * Common API for Inter (de)Quant functions
 ****************************************************************************/

typedef uint32_t (quant_interFunc) (int16_t * coeff,
                                    const int16_t * data,
                                    const uint16_t quant);

typedef quant_interFunc *quant_interFuncPtr;

/* Global function pointers */
//extern quant_interFuncPtr quant_h263_inter;
//extern quant_interFuncPtr quant_mpeg_inter;
extern quant_interFuncPtr dequant_h263_inter;
//extern quant_interFuncPtr dequant_mpeg_inter;
void init_mpeg_matrix(uint16_t * mpeg_quant_matrices);

/*****************************************************************************
 * Known implementation of Inter (de)Quant functions
 ****************************************************************************/

quant_interFunc dequant_h263_inter_c;


void
set_intra_matrix(uint16_t * mpeg_quant_matrices, const uint8_t * matrix);
void
set_inter_matrix(uint16_t * mpeg_quant_matrices, const uint8_t * matrix);

//quant_interFunc dequant_mpeg_inter_c;

//extern uint32_t get_dc_scaler(uint32_t quant,uint32_t lum);

#endif /* _QUANT_H_ */
#endif

