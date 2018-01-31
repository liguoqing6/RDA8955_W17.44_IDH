﻿/* Copyright (C) 2016 RDA Technologies Limited and/or its affiliates("RDA").
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

#ifndef __WIFI_INIT_D_H__
#define __WIFI_INIT_D_H__
//#define RDA5990_WIFI_USE_DCDC_MODE
//note: if the wifi initialization is not correct, need to check the DCDC setting
const UINT32 wifi_core_notch_test_mode_dig[][2] =
{
//  {0x5000050C,0x00008000},  //power saving  modify wangxiuzhuznag, 2012-05-17


//#ifdef PTA_CFG_0424    /*pta config*/
    {0x50000800,0xFC003E05},   //  ctrl and mgmt package as hi priority
    {0x50000804,0x00000000},   // all data package as low priority
    {0x50000808,0xA500001b},   // shorter beacon protect time
    {0x50000810,0x0FCC0F01},   //bt grant
    {0x50000814,0x0fff0F03},   //wf  grant
    {0x50000818,0x00ff0001},   //antSel0 for wl_rx
    {0x5000081C,0x0f000f00},   //antSel1 for wl_tx
    {0x50000820,0x0f000f00},   //antSel2 for wl_pa  dig directly control rf_switch  houzhen Mar 29 2012
    {0x50000824,0xF000f0fe},   //antSel3 for bt_rf
    {0x50000828,0x00100F10},   //penality timer setting
    {0x50000838,0xF8003f2A},   //  rx package lo priority
    {0x5000083c,0x00000003},   // rx package hi priority
    /*end pta config*/
//#endif
    /*
    //  {0x50000808,0x6500001b},       //shorter beacon protect time
        {0x50000800,0xFC003E05},   //  ctrl and mgmt package as hi priority
        {0x50000804,0x00000000},   // all data package as low priority
        {0x50000838,0xF8003f2A},   //  rx package lo priority
      {0x5000083c,0x00000003},   // rx package hi priority
        {0x50000808,0xf900001b},   //
        {0x50000810,0x0FCC0F01},   //bt grant
        {0x50000814,0x0fff0F33},   //wf  grant
        {0x50000818,0x00ff0001},   //antSel0 for wl_rx
        {0x5000081C,0x0f000f00},   //antSel1 for wl_tx
        {0x50000820,0x0f000f00},   //antSel2 for wl_pa  dig directly control rf_switch  houzhen Mar 29 2012
        {0x50000824,0xF000f0fe},   //antSel3 for bt_rf
        {0x50000828,0x00100F10},   //penality timer setting

    */

    {  0x30010000, 0x780369AF },   //disable tports wait  100ms;
    {  0x30000010, 0x7000FFFF },//wait 500ms;
//{  0x50000600, 0x00001200 },//write 00 to 09h tx_on earlier wait 500ms;
//{  0x50000600, 0x00001468 },//write 88 to 0ah tx_on earlier wait 500ms;;;item:lna_step to  22db
    {  0x50090054, 0x00000001 },//enable update
    {  0x50090200, 0x00000000 },
    {  0x50090204, 0x00000000 },
    {  0x50090208, 0x00000002 },
    {  0x5009020c, 0x00000004 },
    {  0x50090210, 0x00000006 },
    {  0x50090214, 0x00000008 },
    {  0x50090218, 0x0000000a },
    {  0x5009021c, 0x00000040 },
    {  0x50090220, 0x00000042 },
    {  0x50090224, 0x00000044 },
    {  0x50090228, 0x00000046 },
    {  0x5009022c, 0x00000048 },
    {  0x50090230, 0x0000004a },
    {  0x50090234, 0x00000080 },
    {  0x50090238, 0x00000082 },
    {  0x5009023c, 0x00000084 },
    {  0x50090240, 0x00000086 },
    {  0x50090244, 0x00000088 },
    {  0x50090248, 0x0000008a },
    {  0x5009024c, 0x000000c0 },
    {  0x50090250, 0x000000c2 },
    {  0x50090254, 0x000000c4 },
    {  0x50090258, 0x000000c6 },
    {  0x5009025c, 0x000000c8 },
    {  0x50090260, 0x000000ca },
    {  0x50090264, 0x00000100 },
    {  0x50090268, 0x00000102 },
    {  0x5009026c, 0x00000104 },
    {  0x50090270, 0x00000106 },
    {  0x50090274, 0x00000108 },
    {  0x50090278, 0x00000140 },
    {  0x5009027c, 0x00000142 },//lna =0 end
    {  0x50090280, 0x00000080 },
    {  0x50090284, 0x00000082 },
    {  0x50090288, 0x00000084 },
    {  0x5009028c, 0x00000086 },
    {  0x50090290, 0x00000088 },
    {  0x50090294, 0x0000008a },
    {  0x50090298, 0x000000c0 },
    {  0x5009029c, 0x000000c2 },
    {  0x500902a0, 0x000000c4 },
    {  0x500902a4, 0x000000c6 },
    {  0x500902a8, 0x000000c8 },
    {  0x500902ac, 0x000000ca },
    {  0x500902b0, 0x00000100 },
    {  0x500902b4, 0x00000102 },
    {  0x500902b8, 0x00000104 },
    {  0x500902bc, 0x00000106 },
    {  0x500902c0, 0x00000108 },
    {  0x500902c4, 0x00000140 },
    {  0x500902c8, 0x00000142 },
    {  0x500902cc, 0x00000144 },
    {  0x500902d0, 0x00000146 },
    {  0x500902d4, 0x00000148 },
    {  0x500902d8, 0x00000180 },
    {  0x500902dc, 0x00000182 },
    {  0x500902e0, 0x00000184 },
    {  0x500902e4, 0x000001c0 },
    {  0x500902e8, 0x000001c2 },
    {  0x500902ec, 0x000001c4 },
    {  0x500902f0, 0x000001c6 },
    {  0x500902f4, 0x000001c8 },
    {  0x500902f8, 0x000001ca },
    {  0x500902fc, 0x000001cc },// lna = 01  end
    {  0x50090300, 0x00000102 },
    {  0x50090304, 0x00000104 },
    {  0x50090308, 0x00000106 },
    {  0x5009030c, 0x00000108 },
    {  0x50090310, 0x00000140 },
    {  0x50090314, 0x00000142 },
    {  0x50090318, 0x00000144 },
    {  0x5009031c, 0x00000146 },
    {  0x50090320, 0x00000148 },
    {  0x50090324, 0x00000180 },
    {  0x50090328, 0x00000182 },
    {  0x5009032c, 0x00000184 },
    {  0x50090330, 0x000001c0 },
    {  0x50090334, 0x000001c2 },
    {  0x50090338, 0x000001c4 },
    {  0x5009033c, 0x000001c6 },
    {  0x50090340, 0x000001c8 },
    {  0x50090344, 0x000001ca },
    {  0x50090348, 0x000001cb },
    {  0x5009034c, 0x000001cb },
    {  0x50090350, 0x000001cb },
    {  0x50090354, 0x000001cb },
    {  0x50090358, 0x000001cb },
    {  0x5009035c, 0x000001cb },
    {  0x50090360, 0x000001cb },
    {  0x50090364, 0x000001cb },
    {  0x50090368, 0x000001cb },
    {  0x5009036c, 0x000001cb },
    {  0x50090370, 0x000001cb },
    {  0x50090374, 0x000001cb },
    {  0x50090378, 0x000001cb },
    {  0x5009037c, 0x000001cb },
    {  0x50090054, 0x00000000 },//disable update
    {  0x50000808, 0x65000013 }, // disable prerx_priority;pta config
    {  0x50000810, 0xFFCD0F01 },  //rx beacon priority

