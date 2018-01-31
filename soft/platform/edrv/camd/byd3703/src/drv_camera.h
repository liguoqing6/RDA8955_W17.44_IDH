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



#include "hal_i2c.h"
#include "hal_camera.h"
#include "camera_m.h"

#if defined(__CAMERA_FULL_OSD__) || defined(__CAM_ROTATE_90__) || defined(__CAM_ROTATE_270__)
#define __RGB565__
#endif

typedef struct
{
    UINT8 Addr;            // Register Address
    UINT8 Data;             // Register Data
    UINT8 Wait;            // Time to wait after write
} CAM_REG_T;

typedef struct
{
    UINT16 Len;             // Size of array
    CAM_REG_T *RegVal;      // Array of registers
} CAM_REG_GROUP_T;

typedef enum
{
    CAM_MODE_IDLE,
    CAM_MODE_VIEWFINDER,
    CAM_MODE_PREP_IMG_CAPTURE,
    CAM_MODE_IMG_CAPTURE,
    CAM_MODE_PREP_VID_CAPTURE,
    CAM_MODE_VID_CAPTURE
} CAM_MODE_T;

// On FPGA platform, Pixel Clock must not be too fast or xfer screws up
#define CAM_CLK_CFG 0x81

// use this for 320x240 {QVGA) capture
PRIVATE const CAM_REG_T RG_InitPowerOnQvga[] =
{
    {0x12,0x80,0x01},
    {0xff,0xff,0x01},
    {0x15,0x02,0x01},  //0x02
    {0x3a,0x04,0x01},
    {0x09,0x01,0x01},
    {0x11,0x80,0x01},
    {0x13,0x00,0x01},
    {0x01,0x13,0x01},
    {0x02,0x25,0x01},
    {0x87,0x18,0x01},
    {0x8c,0x02,0x01},//01 :devided by 2  02 :devided by 1
    {0x8d,0xfd,0x01},//cb: devided by 2  fd :devided by 1
    {0x13,0x07,0x01},

    //black level ,对上电偏绿有改善,如果需要请使用
    /*
    {0x05,0x1f,0x01},
    {0x06,0x60,0x01},
    {0x14,0x1f,0x01},
    {0x27,0x03,0x01},
    {0x06,0xe0,0x01},
    */

    //lens shading
    {0x35,0x68,0x01},
    {0x65,0x68,0x01},
    {0x66,0x62,0x01},
    {0x36,0x05,0x01},
    {0x37,0xf6,0x01},
    {0x38,0x46,0x01},
    {0x9b,0xf6,0x01},
    {0x9c,0x46,0x01},
    {0xbc,0x01,0x01},
    {0xbd,0xf6,0x01},
    {0xbe,0x46,0x01},

    //AE
    {0x82,0x14,0x01},
    {0x83,0x23,0x01},
    {0x9a,0x23,0x01}, //the same as 0x83
    {0x84,0x1a,0x01},
    {0x85,0x20,0x01},
    {0x89,0x04,0x01}, //02 :devided by 2    04 :devided by 1
    {0x8a,0x08,0x01}, //04: devided by 2    05 :devided by 1
    {0x86,0x28,0x01},
    {0x96,0xa6,0x01}, //AE speed
    {0x97,0x0c,0x01}, //AE speed
    {0x98,0x18,0x01}, //AE speed
    //AE target
    {0x24,0x7a,0x01},//灯箱测试  0x6a
    {0x25,0x8a,0x01},//灯箱测试  0x7a
    {0x94,0x0a,0x01}, //INT_OPEN
    {0x80,0x55,0x01},

    //denoise
    {0x70,0x6f,0x01}, //denoise
    {0x72,0x4f,0x01}, //denoise
    {0x73,0x2f,0x01}, //denoise
    {0x74,0x27,0x01}, //denoise
    {0x77,0x90,0x01},//去除格子噪声
    {0x7a,0x4e,0x01},//denoise in   low light , 0x8e\0x4e\0x0e
    {0x7b,0x28,0x01}, //the same as 0x86

    //black level
    {0X1F,0x20,0x01}, //G target
    {0X22,0x20,0x01}, //R target
    {0X26,0x20,0x01}, //B target
    //模拟部分参数
    {0X16,0x00,0x01}, //如果觉得黑色物体不够黑，有点偏红，将0x16写为0x03会有点改善
    {0xbb,0x20,0x01},   // deglitch  对xclk整形
    {0xeb,0x30,0x01},
    {0xf5,0x21,0x01},
    {0xe1,0x3c,0x01},
    {0xbb,0x20,0x01},
    {0X2f,0X66,0x01},
    {0x06,0xe0,0x01},

    //anti black sun spot
    {0x61,0xd3,0x01}, //0x61[3]=0 black sun disable
    {0x79,0x48,0x01}, //0x79[7]=0 black sun disable

    //contrast
    {0x56,0x40,0x01},
    //Gamma

    {0x3b,0x60,0x01}, //auto gamma offset adjust in  low light
    {0x3c,0x20,0x01}, //auto gamma offset adjust in  low light

    {0x39,0x80,0x01},
    //gamma1
    /*
    {0x3f,0xb0,0x01},
    {0X40,0X88,0x01},
    {0X41,0X74,0x01},
    {0X42,0X5E,0x01},
    {0X43,0X4c,0x01},
    {0X44,0X44,0x01},
    {0X45,0X3E,0x01},
    {0X46,0X39,0x01},
    {0X47,0X35,0x01},
    {0X48,0X31,0x01},
    {0X49,0X2E,0x01},
    {0X4b,0X2B,0x01},
    {0X4c,0X29,0x01},
    {0X4e,0X25,0x01},
    {0X4f,0X22,0x01},
    {0X50,0X1F,0x01},
    */
    /*gamma2  过曝过度好，高亮度
    {0x3f,0xb0,0x01},
    {0X40,0X9b,0x01},
    {0X41,0X88,0x01},
    {0X42,0X6e,0x01},
    {0X43,0X59,0x01},
    {0X44,0X4d,0x01},
    {0X45,0X45,0x01},
    {0X46,0X3e,0x01},
    {0X47,0X39,0x01},
    {0X48,0X35,0x01},
    {0X49,0X31,0x01},
    {0X4b,0X2e,0x01},
    {0X4c,0X2b,0x01},
    {0X4e,0X26,0x01},
    {0X4f,0X23,0x01},
    {0X50,0X1F,0x01},
    */
    //gamma3 清晰亮丽 灰阶分布好
    /*
    {0X3f,0Xb0,0x01},
    {0X40,0X60,0x01},
    {0X41,0X60,0x01},
    {0X42,0X66,0x01},
    {0X43,0X57,0x01},
    {0X44,0X4c,0x01},
    {0X45,0X43,0x01},
    {0X46,0X3c,0x01},
    {0X47,0X37,0x01},
    {0X48,0X33,0x01},
    {0X49,0X2f,0x01},
    {0X4b,0X2c,0x01},
    {0X4c,0X29,0x01},
    {0X4e,0X25,0x01},
    {0X4f,0X22,0x01},
    {0X50,0X20,0x01},
    */
    //gamma 4   low noise
    {0X3f,0Xa8,0x01},
    {0X40,0X48,0x01},
    {0X41,0X54,0x01},
    {0X42,0X4E,0x01},
    {0X43,0X44,0x01},
    {0X44,0X3E,0x01},
    {0X45,0X39,0x01},
    {0X46,0X35,0x01},
    {0X47,0X31,0x01},
    {0X48,0X2E,0x01},
    {0X49,0X2B,0x01},
    {0X4b,0X29,0x01},
    {0X4c,0X27,0x01},
    {0X4e,0X23,0x01},
    {0X4f,0X20,0x01},
    {0X50,0X20,0x01},


    //color matrix
    {0x51,0x0d,0x01},
    {0x52,0x21,0x01},
    {0x53,0x14,0x01},
    {0x54,0x15,0x01},
    {0x57,0x8d,0x01},
    {0x58,0x78,0x01},
    {0x59,0x5f,0x01},
    {0x5a,0x84,0x01},
    {0x5b,0x25,0x01},
    {0x5D,0x95,0x01},
    {0x5C,0x0e,0x01},

    /*

    // color  艳丽
    {0x51,0x0e,0x01},
    {0x52,0x16,0x01},
    {0x53,0x07,0x01},
    {0x54,0x1a,0x01},
    {0x57,0x9d,0x01},
    {0x58,0x82,0x01},
    {0x59,0x71,0x01},
    {0x5a,0x8d,0x01},
    {0x5b,0x1c,0x01},
    {0x5D,0x95,0x01},
    {0x5C,0x0e,0x01},
    //



    //适中
    {0x51,0x08,0x01},
    {0x52,0x0E,0x01},
    {0x53,0x06,0x01},
    {0x54,0x12,0x01},
    {0x57,0x82,0x01},
    {0x58,0x70,0x01},
    {0x59,0x5C,0x01},
    {0x5a,0x77,0x01},
    {0x5b,0x1B,0x01},
    {0x5c,0x0e,0x01}, //0x5c[3:0] low light color coefficient，smaller ,lower noise
    {0x5d,0x95,0x01},


    //color 淡
    {0x51,0x03,0x01},
    {0x52,0x0d,0x01},
    {0x53,0x0b,0x01},
    {0x54,0x14,0x01},
    {0x57,0x59,0x01},
    {0x58,0x45,0x01},
    {0x59,0x41,0x01},
    {0x5a,0x5f,0x01},
    {0x5b,0x1e,0x01},
    {0x5c,0x0e,0x01}, //0x5c[3:0] low light color coefficient，smaller ,lower noise
    {0x5d,0x95,0x01},
    */

    {0x60,0x20,0x01}, //color open in low light
    //AWB
    {0x6a,0x01,0x01},//如果肤色偏色，将0x6a写为0x81.
    {0x23,0x66,0x01},//Green gain
    {0xa0,0x07,0x01},//0xa0写0x03，黑色物体更红；0xa0写0x07，黑色物体更黑；

    {0xa1,0X41,0x01},//
    {0xa2,0X0e,0x01},
    {0xa3,0X26,0x01},
    {0xa4,0X0d,0x01},
    //冷色调
    {0xa5,0x28,0x01},//The upper limit of red gain
    /*暖色调
    {0xa5,0x2d,0x01},
    */
    {0xa6,0x04,0x01},
    {0xa7,0x80,0x01}, //BLUE Target
    {0xa8,0x80,0x01},//RED Target
    {0xa9,0x28,0x01},
    {0xaa,0x28,0x01},
    {0xab,0x28,0x01},
    {0xac,0x3c,0x01},
    {0xad,0xf0,0x01},
    {0xc8,0x18,0x01},
    {0xc9,0x20,0x01},
    {0xca,0x17,0x01},
    {0xcb,0x1f,0x01},
    {0xaf,0x00,0x01},
    {0xc5,0x18,0x01},
    {0xc6,0x00,0x01},
    {0xc7,0x20,0x01},
    {0xae,0x83,0x01},
    {0xcc,0x30,0x01},
    {0xcd,0x70,0x01},
    {0xee,0x4c,0x01}, // P_TH

    // color saturation
    {0xb0,0xd0,0x01},
    {0xb1,0xc0,0x01},
    {0xb2,0xb0,0x01},
    /* // 饱和度艳丽
      {0xb1,0xd0,0x01},
      {0xb2,0xc0,0x01},
    */                          //640*480：
    {0xb3,0x88,0x01},

    //switch direction
    {0x1e,0x00,0x01}, //00:normal  10:IMAGE_V_MIRROR     20:IMAGE_H_MIRROR  30:IMAGE_HV_MIRROR
    {0x8e,0x06,0x01},//03
    {0x8f,0x7a,0x01},//3d //10fps

    //320*240：
    {0x17,0x24,0x01},
    {0x18,0x74,0x01},
    {0x19,0x1e,0x01},
    {0x1a,0x5a,0x01},
#ifdef __RGB565__
    {0x12,0x04,0x01},
    {0x3a,0x00,0x01},
#endif
};

