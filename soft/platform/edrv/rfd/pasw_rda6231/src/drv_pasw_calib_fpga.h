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





















#ifndef PASW_RDA6231_CALIB_H
#define PASW_RDA6231_CALIB_H

#include "calib_m.h"
#include "rf_names.h"

// Calibration parameter accessors
// ------------------------------------------------------------------------
#define PA_TIME(n)                  (g_paCalibPtr->pa->times[(n)])


// Default Calibration Times
// ------------------------------------------------------------------------
#define DEFAULT_CALIB_RAMP_UP           4
#define DEFAULT_CALIB_TX_EN_UP          9
#define DEFAULT_CALIB_RAMP_DN           -12
#define DEFAULT_CALIB_TX_EN_DN          2

#define DEFAULT_CALIB_PA_TIMES          {DEFAULT_CALIB_RAMP_UP, \
                                         DEFAULT_CALIB_TX_EN_UP, \
                                         DEFAULT_CALIB_RAMP_DN, \
                                         DEFAULT_CALIB_TX_EN_DN}
// Calibration Times Accessor index
#define PA_TIME_RAMP_UP             0
#define PA_TIME_TX_EN_UP            1
#define PA_TIME_RAMP_DN             2
#define PA_TIME_TX_EN_DN            3


// Default Calibration Parameters
// ------------------------------------------------------------------------

#define DEFAULT_CALIB_PA_PARAM              {}

// Default calibration PAL custom parameters.
// ------------------------------------------------------------------------
#define DEFAULT_CALIB_PCL2DBM_ARFCN_G   { \
    { 3300, 3301 }, /* Pcl  0 to 5 (33 dBm) */ \
    { 3100, 3101 }, /* Pcl  6 (31 dBm) */ \
    { 2900, 2901 }, /* Pcl  7 (29 dBm) */ \
    { 2700, 2701 }, /* Pcl  8 (27 dBm) */ \
    { 2500, 2501 }, /* Pcl  9 (25 dBm) */ \
    { 2300, 2301 }, /* Pcl 10 (23 dBm) */ \
    { 2100, 2101 }, /* Pcl 11 (21 dBm) */ \
    { 1900, 1901 }, /* Pcl 12 (19 dBm) */ \
    { 1700, 1701 }, /* Pcl 13 (17 dBm) */ \
    { 1500, 1501 }, /* Pcl 14 (15 dBm) */ \
    { 1300, 1301 }, /* Pcl 15 (13 dBm) */ \
    { 1100, 1101 }, /* Pcl 16 (11 dBm) */ \
    {  900,  901 }, /* Pcl 17 ( 9 dBm) */ \
    {  700,  701 }, /* Pcl 18 ( 7 dBm) */ \
    {  500,  501 }  /* Pcl 19 to 31 (5 dBm) */ }

#define DEFAULT_CALIB_PCL2DBM_ARFCN_D       { \
    { 3000, 3001 }, /* Pcl  0 (30 dBm) */ \
    { 2800, 2801 }, /* Pcl  1 (28 dBm) */ \
    { 2600, 2601 }, /* Pcl  2 (26 dBm) */ \
    { 2400, 2401 }, /* Pcl  3 (24 dBm) */ \
    { 2200, 2201 }, /* Pcl  4 (22 dBm) */ \
    { 2000, 2001 }, /* Pcl  5 (20 dBm) */ \
    { 1800, 1801 }, /* Pcl  6 (18 dBm) */ \
    { 1600, 1601 }, /* Pcl  7 (16 dBm) */ \
    { 1400, 1401 }, /* Pcl  8 (14 dBm) */ \
    { 1200, 1201 }, /* Pcl  9 (12 dBm) */ \
    { 1000, 1001 }, /* Pcl 10 (10 dBm) */ \
    {  800,  801 }, /* Pcl 11 ( 8 dBm) */ \
    {  600,  601 }, /* Pcl 12 ( 6 dBm) */ \
    {  400,  401 }, /* Pcl 13 ( 4 dBm) */ \
    {  200,  201 }, /* Pcl 14 ( 2 dBm) */ \
    {    0,    1 }, /* Pcl 15 to 28 (0 dBm) */ \
    { 3200, 3201 }  /* Pcl 29 to 31 (32 dBm) */ }