//add notch patch
    //ch 1
    {0x001008d0, 0x50090040},
    {0x001008d4, 0x10000000},
    {0x001008d8, 0x50090044},
    {0x001008dc, 0x10000000},
    //ch 2
    {0x00100910, 0x50090040},
    {0x00100914, 0x10000000},
    {0x00100918, 0x50090044},
    {0x0010091c, 0x10000000},
    //ch 3
    {0x00100950, 0x50090040},
    {0x00100954, 0x10000000},
    {0x00100958, 0x50090044},
    {0x0010095c, 0x10000000},
    //ch 4
    {0x00100990, 0x50090040},
    {0x00100994, 0x10000000},
    {0x00100998, 0x50090044},
    {0x0010099c, 0x10000000},
    //ch 5
    {0x001009d0, 0x50090040},
    {0x001009d4, 0x076794b4},
    {0x001009d8, 0x50090044},
    {0x001009dc, 0x10000000},
    //ch 6
    {0x00100a10, 0x50090040},
    {0x00100a14, 0x077c71de},
    {0x00100a18, 0x50090044},
    {0x00100a1c, 0x046d242e},
    //ch 7
    {0x00100a50, 0x50090040},
    {0x00100a54, 0x077e7ec0},
    {0x00100a58, 0x50090044},
    {0x00100a5c, 0x077e7140},
    //ch 8
    {0x00100a90, 0x50090040},
    {0x00100a94, 0x077c7e22},
    {0x00100a98, 0x50090044},
    {0x00100a9c, 0x046d2bd2},
    //ch 9
    {0x00100ad0, 0x50090040},
    {0x00100ad4, 0x10000000},
    {0x00100ad8, 0x50090044},
    {0x00100adc, 0x10000000},
    //ch 10
    {0x00100b10, 0x50090040},
    {0x00100b14, 0x10000000},
    {0x00100b18, 0x50090044},
    {0x00100b1c, 0x10000000},
    //ch 11
    {0x00100b50, 0x50090040},
    {0x00100b54, 0x10000000},
    {0x00100b58, 0x50090044},
    {0x00100b5c, 0x10000000},
    //ch 12
    {0x00100b90, 0x50090040},
    {0x00100b94, 0x07764310},
    {0x00100b98, 0x50090044},
    {0x00100b9c, 0x10000000},
    //ch 13
    {0x00100bd0, 0x50090040},
    {0x00100bd4, 0x10000000},
    {0x00100bd8, 0x50090044},
    {0x00100bdc, 0x10000000},
    //ch 14
    {0x00100c10, 0x50090040},
    {0x00100c14, 0x0779c279},
    {0x00100c18, 0x50090044},
    {0x00100c1c, 0x0779cd87},
//add end




    //{ 0x3001003c, 0x2e00a100 } ,
    { 0x00106b6c, 0x00000002} , //patch for chanel 13

};

