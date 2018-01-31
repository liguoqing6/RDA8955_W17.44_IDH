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





#include "coder.h"

const HuffInfo huffTabCoupleInfo[5] =
{
    /* table 0 = unused */
    /* table 1 = unused */
    { 2, {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  0},
    { 6, {1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  3},
    { 8, {1, 0, 2, 2, 2, 2, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0}, 10},
    {10, {1, 0, 2, 0, 4, 4, 4, 4, 4, 8, 0, 0, 0, 0, 0, 0}, 25},
    {16, {1, 0, 1, 1, 4, 4, 8, 8, 9, 9, 8, 2, 2, 3, 1, 2}, 56},
};

const unsigned short huffTabCouple[119] =
{
    /* couple table 2 [3] */
    1, 0, 2,

    /* couple table 3 [7] */
    3, 2, 4, 5, 1, 0, 6,

    /* couple table 4 [15] */
    7, 6, 8, 5, 9, 4, 10, 3, 11, 2, 12, 0, 1, 13, 14,

    /* couple table 5 [31] */
    15, 14, 16, 12, 13, 17, 18, 10, 11, 19, 20, 8, 9, 21, 22, 6,
    7, 23, 24, 4, 5, 25, 26, 0, 1, 2, 3, 27, 28, 29, 30,

    /* couple table 6 [63] */
    31, 30, 32, 28, 29, 33, 34, 26, 27, 35, 36, 22, 23, 24, 25, 37,
    38, 39, 40, 18, 19, 20, 21, 41, 42, 43, 44, 13, 14, 15, 16, 17,
    45, 46, 47, 48, 9, 10, 11, 12, 49, 50, 51, 52, 53, 5, 6, 7,
    8, 54, 55, 56, 57, 4, 58, 3, 59, 2, 60, 61, 1, 0, 62
};

const HuffInfo huffTabPowerInfo[13] =
{
    {12, {0, 0, 3, 8, 3, 1, 1, 1, 1, 0, 2, 4, 0, 0, 0, 0},   0},
    {16, {0, 0, 6, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 0, 3, 2},  24},
    {14, {0, 0, 3, 8, 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0},  48},
    {13, {0, 0, 5, 4, 3, 0, 3, 0, 3, 1, 1, 0, 4, 0, 0, 0},  72},
    {14, {0, 0, 5, 3, 4, 3, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0},  96},
    {14, {0, 0, 5, 4, 3, 0, 2, 3, 1, 1, 1, 1, 1, 2, 0, 0}, 120},
    {16, {0, 1, 4, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 4}, 144},
    {15, {0, 1, 4, 2, 3, 0, 3, 0, 3, 1, 1, 1, 0, 3, 2, 0}, 168},
    {13, {0, 0, 6, 2, 2, 2, 2, 2, 3, 1, 1, 1, 2, 0, 0, 0}, 192},
    {14, {0, 0, 6, 2, 2, 3, 0, 3, 1, 1, 1, 1, 0, 4, 0, 0}, 216},
    {14, {0, 1, 3, 4, 2, 3, 0, 2, 3, 1, 1, 1, 1, 2, 0, 0}, 240},
    {16, {0, 1, 3, 4, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 4}, 264},
    {14, {0, 1, 4, 2, 3, 0, 3, 1, 1, 1, 1, 0, 1, 6, 0, 0}, 288},
};

const unsigned short huffTabPower[312] =
{
    /* power table 0 [24] */
    10, 11, 12, 0, 4, 5, 6, 7, 8, 9, 13, 2, 3, 14, 1, 15,
    16, 17, 18, 19, 20, 21, 22, 23,
    /* power table 1 [24] */
    6, 7, 8, 9, 10, 11, 5, 12, 3, 4, 13, 2, 14, 1, 15, 0,
    16, 17, 18, 19, 20, 21, 22, 23,
    /* power table 2 [24] */
    11, 12, 13, 5, 6, 7, 8, 9, 10, 14, 15, 4, 16, 17, 3, 18,
    2, 19, 1, 20, 0, 21, 22, 23,
    /* power table 3 [24] */
    9, 10, 11, 12, 13, 8, 14, 15, 16, 6, 7, 17, 4, 5, 18, 2,
    3, 19, 1, 20, 0, 21, 22, 23,
    /* power table 4 [24] */
    10, 11, 12, 13, 14, 8, 9, 15, 6, 7, 16, 17, 4, 5, 18, 19,
    3, 20, 2, 21, 0, 1, 22, 23,
    /* power table 5 [24] */
    9, 10, 11, 12, 13, 7, 8, 14, 15, 6, 16, 17, 5, 18, 3, 4,
    19, 2, 20, 1, 0, 21, 22, 23,
    /* power table 6 [24] */
    12, 9, 10, 11, 13, 8, 14, 7, 15, 16, 6, 17, 5, 18, 4, 19,
    3, 20, 0, 2, 1, 21, 22, 23,
    /* power table 7 [24] */
    12, 10, 11, 13, 14, 9, 15, 7, 8, 16, 5, 6, 17, 4, 18, 19,
    3, 2, 20, 0, 1, 21, 22, 23,
    /* power table 8 [24] */
    8, 9, 10, 11, 12, 13, 7, 14, 6, 15, 5, 16, 4, 17, 3, 18,
    0, 1, 2, 19, 20, 21, 22, 23,
    /* power table 9 [24] */
    8, 9, 10, 11, 12, 13, 7, 14, 6, 15, 4, 5, 16, 3, 17, 18,
    19, 2, 20, 1, 0, 21, 22, 23,
    /* power table 10 [24] */
    12, 10, 11, 13, 7, 8, 9, 14, 6, 15, 4, 5, 16, 3, 17, 2,
    18, 19, 1, 20, 21, 0, 22, 23,
    /* power table 11 [24] */
    12, 11, 13, 14, 8, 9, 10, 15, 6, 7, 16, 5, 17, 18, 4, 19,
    3, 2, 1, 20, 0, 21, 22, 23,
    /* power table 12 [24] */
    12, 10, 11, 13, 14, 9, 15, 8, 16, 17, 6, 7, 18, 5, 19, 4,
    20, 0, 1, 2, 3, 21, 22, 23,
};

const HuffInfo huffTabVectorInfo[7] =
{
    {16, { 1,  0,  0,  2,  2,  5,  8, 15, 31, 33, 28, 17, 15,  8,  8,   8},    0},
    {16, { 1,  0,  0,  2,  4,  5,  7, 16, 18, 12, 11,  7,  3,  5,  1,   2},  181},
    {16, { 1,  0,  1,  2,  4,  2,  5,  8,  7,  8,  2,  3,  1,  1,  1,   2},  275},
    {16, { 0,  1,  0,  2,  5, 12,  7, 27, 22, 41, 32, 41, 55, 23, 32, 220},  323},
    {15, { 0,  1,  0,  5,  7,  4,  8,  9, 17, 10, 13, 17, 12, 14, 92,   0},  843},
    {15, { 0,  1,  0,  5,  6,  8,  8,  8,  4,  7, 11, 23, 21, 10, 80,   0}, 1052},
    {11, { 1,  0,  0,  5,  0,  9,  1,  7,  4,  3,  2,  0,  0,  0,  0,   0}, 1244},

};

const unsigned short huffTabVector[1276] =
{
    /* vector table 0 [181] */
    0x0000, 0x1010, 0x1001, 0x2011, 0x1002, 0x1020, 0x1030, 0x2021, 0x2012, 0x1003, 0x1040, 0x1050, 0x2031, 0x2041, 0x2022, 0x2013,
    0x1004, 0x2014, 0x1060, 0x1070, 0x1080, 0x2051, 0x2061, 0x2032, 0x2042, 0x2023, 0x2024, 0x1005, 0x2015, 0x1006, 0x2016, 0x1007,
    0x2017, 0x1090, 0x10a0, 0x2071, 0x2081, 0x2091, 0x20a1, 0x2052, 0x2062, 0x2072, 0x2082, 0x2033, 0x2043, 0x2053, 0x2063, 0x2034,
    0x2044, 0x2054, 0x2025, 0x2035, 0x2045, 0x2026, 0x2036, 0x2027, 0x2037, 0x1008, 0x2018, 0x2028, 0x1009, 0x2019, 0x100a, 0x201a,
    0x10b0, 0x20b1, 0x2092, 0x20a2, 0x20b2, 0x2073, 0x2083, 0x2093, 0x20a3, 0x2064, 0x2074, 0x2084, 0x2094, 0x2055, 0x2065, 0x2075,
    0x2085, 0x2046, 0x2056, 0x2047, 0x2057, 0x2038, 0x2048, 0x2058, 0x2029, 0x2039, 0x2049, 0x2059, 0x202a, 0x203a, 0x100b, 0x201b,
    0x202b, 0x10c0, 0x10d0, 0x20c1, 0x20d1, 0x20c2, 0x20b3, 0x20a4, 0x20b4, 0x2095, 0x20a5, 0x2066, 0x2076, 0x2086, 0x2067, 0x2077,
    0x2087, 0x2068, 0x2078, 0x2069, 0x204a, 0x205a, 0x203b, 0x204b, 0x100c, 0x201c, 0x202c, 0x100d, 0x201d, 0x20d2, 0x20c3, 0x20c4,
    0x20b5, 0x2096, 0x20a6, 0x2097, 0x20a7, 0x2088, 0x20a8, 0x2079, 0x2089, 0x206a, 0x205b, 0x206b, 0x203c, 0x202d, 0x20d3, 0x20d4,
    0x20c5, 0x20b6, 0x20c6, 0x20b7, 0x2098, 0x207a, 0x208a, 0x207b, 0x204c, 0x205c, 0x206c, 0x203d, 0x204d, 0x20d5, 0x20c7, 0x20b8,
    0x2099, 0x20a9, 0x209a, 0x20aa, 0x205d, 0x20d6, 0x20d7, 0x20c8, 0x20ba, 0x208b, 0x209b, 0x207c, 0x206d, 0x20d8, 0x20b9, 0x20c9,
    0x20ab, 0x208c, 0x209c, 0x207d, 0x208d,

    /* vector table 1 [94] */
    0x0000, 0x1010, 0x1001, 0x1020, 0x2011, 0x1002, 0x2012, 0x1030, 0x2021, 0x2022, 0x1003, 0x2013, 0x1040, 0x2031, 0x2041, 0x2032,
    0x2023, 0x1004, 0x2014, 0x1050, 0x1060, 0x2051, 0x2061, 0x2042, 0x2052, 0x2033, 0x2043, 0x2024, 0x2034, 0x1005, 0x2015, 0x2025,
    0x1006, 0x2016, 0x2026, 0x1070, 0x2071, 0x2081, 0x2062, 0x2072, 0x2053, 0x2063, 0x2044, 0x2054, 0x2035, 0x2045, 0x2036, 0x1007,
    0x2017, 0x2027, 0x1008, 0x2018, 0x2028, 0x1080, 0x1090, 0x2082, 0x2073, 0x2064, 0x2055, 0x2065, 0x2046, 0x2037, 0x2038, 0x1009,
    0x2019, 0x2091, 0x2092, 0x2083, 0x2074, 0x2084, 0x2075, 0x2056, 0x2066, 0x2047, 0x2048, 0x2029, 0x2093, 0x2085, 0x2076, 0x2057,
    0x2067, 0x2058, 0x2039, 0x2094, 0x2086, 0x2049, 0x2095, 0x2077, 0x2087, 0x2068, 0x2059, 0x2096, 0x2078, 0x2069,

    /* vector table 2 [48] */
    0x0000, 0x1001, 0x1010, 0x2011, 0x1020, 0x2021, 0x1002, 0x2012, 0x2022, 0x2013, 0x1030, 0x2031, 0x2032, 0x1003, 0x2023, 0x1040,
    0x2041, 0x2042, 0x2033, 0x1004, 0x2014, 0x2024, 0x1005, 0x1050, 0x2051, 0x2043, 0x2034, 0x2015, 0x2025, 0x1006, 0x1060, 0x2061,
    0x2052, 0x2062, 0x2053, 0x2044, 0x2035, 0x2016, 0x2045, 0x2026, 0x2063, 0x2054, 0x2036, 0x2046, 0x2064, 0x2055, 0x2065, 0x2056,

    /* vector table 3 [520] */
    0x0000, 0x1200, 0x1001, 0x1040, 0x2240, 0x1008, 0x2048, 0x2009, 0x1400, 0x2440, 0x2208, 0x3248, 0x2201, 0x2041, 0x3241, 0x3209,
    0x3049, 0x4249, 0x1002, 0x200a, 0x1080, 0x2088, 0x3288, 0x1010, 0x2050, 0x2011, 0x3051, 0x1600, 0x2640, 0x2280, 0x2480, 0x2408,
    0x3448, 0x3488, 0x3250, 0x2401, 0x3441, 0x3281, 0x3409, 0x4449, 0x3089, 0x4289, 0x3211, 0x4251, 0x2202, 0x2042, 0x3242, 0x320a,
    0x304a, 0x424a, 0x2012, 0x3052, 0x1003, 0x200b, 0x10c0, 0x22c0, 0x20c8, 0x32c8, 0x2210, 0x2090, 0x3290, 0x1018, 0x2058, 0x2081,
    0x4489, 0x3411, 0x3091, 0x4291, 0x2019, 0x3059, 0x3212, 0x4252, 0x304b, 0x2013, 0x1004, 0x200c, 0x1800, 0x2840, 0x2680, 0x24c0,
    0x1100, 0x2608, 0x3648, 0x3688, 0x34c8, 0x2410, 0x3450, 0x3258, 0x2098, 0x2601, 0x3641, 0x3481, 0x20c1, 0x32c1, 0x4649, 0x30c9,
    0x42c9, 0x4451, 0x4491, 0x42d1, 0x4259, 0x3099, 0x3442, 0x3282, 0x340a, 0x444a, 0x308a, 0x428a, 0x3092, 0x4292, 0x201a, 0x305a,
    0x2203, 0x2043, 0x320b, 0x424b, 0x3053, 0x2300, 0x2808, 0x3308, 0x3490, 0x20d0, 0x32d0, 0x2218, 0x3298, 0x1020, 0x2060, 0x34c1,
    0x3609, 0x4689, 0x30d1, 0x3219, 0x4299, 0x2021, 0x3061, 0x2402, 0x2082, 0x3482, 0x448a, 0x3412, 0x4452, 0x3243, 0x340b, 0x3213,
    0x4253, 0x201b, 0x305b, 0x2044, 0x2014, 0x2880, 0x26c0, 0x3848, 0x36c8, 0x2108, 0x2610, 0x3650, 0x34d0, 0x2110, 0x3310, 0x2418,
    0x3498, 0x3681, 0x3301, 0x44c9, 0x46c9, 0x4309, 0x3611, 0x4651, 0x44d1, 0x4459, 0x42d9, 0x30a1, 0x3642, 0x20c2, 0x464a, 0x42ca,
    0x4492, 0x30d2, 0x42d2, 0x321a, 0x425a, 0x445a, 0x309a, 0x429a, 0x2022, 0x444b, 0x308b, 0x428b, 0x304c, 0x3054, 0x2500, 0x3888,
    0x3508, 0x3850, 0x3690, 0x3458, 0x20d8, 0x32d8, 0x2220, 0x3260, 0x20a0, 0x32a0, 0x2801, 0x3841, 0x2101, 0x3809, 0x4849, 0x3109,
    0x4509, 0x4691, 0x3111, 0x4311, 0x3419, 0x4499, 0x30d9, 0x3221, 0x4261, 0x42a1, 0x2602, 0x3682, 0x32c2, 0x34c2, 0x360a, 0x468a,
    0x30ca, 0x44ca, 0x3612, 0x44d2, 0x449a, 0x3062, 0x4262, 0x2403, 0x3443, 0x2083, 0x3283, 0x4453, 0x4293, 0x321b, 0x425b, 0x309b,
    0x2204, 0x3244, 0x320c, 0x424c, 0x3214, 0x36d0, 0x3510, 0x20e0, 0x3501, 0x4889, 0x4851, 0x3502, 0x310a, 0x430a, 0x450a, 0x4852,
    0x465a, 0x30da, 0x30a2, 0x3483, 0x42cb, 0x3413, 0x3093, 0x4493, 0x3063, 0x2084, 0x444c, 0x4254, 0x28c0, 0x38c8, 0x2810, 0x3658,
    0x3518, 0x2820, 0x3460, 0x36c1, 0x4709, 0x46d1, 0x4659, 0x44a1, 0x36c2, 0x4692, 0x3112, 0x341a, 0x42da, 0x3222, 0x3422, 0x2603,
    0x360b, 0x448b, 0x42d3, 0x44d3, 0x445b, 0x2023, 0x3284, 0x20c4, 0x340c, 0x360c, 0x428c, 0x3414, 0x2700, 0x2900, 0x3708, 0x3908,
    0x3890, 0x38d0, 0x3710, 0x2618, 0x2818, 0x3858, 0x3698, 0x3898, 0x34d8, 0x36d8, 0x38d8, 0x2118, 0x3318, 0x3718, 0x2420, 0x2620,
    0x3660, 0x3860, 0x34a0, 0x36a0, 0x32e0, 0x34e0, 0x36e0, 0x2120, 0x3320, 0x3881, 0x38c1, 0x3701, 0x3901, 0x48c9, 0x4909, 0x3811,
    0x4891, 0x48d1, 0x4511, 0x4711, 0x3619, 0x3819, 0x4859, 0x4699, 0x4899, 0x44d9, 0x46d9, 0x48d9, 0x3119, 0x4319, 0x4519, 0x4719,
    0x3421, 0x3621, 0x3821, 0x4461, 0x4661, 0x4861, 0x46a1, 0x30e1, 0x42e1, 0x44e1, 0x46e1, 0x3121, 0x4321, 0x2802, 0x3842, 0x3882,
    0x38c2, 0x2102, 0x3302, 0x3702, 0x380a, 0x484a, 0x488a, 0x46ca, 0x48ca, 0x470a, 0x3812, 0x4652, 0x4892, 0x46d2, 0x48d2, 0x4312,
    0x4512, 0x4712, 0x361a, 0x381a, 0x485a, 0x469a, 0x489a, 0x44da, 0x46da, 0x311a, 0x431a, 0x451a, 0x3622, 0x4462, 0x4662, 0x42a2,
    0x44a2, 0x46a2, 0x30e2, 0x42e2, 0x44e2, 0x2803, 0x3643, 0x3843, 0x3683, 0x3883, 0x20c3, 0x32c3, 0x34c3, 0x36c3, 0x38c3, 0x2103,
    0x3303, 0x3503, 0x3703, 0x380b, 0x464b, 0x484b, 0x468b, 0x488b, 0x30cb, 0x44cb, 0x46cb, 0x48cb, 0x310b, 0x430b, 0x450b, 0x470b,
    0x3613, 0x3813, 0x4653, 0x4853, 0x4693, 0x4893, 0x30d3, 0x46d3, 0x3113, 0x4313, 0x4513, 0x341b, 0x361b, 0x381b, 0x465b, 0x485b,
    0x429b, 0x449b, 0x469b, 0x30db, 0x42db, 0x44db, 0x46db, 0x311b, 0x431b, 0x3223, 0x3423, 0x3623, 0x4263, 0x4463, 0x4663, 0x30a3,
    0x42a3, 0x44a3, 0x30e3, 0x42e3, 0x2404, 0x2604, 0x2804, 0x3444, 0x3644, 0x3844, 0x3484, 0x3684, 0x32c4, 0x34c4, 0x36c4, 0x2104,
    0x3304, 0x380c, 0x464c, 0x484c, 0x308c, 0x448c, 0x468c, 0x30cc, 0x42cc, 0x44cc, 0x46cc, 0x310c, 0x430c, 0x3614, 0x4454, 0x4654,
    0x3094, 0x4294, 0x4494, 0x4694, 0x30d4, 0x42d4, 0x44d4, 0x201c, 0x321c, 0x341c, 0x361c, 0x305c, 0x425c, 0x445c, 0x465c, 0x309c,
    0x429c, 0x449c, 0x30dc, 0x42dc, 0x2024, 0x3224, 0x3064, 0x4264,

    /* vector table 4 [209] */
    0x0000, 0x1200, 0x1040, 0x1008, 0x1001, 0x2009, 0x2240, 0x2208, 0x2048, 0x3248, 0x2201, 0x2041, 0x3049, 0x3241, 0x3209, 0x4249,
    0x1002, 0x1400, 0x2440, 0x1080, 0x3288, 0x1010, 0x2011, 0x3051, 0x200a, 0x2280, 0x3448, 0x2088, 0x2050, 0x3250, 0x4289, 0x4251,
    0x2042, 0x304a, 0x2408, 0x2210, 0x2401, 0x3441, 0x2081, 0x3281, 0x3409, 0x4449, 0x3089, 0x3211, 0x2202, 0x3242, 0x320a, 0x424a,
    0x2012, 0x3052, 0x1003, 0x1600, 0x2640, 0x2480, 0x3488, 0x2090, 0x3290, 0x3091, 0x4291, 0x2019, 0x200b, 0x10c0, 0x22c0, 0x20c8,
    0x32c8, 0x1018, 0x2058, 0x3481, 0x4489, 0x4451, 0x3059, 0x308a, 0x3212, 0x4252, 0x2608, 0x3648, 0x2410, 0x3450, 0x3609, 0x42c9,
    0x3411, 0x3219, 0x3442, 0x2082, 0x3282, 0x444a, 0x428a, 0x2203, 0x2043, 0x320b, 0x304b, 0x3490, 0x2218, 0x3258, 0x2601, 0x3641,
    0x32c1, 0x4649, 0x30c9, 0x4259, 0x2402, 0x340a, 0x3243, 0x2680, 0x20d0, 0x32d0, 0x2098, 0x20c1, 0x4491, 0x30d1, 0x2602, 0x3092,
    0x4292, 0x201a, 0x305a, 0x424b, 0x2013, 0x24c0, 0x26c0, 0x3688, 0x34c8, 0x36c8, 0x2610, 0x3650, 0x3690, 0x34d0, 0x2418, 0x2618,
    0x3458, 0x3658, 0x3298, 0x3498, 0x20d8, 0x32d8, 0x3681, 0x34c1, 0x36c1, 0x4689, 0x44c9, 0x46c9, 0x3611, 0x4651, 0x4691, 0x42d1,
    0x44d1, 0x3419, 0x3619, 0x4459, 0x4659, 0x3099, 0x4299, 0x4499, 0x30d9, 0x42d9, 0x3642, 0x3482, 0x3682, 0x20c2, 0x32c2, 0x34c2,
    0x360a, 0x464a, 0x448a, 0x468a, 0x30ca, 0x42ca, 0x44ca, 0x3412, 0x3612, 0x4452, 0x4652, 0x4492, 0x30d2, 0x42d2, 0x321a, 0x341a,
    0x425a, 0x445a, 0x309a, 0x429a, 0x2403, 0x2603, 0x3443, 0x3643, 0x2083, 0x3283, 0x3483, 0x20c3, 0x32c3, 0x340b, 0x360b, 0x444b,
    0x464b, 0x308b, 0x428b, 0x448b, 0x30cb, 0x42cb, 0x3213, 0x3413, 0x3053, 0x4253, 0x4453, 0x3093, 0x4293, 0x201b, 0x321b, 0x305b,
    0x425b,

    /* vector table 5 [192] */
    0x0000, 0x1100, 0x1040, 0x1010, 0x1004, 0x1001, 0x2140, 0x2050, 0x2014, 0x2101, 0x2041, 0x2005, 0x2110, 0x3150, 0x2104, 0x2044,
    0x3054, 0x2011, 0x3105, 0x3015, 0x3144, 0x3114, 0x4154, 0x3141, 0x3111, 0x3051, 0x3045, 0x4055, 0x1200, 0x1008, 0x4151, 0x4145,
    0x4115, 0x5155, 0x1002, 0x2006, 0x2240, 0x1080, 0x1020, 0x2009, 0x2180, 0x2090, 0x2060, 0x2024, 0x2018, 0x2102, 0x2012, 0x2210,
    0x3190, 0x2120, 0x3064, 0x2048, 0x2201, 0x2081, 0x2021, 0x3019, 0x2042, 0x3016, 0x3250, 0x2204, 0x3244, 0x2084, 0x3184, 0x3094,
    0x3124, 0x3148, 0x3058, 0x3241, 0x3181, 0x3091, 0x3061, 0x3085, 0x3025, 0x4125, 0x4065, 0x3049, 0x3142, 0x3112, 0x3052, 0x3106,
    0x3046, 0x3160, 0x3214, 0x4254, 0x4194, 0x4164, 0x2108, 0x3118, 0x3211, 0x3121, 0x4161, 0x3205, 0x5165, 0x3109, 0x4149, 0x4119,
    0x4059, 0x5159, 0x4152, 0x4146, 0x4116, 0x4056, 0x2280, 0x20a0, 0x4251, 0x4191, 0x4185, 0x4215, 0x4095, 0x3029, 0x2022, 0x200a,
    0x3290, 0x2220, 0x3260, 0x31a0, 0x3284, 0x4294, 0x3224, 0x4264, 0x30a4, 0x41a4, 0x2208, 0x3248, 0x2088, 0x3188, 0x3218, 0x4158,
    0x4258, 0x3098, 0x4198, 0x2028, 0x3128, 0x3068, 0x4168, 0x3281, 0x4291, 0x3221, 0x4261, 0x30a1, 0x41a1, 0x4245, 0x4285, 0x5255,
    0x5195, 0x5295, 0x4225, 0x5265, 0x40a5, 0x51a5, 0x3209, 0x4249, 0x3089, 0x4189, 0x4219, 0x5259, 0x4099, 0x5199, 0x4129, 0x4069,
    0x5169, 0x2202, 0x3242, 0x2082, 0x3182, 0x3212, 0x4252, 0x3092, 0x4192, 0x3122, 0x3062, 0x4162, 0x3206, 0x4246, 0x3086, 0x4186,
    0x4216, 0x5156, 0x5256, 0x4096, 0x5196, 0x3026, 0x4126, 0x4066, 0x5166, 0x310a, 0x304a, 0x414a, 0x301a, 0x411a, 0x405a, 0x515a,

    /* vector table 6 [32] */
    0x0000, 0x1100, 0x1040, 0x1010, 0x1004, 0x1001, 0x2140, 0x2110, 0x2050, 0x2104, 0x2044, 0x2014, 0x2101, 0x2011, 0x2005, 0x2041,
    0x3150, 0x3144, 0x3054, 0x3141, 0x3051, 0x3045, 0x3015, 0x3114, 0x3111, 0x3105, 0x4055, 0x4154, 0x4145, 0x4115, 0x4151, 0x5155,
};