#define DEFAULT_CALIB_PCL2DBM_ARFCN_P       { \
    { 3000, 3001 }, /* Pcl  0 (30 dBm) */ \
    { 2800, 2801 }, /* Pcl  1 (28 dBm) */ \
    { 2600, 2601 }, /* Pcl  2 (26 dBm) */ \
    { 2400, 2401 }, /* Pcl  3 (24 dBm) */ \
    { 2200, 2201 }, /* Pcl  4 (22 dBm) */ \
    { 2000, 2001 }, /* Pcl  5 (20 dBm) */ \
    { 1800, 1801 }, /* Pcl  6 (18 dBm) */ \
    { 1600, 1601 }, /* Pcl  7 (16 dBm) */ \
    { 1400, 1401 }, /* Pcl  8 (14 dBm) */ \
    { 1200, 1201 }, /* Pcl  9 (12 dBm) */ \
    { 1000, 1001 }, /* Pcl 10 (10 dBm) */ \
    {  800,  801 }, /* Pcl 11 ( 8 dBm) */ \
    {  600,  601 }, /* Pcl 12 ( 6 dBm) */ \
    {  400,  401 }, /* Pcl 13 ( 4 dBm) */ \
    {  200,  201 }, /* Pcl 14 ( 2 dBm) */ \
    {    0,    1 }, /* Pcl 15 ( 0 dBm) */ \
    { 3300, 3301 }, /* Pcl 30 (33 dBm) */ \
    { 3200, 3201 }  /* Pcl 31 (32 dBm) */ }

#define DEFAULT_CALIB_PROF_INTERP_G     { \
    180, 190, 200, 220, 240, 280, 300, 350, \
    400, 450, 500, 550, 600, 650, 700, 1000 }

#define DEFAULT_CALIB_PROF_INTERP_DP    { \
    200, 220, 230, 240, 250, 280, 300, 350, \
    400, 450, 500, 550, 600, 650, 700, 1000 }