const UINT32 wifi_core_notch_test_mode_notch[][2] =
{

//add notch patch
    //ch 1
    {0x001008d0, 0x50090040},
    {0x001008d4, 0x10000000},
    {0x001008d8, 0x50090044},
    {0x001008dc, 0x10000000},
    //ch 2
    {0x00100910, 0x50090040},
    {0x00100914, 0x10000000},
    {0x00100918, 0x50090044},
    {0x0010091c, 0x10000000},
    //ch 3
    {0x00100950, 0x50090040},
    {0x00100954, 0x10000000},
    {0x00100958, 0x50090044},
    {0x0010095c, 0x10000000},
    //ch 4
    {0x00100990, 0x50090040},
    {0x00100994, 0x10000000},
    {0x00100998, 0x50090044},
    {0x0010099c, 0x10000000},
    //ch 5
    {0x001009d0, 0x50090040},
    {0x001009d4, 0x076794b4},
    {0x001009d8, 0x50090044},
    {0x001009dc, 0x10000000},
    //ch 6
    {0x00100a10, 0x50090040},
    {0x00100a14, 0x077c71de},
    {0x00100a18, 0x50090044},
    {0x00100a1c, 0x046d242e},
    //ch 7
    {0x00100a50, 0x50090040},
    {0x00100a54, 0x077e7ec0},
    {0x00100a58, 0x50090044},
    {0x00100a5c, 0x077e7140},
    //ch 8
    {0x00100a90, 0x50090040},
    {0x00100a94, 0x077c7e22},
    {0x00100a98, 0x50090044},
    {0x00100a9c, 0x046d2bd2},
    //ch 9
    {0x00100ad0, 0x50090040},
    {0x00100ad4, 0x10000000},
    {0x00100ad8, 0x50090044},
    {0x00100adc, 0x10000000},
    //ch 10
    {0x00100b10, 0x50090040},
    {0x00100b14, 0x10000000},
    {0x00100b18, 0x50090044},
    {0x00100b1c, 0x10000000},
    //ch 11
    {0x00100b50, 0x50090040},
    {0x00100b54, 0x10000000},
    {0x00100b58, 0x50090044},
    {0x00100b5c, 0x10000000},
    //ch 12
    {0x00100b90, 0x50090040},
    {0x00100b94, 0x07764310},
    {0x00100b98, 0x50090044},
    {0x00100b9c, 0x10000000},
    //ch 13
    {0x00100bd0, 0x50090040},
    {0x00100bd4, 0x10000000},
    {0x00100bd8, 0x50090044},
    {0x00100bdc, 0x10000000},
    //ch 14
    {0x00100c10, 0x50090040},
    {0x00100c14, 0x0779c279},
    {0x00100c18, 0x50090044},
    {0x00100c1c, 0x0779cd87},
//add end




    //{ 0x3001003c, 0x2e00a100 } ,
    { 0x00106b6c, 0x00000002} , //patch for chanel 13


};




