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



# ifndef LIBMAD_LAYER12_H
# define LIBMAD_LAYER12_H

# include "stream.h"
# include "frame.h"

int mad_layer_I(struct mad_stream *, struct mad_frame *);
int mad_layer_II(struct mad_stream *, struct mad_frame *);

# endif