#define DEFAULT_CALIB_PROFILE_G { \
    180,180,180,180,180,180,180,180,180,180,180,180,180,180,180,180, \
    181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181, \
    182,182,182,182,182,182,182,182,182,182,182,182,182,182,182,182, \
    182,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183, \
    183,184,184,184,184,184,184,184,184,184,184,184,184,184,184,184, \
    184,185,185,185,185,185,185,185,185,185,185,185,185,185,185,185, \
    185,186,186,186,186,186,186,186,186,186,186,186,186,186,186,186, \
    187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,188, \
    188,188,188,188,188,188,188,188,188,188,188,188,188,188,189,189, \
    189,189,189,189,189,189,189,189,189,189,189,190,190,190,190,190, \
    190,190,190,190,190,190,190,190,191,191,191,191,191,191,191,191, \
    191,191,191,191,191,192,192,192,192,192,192,192,192,192,192,192, \
    193,193,193,193,193,193,193,193,193,193,193,193,194,194,194,194, \
    194,194,194,194,194,194,195,195,195,195,195,195,195,195,195,195, \
    196,196,196,196,196,196,196,196,196,196,197,197,197,197,197,197, \
    197,197,197,198,198,198,198,198,198,198,198,198,199,199,199,199, \
    199,199,199,199,199,200,200,200,200,200,200,200,200,200,201,201, \
    201,201,201,201,201,201,202,202,202,202,202,202,202,202,202,203, \
    203,203,203,203,203,203,203,203,204,204,204,204,204,204,204,204, \
    205,205,205,205,205,205,205,205,205,205,206,206,206,206,206,206, \
    206,206,207,207,207,207,207,207,207,207,208,208,208,208,208,208, \
    208,208,208,209,209,209,209,209,209,209,210,210,210,210,210,210, \
    210,210,210,211,211,211,211,211,211,211,212,212,212,212,212,212, \
    212,212,212,213,213,213,213,213,213,213,214,214,214,214,214,214, \
    214,215,215,215,215,215,215,215,215,216,216,216,216,216,216,216, \
    217,217,217,217,217,217,217,217,218,218,218,218,218,218,218,219, \
    219,219,219,219,219,220,220,220,220,220,220,220,221,221,221,221, \
    221,221,222,222,222,222,222,222,222,223,223,223,223,223,223,224, \
    224,224,224,224,224,225,225,225,225,225,225,226,226,226,226,226, \
    227,227,227,227,227,227,228,228,228,228,228,229,229,229,229,229, \
    230,230,230,230,230,231,231,231,231,232,232,232,232,232,233,233, \
    233,233,233,234,234,234,235,235,235,235,235,236,236,236,236,237, \
    237,237,237,237,238,238,238,239,239,239,239,240,240,240,240,241, \
    241,241,241,242,242,242,242,243,243,243,243,244,244,244,245,245, \
    245,245,246,246,246,247,247,247,247,248,248,248,249,249,249,250, \
    250,250,250,251,251,251,252,252,252,252,253,253,253,253,254,254, \
    254,255,255,255,256,256,256,256,257,257,257,258,258,258,258,259, \
    259,259,260,260,260,261,261,261,261,262,262,262,263,263,263,264, \
    264,264,265,265,265,266,266,266,266,267,267,267,268,268,268,269, \
    269,269,270,270,270,271,271,271,272,272,272,272,273,273,274,274, \
    274,274,275,275,276,276,276,276,277,277,277,278,278,278,279,279, \
    279,280,280,280,281,281,281,282,282,282,283,283,283,284,284,284, \
    284,285,285,286,286,286,287,287,287,288,288,289,289,290,290,290, \
    291,291,292,292,293,293,294,294,295,295,296,296,297,297,297,298, \
    299,299,300,300,301,301,302,302,303,303,304,304,305,305,306,306, \
    307,307,308,308,309,309,310,310,311,311,312,312,313,313,314,315, \
    315,316,316,316,317,317,318,319,319,320,320,321,321,322,323,323, \
    323,324,324,325,326,326,327,327,328,328,329,329,330,330,331,331, \
    332,333,333,334,334,335,336,336,337,337,337,338,339,339,340,340, \
    341,342,342,343,344,344,345,346,346,347,347,348,348,349,350,350, \
    351,352,353,353,353,354,355,356,356,357,358,358,359,359,360,361, \
    362,363,363,364,365,366,366,366,367,368,369,369,370,371,372,373, \
    373,374,375,376,376,377,378,379,379,380,381,382,383,384,385,386, \
    386,387,388,389,389,391,392,393,393,394,396,396,397,398,399,400, \
    401,402,403,404,405,406,407,409,409,410,411,413,414,415,417,418, \
    419,421,422,423,424,426,427,428,430,432,434,435,436,438,439,440, \
    443,444,446,447,448,450,451,453,455,457,459,460,461,463,465,467, \
    469,471,473,474,476,478,480,482,484,486,488,492,494,496,498,500, \
    504,509,511,513,522,527,531,536,540,545,554,558,562,566,570,574, \
    579,583,587,591,595,598,602,604,607,609,612,614,617,619,622,624, \
    625,627,629,632,634,637,639,642,644,647,650,653,656,657,658,660, \
    662,666,671,678,682,687,695,704,709,714,726,733,741,748,756,763, \
    767,772,780,788,798,806,815,820,825,833,843,852,861,866,871,879, \
    889,897,906,915,919,924,932,940,948,955,969,976,981,986,996,1000, \
    }