// dig
const UINT32 wifi_core_notch_patch_test_mode[][2] =  // this array for wifi test mode only
{
//  {0x5000050C,0x00008000},  //power saving  modify wangxiuzhuznag, 2012-05-17


//#ifdef PTA_CFG_0424    /*pta config*/
    {0x50000800,0xFC003E05},   //  ctrl and mgmt package as hi priority
    {0x50000804,0x00000000},   // all data package as low priority
    {0x50000808,0xA500001b},   // shorter beacon protect time
    {0x50000810,0x0FCC0F01},   //bt grant
    {0x50000814,0x0fff0F03},   //wf  grant
    {0x50000818,0x00ff0001},   //antSel0 for wl_rx
    {0x5000081C,0x0f000f00},   //antSel1 for wl_tx
    {0x50000820,0x0f000f00},   //antSel2 for wl_pa  dig directly control rf_switch  houzhen Mar 29 2012
    {0x50000824,0xF000f0fe},   //antSel3 for bt_rf
    {0x50000828,0x00100F10},   //penality timer setting
    {0x50000838,0xF8003f2A},   //  rx package lo priority
    {0x5000083c,0x00000003},   // rx package hi priority
    /*end pta config*/
//#endif
    /*
    //  {0x50000808,0x6500001b},       //shorter beacon protect time
        {0x50000800,0xFC003E05},   //  ctrl and mgmt package as hi priority
        {0x50000804,0x00000000},   // all data package as low priority
        {0x50000838,0xF8003f2A},   //  rx package lo priority
      {0x5000083c,0x00000003},   // rx package hi priority
        {0x50000808,0xf900001b},   //
        {0x50000810,0x0FCC0F01},   //bt grant
        {0x50000814,0x0fff0F33},   //wf  grant
        {0x50000818,0x00ff0001},   //antSel0 for wl_rx
        {0x5000081C,0x0f000f00},   //antSel1 for wl_tx
        {0x50000820,0x0f000f00},   //antSel2 for wl_pa  dig directly control rf_switch  houzhen Mar 29 2012
        {0x50000824,0xF000f0fe},   //antSel3 for bt_rf
        {0x50000828,0x00100F10},   //penality timer setting

    */

    {  0x30010000, 0x780369AF },   //disable tports wait  100ms;
    {  0x30000010, 0x7000FFFF },//wait 500ms;
//{  0x50000600, 0x00001200 },//write 00 to 09h tx_on earlier wait 500ms;
//{  0x50000600, 0x00001468 },//write 88 to 0ah tx_on earlier wait 500ms;;;item:lna_step to  22db
    {  0x50090054, 0x00000001 },//enable update
    {  0x50090200, 0x00000000 },
    {  0x50090204, 0x00000000 },
    {  0x50090208, 0x00000002 },
    {  0x5009020c, 0x00000004 },
    {  0x50090210, 0x00000006 },
    {  0x50090214, 0x00000008 },
    {  0x50090218, 0x0000000a },
    {  0x5009021c, 0x00000040 },
    {  0x50090220, 0x00000042 },
    {  0x50090224, 0x00000044 },
    {  0x50090228, 0x00000046 },
    {  0x5009022c, 0x00000048 },
    {  0x50090230, 0x0000004a },
    {  0x50090234, 0x00000080 },
    {  0x50090238, 0x00000082 },
    {  0x5009023c, 0x00000084 },
    {  0x50090240, 0x00000086 },
    {  0x50090244, 0x00000088 },
    {  0x50090248, 0x0000008a },
    {  0x5009024c, 0x000000c0 },
    {  0x50090250, 0x000000c2 },
    {  0x50090254, 0x000000c4 },
    {  0x50090258, 0x000000c6 },
    {  0x5009025c, 0x000000c8 },
    {  0x50090260, 0x000000ca },
    {  0x50090264, 0x00000100 },
    {  0x50090268, 0x00000102 },
    {  0x5009026c, 0x00000104 },
    {  0x50090270, 0x00000106 },
    {  0x50090274, 0x00000108 },
    {  0x50090278, 0x00000140 },
    {  0x5009027c, 0x00000142 },//lna =0 end
    {  0x50090280, 0x00000080 },
    {  0x50090284, 0x00000082 },
    {  0x50090288, 0x00000084 },
    {  0x5009028c, 0x00000086 },
    {  0x50090290, 0x00000088 },
    {  0x50090294, 0x0000008a },
    {  0x50090298, 0x000000c0 },
    {  0x5009029c, 0x000000c2 },
    {  0x500902a0, 0x000000c4 },
    {  0x500902a4, 0x000000c6 },
    {  0x500902a8, 0x000000c8 },
    {  0x500902ac, 0x000000ca },
    {  0x500902b0, 0x00000100 },
    {  0x500902b4, 0x00000102 },
    {  0x500902b8, 0x00000104 },
    {  0x500902bc, 0x00000106 },
    {  0x500902c0, 0x00000108 },
    {  0x500902c4, 0x00000140 },
    {  0x500902c8, 0x00000142 },
    {  0x500902cc, 0x00000144 },
    {  0x500902d0, 0x00000146 },
    {  0x500902d4, 0x00000148 },
    {  0x500902d8, 0x00000180 },
    {  0x500902dc, 0x00000182 },
    {  0x500902e0, 0x00000184 },
    {  0x500902e4, 0x000001c0 },
    {  0x500902e8, 0x000001c2 },
    {  0x500902ec, 0x000001c4 },
    {  0x500902f0, 0x000001c6 },
    {  0x500902f4, 0x000001c8 },
    {  0x500902f8, 0x000001ca },
    {  0x500902fc, 0x000001cc },// lna = 01  end
    {  0x50090300, 0x00000102 },
    {  0x50090304, 0x00000104 },
    {  0x50090308, 0x00000106 },
    {  0x5009030c, 0x00000108 },
    {  0x50090310, 0x00000140 },
    {  0x50090314, 0x00000142 },
    {  0x50090318, 0x00000144 },
    {  0x5009031c, 0x00000146 },
    {  0x50090320, 0x00000148 },
    {  0x50090324, 0x00000180 },
    {  0x50090328, 0x00000182 },
    {  0x5009032c, 0x00000184 },
    {  0x50090330, 0x000001c0 },
    {  0x50090334, 0x000001c2 },
    {  0x50090338, 0x000001c4 },
    {  0x5009033c, 0x000001c6 },
    {  0x50090340, 0x000001c8 },
    {  0x50090344, 0x000001ca },
    {  0x50090348, 0x000001cb },
    {  0x5009034c, 0x000001cb },
    {  0x50090350, 0x000001cb },
    {  0x50090354, 0x000001cb },
    {  0x50090358, 0x000001cb },
    {  0x5009035c, 0x000001cb },
    {  0x50090360, 0x000001cb },
    {  0x50090364, 0x000001cb },
    {  0x50090368, 0x000001cb },
    {  0x5009036c, 0x000001cb },
    {  0x50090370, 0x000001cb },
    {  0x50090374, 0x000001cb },
    {  0x50090378, 0x000001cb },
    {  0x5009037c, 0x000001cb },
    {  0x50090054, 0x00000000 },//disable update
    {  0x50000808, 0x65000013 }, // disable prerx_priority;pta config
    {  0x50000810, 0xFFCD0F01 },  //rx beacon priority

//add notch patch

    //ch 1
    {0x001008d0, 0x50090040},
    {0x001008d4, 0x10000000},
    {0x001008d8, 0x50090044},
    {0x001008dc, 0x10000000},
    //ch 2
    {0x00100910, 0x50090040},
    {0x00100914, 0x10000000},
    {0x00100918, 0x50090044},
    {0x0010091c, 0x10000000},
    //ch 3
    {0x00100950, 0x50090040},
    {0x00100954, 0x10000000},
    {0x00100958, 0x50090044},
    {0x0010095c, 0x10000000},
    //ch 4
    {0x00100990, 0x50090040},
    {0x00100994, 0x10000000},
    {0x00100998, 0x50090044},
    {0x0010099c, 0x10000000},
    //ch 5
    {0x001009d0, 0x50090040},
    {0x001009d4, 0x076794b4},
    {0x001009d8, 0x50090044},
    {0x001009dc, 0x10000000},
    //ch 6
    {0x00100a10, 0x50090040},
    {0x00100a14, 0x077c71de},
    {0x00100a18, 0x50090044},
    {0x00100a1c, 0x046d242e},
    //ch 7
    {0x00100a50, 0x50090040},
    {0x00100a54, 0x077e7ec0},
    {0x00100a58, 0x50090044},
    {0x00100a5c, 0x077e7140},
    //ch 8
    {0x00100a90, 0x50090040},
    {0x00100a94, 0x077c7e22},
    {0x00100a98, 0x50090044},
    {0x00100a9c, 0x046d2bd2},
    //ch 9
    {0x00100ad0, 0x50090040},
    {0x00100ad4, 0x10000000},
    {0x00100ad8, 0x50090044},
    {0x00100adc, 0x10000000},
    //ch 10
    {0x00100b10, 0x50090040},
    {0x00100b14, 0x10000000},
    {0x00100b18, 0x50090044},
    {0x00100b1c, 0x10000000},
    //ch 11
    {0x00100b50, 0x50090040},
    {0x00100b54, 0x10000000},
    {0x00100b58, 0x50090044},
    {0x00100b5c, 0x10000000},
    //ch 12
    {0x00100b90, 0x50090040},
    {0x00100b94, 0x07764310},
    {0x00100b98, 0x50090044},
    {0x00100b9c, 0x10000000},
    //ch 13
    {0x00100bd0, 0x50090040},
    {0x00100bd4, 0x10000000},
    {0x00100bd8, 0x50090044},
    {0x00100bdc, 0x10000000},
    //ch 14
    {0x00100c10, 0x50090040},
    {0x00100c14, 0x0779c279},
    {0x00100c18, 0x50090044},
    {0x00100c1c, 0x0779cd87},
//add end

    //{ 0x3001003c, 0x2e00a100 } ,
    { 0x00106b6c, 0x00000002} , //patch for chanel 13

};


