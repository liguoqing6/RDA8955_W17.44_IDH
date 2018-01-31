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




#include "ml.h"

#ifdef CP1256

static const UINT16 charset2uni[256] =
{
    /* 0x00 */
    0x0000, 0x0001, 0x0002, 0x0003,
    0x0004, 0x0005, 0x0006, 0x0007,
    0x0008, 0x0009, 0x000a, 0x000b,
    0x000c, 0x000d, 0x000e, 0x000f,

    /* 0x10 */
    0x0010, 0x0011, 0x0012, 0x0013,
    0x0014, 0x0015, 0x0016, 0x0017,
    0x0018, 0x0019, 0x001a, 0x001b,
    0x001c, 0x001d, 0x001e, 0x001f,

    /* 0x20 */
    0x0020, 0x0021, 0x0022, 0x0023,
    0x0024, 0x0025, 0x0026, 0x0027,
    0x0028, 0x0029, 0x002a, 0x002b,
    0x002c, 0x002d, 0x002e, 0x002f,

    /* 0x30 */
    0x0030, 0x0031, 0x0032, 0x0033,
    0x0034, 0x0035, 0x0036, 0x0037,
    0x0038, 0x0039, 0x003a, 0x003b,
    0x003c, 0x003d, 0x003e, 0x003f,

    /* 0x40 */
    0x0040, 0x0041, 0x0042, 0x0043,
    0x0044, 0x0045, 0x0046, 0x0047,
    0x0048, 0x0049, 0x004a, 0x004b,
    0x004c, 0x004d, 0x004e, 0x004f,

    /* 0x50 */
    0x0050, 0x0051, 0x0052, 0x0053,
    0x0054, 0x0055, 0x0056, 0x0057,
    0x0058, 0x0059, 0x005a, 0x005b,
    0x005c, 0x005d, 0x005e, 0x005f,

    /* 0x60 */
    0x0060, 0x0061, 0x0062, 0x0063,
    0x0064, 0x0065, 0x0066, 0x0067,
    0x0068, 0x0069, 0x006a, 0x006b,
    0x006c, 0x006d, 0x006e, 0x006f,

    /* 0x70 */
    0x0070, 0x0071, 0x0072, 0x0073,
    0x0074, 0x0075, 0x0076, 0x0077,
    0x0078, 0x0079, 0x007a, 0x007b,
    0x007c, 0x007d, 0x007e, 0x007f,

    /* 0x80 */
    0x0080, 0x067E, 0x201A, 0x0192,
    0x201E, 0x2026, 0x2020, 0x2021,
    0x02C6, 0x2030, 0x008A, 0x2039,
    0x0152, 0x0686, 0x0698, 0x008F,

    /* 0x90 */
    0x06AF, 0x2018, 0x2019, 0x201C,
    0x201D, 0x2022, 0x2013, 0x2014,
    0x0098, 0x2122, 0x009A, 0x203A,
    0x0153, 0x200C, 0x200D, 0x009F,

    /* 0xa0 */
    0x00A0, 0x060C, 0x00A2, 0x00A3,
    0x00A4, 0x00A5, 0x00A6, 0x00A7,
    0x00A8, 0x00A9, 0xF897, 0x00AB,
    0x00AC, 0x00AD, 0x00AE, 0x00AF,

    /* 0xb0 */
    0x00B0, 0x00B1, 0x00B2, 0x00B3,
    0x00B4, 0x00B5, 0x00B6, 0x00B7,
    0x00B8, 0x00B9, 0x061B, 0x00BB,
    0x00BC, 0x00BD, 0x00BE, 0x061F,

    /* 0xc0 */
    0xF898, 0x0621, 0x0622, 0x0623,
    0x0624, 0x0625, 0x0626, 0x0627,
    0x0628, 0x0629, 0x062A, 0x062B,
    0x062C, 0x062D, 0x062E, 0x062F,

    /* 0xd0 */
    0x0630, 0x0631, 0x0632, 0x0633,
    0x0634, 0x0635, 0x0636, 0x00D7,
    0x0637, 0x0638, 0x0639, 0x063A,
    0x0640, 0x0641, 0x0642, 0x0643,

    /* 0xe0 */
    0x00E0, 0x0644, 0x00E2, 0x0645,
    0x0646, 0x0647, 0x0648, 0x00E7,
    0x00E8, 0x00E9, 0x00EA, 0x00EB,
    0x0649, 0x064A, 0x00EE, 0x00EF,

    /* 0xf0 */
    0x064B, 0x064C, 0x064D, 0x064E,
    0x00F4, 0x064F, 0x0650, 0x00F7,
    0x0651, 0x00F9, 0x0652, 0x00FB,
    0x00FC, 0x200E, 0x200F, 0xF899,
};