// use this for 640x480 {VGA) capture
// sensor initiation for camera mode
PRIVATE const CAM_REG_T RG_InitPowerOnVga[] =
{
    {0x12,0x80,0x01},
    {0xff,0xff,0x01},
    {0x15,0x02,0x01},  //0x02
    {0x3a,0x04,0x01},
    {0x09,0x01,0x01},
    {0x11,0x80,0x01},
    {0x13,0x00,0x01},
    {0x01,0x13,0x01},
    {0x02,0x25,0x01},
    {0x87,0x18,0x01},
    {0x8c,0x02,0x01},//01 :devided by 2  02 :devided by 1
    {0x8d,0xfd,0x01},//cb: devided by 2  fd :devided by 1
    {0x13,0x07,0x01},

    //black level ,对上电偏绿有改善,如果需要请使用
    /*
    {0x05,0x1f,0x01},
    {0x06,0x60,0x01},
    {0x14,0x1f,0x01},
    {0x27,0x03,0x01},
    {0x06,0xe0,0x01},
    */

    //lens shading
    {0x35,0x68,0x01},
    {0x65,0x68,0x01},
    {0x66,0x62,0x01},
    {0x36,0x05,0x01},
    {0x37,0xf6,0x01},
    {0x38,0x46,0x01},
    {0x9b,0xf6,0x01},
    {0x9c,0x46,0x01},
    {0xbc,0x01,0x01},
    {0xbd,0xf6,0x01},
    {0xbe,0x46,0x01},

    //AE
    {0x82,0x12,0x01},
    {0x83,0x23,0x01},
    {0x9a,0x23,0x01}, //the same as 0x83
    {0x84,0x1a,0x01},
    {0x85,0x20,0x01},
    {0x89,0x04,0x01}, //02 :devided by 2    04 :devided by 1
    {0x8a,0x08,0x01}, //04: devided by 2    05 :devided by 1
    {0x86,0x25,0x01},
    {0x96,0xa6,0x01}, //AE speed
    {0x97,0x0c,0x01}, //AE speed
    {0x98,0x18,0x01}, //AE speed
    //AE target
    {0x24,0x7a,0x01},//灯箱测试  0x6a
    {0x25,0x8a,0x01},//灯箱测试  0x7a
    {0x94,0x0a,0x01}, //INT_OPEN
    {0x80,0x55,0x01},

    //denoise
    {0x70,0x2f,0x01}, //denoise
    {0x72,0x4f,0x01}, //denoise
    {0x73,0x2f,0x01}, //denoise
    {0x74,0x27,0x01}, //denoise
    {0x77,0x90,0x01},//去除格子噪声
    {0x7a,0x0e,0x01},//denoise in   low light , 0x8e\0x4e\0x0e
    {0x7b,0x28,0x01}, //the same as 0x86

    //black level
    {0X1F,0x20,0x01}, //G target
    {0X22,0x20,0x01}, //R target
    {0X26,0x20,0x01}, //B target
    //模拟部分参数
    {0X16,0x03,0x01}, //如果觉得黑色物体不够黑，有点偏红，将0x16写为0x03会有点改善
    {0xbb,0x20,0x01},   // deglitch  对xclk整形
    {0xeb,0x30,0x01},
    {0xf5,0x21,0x01},
    {0xe1,0x3c,0x01},
    {0xbb,0x20,0x01},
    {0X2f,0Xf6,0x01},
    {0x06,0xe0,0x01},

    //anti black sun spot
    {0x61,0xd3,0x01}, //0x61[3]=0 black sun disable
    {0x79,0x48,0x01}, //0x79[7]=0 black sun disable

    //contrast
    {0x56,0x40,0x01},
    //Gamma

    {0x3b,0x60,0x01}, //auto gamma offset adjust in  low light
    {0x3c,0x20,0x01}, //auto gamma offset adjust in  low light

    {0x39,0x80,0x01},
    //gamma1
    /*
    {0x3f,0xb0,0x01},
    {0X40,0X88,0x01},
    {0X41,0X74,0x01},
    {0X42,0X5E,0x01},
    {0X43,0X4c,0x01},
    {0X44,0X44,0x01},
    {0X45,0X3E,0x01},
    {0X46,0X39,0x01},
    {0X47,0X35,0x01},
    {0X48,0X31,0x01},
    {0X49,0X2E,0x01},
    {0X4b,0X2B,0x01},
    {0X4c,0X29,0x01},
    {0X4e,0X25,0x01},
    {0X4f,0X22,0x01},
    {0X50,0X1F,0x01},
    */
    /*gamma2  过曝过度好，高亮度
    {0x3f,0xb0,0x01},
    {0X40,0X9b,0x01},
    {0X41,0X88,0x01},
    {0X42,0X6e,0x01},
    {0X43,0X59,0x01},
    {0X44,0X4d,0x01},
    {0X45,0X45,0x01},
    {0X46,0X3e,0x01},
    {0X47,0X39,0x01},
    {0X48,0X35,0x01},
    {0X49,0X31,0x01},
    {0X4b,0X2e,0x01},
    {0X4c,0X2b,0x01},
    {0X4e,0X26,0x01},
    {0X4f,0X23,0x01},
    {0X50,0X1F,0x01},
    */
    /*
    //gamma3 清晰亮丽 灰阶分布好
    {0X3f,0Xb0,0x01},
    {0X40,0X60,0x01},
    {0X41,0X60,0x01},
    {0X42,0X66,0x01},
    {0X43,0X57,0x01},
    {0X44,0X4c,0x01},
    {0X45,0X43,0x01},
    {0X46,0X3c,0x01},
    {0X47,0X37,0x01},
    {0X48,0X33,0x01},
    {0X49,0X2f,0x01},
    {0X4b,0X2c,0x01},
    {0X4c,0X29,0x01},
    {0X4e,0X25,0x01},
    {0X4f,0X22,0x01},
    {0X50,0X20,0x01},
    */

    //gamma 4   low noise
    {0X3f,0Xb8,0x01},
    {0X40,0X48,0x01},
    {0X41,0X54,0x01},
    {0X42,0X4E,0x01},
    {0X43,0X44,0x01},
    {0X44,0X3E,0x01},
    {0X45,0X39,0x01},
    {0X46,0X35,0x01},
    {0X47,0X31,0x01},
    {0X48,0X2E,0x01},
    {0X49,0X2B,0x01},
    {0X4b,0X29,0x01},
    {0X4c,0X27,0x01},
    {0X4e,0X23,0x01},
    {0X4f,0X20,0x01},
    {0X50,0X20,0x01},
    /*
        //color matrix
        {0x51,0x0d,0x01},
        {0x52,0x21,0x01},
        {0x53,0x14,0x01},
        {0x54,0x15,0x01},
        {0x57,0x8d,0x01},
        {0x58,0x78,0x01},
        {0x59,0x5f,0x01},
        {0x5a,0x84,0x01},
        {0x5b,0x25,0x01},
        {0x5D,0x95,0x01},
        {0x5C,0x0e,0x01},
    */

    // color 艳丽
    {0x51,0x0e,0x01},
    {0x52,0x16,0x01},
    {0x53,0x07,0x01},
    {0x54,0x1a,0x01},
    {0x57,0x9d,0x01},
    {0x58,0x82,0x01},
    {0x59,0x71,0x01},
    {0x5a,0x8d,0x01},
    {0x5b,0x1c,0x01},
    {0x5D,0x95,0x01},
    {0x5C,0x0e,0x01},



    // color 适中
    /*
        {0x51,0x08,0x01},
        {0x52,0x0E,0x01},
        {0x53,0x06,0x01},
        {0x54,0x12,0x01},
        {0x57,0x82,0x01},
        {0x58,0x70,0x01},
        {0x59,0x5C,0x01},
        {0x5a,0x77,0x01},
        {0x5b,0x1B,0x01},
        {0x5c,0x0e,0x01}, //0x5c[3:0] low light color coefficient，smaller ,lower noise
        {0x5d,0x95,0x01},
    */
    //color 淡
    /*
        {0x51,0x03,0x01},
        {0x52,0x0d,0x01},
        {0x53,0x0b,0x01},
        {0x54,0x14,0x01},
        {0x57,0x59,0x01},
        {0x58,0x45,0x01},
        {0x59,0x41,0x01},
        {0x5a,0x5f,0x01},
        {0x5b,0x1e,0x01},
        {0x5c,0x0e,0x01}, //0x5c[3:0] low light color coefficient，smaller ,lower noise
        {0x5d,0x95,0x01},
    */

    {0x60,0x20,0x01}, //color open in low light
    //AWB
    {0x6a,0x01,0x01},//如果肤色偏色，将0x6a写为0x81.
    {0x23,0x66,0x01},//Green gain
    {0xa0,0x07,0x01},//0xa0写0x03，黑色物体更红；0xa0写0x07，黑色物体更黑；

    {0xa1,0X41,0x01},//
    {0xa2,0X0e,0x01},
    {0xa3,0X26,0x01},
    {0xa4,0X0d,0x01},

    //冷色调
    /*
    {0xa5,0x28,0x01},//The upper limit of red gain
    */
    // 暖色调
    {0xa5,0x2d,0x01},

    {0xa6,0x04,0x01},
    {0xa7,0x80,0x01}, //BLUE Target
    {0xa8,0x80,0x01},//RED Target
    {0xa9,0x28,0x01},
    {0xaa,0x28,0x01},
    {0xab,0x28,0x01},
    {0xac,0x3c,0x01},
    {0xad,0xf0,0x01},
    {0xc8,0x18,0x01},
    {0xc9,0x20,0x01},
    {0xca,0x17,0x01},
    {0xcb,0x1f,0x01},
    {0xaf,0x00,0x01},
    {0xc5,0x18,0x01},
    {0xc6,0x00,0x01},
    {0xc7,0x20,0x01},
    {0xae,0x83,0x01},//如果照户外偏蓝，将此寄存器0xae写为0x81。
    {0xcc,0x30,0x01},
    {0xcd,0x70,0x01},
    {0xee,0x4c,0x01}, // P_TH

    // color saturation
    {0xb0,0xd0,0x01},
    {0xb1,0xc0,0x01},
    {0xb2,0xb0,0x01},

    /* // 饱和度艳丽
      {0xb1,0xd0,0x01},
      {0xb2,0xc0,0x01},
    */                          //640*480：
    {0xb3,0x88,0x01},

    //switch direction
    {0x1e,0x10,0x01}, //00:normal  10:IMAGE_V_MIRROR     20:IMAGE_H_MIRROR  30:IMAGE_HV_MIRROR
    {0x8e,0x06,0x01},//03
    {0x8f,0x7a,0x01},//3d //10fps

    //640*480：
    {0x17,0x00,0x01},
    {0x18,0xa0,0x01},
    {0x19,0x00,0x01},
    {0x1a,0x78,0x01},
#ifdef __RGB565__
    {0x12,0x04,0x01},
    {0x3a,0x00,0x01},
#endif

};
#if 1
// use this for 160*120 {QQVGA) capture
PRIVATE const CAM_REG_T RG_InitPowerOnQqvga[] =
{
    {0x12,0x80,0x01},
    {0xff,0xff,0x01},
    {0x15,0x02,0x01},  //0x02
    {0x3a,0x04,0x01},
    {0x09,0x01,0x01},
    {0x11,0x80,0x01},
    {0x13,0x00,0x01},
    {0x01,0x15,0x01},
    {0x02,0x24,0x01},
    {0x87,0x18,0x01},
    {0x8c,0x02,0x01},  //02
    {0x8d,0x64,0x01},
    {0x13,0x07,0x01},
// DBLK manual

    //black level ,对上电偏绿有改善
    /*
    {0x05,0x1f,0x01},
    {0x06,0x60,0x01},
    {0x14,0x1f,0x01},
    {0x06,0xe0,0x01},
    */
    //lens shading
    {0x35,0x50,0x01},
    {0x65,0x53,0x01},
    {0x66,0x50,0x01},
    {0x36,0x05,0x01},
    {0x37,0xf6,0x01},
    {0x38,0x46,0x01},
    {0x9b,0xff,0x01},
    {0x9c,0x46,0x01},
    {0xbc,0x01,0x01},
    {0xbd,0xff,0x01},
    {0xbe,0x46,0x01},

    //AE
    {0x82,0x14,0x01},
    {0x83,0x23,0x01},
    {0x9a,0x23,0x01},//the same as 0x83
    {0x84,0x20,0x01},
    {0x85,0x26,0x01},
    {0x89,0x02,0x01},//01 :devided by 2  02 :devided by 1
    {0x8a,0x64,0x01},//32: devided by 2  64 :devided by 1
    {0x86,0x28,0x01},
    {0x96,0xa6,0x01},//AE speed
    {0x97,0x0c,0x01},//AE speed
    {0x98,0x18,0x01},//AE speed
    //AE target
    {0x24,0x80,0x01},///0x78
    {0x25,0x90,0x01},////0x88
    {0x94,0x0a,0x01},//INT_OPEN
    {0x80,0x55,0x01},

    //denoise
    {0x70,0x6f,0x01},//denoise
    {0x72,0x4f,0x01},//denoise
    {0x73,0x2f,0x01},//denoise
    {0x74,0x07,0x01},//denoise   0x27
    {0x7a,0x0e,0x01},//denoise in  low light,0x8e\0x4e\0x0e
    {0x7b,0x28,0x01},//the same as 0x86

    //black level
    {0X1F,0x20,0x01},//G target
    {0X22,0x20,0x01},//R target
    {0X26,0x20,0x01},//B target
    //模拟部分参数
    {0X16,0x00,0x01},//如果觉得黑色物体不够黑，有点偏红，将0x16写为0x03会有点改善
    {0xbb,0x20,0x01},  // deglitch
    {0xeb,0x30,0x01},
    {0xf5,0x21,0x01},
    {0xe1,0x3c,0x01},
    {0xbb,0x20,0x01},
    {0X2f,0X66,0x01},
    {0x06,0xe0,0x01},

    //anti black sun spot
    {0x61,0xd3,0x01},//0x61[3]=0 black sun disable
    {0x79,0x48,0x01},//0x79[7]=0 black sun disable

    //Gamma

    {0x3b,0x60,0x01},//auto gamma offset adjust in  low light
    {0x3c,0x20,0x01},//auto gamma offset adjust in  low light
    {0x56,0x40,0x01},
    {0x39,0x80,0x01},

    /*
        {0x3f,0xc0,0x01},
        {0X40,0X88,0x01},
        {0X41,0X74,0x01},
        {0X42,0X5E,0x01},
        {0X43,0X4c,0x01},
        {0X44,0X44,0x01},
        {0X45,0X3E,0x01},
        {0X46,0X39,0x01},
        {0X47,0X35,0x01},
        {0X48,0X31,0x01},
        {0X49,0X2E,0x01},
        {0X4b,0X2B,0x01},
        {0X4c,0X29,0x01},
        {0X4e,0X25,0x01},
        {0X4f,0X22,0x01},
        {0X50,0X1F,0x01},

    */

    /*
    //gamma1
        {0x3f,0xb0,0x01},
        {0X40,0X88,0x01},
        {0X41,0X74,0x01},
        {0X42,0X5E,0x01},
        {0X43,0X4c,0x01},
        {0X44,0X44,0x01},
        {0X45,0X3E,0x01},
        {0X46,0X39,0x01},
        {0X47,0X35,0x01},
        {0X48,0X31,0x01},
        {0X49,0X2E,0x01},
        {0X4b,0X2B,0x01},
        {0X4c,0X29,0x01},
        {0X4e,0X25,0x01},
        {0X4f,0X22,0x01},
        {0X50,0X1F,0x01},*/

    /* gamma2 高亮
    //gamma 2 清晰
    {0X1f,0X20,0x01},
    {0X22,0X20,0x01},
    {0X3f,0X90,0x01},
    {0X40,0X25,0x01},
    {0X41,0X2a,0x01},
    {0X42,0X28,0x01},
    {0X43,0X28,0x01},
    {0X44,0X20,0x01},
    {0X45,0X1d,0x01},
    {0X46,0X17,0x01},
    {0X47,0X15,0x01},

    */
    /*//gamma3 清晰亮丽
    {0X3f,0Xa0,0x01},
    {0X40,0X60,0x01},
    {0X41,0X60,0x01},
    {0X42,0X66,0x01},
    {0X43,0X57,0x01},
    {0X44,0X4c,0x01},
    {0X45,0X43,0x01},
    {0X46,0X3c,0x01},
    {0X47,0X37,0x01},
    {0X48,0X32,0x01},
    {0X49,0X2f,0x01},
    {0X4b,0X2c,0x01},
    {0X4c,0X29,0x01},
    {0X4e,0X25,0x01},
    {0X4f,0X22,0x01},
    {0X50,0X20,0x01},
    */
    //gamma 4   low noise
    {0X3f,0Xa0,0x01},
    {0X40,0X48,0x01},
    {0X41,0X54,0x01},
    {0X42,0X4E,0x01},
    {0X43,0X44,0x01},
    {0X44,0X3E,0x01},
    {0X45,0X39,0x01},
    {0X46,0X34,0x01},
    {0X47,0X30,0x01},
    {0X48,0X2D,0x01},
    {0X49,0X2A,0x01},
    {0X4b,0X28,0x01},
    {0X4c,0X26,0x01},
    {0X4e,0X22,0x01},
    {0X4f,0X20,0x01},
    {0X50,0X1E,0x01},


    //color matrix
    //艳丽
    {0x51,0x08,0x01},
    {0x52,0x0E,0x01},
    {0x53,0x06,0x01},
    {0x54,0x12,0x01},
    {0x57,0x82,0x01},
    {0x58,0x70,0x01},
    {0x59,0x5C,0x01},
    {0x5a,0x77,0x01},
    {0x5b,0x1B,0x01},
    {0x5c,0x0e,0x01},//0x5c[3:0] low light color coefficient，smaller ,lower noise
    {0x5d,0x95,0x01},

    /* //适中
    {0x51,0x06,0x01},
    {0x52,0x16,0x01},
    {0x53,0x10,0x01},
    {0x54,0x11,0x01},
    {0x57,0x62,0x01},
    {0x58,0x51,0x01},
    {0x59,0x49,0x01},
    {0x5a,0x65,0x01},
    {0x5b,0x1c,0x01},
    {0x5c,0x0e,0x01},//0x5c[3:0] low light color coefficient，smaller ,lower noise
    {0x5d,0x95,0x01},
    */

    /* //淡
    {0x51,0x03,0x01},
    {0x52,0x0d,0x01},
    {0x53,0x0b,0x01},
    {0x54,0x14,0x01},
    {0x57,0x59,0x01},
    {0x58,0x45,0x01},
    {0x59,0x41,0x01},
    {0x5a,0x5f,0x01},
    {0x5b,0x1e,0x01},
    {0x5c,0x0e,0x01},//0x5c[3:0] low light color coefficient，smaller ,lower noise
    {0x5d,0x95,0x01},
    */

    {0x60,0x20,0x01},//color open in low light
    //AWB
    {0x6a,0x81,0x01},
    {0x23,0x66,0x01},//Green gain
    {0xa0,0x03,0x01},

    {0xa1,0X31,0x01},
    {0xa2,0X0e,0x01},
    {0xa3,0X26,0x01},
    {0xa4,0X0d,0x01},
    {0xa5,0x23,0x01},
    {0xa6,0x06,0x01},
    {0xa7,0x81,0x01},//BLUE Target
    {0xa8,0x7f,0x01},//RED Target
    {0xa9,0x1e,0x01},
    {0xaa,0x23,0x01},
    {0xab,0x1e,0x01},
    {0xac,0x3c,0x01},
    {0xad,0xf0,0x01},
    {0xc8,0x19,0x01},
    {0xc9,0x20,0x01},
    {0xca,0x18,0x01},
    {0xcb,0x1f,0x01},
    {0xaf,0x00,0x01},
    {0xc5,0x19,0x01},
    {0xc6,0x00,0x01},
    {0xc7,0x20,0x01},
    {0xae,0x81,0x01},
    {0xcd,0x90,0x01},
    {0xee,0x4c,0x01},// P_TH

    // color saturation
    {0xb0,0xd0,0x01},
    {0xb1,0xb0,0x01},
    {0xb2,0xb0,0x01},
    {0xb3,0x8a,0x01},

    //anti webcamera banding
//  {0x9d,0x4c,0x01},

    //switch direction
    {0x1e,0x00,0x01},//00:normal  10:IMAGE_V_MIRROR   20:IMAGE_H_MIRROR  30:IMAGE_HV_MIRROR

    {0x80,0x55,0x01},/* 50 Hz */
    {0x9d,0x8e,0x01},// MCLK=156M/7=22.28M


    //Fix FR to 20FPS@26M MCLK
    /*
    {0x92,0x53,0x01},
    {0x93,0x02,0x01},
    */
    {0x8e,0x04,0x01},
    {0x8f,0x51,0x01},

    //160*120：
#ifdef __RGB565__
    {0x12,0x14,0x01},
    {0x3a,0x00,0x01},
#else
    {0x12,0x10,0x01},
#endif
    {0x17,0x24,0x01},
    {0x18,0x74,0x01},
    {0x19,0x1e,0x01},
    {0x1a,0x5a,0x01},
};
#else
// use this for 160*120 {QQVGA) capture
PRIVATE const CAM_REG_T RG_InitPowerOnQqvga[] =
{

    {0x12,0x80,0x01},
    {0xff,0xff,0x01},
    {0x15,0x02,0x01},  //0x02
    {0x3a,0x04,0x01},
    {0x09,0x01,0x01},
    {0x11,0x80,0x01},
    {0x13,0x00,0x01},
    {0x01,0x13,0x01},
    {0x02,0x25,0x01},
    {0x87,0x18,0x01},
    {0x8c,0x02,0x01},//01 :devided by 2  02 :devided by 1
    {0x8d,0xfd,0x01},//cb: devided by 2  fd :devided by 1
    {0x13,0x07,0x01},


    //black level ,对上电偏绿有改善,如果需要请使用
    /*
    {0x05,0x1f,0x01},
    {0x06,0x60,0x01},
    {0x14,0x1f,0x01},
    {0x27,0x03,0x01},
    {0x06,0xe0,0x01},
    */

    //lens shading
    {0x35,0x68,0x01},
    {0x65,0x68,0x01},
    {0x66,0x62,0x01},
    {0x36,0x05,0x01},
    {0x37,0xf6,0x01},
    {0x38,0x46,0x01},
    {0x9b,0xf6,0x01},
    {0x9c,0x46,0x01},
    {0xbc,0x01,0x01},
    {0xbd,0xf6,0x01},
    {0xbe,0x46,0x01},

    //AE
    {0x82,0x14,0x01},
    {0x83,0x23,0x01},
    {0x9a,0x23,0x01}, //the same as 0x83
    {0x84,0x1a,0x01},
    {0x85,0x20,0x01},
    {0x89,0x04,0x01}, //02 :devided by 2    04 :devided by 1
    {0x8a,0x08,0x01}, //04: devided by 2    05 :devided by 1
    {0x86,0x28,0x01},//the same as 0x7b
    {0x96,0xa6,0x01}, //AE speed
    {0x97,0x0c,0x01}, //AE speed
    {0x98,0x18,0x01}, //AE speed
    //AE target
    {0x24,0x7a,0x01},//灯箱测试  0x6a
    {0x25,0x8a,0x01},//灯箱测试  0x7a
    {0x94,0x0a,0x01}, //INT_OPEN
    {0x80,0x55,0x01},

    //denoise
    {0x70,0x6f,0x01}, //denoise
    {0x72,0x4f,0x01}, //denoise
    {0x73,0x2f,0x01}, //denoise
    {0x74,0x27,0x01}, //denoise
    {0x77,0x90,0x01},//去除格子噪声
    {0x7a,0x4e,0x01},//denoise in   low light , 0x8e\0x4e\0x0e
    {0x7b,0x28,0x01}, //the same as 0x86

    //black level
    {0X1F,0x20,0x01}, //G target
    {0X22,0x20,0x01}, //R target
    {0X26,0x20,0x01}, //B target
    //模拟部分参数
    {0X16,0x00,0x01}, //如果觉得黑色物体不够黑，有点偏红，将0x16写为0x03会有点改善
    {0xbb,0x20,0x01},   // deglitch  对xclk整形
    {0xeb,0x30,0x01},
    {0xf5,0x21,0x01},
    {0xe1,0x3c,0x01},
    {0xbb,0x20,0x01},
    {0X2f,0X66,0x01},
    {0x06,0xe0,0x01},

    //anti black sun spot
    {0x61,0xd3,0x01}, //0x61[3]=0 black sun disable
    {0x79,0x48,0x01}, //0x79[7]=0 black sun disable

    //contrast
    {0x56,0x40,0x01},
    //Gamma

    {0x3b,0x60,0x01}, //auto gamma offset adjust in  low light
    {0x3c,0x20,0x01}, //auto gamma offset adjust in  low light

    {0x39,0x80,0x01},
    //gamma1
    /*
    {0x3f,0xb0,0x01},
    {0X40,0X88,0x01},
    {0X41,0X74,0x01},
    {0X42,0X5E,0x01},
    {0X43,0X4c,0x01},
    {0X44,0X44,0x01},
    {0X45,0X3E,0x01},
    {0X46,0X39,0x01},
    {0X47,0X35,0x01},
    {0X48,0X31,0x01},
    {0X49,0X2E,0x01},
    {0X4b,0X2B,0x01},
    {0X4c,0X29,0x01},
    {0X4e,0X25,0x01},
    {0X4f,0X22,0x01},
    {0X50,0X1F,0x01},
    */
    /*gamma2  过曝过度好，高亮度
    {0x3f,0xb0,0x01},
    {0X40,0X9b,0x01},
    {0X41,0X88,0x01},
    {0X42,0X6e,0x01},
    {0X43,0X59,0x01},
    {0X44,0X4d,0x01},
    {0X45,0X45,0x01},
    {0X46,0X3e,0x01},
    {0X47,0X39,0x01},
    {0X48,0X35,0x01},
    {0X49,0X31,0x01},
    {0X4b,0X2e,0x01},
    {0X4c,0X2b,0x01},
    {0X4e,0X26,0x01},
    {0X4f,0X23,0x01},
    {0X50,0X1F,0x01},
    */
    //gamma3 清晰亮丽 灰阶分布好
    /*
    {0X3f,0Xb0,0x01},
    {0X40,0X60,0x01},
    {0X41,0X60,0x01},
    {0X42,0X66,0x01},
    {0X43,0X57,0x01},
    {0X44,0X4c,0x01},
    {0X45,0X43,0x01},
    {0X46,0X3c,0x01},
    {0X47,0X37,0x01},
    {0X48,0X33,0x01},
    {0X49,0X2f,0x01},
    {0X4b,0X2c,0x01},
    {0X4c,0X29,0x01},
    {0X4e,0X25,0x01},
    {0X4f,0X22,0x01},
    {0X50,0X20,0x01},
    */
    //gamma 4   low noise
    {0X3f,0Xa8,0x01},
    {0X40,0X48,0x01},
    {0X41,0X54,0x01},
    {0X42,0X4E,0x01},
    {0X43,0X44,0x01},
    {0X44,0X3E,0x01},
    {0X45,0X39,0x01},
    {0X46,0X35,0x01},
    {0X47,0X31,0x01},
    {0X48,0X2E,0x01},
    {0X49,0X2B,0x01},
    {0X4b,0X29,0x01},
    {0X4c,0X27,0x01},
    {0X4e,0X23,0x01},
    {0X4f,0X20,0x01},
    {0X50,0X20,0x01},


    //color matrix
    {0x51,0x0d,0x01},
    {0x52,0x21,0x01},
    {0x53,0x14,0x01},
    {0x54,0x15,0x01},
    {0x57,0x8d,0x01},
    {0x58,0x78,0x01},
    {0x59,0x5f,0x01},
    {0x5a,0x84,0x01},
    {0x5b,0x25,0x01},
    {0x5D,0x95,0x01},
    {0x5C,0x0e,0x01},

    /*

    // color  艳丽
    {0x51,0x0e,0x01},
    {0x52,0x16,0x01},
    {0x53,0x07,0x01},
    {0x54,0x1a,0x01},
    {0x57,0x9d,0x01},
    {0x58,0x82,0x01},
    {0x59,0x71,0x01},
    {0x5a,0x8d,0x01},
    {0x5b,0x1c,0x01},
    {0x5D,0x95,0x01},
    {0x5C,0x0e,0x01},
    //



    //适中
    {0x51,0x08,0x01},
    {0x52,0x0E,0x01},
    {0x53,0x06,0x01},
    {0x54,0x12,0x01},
    {0x57,0x82,0x01},
    {0x58,0x70,0x01},
    {0x59,0x5C,0x01},
    {0x5a,0x77,0x01},
    {0x5b,0x1B,0x01},
    {0x5c,0x0e,0x01}, //0x5c[3:0] low light color coefficient，smaller ,lower noise
    {0x5d,0x95,0x01},


    //color 淡
    {0x51,0x03,0x01},
    {0x52,0x0d,0x01},
    {0x53,0x0b,0x01},
    {0x54,0x14,0x01},
    {0x57,0x59,0x01},
    {0x58,0x45,0x01},
    {0x59,0x41,0x01},
    {0x5a,0x5f,0x01},
    {0x5b,0x1e,0x01},
    {0x5c,0x0e,0x01}, //0x5c[3:0] low light color coefficient，smaller ,lower noise
    {0x5d,0x95,0x01},
    */

    {0x60,0x20,0x01}, //color open in low light
    //AWB
    {0x6a,0x01,0x01},//如果肤色偏色，将0x6a写为0x81.
    {0x23,0x66,0x01},//Green gain
    {0xa0,0x07,0x01},//0xa0写0x03，黑色物体更红；0xa0写0x07，黑色物体更黑；

    {0xa1,0X41,0x01},//
    {0xa2,0X0e,0x01},
    {0xa3,0X26,0x01},
    {0xa4,0X0d,0x01},
    {0xa5,0x28,0x01},//The upper limit of red gain
    /*暖色调
    {0xa5,0x2d,0x01},
    */
    {0xa6,0x04,0x01},
    {0xa7,0x80,0x01}, //BLUE Target
    {0xa8,0x80,0x01},//RED Target
    {0xa9,0x28,0x01},
    {0xaa,0x28,0x01},
    {0xab,0x28,0x01},
    {0xac,0x3c,0x01},
    {0xad,0xf0,0x01},
    {0xc8,0x18,0x01},
    {0xc9,0x20,0x01},
    {0xca,0x17,0x01},
    {0xcb,0x1f,0x01},
    {0xaf,0x00,0x01},
    {0xc5,0x18,0x01},
    {0xc6,0x00,0x01},
    {0xc7,0x20,0x01},
    {0xae,0x83,0x01},
    {0xcc,0x30,0x01},
    {0xcd,0x70,0x01},
    {0xee,0x4c,0x01}, // P_TH

    // color saturation
    {0xb0,0xd0,0x01},
    {0xb1,0xc0,0x01},
    {0xb2,0xb0,0x01},
    /* // 饱和度艳丽
      {0xb1,0xd0,0x01},
      {0xb2,0xc0,0x01},
    */                          //640*480：
    {0xb3,0x88,0x01},

    //switch direction
    {0x1e,0x00,0x01}, //00:normal  10:IMAGE_V_MIRROR     20:IMAGE_H_MIRROR  30:IMAGE_HV_MIRROR
    {0x8e,0x06,0x01},//03
    {0x8f,0x7a,0x01},//3d //10fps

    //160*120：
    {0x17,0x00,0x01},
    {0x18,0xa0,0x01},
    {0x19,0x00,0x01},
    {0x1a,0x78,0x01},


};
#endif