const UINT32 wifi_test_mode_patch2[][2] = //no
{
    {0x50000600,0x0000501a},//write 1a(52) to 28h hightolow
    {0x50000600,0x0000520d},//write 0d(26) to 29h hightomid
    {0x50000600,0x00006a1e},//35h reg coarse2 upper window from 0d to 1a for
    {0x50000600,0x00009890},//4ch reg unlock upper threshold from 70 to 90
    {0x50000600,0x00009a38},//4dh reg unlock lower threshold from 78 to 38
    {0x50000600,0x00007207},//39h reg change vga gain ,9 -> 7 for big signal
    {0x50000600,0x0001c8f5},//e4h reg change hpf coeff to f5
    {0x50000600,0x00004200},//21h reg add fine gain 0db
    {0x50000600,0x00004610},//23h reg change maxgain index as agc table
    {0x50000600,0x0000900e},//48h reg unlock lower threshold change from 0a t
    {0x50000600,0x00004a00},//25h reg pecket dection threshold
    {0x50000600,0x000040a8},//20h reg add  fine itr2 98->a8
    {0x50000600,0x00007e05},//3f reg rssi window for fine itr2 0->5
    {0x50000600,0x00008237},//41 reg fine itr1 nextstate 4->3
    {0x50000600,0x00008440},//42 reg fine itr2 nextstate 0->4 settle time 0->
    {0x50000600,0x0000b6a9},//5b reg change GreatN rssi avg count from 1 to 8

};