static const UINT8 page00[256] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, /* 0x00-0x07 */
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, /* 0x08-0x0f */
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, /* 0x10-0x17 */
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, /* 0x18-0x1f */
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, /* 0x20-0x27 */
    0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, /* 0x28-0x2f */
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, /* 0x30-0x37 */
    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, /* 0x38-0x3f */
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, /* 0x40-0x47 */
    0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, /* 0x48-0x4f */
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, /* 0x50-0x57 */
    0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, /* 0x58-0x5f */
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, /* 0x60-0x67 */
    0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, /* 0x68-0x6f */
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, /* 0x70-0x77 */
    0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, /* 0x78-0x7f */

    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x80-0x87 */
    0x00, 0x00, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x8F, /* 0x88-0x8f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x90-0x97 */
    0x98, 0x00, 0x9A, 0x00, 0x00, 0x00, 0x00, 0x9F, /* 0x98-0x9f */
    0xA0, 0x00, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, /* 0xa0-0xa7 */
    0xA8, 0xA9, 0x00, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7,
    0xB8, 0xB9, 0x00, 0xBB, 0xBC, 0xBD, 0xBE, 0x00,
    0xE0, 0x00, 0xE2, 0x00, 0x00, 0x00, 0x00, 0xE7,
    0xE8, 0xE9, 0xEA, 0xEB, 0x00, 0x00, 0xEE, 0xEF,
    0x00, 0x00, 0x00, 0x00, 0xF4, 0x00, 0x00, 0xF7,
    0x00, 0xF9, 0x00, 0xFB, 0xFC, 0x00, 0x00, 0x00,
};
static const UINT8 page01[256] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x8C, 0x9C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x46, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static const UINT8 page02[256] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x00-0x07 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x08-0x0f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10-0x17 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x18-0x1f */

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x20-0x27 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x28-0x2f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x30-0x37 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x38-0x3f */

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x40-0x47 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x48-0x4f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x50-0x57 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x58-0x5f */

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x60-0x67 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x68-0x6f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x70-0x77 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x78-0x7f */

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x80-0x87 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x88-0x8f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x90-0x97 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x98-0x9f */

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa0-0xa7 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa8-0xaf */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xb0-0xb7 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xb8-0xbf */

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x00, /* 0xc0-0xc7 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xc8-0xcf */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xd0-0xd7 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xd8-0xdf */
};

static const UINT8 page06[256] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x00-0x07 */
    0x00, 0x00, 0x00, 0x00, 0xA1, 0x00, 0x00, 0x00, /* 0x08-0x0f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10-0x17 */
    0x00, 0x00, 0x00, 0xBA, 0x00, 0x00, 0x00, 0xBF, /* 0x18-0x1f */
    0x00, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, /* 0x20-0x27 */
    0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, /* 0x28-0x2f */
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD8, /* 0x30-0x37 */
    0xD9, 0xDA, 0xDB, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x38-0x3f */
    0xDC, 0xDD, 0xDE, 0xDF, 0xE1, 0xE3, 0xE4, 0xE5, /* 0x40-0x47 */
    0xE6, 0xEC, 0xED, 0xF0, 0xF1, 0xF2, 0xF3, 0xF5, /* 0x48-0x4f */
    0xF6, 0xF8, 0xFA, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x50-0x57 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x58-0x5f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x60-0x67 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x68-0x6f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x70-0x77 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x00, /* 0x78-0x7f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8D, 0x00, /* 0x80-0x87 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x88-0x8f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x90-0x97 */
    0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x98-0x9f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa0-0xa7 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, /* 0xa8-0xaf */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xb0-0xb7 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xb8-0xbf */
};


static const UINT8 page20[256] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x00-0x07 */
    0x00, 0x00, 0x00, 0x00, 0x9D, 0x9E, 0xFD, 0xFE, /* 0x08-0x0f */
    0x00, 0x00, 0x00, 0x96, 0x97, 0x00, 0x00, 0x00, /* 0x10-0x17 */
    0x91, 0x92, 0x82, 0x00, 0x93, 0x94, 0x84, 0x00, /* 0x18-0x1f */
    0x86, 0x87, 0x95, 0x00, 0x00, 0x00, 0x85, 0x00, /* 0x20-0x27 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x28-0x2f */
    0x89, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x30-0x37 */
    0x00, 0x8B, 0x9B, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x38-0x3f */
};

static const UINT8 page21[256] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x00-0x07 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x08-0x0f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10-0x17 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x18-0x1f */
    0x00, 0x00, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x20-0x27 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x28-0x2f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x30-0x37 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x38-0x3f */
};