PRIVATE const CAM_REG_T RG_VidFormatVga[] =
{
    {0x2a,0x10,0x01}, //dummy pixel
    {0x2b,0x6a,0x01}, //dummy pixel

    {0x92,0xc8,0x01}, //dummy line
    {0x93,0x00,0x01}, //dummy line

    {0x13,0x02,0x01}, //disable AE

    {0x24,0x8a,0x01},
    {0x25,0x9a,0x01},

    {0x8c,0x02,0x01}, //real integration time [15:8]
    {0x8d,0x60,0x01}, //real integration time [7:0]
    {0x8e,0x02,0x01}, //max integration time [15:8]
    {0x8f,0x60,0x01}, //max integration time [7:0]

};

PRIVATE const CAM_REG_T RG_VidFormatQvga[] =
{
#if !defined(VDOREC_FAST_RECORDING)
    {0x2a,0x10,0x01}, //dummy pixel
    {0x2b,0xf0,0x01}, //dummy pixel

    {0x92,0x00,0x01}, //dummy line
    {0x93,0x00,0x01}, //dummy line
#else
    {0x2a,0x00,0x01}, //dummy pixel
    {0x2b,0x28,0x01}, //dummy pixel

    {0x92,0x00,0x01}, //dummy line
    {0x93,0x00,0x01}, //dummy line
#endif
    {0x13,0x02,0x01}, //disable AE

    {0x24,0x8a,0x01},
    {0x25,0x9a,0x01},

    {0x8c,0x02,0x01}, //real integration time [15:8]
    {0x8d,0x06,0x01}, //real integration time [7:0]
    {0x8e,0x02,0x01}, //max integration time [15:8]
    {0x8f,0x06,0x01}, //max integration time [7:0]
};