const UINT32 wifi_core_init_data[][2] =
{

    { 0x3001003c, 0x2e00a000 } ,// sdio clock

#if 0
// 2012-06-14 patch
    {0x00108000, 0xEA03DF9C},
    {0x00108004, 0xE59F101C},
    {0x00108008, 0xE3A00040},
    {0x0010800C, 0xE5C10038},
    {0x00108010, 0xE1A0F00E},
    {0x00108014, 0xEA03DF95},
    {0x00108018, 0xE59F1008},
    {0x0010801C, 0xE3A00040},
    {0x00108020, 0xE5C10038},
    {0x00108024, 0xE1A0F00E},
    {0x00108028, 0x50300000},
    {0x0010802C, 0xEB03D6F2},
    {0x00108030, 0xE1A00B84},
    {0x00108034, 0xE1B00BA0},
    {0x00108038, 0x11A00B84},
    {0x0010803C, 0x11A00BA0},
    {0x00108040, 0x12600F80},
    {0x00108044, 0x10804004},
    {0x00108048, 0xE1A00124},
    {0x0010804C, 0xE92D0011},
    {0x00108050, 0xE51F4030},
    {0x00108054, 0xE3A00020},
    {0x00108058, 0xE5C40038},
    {0x0010805C, 0xE8BD0011},
    {0x00108060, 0xE1A0F00E},
    {0x00108064, 0xEA03D3D2},
    {0x00108068, 0xE3A00001},
    {0x0010806C, 0xE1A0F00E},
    {0x00108070, 0xEA03D6CD},
    {0x00108074, 0xE3A00001},
    {0x00108078, 0xE1A0F00E},
    {0x0010807C, 0xEB03C786},
    {0x00108080, 0xE51F0060},
    {0x00108084, 0xE5D00038},
    {0x00108088, 0xE3100080},
    {0x0010808C, 0x1A000001},
    {0x00108090, 0xE3A00001},
    {0x00108094, 0xE1A0F00E},
    {0x00108098, 0xE3A00000},
    {0x0010809C, 0xE1A0F00E},
    {0x001080A0, 0xEB03EADE},
    {0x001080A4, 0xE51F0084},
    {0x001080A8, 0xE5D00038},
    {0x001080AC, 0xE3100080},
    {0x001080B0, 0x1A000001},
    {0x001080B4, 0xE3A00001},
    {0x001080B8, 0xE1A0F00E},
    {0x001080BC, 0xE3A00000},
    {0x001080C0, 0xE1A0F00E},
    {0x001080C4, 0xEB03D89D},
    {0x001080C8, 0xE51F00A8},
    {0x001080CC, 0xE3A01080},
    {0x001080D0, 0xE5C01038},
    {0x001080D4, 0xE1A0F00E},
    {0x001080D8, 0xEB03D714},
    {0x001080DC, 0xE51F10BC},
    {0x001080E0, 0xE5D10038},
    {0x001080E4, 0xE3100080},
    {0x001080E8, 0x159F001C},
    {0x001080EC, 0x059F0014},
    {0x001080F0, 0xE59F100C},
    {0x001080F4, 0xE581003C},
    {0x001080F8, 0xE51F10D8},
    {0x001080FC, 0xE1D101B4},
    {0x00108100, 0xE1A0F00E},
    {0x00108104, 0x30010000},
    {0x00108108, 0x2E00A100},
    {0x0010810C, 0x2E00A000},
    {0x00108110, 0xEB03B485},
    {0x00108114, 0x13100010},
    {0x00108118, 0x13A00002},
    {0x0010811C, 0x15C50067},
    {0x00108120, 0xE1A0F00E},
    {0x00108124, 0xEA03D804},
    {0x00108128, 0xE51F1108},
    {0x0010812C, 0xE5D10038},
    {0x00108130, 0xE2000020},
    {0x00108134, 0xE3500000},
    {0x00108138, 0x1AFFFFFB},
    {0x0010813C, 0xE3A01004},
    {0x00108140, 0xE3A00B48},
    {0x00108144, 0xE280FF45},
    {0x00108148, 0xEA04020A},
    {0x0010814C, 0x08BD4010},
    {0x00108150, 0x0A000002},
    {0x00108154, 0x13A00001},
    {0x00108158, 0x18BD4010},
    {0x0010815C, 0x1A000001},
    {0x00108160, 0xE51FF004},
    {0x00108164, 0x0000D470},
    {0x00108168, 0xE51FF004},
    {0x0010816C, 0x0000D2C0},
    {0x00108170, 0x00000000},
    {0x00108174, 0x00108170},
    {0x00108178, 0xEA03E011},
    {0x0010817C, 0xE5902828},
    {0x00108180, 0xE51F0014},
    {0x00108184, 0xE5802000},
    {0x00108188, 0xE3A00450},
    {0x0010818C, 0xE3A01000},
    {0x00108190, 0xE5801828},
    {0x00108194, 0xE51FF004},
    {0x00108198, 0x00010134},
    {0x0010819C, 0xEA03E091},
    {0x001081A0, 0xE51F0034},
    {0x001081A4, 0xE5902000},
    {0x001081A8, 0xE5812828},
    {0x001081AC, 0xE1A0F00E},
    {0x20040004, 0x0001018C},
    {0x20040024, 0x00108000},
    {0x20040008, 0x000101BC},
    {0x20040028, 0x00108014},
    {0x2004000C, 0x00012460},
    {0x2004002C, 0x0010802C},
    {0x20040010, 0x00013118},
    {0x20040030, 0x00108064},
    {0x20040014, 0x00012538},
    {0x20040034, 0x00108070},
    {0x20040018, 0x00016260},
    {0x20040038, 0x0010807C},
    {0x2004001C, 0x0000D524},
    {0x2004003C, 0x001080A0},
    {0x20040020, 0x00011E4C},
    {0x20040040, 0x001080C4},
    {0x20040100, 0x00012484},
    {0x20040120, 0x001080D8},
    {0x20040104, 0x0001AEF8},
    {0x20040124, 0x00108110},
    {0x20040108, 0x00012110},
    {0x20040128, 0x00108124},
    {0x2004010C, 0x0000791C},
    {0x2004012C, 0x00108148},
    {0x20040110, 0x00010130},
    {0x20040130, 0x00108178},
    {0x20040114, 0x0000FF54},
    {0x20040134, 0x0010819C},
    {0x20040000, 0x00003FFF},
#else //2012-11-12, from hunaiquan
    {0x00108000, 0xEA03DF9C},
    {0x00108004, 0xE59F101C},
    {0x00108008, 0xE3A00040},
    {0x0010800C, 0xE5C10038},
    {0x00108010, 0xE1A0F00E},
    {0x00108014, 0xEA03DF95},
    {0x00108018, 0xE59F1008},
    {0x0010801C, 0xE3A00040},
    {0x00108020, 0xE5C10038},
    {0x00108024, 0xE1A0F00E},
    {0x00108028, 0x50300000},
    {0x0010802C, 0xEB03D6F2},
    {0x00108030, 0xE1A00B84},
    {0x00108034, 0xE1B00BA0},
    {0x00108038, 0x11A00B84},
    {0x0010803C, 0x11A00BA0},
    {0x00108040, 0x12600F80},
    {0x00108044, 0x10804004},
    {0x00108048, 0xE1A00124},
    {0x0010804C, 0xE92D0011},
    {0x00108050, 0xE51F4030},
    {0x00108054, 0xE3A00020},
    {0x00108058, 0xE5C40038},
    {0x0010805C, 0xE8BD0011},
    {0x00108060, 0xE1A0F00E},
    {0x00108064, 0xEA03D3D2},
    {0x00108068, 0xE3A00001},
    {0x0010806C, 0xE1A0F00E},
    {0x00108070, 0xEA03D6CD},
    {0x00108074, 0xE3A00001},
    {0x00108078, 0xE1A0F00E},
    {0x0010807C, 0xEB03C786},
    {0x00108080, 0xE51F0060},
    {0x00108084, 0xE5D00038},
    {0x00108088, 0xE3100080},
    {0x0010808C, 0x1A000001},
    {0x00108090, 0xE3A00001},
    {0x00108094, 0xE1A0F00E},
    {0x00108098, 0xE3A00000},
    {0x0010809C, 0xE1A0F00E},
    {0x001080A0, 0xEB03EADE},
    {0x001080A4, 0xE51F0084},
    {0x001080A8, 0xE5D00038},
    {0x001080AC, 0xE3100080},
    {0x001080B0, 0x1A000001},
    {0x001080B4, 0xE3A00001},
    {0x001080B8, 0xE1A0F00E},
    {0x001080BC, 0xE3A00000},
    {0x001080C0, 0xE1A0F00E},
    {0x001080C4, 0xEB03D89D},
    {0x001080C8, 0xE51F00A8},
    {0x001080CC, 0xE3A01080},
    {0x001080D0, 0xE5C01038},
    {0x001080D4, 0xE1A0F00E},
    {0x001080D8, 0xEB03D714},
    {0x001080DC, 0xE51F10BC},
    {0x001080E0, 0xE5D10038},
    {0x001080E4, 0xE3100080},
    {0x001080E8, 0x159F001C},
    {0x001080EC, 0x059F0014},
    {0x001080F0, 0xE59F100C},
    {0x001080F4, 0xE581003C},
    {0x001080F8, 0xE51F10D8},
    {0x001080FC, 0xE1D101B4},
    {0x00108100, 0xE1A0F00E},
    {0x00108104, 0x30010000},
    {0x00108108, 0x2E00A100},
    {0x0010810C, 0x2E00A000},
    {0x00108110, 0xEB03B485},
    {0x00108114, 0x13100010},
    {0x00108118, 0x13A00002},
    {0x0010811C, 0x15C50067},
    {0x00108120, 0xE1A0F00E},
    {0x00108124, 0xEA03D804},
    {0x00108128, 0xE51F1108},
    {0x0010812C, 0xE5D10038},
    {0x00108130, 0xE2000020},
    {0x00108134, 0xE3500000},
    {0x00108138, 0x1AFFFFFB},
    {0x0010813C, 0xE3A01004},
    {0x00108140, 0xE3A00B48},
    {0x00108144, 0xE280FF45},
    {0x00108148, 0xEA04020A},
    {0x0010814C, 0x08BD4010},
    {0x00108150, 0x0A000002},
    {0x00108154, 0x13A00001},
    {0x00108158, 0x18BD4010},
    {0x0010815C, 0x1A000001},
    {0x00108160, 0xE51FF004},
    {0x00108164, 0x0000D470},
    {0x00108168, 0xE51FF004},
    {0x0010816C, 0x0000D2C0},
    {0x00108170, 0xEA0402CF},
    {0x00108174, 0xE59F600C},
    {0x00108178, 0xE3A04000},
    {0x0010817C, 0xE5C64000},
    {0x00108180, 0xE59F6004},
    {0x00108184, 0xE59FF004},
    {0x00108188, 0x0010200B},
    {0x0010818C, 0x0010121D},
    {0x00108190, 0x00007634},
    {0x00108194, 0xEAFFFFEC},
    {0x00108198, 0xE1A00004},
    {0x0010819C, 0xE1A00000},
    {0x20040004, 0x0001018C},
    {0x20040024, 0x00108000},
    {0x20040008, 0x000101BC},
    {0x20040028, 0x00108014},
    {0x2004000C, 0x00012460},
    {0x2004002C, 0x0010802C},
    {0x20040010, 0x00013118},
    {0x20040030, 0x00108064},
    {0x20040014, 0x00012538},
    {0x20040034, 0x00108070},
    {0x20040018, 0x00016260},
    {0x20040038, 0x0010807C},
    {0x2004001C, 0x0000D524},
    {0x2004003C, 0x001080A0},
    {0x20040020, 0x00011E4C},
    {0x20040040, 0x001080C4},
    {0x20040100, 0x00012484},
    {0x20040120, 0x001080D8},
    {0x20040104, 0x0001AEF8},
    {0x20040124, 0x00108110},
    {0x20040108, 0x00012110},
    {0x20040128, 0x00108124},
    {0x2004010C, 0x0000791C},
    {0x2004012C, 0x00108148},
    {0x20040110, 0x00007630},
    {0x20040130, 0x00108170},
    {0x20040114, 0x00017158},
    {0x20040134, 0x00108194},
    {0x20040118, 0x00002594},
    {0x20040138, 0x00108198},
    {0x2004011C, 0x000172A4},
    {0x2004013C, 0x0010819C},
    {0x20040000, 0x0000FFFF},
#endif




};