#define DEFAULT_CALIB_PROFILE_DP { \
    200,200,200,200,200,200,200,200,201,201,201,201,201,201,201,201, \
    201,201,202,202,202,202,202,202,202,202,203,203,203,203,203,203, \
    203,203,203,203,204,204,204,204,204,204,204,204,205,205,205,205, \
    205,205,205,205,205,206,206,206,206,206,206,206,206,206,207,207, \
    207,207,207,207,207,207,208,208,208,208,208,208,208,208,208,209, \
    209,209,209,209,209,209,209,209,209,210,210,210,210,210,210,210, \
    210,211,211,211,211,211,211,211,211,211,212,212,212,212,212,212, \
    212,212,212,213,213,213,213,213,213,213,213,214,214,214,214,214, \
    214,214,214,214,215,215,215,215,215,215,215,215,216,216,216,216, \
    216,216,216,216,216,217,217,217,217,217,217,217,217,218,218,218, \
    218,218,218,218,218,219,219,219,219,219,219,219,219,220,220,220, \
    220,220,220,220,220,221,221,221,221,221,221,221,221,222,222,222, \
    222,222,222,222,223,223,223,223,223,223,224,224,224,224,224,224, \
    225,225,225,225,225,226,226,226,226,226,227,227,227,227,227,227, \
    228,228,228,228,228,229,229,229,229,229,229,230,230,230,230,230, \
    230,231,231,231,231,231,231,232,232,232,232,232,233,233,233,233, \
    233,233,233,234,234,234,234,234,235,235,235,235,235,235,236,236, \
    236,236,236,237,237,237,237,237,238,238,238,238,238,239,239,239, \
    239,239,240,240,240,240,240,241,241,241,241,241,242,242,242,242, \
    243,243,243,243,243,244,244,244,244,245,245,245,245,245,246,246, \
    246,246,247,247,247,247,248,248,248,249,249,249,249,250,250,250, \
    250,251,251,251,252,252,252,252,253,253,253,253,254,254,254,255, \
    255,255,255,256,256,256,256,257,257,257,258,258,258,258,259,259, \
    259,259,260,260,260,261,261,261,261,262,262,262,263,263,263,263, \
    264,264,264,264,265,265,265,266,266,266,266,267,267,267,268,268, \
    268,268,269,269,269,270,270,270,271,271,271,271,271,272,272,272, \
    273,273,273,274,274,274,274,275,275,275,276,276,276,277,277,277, \
    278,278,278,278,279,279,279,280,280,280,280,281,281,282,282,282, \
    282,283,283,283,284,284,284,285,285,285,285,286,286,287,287,287, \
    288,288,288,289,289,290,290,290,290,291,291,292,292,292,293,293, \
    294,294,295,295,295,296,296,297,297,298,298,298,299,299,300,300, \
    300,301,302,302,302,303,303,304,304,304,305,305,306,306,307,307, \
    307,308,309,309,309,310,310,311,311,312,312,313,313,313,314,314, \
    314,315,315,316,316,317,317,318,318,319,319,320,320,321,321,322, \
    322,322,323,323,324,324,325,325,326,326,327,327,327,328,328,329, \
    329,330,330,331,331,332,332,332,333,333,334,334,335,335,336,336, \
    337,337,338,338,339,339,340,340,341,341,342,342,343,343,344,344, \
    345,345,346,346,347,347,348,348,349,349,350,350,351,351,352,353, \
    353,354,354,354,355,356,356,357,357,358,359,359,360,360,360,361, \
    362,362,363,364,364,365,365,366,367,367,368,368,369,370,370,371, \
    371,372,373,373,374,374,375,376,376,377,378,378,379,379,380,381, \
    381,382,382,383,384,385,385,386,387,387,388,389,389,390,390,391, \
    392,393,393,394,395,395,396,396,397,398,398,399,400,400,401,402, \
    402,403,404,405,405,406,407,408,408,408,409,410,411,411,412,413, \
    413,414,415,416,416,417,418,419,419,420,421,422,422,423,424,424, \
    425,426,427,427,428,429,430,430,431,432,433,433,434,435,436,436, \
    437,438,439,440,441,441,442,443,444,444,445,446,447,447,448,449, \
    450,450,451,452,453,454,455,456,456,457,458,459,460,461,462,462, \
    463,463,464,465,466,467,468,468,469,470,471,472,473,474,474,475, \
    476,477,478,479,480,481,481,482,483,485,486,487,487,488,489,490, \
    491,492,493,493,494,495,496,497,498,499,500,501,502,503,504,505, \
    506,507,508,509,510,511,512,513,514,515,516,517,518,519,520,521, \
    522,523,524,525,526,527,528,529,530,531,532,533,534,535,536,537, \
    538,539,540,541,542,543,544,545,546,547,548,550,551,552,553,554, \
    555,556,558,559,560,561,562,563,565,566,567,568,569,570,572,573, \
    574,575,576,577,579,580,581,582,583,584,586,587,588,589,590,591, \
    593,594,595,596,597,598,600,601,602,603,605,606,607,608,610,611, \
    612,614,615,616,617,619,620,621,623,624,625,626,628,629,630,632, \
    633,634,635,637,638,639,641,642,643,644,646,647,648,650,651,653, \
    654,654,655,656,656,657,657,657,658,658,660,660,662,663,665,667, \
    669,672,675,678,683,685,688,692,697,703,706,710,714,718,723,728, \
    733,738,743,749,755,761,766,772,778,785,788,792,798,804,811,819, \
    825,828,832,838,845,852,859,862,866,873,879,886,893,899,906,909, \
    912,919,925,931,937,943,948,959,964,969,974,982,987,991,998,1000, \
    }