PRIVATE const CAM_REG_T RG_VidFormatQqvga[] =
{
#if !defined(VDOREC_FAST_RECORDING)
    {0x2a,0x10,0x01}, //dummy pixel
    {0x2b,0xf0,0x01}, //dummy pixel

    {0x92,0x00,0x01}, //dummy line
    {0x93,0x00,0x01}, //dummy line
#else
    {0x2a,0x00,0x01}, //dummy pixel
    {0x2b,0x36,0x01}, //dummy pixel

    {0x92,0x00,0x01}, //dummy line
    {0x93,0x00,0x01}, //dummy line
#endif
    {0x13,0x02,0x01}, //disable AE

    {0x24,0x8a,0x01},
    {0x25,0x9a,0x01},

    {0x8c,0x02,0x01}, //real integration time [15:8]
    {0x8d,0x06,0x01}, //real integration time [7:0]
    {0x8e,0x02,0x01}, //max integration time [15:8]
    {0x8f,0x06,0x01}, //max integration time [7:0]
};

typedef struct
{
// Camera information structure
    char                desc[40];

    UINT8               snrtype;            //sensor type(RGB or YUV)
    UINT8               pclk;               //use PCLK of sensor
    UINT8               clkcfg;             //[0]: VSync delay enable; [1]: Fifo VSync delay enable; [2]: Use PCLK Negtive Edge.
    HAL_I2C_BPS_T       i2crate;            //I2C rate : KHz
    UINT8               i2caddress;         //I2C address
    UINT8               i2cispaddress;      //ISP I2C address
    UINT8               pwrcfg;             //sensor power initial configure(SIF REG801 BIT[0]~BIT[2])
    BOOL                rstactiveh;         //sensor reset active hi/low polarity (TRUE = active hi)
    BOOL                snrrst;             //Reset sensor enable

    CAM_MODE_T          cammode;


    BOOL                capturevideo;
    BOOL                captureframe;
    UINT8               numactivebuffers;
    UINT8               currentbuf;

    UINT8               brightness;         //brightness
    UINT8               contrast;           //contrast

    CAM_FORMAT_T        format;
    UINT32            npixels;
    CAM_IMAGE_T         vidbuffer;

    CAM_REG_GROUP_T     standby;            //sensor standby register
    CAM_REG_GROUP_T     Initpoweron;        //SENSOR ISP initial configure

    CAM_REG_GROUP_T     sifpwronseq;        //Sif config sequence(Reg.800 bit0~2) when sensor power on
    CAM_REG_GROUP_T     sifstdbyseq;        //Sif config sequence(Reg.800 bit0~2) when sensor standby
    CAM_REG_GROUP_T     dsif;               //SIF initial configure
//    TSnrSizeCfgGroup    snrSizeCfg;         //sensor size configure information

// This 'callback' mechanism is not necessary because the encapsulation is taken
// care of by the environment
//    PSensorSetReg       snrSetRegCall;      //set reg callback
//    PSensorGetReg       snrGetRegCall;
//    PSnrIdChk           snrIdChkCall;
//    PSnrMirrorFlip      snrMirrorFlipCall;
//    PSnrContrast        snrContrastCall;
//    PSnrBrightness      snrBrightnessCall;
//    PSnrMode            snrModeCall;
//    PSnrGetEt           snrGetEt;
//    PSnrSetEt           snrSetEt;
//    TFlashParm          flashparm;
    CAM_IRQ_HANDLER_T   camirqhandler;
} CAM_INFO_T;