UINT16 wifi_version[][2] =
{
//item:wf_on_2011_10_01
//set_power

    { 0x3F, 0x0001 },
    { 0x20, 0x0000 },
    { 0x21, 0x0000 },
    { 0x3F, 0x0000 },
};
UINT16 Rda_wf_poweron_data[][2]=
{
    //item:VerD_wf_on_2012_02_08
    {0x3f, 0x0001},
#ifdef RDA5990_WIFI_USE_DCDC_MODE     /*houzhen update Mar 15 2012 */
    {0x23, 0x8FA1},//20111001 higher AVDD voltage to improve EVM to 0x8f21 download current -1db 0x8fA1>>0x8bA1
#else
    {0x23, 0x0FA1},
#endif
    {0x31, 0x0B40 }, //power off wifi
    {0x22, 0xD3C7},//for ver.c 20111109, txswitch
    {0x24, 0x80C8},//freq_osc_in[1:0]00  0x80C8 >> 0x80CB
    {0x27, 0x4925},//for ver.c20111109, txswitch
    //                {0x28, 0x80A1}, //BT_enable
    {0x31, 0x8140},//enable wifi
    {0x32, 0x0113},//set_ rdenout_ldooff_wf=0; rden4in_ldoon_wf=1
    //{0x39, 0x0004},   //uart switch to wf
    {0x3F, 0x0000}, //page down
};