static const UINT8 pageF8[256] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x00-0x07 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x08-0x0f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10-0x17 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x18-0x1f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x20-0x27 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x28-0x2f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x30-0x37 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x38-0x3f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x40-0x47 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x48-0x4f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x50-0x57 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x58-0x5f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x60-0x67 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x68-0x6f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x70-0x77 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x78-0x7f */

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x80-0x87 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x88-0x8f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, /* 0x90-0x97 */
    0xC0, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x98-0x9f */
};
static const UINT8 pageFE[256] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x00-0x07 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x08-0x0f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10-0x17 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x18-0x1f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x20-0x27 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x28-0x2f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x30-0x37 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x38-0x3f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x40-0x47 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x48-0x4f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x50-0x57 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x58-0x5f */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x60-0x67 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x68-0x6f */
    0xF0, 0xF0, 0xF1, 0x00, 0xF2, 0x00, 0xF3, 0xF3, /* 0x70-0x77 */
    0xF5, 0xF5, 0xF6, 0xF6, 0xF8, 0xF8, 0xFA, 0xFA, /* 0x78-0x7f */

    0xC1, 0xC2, 0xC2, 0xC3, 0xC3, 0xC4, 0xC4, 0xC5, /* 0x80-0x87 */
    0xC5, 0xC6, 0xC6, 0xC6, 0xC6, 0xC7, 0xC7, 0xC8, /* 0x88-0x8f */
    0xC8, 0xC8, 0xC8, 0xC9, 0xC9, 0xCA, 0xCA, 0xCA, /* 0x90-0x97 */
    0xCA, 0xCB, 0xCB, 0xCB, 0xCB, 0xCC, 0xCC, 0xCC, /* 0x98-0x9f */
    0xCC, 0xCD, 0xCD, 0xCD, 0xCD, 0xCE, 0xCE, 0xCE, /* 0xa0-0xa7 */
    0xCE, 0xCF, 0xCF, 0xD0, 0xD0, 0xD1, 0xD1, 0xD2, /* 0xa8-0xaf */
    0xD2, 0xD3, 0xD3, 0xD3, 0xD3, 0xD4, 0xD4, 0xD4, /* 0xb0-0xb7 */
    0xD4, 0xD5, 0xD5, 0xD5, 0xD5, 0xD6, 0xD6, 0xD6, /* 0xb8-0xbf */
    0xD6, 0xD8, 0xD8, 0xD8, 0xD8, 0xD9, 0xD9, 0xD9, /* 0xc0-0xc7 */
    0xD9, 0xDA, 0xDA, 0xDA, 0xDA, 0xDB, 0xDB, 0xDB, /* 0xc8-0xcf */
    0xDB, 0xDD, 0xDD, 0xDD, 0xDD, 0xDE, 0xDE, 0xDE, /* 0xd0-0xd7 */
    0xDE, 0xDF, 0xDF, 0xDF, 0xDF, 0xE1, 0xE1, 0xE1, /* 0xd8-0xdf */
    0xE1, 0xE3, 0xE3, 0xE3, 0xE3, 0xE4, 0xE4, 0xE4, /* 0xe0-0xef */
    0xE4, 0xE5, 0xE5, 0xE5, 0xE5, 0xE6, 0xE6, 0xEC, /* 0xe8-0xef */
    0xEC, 0xED, 0xED, 0xED, 0xED, 0x00, 0x00, 0x00, /* 0xf0-0xf7 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xf8-0xff */

};
static const UINT8 pageFF[256] =
{
    0x00, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, /* 0x00-0x07 */
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, /* 0x08-0x0f */
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, /* 0x10-0x17 */
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x00, /* 0x18-0x1f */
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, /* 0x20-0x27 */
    0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, /* 0x28-0x2f */
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, /* 0x30-0x37 */
    0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, /* 0x38-0x3f */
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, /* 0x40-0x47 */
    0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, /* 0x48-0x4f */
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, /* 0x50-0x57 */
    0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x00, /* 0x58-0x5f */


};
static const UINT8 *CONST page_uni2charset[256] =
{
    page00, page01, page02, NULL, NULL, NULL, page06, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,

    page20, page21, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,

    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,//40
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,

    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,//60
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,

    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,//80
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,

    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,//a0
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,


    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,//c0
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,

    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,//e0
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    pageF8, NULL, NULL, NULL, NULL, NULL, pageFE, pageFF,

};

static INT32 uni2char(UINT16 uni, UINT8 *out, UINT32 boundlen)
{
    UINT8 *uni2charset;
    UINT8 cl = uni & 0x00ff;
    UINT8 ch = (uni & 0xff00) >> 8;

    if (boundlen <= 0)
        return -1;

    uni2charset = (UINT8 *)page_uni2charset[ch];
    if (uni2charset && uni2charset[cl])
        out[0] = uni2charset[cl];
    else
        return -2;
    return 1;
}

static INT32 char2uni(UINT8 *rawstring, UINT32 boundlen, UINT16 *uni)
{
    *uni = charset2uni[*rawstring];
    if (*uni == 0x0000)
        return -2;
    return 1;
}

static struct ML_Table table =
{
    (UINT8 *)"CP1256",
    uni2char,
    char2uni,
    NULL,
    NULL,
};

UINT32 ML_InitCP1256(void)
{
    return ML_RegisterTable(&table);
}

VOID ML_ExitCP1256(void)
{
    ML_UnRegisterTable(&table);
}

#endif