PRIVATE volatile CAM_INFO_T gSensorInfo =
{
    "BF3703 RGB Mode",      // char desc[40];

    0,                      // UINT8 snrtype; (rgb)
    1,                      // UINT8 pclk; use or don't use PCLK of sensor???
    0,                      // UINT8 clkcfg; ???
    HAL_I2C_BPS_100K,       // UINT16 i2crate;
    0x6E,                   // UINT8 i2caddress; this is the _REAL_ slave address.
    //  The value written in phase 1 of a write cycle will be 0x42
    //  while the value just before the read will be 0x43
    0x6E,                   // UINT8 i2cispaddress;
    0x02,                   // UINT8 pwrcfg;???
    TRUE,                   // BOOL rstactiveh;  // active high
    FALSE,                  // BOOL snrrst;

    CAM_MODE_IDLE,          // cammode

    FALSE,                  // Capture video mode
    FALSE,                  // Capturing single frame
    0,                      // Number of active buffers reserved by the upper layer
    0,                      // current frame buffer

    3,                      // UINT8 brightness;
    4,                      // UINT8 contrast;
    CAM_FORMAT_RGB565,      // Format
    CAM_NPIX_VGA,           // npixels(VGA, QVGA, QQVGA...)
    NULL,                   // Video Buffer.  First frame buffer for video or image buffer

    {0, NULL},              // CAM_REG_GROUP_T standby;
    // Should start with QQVGA, but for testing, start with VGA
//    {sizeof(RG_InitPowerOnQqvga) / sizeof(CAM_REG_T), (CAM_REG_T*)&RG_InitPowerOnQqvga}, // CAM_REG_GROUP_T Initpoweron;
    {sizeof(RG_InitPowerOnVga) / sizeof(CAM_REG_T), (CAM_REG_T*)&RG_InitPowerOnVga}, // CAM_REG_GROUP_T Initpoweron;

    {0, NULL},              // CAM_REG_GROUP_T sifpwronseq;
    {0, NULL},              // CAM_REG_GROUP_T sifstdbyseq;
    {0, NULL},              // CAM_REG_GROUP_T dsif; initial value
    NULL                    // IRQ Callback
};