UINT16 wifi_dc_cal_data[][2] =
{
    { 0x3F, 0x0000 },//page0
//DC_CAL
    { 0x30, 0x0248 },
    { 0x30, 0x0249 },
    { 0x3F, 0x0000 },//page0
};


UINT16 wifi_mdll_reset_data[][2] =
{
    {0x3F,0x0000},//page0
    {0x30,0x024D},
    {0x29,0xD468},
    {0x29,0x1468},
    {0x30,0x0249},
    {0x3F,0x0000},//page0
};




UINT16 wifi_dig_reset_data[][2] =
{
    {0x3F,  0x0001},//page1
    {0x31,  0x8D40},
    {0x31,  0x8F40},
    {0x31,  0x8b40},
    {0x3F,  0x0000},//page0
};

// for wifi test mode
UINT16 wifi_poweron_uart[][2] =
{
//set_RF
    {0x3F,  0x0001},//page1
    {0x39,  0x0004},//switch uart to wifi
    {0x28,  0x80A1},//enable bt
    {0x3F,  0x0000},//page0
};




UINT16 wifi_rf_init_data[][2] =
{
    //verE
    {0x3f, 0x0000},
    //{;;set_rf_swi},ch
    {0x06, 0x0101},
    {0x07, 0x0101},
    {0x08, 0x0101},
    {0x09, 0x303C},
    {0x0A, 0x002C},//aain_0
    {0x0D, 0x0507},
    {0x0E, 0x2300},
    {0x0F, 0x5689},//
    //{;;//set_RF  },
    {0x10, 0x0f78},//20110824
    {0x11, 0x0602},
    {0x13, 0x0652},//adc_tuning_bit[011]
    {0x14, 0x8886},
    {0x15, 0x0990},
    {0x16, 0x049f},
    {0x17, 0x0990},
    {0x18, 0x049F},
    {0x19, 0x3C01},
    {0x1C, 0x0934},
    {0x1D, 0xFF00},//for ver.D20120119for temperature 70 degree
    //{0x1F, 0x01F8},//for ver.c20111109
    //{0x1F, 0x0300},//for burst tx 不锁
    {0x20, 0x06E4},
    {0x21, 0x0ACF},//for ver.c20111109,dr dac reset,dr txflt reset
    {0x22, 0x24DC},
    //{0x23, 0x23FF},
    {0x23, 0x0BFF},
    {0x24, 0x00FC},
    {0x26, 0x004F},//004F >> 005f premote pa
    {0x27, 0x171D},///mdll*7
    {0x28, 0x031D},///mdll*7
    {0x2A, 0x2860},//et0x2849-8.5p  :yd 0x2861-7pf C1,C2=6.8p
    {0x2B, 0x0800},//bbpll,or ver.c20111116
    {0x32, 0x8a08},
    {0x33, 0x1D02},//liuyanan
    //{;;//agc_gain},
#ifndef RDA5990_USE_LNA
    {0x36, 0x02f4}, //00F8;//gain_7
    {0x37, 0x01f4}, //0074;//aain_6
    {0x38, 0x21d4}, //0014;//gain_5
    {0x39, 0x25d4}, //0414;//aain_4
    {0x3A, 0x2584}, //1804;//gain_3
    {0x3B, 0x2dc4}, //1C04;//aain_2
    {0x3C, 0x2d04}, //1C02;//gain_1
    {0x3D, 0x2c02}, //3C01;//gain_0
#else
    {0x36, 0x24f4}, //00F8;//gain_7
    {0x37, 0x01f4}, //0074;//gain_6
    {0x38, 0x21d4}, //0014;//gain_5
    {0x39, 0x2073}, //0414;//gain_4
    {0x3A, 0x2473}, //1804;//gain_3
    {0x3B, 0x2dc7}, //1C04;//aain_2
    {0x3C, 0x2d07}, //1C02;//gain_1
    {0x3D, 0x2c04}, //3C01;//gain_0
#endif
    {0x33, 0x1502},//liuyanan
    //{;;SET_channe},_to_11
    {0x1B, 0x0001},//set_channel
    {0x30, 0x024D},
    {0x29, 0xD468},
    {0x29, 0x1468},
    {0x30, 0x0249},
    {0x3f, 0x0000},

};


#endif