#define DEFAULT_CALIB_PROFILE_DBM_MIN_G     -908  //-2100
#define DEFAULT_CALIB_PROFILE_DBM_MAX_G      2530 // 3750

#define DEFAULT_CALIB_PROFILE_DBM_MIN_DP    -220  //-2100
#define DEFAULT_CALIB_PROFILE_DBM_MAX_DP     2302 // 3750

#ifdef PA_VRAMP_220PF
#define DEFAULT_CALIB_RAMP0     63,62,60,57,53,47,41,34,28,23,18,13,9,5,3,2
#define DEFAULT_CALIB_RAMP1     63,63,63,63,61,57,50,42,35,28,20,13,9,5,3,2
#define DEFAULT_CALIB_RAMP2     63,63,63,63,63,61,59,56,52,47,40,33,27,22,17,10
#define DEFAULT_CALIB_RAMP3     63,63,63,63,63,63,61,58,55,50,44,39,35,31,27,22
#else // !PA_VRAMP_220PF
#define DEFAULT_CALIB_RAMP0     63,62,60,57,53,47,41,34,28,23,18,13,9,5,3,2
#define DEFAULT_CALIB_RAMP1     63,63,63,63,61,57,50,42,35,28,20,13,9,5,3,2
#define DEFAULT_CALIB_RAMP2     63,63,63,63,63,61,59,56,52,47,40,33,27,22,17,10
#define DEFAULT_CALIB_RAMP3     63,63,63,63,63,63,61,58,55,50,44,39,35,31,27,22
#endif // !PA_VRAMP_220PF

#define DEFAULT_CALIB_RAMP_LOW              { \
    DEFAULT_CALIB_RAMP0,\
    DEFAULT_CALIB_RAMP1}

#define DEFAULT_CALIB_RAMP_HIGH             { \
     DEFAULT_CALIB_RAMP2,\
     DEFAULT_CALIB_RAMP3}