// ############
// Private
// ############

// These are the commands specific to the SCCB
#define PHASE3_WR_PH1   0x11000     // Start & Write    Slave ID
#define PHASE3_WR_PH2   0x1000      // Write            Slave Register Address
#define PHASE3_WR_PH3   0x1100      // Stop & Write     Slave Register Data

#define PHASE2_WR_PH1   0x11000     // Start & Write    Slave ID
#define PHASE2_WR_PH2   0x1100      // Stop & Write     Slave Register Address (to read)

#define PHASE2_RD_PH1   0x11000     // Start & Write    Slave ID
#define PHASE2_RD_PH2   0x111       // Stop & Read & NACK   Slave Register Read Data

PRIVATE VOID camerap_WriteOneReg( UINT8 Addr, UINT8 Data);
PRIVATE VOID camerap_Delay(UINT16 Wait_mS);
PRIVATE VOID camerap_WriteReg(CAM_REG_T RegWrite);
PRIVATE UINT8 camerap_ReadReg(UINT8 Addr);
PRIVATE VOID camerap_SendRgSeq(const CAM_REG_T *RegList, UINT16 Len);
PRIVATE VOID camerap_InteruptHandler(HAL_CAMERA_IRQ_CAUSE_T cause);
PRIVATE UINT8 camerap_GetId(VOID);