#define DEFAULT_CALIB_RAMP_SWAP_G            4000 // 4000
#define DEFAULT_CALIB_RAMP_SWAP_DP           4001 // 4000

#define DEFAULT_CALIB_LOW_VOLT_LIMIT    { 3600,3580,3550,3450,3400,3350 }
#define DEFAULT_CALIB_LOW_DAC_LIMIT     {  450, 410, 390, 350, 330, 300 }

#define DEFAULT_CALIB_PA_SPARE          {0, 0, 0, 0, 0, 0, 0, 0}

#define DEFAULT_CALIB_PA_PALCUST        {DEFAULT_CALIB_PA_RDA6231, \
                                         DEFAULT_CALIB_PCL2DBM_ARFCN_G, \
                                         DEFAULT_CALIB_PCL2DBM_ARFCN_D, \
                                         DEFAULT_CALIB_PCL2DBM_ARFCN_P, \
                                         DEFAULT_CALIB_PROF_INTERP_G, \
                                         DEFAULT_CALIB_PROF_INTERP_DP, \
                                         DEFAULT_CALIB_PROFILE_G, \
                                         DEFAULT_CALIB_PROFILE_DP, \
                                         DEFAULT_CALIB_PROFILE_DBM_MIN_G, \
                                         DEFAULT_CALIB_PROFILE_DBM_MIN_DP, \
                                         DEFAULT_CALIB_PROFILE_DBM_MAX_G, \
                                         DEFAULT_CALIB_PROFILE_DBM_MAX_DP, \
                                         DEFAULT_CALIB_RAMP_LOW, \
                                         DEFAULT_CALIB_RAMP_HIGH, \
                                         DEFAULT_CALIB_RAMP_SWAP_G, \
                                         DEFAULT_CALIB_RAMP_SWAP_DP, \
                                         DEFAULT_CALIB_LOW_VOLT_LIMIT, \
                                         DEFAULT_CALIB_LOW_DAC_LIMIT, \
                                         DEFAULT_CALIB_PA_SPARE}

//
//  RF Switch part
//


// Calibration parameter accessors
// ------------------------------------------------------------------------
#define SW_TIME(n)                  (g_paCalibPtr->sw->times[(n)])

// Default calibration times.
// ------------------------------------------------------------------------
#define DEFAULT_CALIB_TX_SWITCH_UP      -16
#define DEFAULT_CALIB_TX_SWITCH_DN      4
#define DEFAULT_CALIB_RX_SWITCH_UP      -100
#define DEFAULT_CALIB_RX_SWITCH_DN      0
#define DEFAULT_CALIB_MOD_EN_UP         0
#define DEFAULT_CALIB_MOD_EN_DN         0


#define DEFAULT_CALIB_SW_TIMES          {DEFAULT_CALIB_TX_SWITCH_UP, \
                                         DEFAULT_CALIB_TX_SWITCH_DN, \
                                         DEFAULT_CALIB_RX_SWITCH_UP, \
                                         DEFAULT_CALIB_RX_SWITCH_DN}
// Calibration Times Accessor index
#define SW_TIME_TX_SWITCH_UP        0
#define SW_TIME_TX_SWITCH_DN        1
#define SW_TIME_RX_SWITCH_UP        2
#define SW_TIME_RX_SWITCH_DN        3
#define SW_TIME_MOD_EN_UP           0
#define SW_TIME_MOD_EN_DN           0

// Default calibration parameters.
// ------------------------------------------------------------------------
#define DEFAULT_CALIB_SW_PARAM              {}

// Default calibration PAL custom parameters.
// ------------------------------------------------------------------------
#define DEFAULT_CALIB_SW_SPARE          {0, 0, 0, 0, 0, 0, 0, 0}

#define DEFAULT_CALIB_SW_PALCUST        {DEFAULT_CALIB_SW_RDA6231, \
                                         DEFAULT_CALIB_SW_SPARE}


#endif // PASW_RDA6231_CALIB_H
