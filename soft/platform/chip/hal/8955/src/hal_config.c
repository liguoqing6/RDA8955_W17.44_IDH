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


#include "cs_types.h"
#include "chip_id.h"

#include "global_macros.h"
#include "cfg_regs.h"
#include "gpio.h"
#include "tcu.h"
#include "uart.h"

#include "halp_sys.h"
#include "halp_debug.h"
#include "halp_gpio.h"
#include "halp_config.h"
#include "halp_pwm.h"

#include "hal_config.h"
#include "hal_gouda.h"
#include "hal_gpio.h"
#include "hal_pwm.h"
#include "iomux.h"
#include "tgt_hal_cfg.h"

#include "pmd_m.h"


// =============================================================================
//  GLOBAL VARIABLES
// =============================================================================

CONST HAL_CFG_CONFIG_T* g_halCfg;


// =============================================================================
//  FUNCTIONS
// =============================================================================

// =============================================================================
// hal_BoardConfigClk32k
// -----------------------------------------------------------------------------
/// Configure CLK_32K output.
/// @param enable TRUE to configure, and FALSE to disable.
// ============================================================================
PROTECTED VOID hal_BoardConfigClk32k(BOOL enable)
{
    HAL_ASSERT(g_halCfg->useClk32k == TRUE, "32K clock is not configured");
#ifdef FPGA
#else
    if (enable)
    {
        // Setup the pin as 32K clock output
        //  hwp_configRegs->Alt_mux_select =
        //    (hwp_configRegs->Alt_mux_select & ~CFG_REGS_PWL1_MASK) |
        //  CFG_REGS_PWL1_CLK_32K;
         hwp_iomux->pad_KEYOUT_3_cfg = (hwp_iomux->pad_KEYOUT_3_cfg && (~(IOMUX_PAD_KEYOUT_3_SEL(0xf))))|IOMUX_PAD_KEYOUT_3_SEL(5);
		 hwp_sysCtrl->Cfg_Clk_Out = SYS_CTRL_CLKOUT_ENABLE_ENABLE|SYS_CTRL_CLKOUT_SEL_CLK_32K;
    }
    else
    {
        // Setup the pin as GPO (and low ouput has been
        // configured in hal_BoardSetup())
        //   hwp_configRegs->Alt_mux_select =
        //  (hwp_configRegs->Alt_mux_select & ~CFG_REGS_PWL1_MASK) |
        //  CFG_REGS_PWL1_GPO_6;
		hwp_sysCtrl->Cfg_Clk_Out = SYS_CTRL_CLKOUT_ENABLE_DISABLE;
    }
#endif
}


// =============================================================================
// hal_BoardSetupFp
// -----------------------------------------------------------------------------
/// Apply board dependent configuration to HAL for flash programmer
/// @param halCfg Pointer to HAL configuration structure (from the target
/// module).
// ============================================================================
PROTECTED VOID hal_BoardSetupFp(CONST HAL_CFG_CONFIG_T* halCfg)
{
#ifdef FPGA
#else
    // Store the config pointer for later use in hal
    g_halCfg = halCfg;
    hwp_sysCtrl->Cfg_Rsd |= (1<<3);// enalbe the debug r 0 in coolwatcher.

    // Setup all GPIO pins as input mode
    //hwp_configRegs->GPIO_Mode = 0xFFFFFFFF;

    hwp_gpio->gpio_oen_set_in_l = 0xFFFFFFFF;
    hwp_gpio->gpio_oen_set_in_h = 0xFFFFFFFF;

    // Set the LPSCOs polarity from PMD
    // this is assuming xvc needs V_RF, anyway pal will get the real info
    // from xcv and configure LPS properly.
    hwp_tcu->LPS_PU_Ctrl |= pmd_ConfigureRfLowPower(TRUE, FALSE);

    hwp_sysCtrl->Cfg_Rsd |= ((1<<3));// disabel lcd sync
#endif
}


// =============================================================================
// hal_BoardSetupGeneral
// -----------------------------------------------------------------------------
/// Apply board dependent configuration to HAL for general purpose
/// @param halCfg Pointer to HAL configuration structure (from the target
/// module).
// ============================================================================
PROTECTED VOID hal_BoardSetupGeneral(CONST HAL_CFG_CONFIG_T* halCfg)
{
    UINT32 availableGpio = 0;
    UINT32 availableGpo = 0;
    UINT32 altMux = 0;

#ifdef FPGA
    hwp_sysCtrl->Cfg_Rsd &= (~(1<<6));// disabel lcd sync
    // no muxing, do nothing
    availableGpio = 0;
    altMux = 0;

#else // !FPGA

    UINT32 ioDrive2Sel = 0;
	hwp_sysCtrl->Cfg_Rsd |= (1<<3);// enalbe the debug r 0 in coolwatcher.

    // computed GPIO usage depending on the used functionality.
    // GPIO 0 are always GPIO
    availableGpio = HAL_GPIO_BIT(0);

    // computed GPO usage depending on the used functionality.


    // Other Mux configuration
    altMux = 0;

    if (halCfg->camCfg.camSerialIfMode)
    {
        //  HAL_ASSERT(!(halCfg->i2c2UseCamPins),"Cannot use CAM_I2C2 when Serial CAM is used");
        availableGpio |= HAL_GPIO_BIT(19)
                         | HAL_GPIO_BIT(20)
                         | HAL_GPIO_BIT(21)
                         | HAL_GPIO_BIT(22)
                         | HAL_GPIO_BIT(23)
                         | HAL_GPIO_BIT(24);
        //hwp_iomux->pad_CAM_PWDN_cfg = (hwp_iomux->pad_CAM_PWDN_cfg && (~(IOMUX_PAD_SPI_CAM_SCK_SEL(0xf))))|IOMUX_PAD_SPI_CAM_SCK_SEL(0);
        //hwp_iomux->pad_CAM_RSTB_cfg = (hwp_iomux->pad_CAM_RSTB_cfg && (~(IOMUX_PAD_CAM_RSTB_SEL(0xf))))|IOMUX_PAD_CAM_RSTB_SEL(0);
        hwp_iomux->pad_CAM_CLK_cfg = (hwp_iomux->pad_CAM_CLK_cfg && (~(IOMUX_PAD_CAM_CLK_SEL(0xf))))|IOMUX_PAD_CAM_CLK_SEL(0);
        hwp_iomux->pad_SPI_CAM_SCK_cfg = (hwp_iomux->pad_SPI_CAM_SCK_cfg && (~(IOMUX_PAD_SPI_CAM_SCK_SEL(0xf))))|IOMUX_PAD_SPI_CAM_SCK_SEL(0);
        hwp_iomux->pad_SPI_CAM_DI_0_cfg = (hwp_iomux->pad_SPI_CAM_SCK_cfg && (~(IOMUX_PAD_SPI_CAM_DI_0_SEL(0xf))))|IOMUX_PAD_SPI_CAM_DI_0_SEL(0);
        hwp_iomux->pad_SPI_CAM_DI_1_cfg = (hwp_iomux->pad_SPI_CAM_DI_1_cfg && (~(IOMUX_PAD_SPI_CAM_DI_1_SEL(0xf))))|IOMUX_PAD_SPI_CAM_DI_1_SEL(0);
    }
    if (halCfg->i2c2UseCamPins)
    {
        hwp_iomux->pad_CAM_PWDN_cfg = (hwp_iomux->pad_CAM_PWDN_cfg && (~(IOMUX_PAD_SPI_CAM_SCK_SEL(0xf))))|IOMUX_PAD_SPI_CAM_SCK_SEL(2);
        hwp_iomux->pad_CAM_RSTB_cfg = (hwp_iomux->pad_CAM_RSTB_cfg && (~(IOMUX_PAD_CAM_RSTB_SEL(0xf))))|IOMUX_PAD_CAM_RSTB_SEL(2);
    }
    // UART 1 Pin configuration
    switch (halCfg->uartCfg[0])
    {
        case HAL_UART_CONFIG_NONE:
            // continue with HAL_UART_CONFIG_DATA ...
            break;
        case HAL_UART_CONFIG_DATA:
            // use UART1 TXD, RXD
            hwp_iomux->pad_GPIO_0_cfg = IOMUX_PAD_GPIO_0_SEL(1);
            hwp_iomux->pad_GPIO_1_cfg = IOMUX_PAD_GPIO_1_SEL(1);
            availableGpio |= HAL_GPIO_BIT(0)
                             | HAL_GPIO_BIT(1);
            break;
        case HAL_UART_CONFIG_FLOWCONTROL:
            // use UART1 TXD, RXD, CTS, RTS
            hwp_iomux->pad_GPIO_0_cfg = IOMUX_PAD_GPIO_0_SEL(1);
            hwp_iomux->pad_GPIO_1_cfg = IOMUX_PAD_GPIO_1_SEL(1);
            hwp_iomux->pad_GPIO_2_cfg = IOMUX_PAD_GPIO_2_SEL(1);
            hwp_iomux->pad_GPIO_3_cfg = IOMUX_PAD_GPIO_3_SEL(1);
            availableGpio |= HAL_GPIO_BIT(0)
                             | HAL_GPIO_BIT(1)
                             | HAL_GPIO_BIT(2)
                             | HAL_GPIO_BIT(3);
            break;
        case HAL_UART_CONFIG_MODEM:
            // use UART1 TXD, RXD, CTS, RTS, RI, DSR, DCD, DTR
            hwp_iomux->pad_GPIO_0_cfg = IOMUX_PAD_GPIO_0_SEL(1);
            hwp_iomux->pad_GPIO_1_cfg = IOMUX_PAD_GPIO_1_SEL(1);
            hwp_iomux->pad_GPIO_2_cfg = IOMUX_PAD_GPIO_2_SEL(1);
            hwp_iomux->pad_GPIO_3_cfg = IOMUX_PAD_GPIO_3_SEL(1);
            availableGpio |= HAL_GPIO_BIT(0)
                             | HAL_GPIO_BIT(1)
                             | HAL_GPIO_BIT(2)
                             | HAL_GPIO_BIT(3);
            break;
        default:
            HAL_ASSERT(FALSE,
                       "Invalid Uart 1 Configuration (%d).",
                       halCfg->uartCfg[0]);
            break;
    }
    // UART 2 Pin configuration
    switch (halCfg->uartCfg[1])
    {
        case HAL_UART_CONFIG_NONE:
            // continue with HAL_UART_CONFIG_DATA ...
            break;
        case HAL_UART_CONFIG_DATA:
            // use UART1 TXD, RXD
            hwp_iomux->pad_GPIO_4_cfg = IOMUX_PAD_GPIO_4_SEL(1);
            hwp_iomux->pad_GPIO_5_cfg = IOMUX_PAD_GPIO_5_SEL(1);
            availableGpio |= HAL_GPIO_BIT(4)
                             | HAL_GPIO_BIT(5);
            break;
        case HAL_UART_CONFIG_FLOWCONTROL:
            // use UART1 TXD, RXD, CTS, RTS
            hwp_iomux->pad_GPIO_4_cfg = IOMUX_PAD_GPIO_4_SEL(1);
            hwp_iomux->pad_GPIO_5_cfg = IOMUX_PAD_GPIO_5_SEL(1);
            hwp_iomux->pad_GPIO_6_cfg = IOMUX_PAD_GPIO_6_SEL(1);
            hwp_iomux->pad_GPIO_7_cfg = IOMUX_PAD_GPIO_7_SEL(1);
            availableGpio |= HAL_GPIO_BIT(4)
                             | HAL_GPIO_BIT(5)
                             | HAL_GPIO_BIT(6)
                             | HAL_GPIO_BIT(7);
            break;
        case HAL_UART_CONFIG_MODEM:
            // use UART1 TXD, RXD, CTS, RTS, RI, DSR, DCD, DTR
            hwp_iomux->pad_GPIO_4_cfg = IOMUX_PAD_GPIO_4_SEL(1);
            hwp_iomux->pad_GPIO_5_cfg = IOMUX_PAD_GPIO_5_SEL(1);
            hwp_iomux->pad_GPIO_6_cfg = IOMUX_PAD_GPIO_6_SEL(1);
            hwp_iomux->pad_GPIO_7_cfg = IOMUX_PAD_GPIO_7_SEL(1);
            availableGpio |= HAL_GPIO_BIT(4)
                             | HAL_GPIO_BIT(5)
                             | HAL_GPIO_BIT(6)
                             | HAL_GPIO_BIT(7);

            break;
        default:
            HAL_ASSERT(FALSE,
                       "Invalid Uart 2 Configuration (%d).",
                       halCfg->uartCfg[1]);
            break;
    }

    if (halCfg->spiCfg[0].cs1Used)
    {
        hwp_iomux->pad_SDMMC_DATA_0_cfg = IOMUX_PAD_SDMMC_DATA_0_SEL(2);
        hwp_iomux->pad_SDMMC_CLK_cfg = IOMUX_PAD_SDMMC_CLK_SEL(2);
        hwp_iomux->pad_SDMMC_DATA_2_cfg = IOMUX_PAD_SDMMC_DATA_2_SEL(2);
        hwp_iomux->pad_SDMMC_DATA_1_cfg = IOMUX_PAD_SDMMC_DATA_1_SEL(2);
    }
    if (halCfg->spiCfg[0].cs0Used)
    {
        hwp_iomux->pad_SDMMC_CMD_cfg = IOMUX_PAD_SDMMC_CMD_SEL(2);
        hwp_iomux->pad_SDMMC_CLK_cfg = IOMUX_PAD_SDMMC_CLK_SEL(2);
        hwp_iomux->pad_SDMMC_DATA_2_cfg = IOMUX_PAD_SDMMC_DATA_2_SEL(2);
        hwp_iomux->pad_SDMMC_DATA_1_cfg = IOMUX_PAD_SDMMC_DATA_1_SEL(2);
    }
    if (halCfg->spiCfg[1].cs1Used)
    {
        hwp_iomux->pad_GPIO_2_cfg = IOMUX_PAD_GPIO_2_SEL(2);
        hwp_iomux->pad_GPIO_0_cfg = IOMUX_PAD_GPIO_0_SEL(2);
        hwp_iomux->pad_GPIO_4_cfg = IOMUX_PAD_GPIO_4_SEL(2);
        hwp_iomux->pad_GPIO_3_cfg = IOMUX_PAD_GPIO_3_SEL(2);
        availableGpio |= HAL_GPIO_BIT(2)
                         | HAL_GPIO_BIT(0)
                         | HAL_GPIO_BIT(4)
                         | HAL_GPIO_BIT(3);
    }
    if (halCfg->spiCfg[1].cs0Used)
    {
        hwp_iomux->pad_GPIO_1_cfg = IOMUX_PAD_GPIO_1_SEL(2);
        hwp_iomux->pad_GPIO_0_cfg = IOMUX_PAD_GPIO_0_SEL(2);
        hwp_iomux->pad_GPIO_4_cfg = IOMUX_PAD_GPIO_4_SEL(2);
        hwp_iomux->pad_GPIO_3_cfg = IOMUX_PAD_GPIO_3_SEL(2);
        availableGpio |= HAL_GPIO_BIT(1)
                         | HAL_GPIO_BIT(0)
                         | HAL_GPIO_BIT(4)
                         | HAL_GPIO_BIT(3);
    }

    if (halCfg->i2cCfg.i2cUsed)
     {
    	 hwp_iomux->pad_SDMMC_CMD_cfg = IOMUX_PAD_SDMMC_CMD_SEL(3);
    	 hwp_iomux->pad_SDMMC_CLK_cfg = IOMUX_PAD_SDMMC_CLK_SEL(3);
     }

    if (halCfg->i2cCfg.i2cUsed)
     {
    	 hwp_iomux->pad_SDMMC_CMD_cfg = IOMUX_PAD_SDMMC_CMD_SEL(3);
    	 hwp_iomux->pad_SDMMC_CLK_cfg = IOMUX_PAD_SDMMC_CLK_SEL(3);
     }

	if (halCfg->i2cCfg.i2c2Used)
     {
    	 hwp_iomux->pad_CAM_PWDN_cfg = IOMUX_PAD_CAM_RSTB_SEL(2);
    	 hwp_iomux->pad_CAM_RSTB_cfg = IOMUX_PAD_CAM_PWDN_SEL(2);
     }
	#ifdef ONLY_AT_SUPPORT 
	#else
	if (halCfg->i2cCfg.i2c3Used)
     {
	 hwp_iomux->pad_GPIO_6_cfg = IOMUX_PAD_GPIO_6_SEL(2);
	 hwp_iomux->pad_GPIO_7_cfg = IOMUX_PAD_GPIO_7_SEL(2);
	 availableGpio |= HAL_GPIO_BIT(6) | HAL_GPIO_BIT(7);
     }
	#endif
	#ifdef GPS_SUPPORT
	//set 32k out
	hwp_iomux->pad_KEYOUT_3_cfg = IOMUX_PAD_KEYOUT_3_SEL_FUN_DBG_CLK_SEL;
	hwp_sysCtrl->Cfg_Clk_Out = SYS_CTRL_CLKOUT_SEL_CLK_32K|SYS_CTRL_CLKOUT_ENABLE_ENABLE;
	//set GPIO 25 29 30
	hwp_iomux->pad_KEYIN_0_cfg	= IOMUX_PAD_KEYIN_0_SEL_FUN_GPIO_25_SEL;
	hwp_iomux->pad_KEYIN_4_cfg	= IOMUX_PAD_KEYIN_4_SEL_FUN_GPIO_29_SEL;
	hwp_iomux->pad_KEYOUT_0_cfg	= IOMUX_PAD_KEYOUT_0_SEL_FUN_GPIO_30_SEL;
	#endif

#if 0

    if (halCfg->camCfg.camUsed || halCfg->camCfg.cam1Used)
    {
        altMux |= CFG_REGS_DEBUG_PORT_CAMERA;
    }
    else
    {
        altMux |= CFG_REGS_DEBUG_PORT_DEBUG;
    }

    // Gouda Pin Configuration
    if (halCfg->goudaCfg.cs0Used)
    {
        altMux |= CFG_REGS_LCD_CS_0_LCD_CS_0;
    }
    else
    {
        altMux |= CFG_REGS_LCD_CS_0_SPI1_CS_2;
    }

    if (halCfg->goudaCfg.cs1Used)
    {
        altMux |= CFG_REGS_LCD_CS_1_LCD_CS_1;
    }
    else
    {
        altMux |= CFG_REGS_LCD_CS_1_GPO_7;
        availableGpo |= HAL_GPO_BIT(7);
    }

    // Memory Pin Configuration : MA_24 / M_CS_4
    if (halCfg->ebcCfg.cs4Used)
    {
        altMux |= CFG_REGS_MEMORY_ADDRESS_24_M_CS4;
    }
    else
    {
        altMux |= CFG_REGS_MEMORY_ADDRESS_24_MA_24;
    }

    // SDMMC2
    if (halCfg->useSdmmc2==HAL_CFG_SDIO2_SPI1)
    {
        ioDrive2Sel |= CFG_REGS_SDMMC2_SPI1_SDMMC2;
        HAL_ASSERT(!halCfg->spiCfg[0].cs0Used,
                   "Cannot use SPI1 when SDMMC2 is used");
        HAL_ASSERT(!halCfg->spiCfg[0].cs1Used,
                   "Cannot use SPI1 when SDMMC2 is used");
        HAL_ASSERT(!halCfg->i2cCfg.i2c3Used,
                   "Cannot use I2C3 when SDMMC2 is used");
        HAL_ASSERT((halCfg->usedTco & 0x18)==0,
                   "Cannot use TCO_3,4 when SDMMC2 is used");
    }
    // SPI1 Pin Configuration
    else
    {
        if (halCfg->spiCfg[0].cs1Used || halCfg->spiCfg[0].di1Used)
        {
            altMux |= CFG_REGS_SPI1_SELECT_SPI1;

            if (!halCfg->spiCfg[0].cs1Used)
            {
                availableGpio |= HAL_GPIO_BIT(14);
            }
            if (!halCfg->spiCfg[0].di1Used)
            {
                availableGpio |= HAL_GPIO_BIT(16);
            }

            HAL_ASSERT(!halCfg->i2cCfg.i2c3Used,
                       "Cannot use I2C3 when SPI1 is used");
        }
        else
        {
            if (halCfg->i2cCfg.i2c3Used)
            {
                altMux |= CFG_REGS_SPI1_SELECT_I2C_3;
            }
            else
            {
                availableGpio |= HAL_GPIO_BIT(14)
                                 | HAL_GPIO_BIT(16);
            }
        }

        if ((!halCfg->spiCfg[0].cs0Used) && (!halCfg->spiCfg[0].cs1Used))
        {
            availableGpio |= HAL_GPIO_BIT(12);
            availableGpio |= HAL_GPIO_BIT(15);
        }

        // TCO
        if(halCfg->uartKeyinoutSel.uart2UseTco
                || halCfg->uartKeyinoutSel.uart1UseTco)
        {
            HAL_ASSERT(!(halCfg->usedTco & (1<<4)),
                       "Cannot use TCO_4 when UART1/2 is used");
        }
        else if (halCfg->usedTco & (1<<4))
        {
            altMux |= CFG_REGS_TCO_4_TCO_4;
        }
        else
        {
            altMux |= CFG_REGS_TCO_4_GPO_9;
            availableGpo |= HAL_GPO_BIT(9);
        }

        if(halCfg->uartKeyinoutSel.uart2UseTco
                || halCfg->uartKeyinoutSel.uart1UseTco)
        {
            HAL_ASSERT(!(halCfg->usedTco & (1<<3)),
                       "Cannot use TCO_3 when UART1/2 is used");
        }
        else if (halCfg->usedTco & (1<<3))
        {
            altMux |= CFG_REGS_TCO_3_TCO_3;
        }
        else
        {
            altMux |= CFG_REGS_TCO_3_GPO_8;
            availableGpo |= HAL_GPO_BIT(8);
        }
    }

    if(halCfg->uartKeyinoutSel.uart2UseTco)
    {
        ioDrive2Sel |= CFG_REGS_UART2_SPI1_UART2;
        HAL_ASSERT((halCfg->keyInMask & 0x80)==0,
                   "Cannot use KEYIN_7 when UART2 is used");
        HAL_ASSERT(!halCfg->spiCfg[0].cs0Used,
                   "Cannot use SPI1_CS_0 when UART2 is used");
    }
    else if (halCfg->spiCfg[0].cs0Used)
    {
        altMux |= CFG_REGS_SPI1_CS0_SELECT_SPI1_CS0;
        HAL_ASSERT((halCfg->keyInMask & 0x80)==0,
                   "Cannot use KEYIN_7 when SPI1_CS_0 is used");
    }
    else
    {
        if (halCfg->keyInMask & 0x80)
        {
            altMux |= CFG_REGS_SPI1_CS0_SELECT_KEYIN_7;
        }
        else
        {
            availableGpio |= HAL_GPIO_BIT(6);
        }
    }

    // GPIO 20 and 21 do NOT mux with UART any more on 8809
    availableGpio |= HAL_GPIO_BIT(20)|HAL_GPIO_BIT(21);

    // UART 1 Pin configuration
    switch (halCfg->uartCfg[0])
    {
        case HAL_UART_CONFIG_NONE:
            // force TXD line to '0' to not drain power out
            hwp_uart->CMD_Set = UART_TX_BREAK_CONTROL;
            hwp_uart->ctrl = UART_ENABLE;
        // continue with HAL_UART_CONFIG_DATA ...
        case HAL_UART_CONFIG_DATA:
            // use UART1 TXD, RXD
            altMux |= CFG_REGS_UART2_UART2;
            break;
        case HAL_UART_CONFIG_FLOWCONTROL:
            // use UART1 TXD, RXD, CTS, RTS
            altMux |= CFG_REGS_UART2_UART2;
            break;
        case HAL_UART_CONFIG_MODEM:
            // use UART1 TXD, RXD, CTS, RTS, RI, DSR, DCD, DTR
            altMux |= CFG_REGS_UART2_UART1;
            HAL_ASSERT(halCfg->uartCfg[1] == HAL_UART_CONFIG_NONE,
                       "UART 2 must be unused to use UART 1 Modem lines.");
            break;
        default:
            HAL_ASSERT(FALSE,
                       "Invalid Uart 1 Configuration (%d).",
                       halCfg->uartCfg[0]);
            break;
    }
    // UART 2 Pin configuration
    if (halCfg->uartCfg[0] != HAL_UART_CONFIG_MODEM)
    {
        if(halCfg->uartKeyinoutSel.uart2UseTco)
        {
            availableGpio |= HAL_GPIO_BIT(5)
                             | HAL_GPIO_BIT(13)
                             | HAL_GPIO_BIT(7)
                             | HAL_GPIO_BIT(8);
            HAL_ASSERT((halCfg->uartCfg[1]==HAL_UART_CONFIG_NONE
                        || halCfg->uartCfg[1]==HAL_UART_CONFIG_DATA
                        || halCfg->uartCfg[1]==HAL_UART_CONFIG_FLOWCONTROL),
                       "Invalid Uart 2 Configuration (%d).",
                       halCfg->uartCfg[0]);
        }
        else
        {
            switch (halCfg->uartCfg[1])
            {
                case HAL_UART_CONFIG_NONE:
                    availableGpio |= HAL_GPIO_BIT(5)
                                     | HAL_GPIO_BIT(13)
                                     | HAL_GPIO_BIT(7)
                                     | HAL_GPIO_BIT(8);
                    break;
                case HAL_UART_CONFIG_DATA:
                    // use UART2 TXD, RXD
                    availableGpio |= HAL_GPIO_BIT(5)
                                     | HAL_GPIO_BIT(7);
                    break;
                case HAL_UART_CONFIG_FLOWCONTROL:
                    // use UART2 TXD, RXD, CTS, RTS
                    break;
                default:
                    HAL_ASSERT(FALSE,
                               "Invalid Uart 2 Configuration (%d).",
                               halCfg->uartCfg[0]);
                    break;
            }
        }
    }

    hwp_sysCtrl->Cfg_Rsd &= (~(1<<6));// disabel lcd sync

    // PWM Pin Configuration
    if(halCfg->uartKeyinoutSel.uart1UseTco)
    {
        hwp_sysCtrl->Cfg_Reserved |= SYS_CTRL_UART1_TCO;
        HAL_ASSERT(!halCfg->pwmCfg.pwl1Used,
                   "Cannot use PWL1 when UART1 is used");
        HAL_ASSERT(halCfg->useClk32k == FALSE,
                   "Cannot use CLK_32K when UART1 is used");
    }
    else if (halCfg->pwmCfg.pwl1Used)
    {
        altMux |= CFG_REGS_PWL1_PWL1;
        HAL_ASSERT(halCfg->useClk32k == FALSE,
                   "Cannot use CLK_32K with PWL1");
    }
    else
    {
        if (halCfg->useClk32k)
        {
            // Default to GPO low output
            // 32K clock will be enabled per request
            //altMux |= CFG_REGS_PWL1_CLK_32K;
            altMux |= CFG_REGS_PWL1_GPO_6;
        }
        else
        {
            altMux |= CFG_REGS_PWL1_GPO_6;
            availableGpo |= HAL_GPO_BIT(6);
        }
    }

    // SD Card Interface
    if (halCfg->useSdmmc)
    {
        altMux |= CFG_REGS_SDMMC_SDMMC;
    }
    else
    {
        altMux |= CFG_REGS_SDMMC_DIGRF;
    }

    if (halCfg->useUsbBackup)
    {
        altMux |= CFG_REGS_GPO_0_USB
                  | CFG_REGS_GPO_4_1_USB
                  | CFG_REGS_GPO_5_USB
                  | CFG_REGS_I2C2_USB;

        HAL_ASSERT( (halCfg->keyOutMask & 0xc0) == 0,
                    "Cannot use KEYOUT_6, 7 when USB backup is used");
        HAL_ASSERT( !halCfg->spiCfg[1].cs0Used && !halCfg->spiCfg[1].cs1Used,
                    "Cannot use SPI2 when USB backup is used");
        HAL_ASSERT( !halCfg->i2cCfg.i2c2Used,
                    "Cannot use I2C2 when USB backup is used");
    }
    else
    {
        if (halCfg->keyOutMask & 0x40)
        {
            altMux |= CFG_REGS_GPO_0_KEYOUT_6;
        }
        else
        {
            altMux |= CFG_REGS_GPO_0_GPO_0;
            availableGpo |= HAL_GPO_BIT(0);
        }

        // SPI2 Pins Configuration
        if (halCfg->spiCfg[1].cs0Used || halCfg->spiCfg[1].cs1Used)
        {
            altMux |= CFG_REGS_GPO_4_1_SPI2;
            if (halCfg->spiCfg[1].cs1Used)
            {
                altMux |= CFG_REGS_GPO_5_SPI2_CS_1;
                HAL_ASSERT( (halCfg->keyOutMask & 0x80) == 0,
                            "Cannot use KEYOUT_7 when SPI2_CS_1 is used");
            }
        }
        else
        {
            altMux |= CFG_REGS_GPO_4_1_GPO_4_1;
            availableGpo |= HAL_GPO_BIT(1)
                            | HAL_GPO_BIT(2)
                            | HAL_GPO_BIT(3)
                            | HAL_GPO_BIT(4);
        }

        if (halCfg->keyOutMask & 0x80)
        {
            altMux |= CFG_REGS_GPO_5_KEYOUT_7;
        }
        else
        {
            altMux |= CFG_REGS_GPO_5_GPO_5;
            availableGpo |= HAL_GPO_BIT(5);
        }

        if (halCfg->i2cCfg.i2c2Used)
        {
            altMux |= CFG_REGS_I2C2_I2C2;
        }
        else
        {
            availableGpio |= HAL_GPIO_BIT(24);
        }
    }


    // 6th column and line of the keypad can be gpios, PWT or LPG
    if (halCfg->keyOutMask & 0x20)
    {
        altMux |= CFG_REGS_KEYOUT_5_KEYOUT_5;
        HAL_ASSERT( !halCfg->pwmCfg.lpgUsed,
                    "pin KEYOUT_5 cannot be both used as Key Out and LPG!");
    }
    else if (halCfg->pwmCfg.lpgUsed)
    {
        altMux |= CFG_REGS_KEYOUT_5_LPG;
    }
    else
    {
        availableGpio |= HAL_GPIO_BIT(9);
    }

    if (halCfg->keyInMask & 0x20)
    {
        altMux |= CFG_REGS_KEYIN_5_KEYIN_5;
        HAL_ASSERT( !halCfg->pwmCfg.pwtUsed,
                    "pin KEYIN_5 cannot be both used as Key In and PWT!");
    }
    else if (halCfg->pwmCfg.pwtUsed)
    {
        altMux |= CFG_REGS_KEYIN_5_PWT;
    }
    else
    {
        availableGpio |= HAL_GPIO_BIT(10);
    }

    // Always used as I2S_DO on 8809
    altMux |= CFG_REGS_I2S_DO_I2S_DO;
    HAL_ASSERT( (halCfg->usedTco & (1<<5)) == 0,
                "Cannot use TCO_5 when I2S_DO is used");

#if (CHIP_HAS_DBG_UART_SW_FLOW_CONTROL == 1)
    availableGpio |= HAL_GPIO_BIT(2)
                     |HAL_GPIO_BIT(3);
#endif

    // GPIO1 and KEYIN_6
    if (!(halCfg->keyInMask & 0x40))
    {
        availableGpio |= HAL_GPIO_BIT(1);
    }

    if(halCfg->uartKeyinoutSel.uart2UseTco
            || halCfg->uartKeyinoutSel.uart1UseTco)
    {
        HAL_ASSERT( !halCfg->i2sCfg.di2Used,
                    "Cannot use I2S_DI_2 when UART1/2 is used");
        HAL_ASSERT( !halCfg->useLpsCo1,
                    "Cannot use LPSCO_1 when UART1/2 is used");
    }
    else if (halCfg->i2sCfg.di2Used)
    {
        altMux |= CFG_REGS_I2S_DI_2_I2S_DI_2;
        HAL_ASSERT( !halCfg->useLpsCo1,
                    "Cannot use LPSCO_1 when I2S_DI_2 is used");
    }
    else if (!halCfg->useLpsCo1)
    {
        availableGpio |= HAL_GPIO_BIT(4);
    }

    HAL_ASSERT(halCfg->i2sCfg.di1Used && halCfg->i2sCfg.di0Used && halCfg->i2sCfg.doUsed,
               "Always use I2S DI1, DI0 and DO on 8809");
    HAL_ASSERT( ((halCfg->usedGpio & (HAL_GPIO_BIT(11)|HAL_GPIO_BIT(17))) == 0) &&
                ((halCfg->noConnectGpio & (HAL_GPIO_BIT(11)|HAL_GPIO_BIT(17))) == 0),
                "GPIO 11 and 17 must be configured as ALT_FUNC on 8809");

    if (!halCfg->ebcCfg.cs2Used)
    {
        availableGpio |= HAL_GPIO_BIT(22);
    }

    if (!halCfg->ebcCfg.cs3Used)
    {
        availableGpio |= HAL_GPIO_BIT(23);
    }

    if (!halCfg->i2cCfg.i2c2Used)
    {
        availableGpio |= HAL_GPIO_BIT(25);
    }

    if (halCfg->useSdmmc2==HAL_CFG_SDIO2_LCD)
    {
        ioDrive2Sel |= CFG_REGS_SDMMC2_LCD_SDMMC2;
        HAL_ASSERT(!halCfg->goudaCfg.lcdData16Bit,
                   "Cannot use LCD High 8-bit when SDMMC2 is used");
        HAL_ASSERT(!(!halCfg->goudaCfg.lcdData16Bit && halCfg->goudaCfg.swapByte),
                   "Cannot use LCD High 8-bit when SDMMC2 is used");
        availableGpio |= HAL_GPIO_BIT(29)
                         | HAL_GPIO_BIT(31);
    }
    else
    {
        if (!halCfg->goudaCfg.lcdData16Bit)
        {
            if(!halCfg->goudaCfg.swapByte)
            {
                availableGpio |= HAL_GPIO_BIT(18)
                                 | HAL_GPIO_BIT(19)
                                 | HAL_GPIO_BIT(26)
                                 | HAL_GPIO_BIT(27)
                                 | HAL_GPIO_BIT(28)
                                 | HAL_GPIO_BIT(29)
                                 | HAL_GPIO_BIT(30)
                                 | HAL_GPIO_BIT(31);
            }
        }
    }

    if (halCfg->useSdmmc2==HAL_CFG_SDIO2_KEY)
    {
        ioDrive2Sel |= CFG_REGS_SDMMC2_KEY_SDMMC2;
        HAL_ASSERT(!(halCfg->uartKeyinoutSel.keyin0GpioEn
                     || halCfg->uartKeyinoutSel.keyin4GpioEn
                     || halCfg->uartKeyinoutSel.keyout1GpioEn
                     || halCfg->uartKeyinoutSel.keyout2GpioEn),
                   "Cannot use Keyin_0/4/5 Keyout_0/1/2 when SDMMC2 is used");
    }
    else
    {
        if(halCfg->uartKeyinoutSel.keyin0GpioEn)
        {
            ioDrive2Sel |= CFG_REGS_KEYIN_0_GPIO_20;
        }
        if(halCfg->uartKeyinoutSel.keyin4GpioEn)
        {
            ioDrive2Sel |= CFG_REGS_KEYIN_4_GPIO_21;
        }
        if(halCfg->uartKeyinoutSel.keyout1GpioEn)
        {
            ioDrive2Sel |= CFG_REGS_KEYOUT_1_GPIO_17;
        }
        if(halCfg->uartKeyinoutSel.keyout2GpioEn)
        {
            ioDrive2Sel |= CFG_REGS_KEYOUT_2_GPIO_11;
        }
    }

    if(halCfg->uartKeyinoutSel.keyout3GpioEn)
    {
        ioDrive2Sel |= CFG_REGS_KEYOUT_3_GPIO_7;
    }
    if(halCfg->uartKeyinoutSel.keyout4GpioEn)
    {
        ioDrive2Sel |= CFG_REGS_KEYOUT_4_GPIO_8;
    }

    hwp_configRegs->IO_Drive1_Select = halCfg->ioDrive.select1;
    hwp_configRegs->IO_Drive2_Select = ioDrive2Sel;
#ifdef CHIP_DIE_8955
    // hwp_configRegs->IO_Drive2_Select |= CFG_REGS_USB_ID;
#endif

    // Common to all chips :

    UINT32 gpioMask;
    // GPIO mask check
    gpioMask = ~availableGpio & halCfg->usedGpio;
    HAL_ASSERT(gpioMask == 0,
               "Some used GPIO are not available (0x%x)",
               gpioMask);
    gpioMask = ~availableGpio & halCfg->noConnectGpio;
    HAL_ASSERT(gpioMask == 0,
               "Some GPIO declared as not connected are not available (0x%x)",
               gpioMask);
    gpioMask = halCfg->usedGpio & halCfg->noConnectGpio;
    HAL_ASSERT(gpioMask == 0,
               "Some GPIO declared as not connected are used (0x%x)",
               gpioMask);
#ifdef CHECK_GPIO_ALT_FUNC
    gpioMask = availableGpio &
               (~halCfg->usedGpio & ~halCfg->noConnectGpio);
    HAL_ASSERT(gpioMask == 0,
               "Some available GPIO declared as alt function (0x%x)",
               gpioMask);
#endif

    // GPO mask check
    gpioMask = ~availableGpo & halCfg->usedGpo;
    HAL_ASSERT(gpioMask == 0,
               "Some used GPO are not available (0x%x)",
               gpioMask);
#endif
#endif // !FPGA


    if (halCfg->goudaCfg.lcdResetPin.type == HAL_GPIO_TYPE_IO ||
            halCfg->goudaCfg.lcdResetPin.type == HAL_GPIO_TYPE_O)
    {
        UINT32 lcdResetPin;
        if (halCfg->goudaCfg.lcdResetPin.type == HAL_GPIO_TYPE_IO)
        {
            lcdResetPin = HAL_GPIO_BIT(halCfg->goudaCfg.lcdResetPin.id);
            if ((halCfg->usedGpio & lcdResetPin) == 0)
            {
                HAL_ASSERT(FALSE, "LCD reset pin (0x%08x) is not used as GPIO (0x%08x)",
                           lcdResetPin, halCfg->usedGpio);
            }
        }
        else     // if (halCfg->goudaCfg.lcdResetPin.type == HAL_GPIO_TYPE_O)
        {
            lcdResetPin = HAL_GPO_BIT(halCfg->goudaCfg.lcdResetPin.id);
            if ((halCfg->usedGpo & lcdResetPin) == 0)
            {
                HAL_ASSERT(FALSE, "LCD reset pin (0x%08x) is not used as GPO (0x%08x)",
                           lcdResetPin, halCfg->usedGpo);
            }
        }
        // Init GPIO/GPO pin after it is configured as usable
        hal_GoudaInitResetPin();
    }
    else if (halCfg->goudaCfg.lcdResetPin.type != HAL_GPIO_TYPE_NONE)
    {
        HAL_ASSERT(FALSE, "LCD reset pin must be GPIO or GPO or none");
    }

#ifdef FPGA

#else
#if 1
    // Set the not connected ones as output and drive 0
    UINT32 noConnectMask = halCfg->noConnectGpio;
#ifdef GPIO_2_BT_HOSTWAKE_WORKAROUND
    // GPIO_2 on other chips should be configured as input
    noConnectMask &= ~(HAL_GPIO_BIT(2));
#endif // GPIO_2_BT_HOSTWAKE_WORKAROUND
    hwp_gpio->gpio_clr_l = noConnectMask;
    hwp_gpio->gpio_clr_h = noConnectMask;

    hwp_gpio->gpio_oen_set_out_l = noConnectMask;
    hwp_gpio->gpio_oen_set_out_h = noConnectMask;

    // init GPO values

    // Init 32K clock pin to low (by setting up GPO)
    //  if (halCfg->useClk32k)
    {
        //   hwp_gpio->gpo_clr = HAL_GPO_BIT(6);
    }

    // Configure MUX after initializing all the GPO pins
    // (GPIO pins are in input mode by default)

    // Set GPIO mode
    // hwp_configRegs->GPIO_Mode = availableGpio;
    // Set Alt Mux configuration
    // hwp_configRegs->Alt_mux_select = altMux;
#endif
#endif
    // --------------------------------------------------
    // As of now, all connected GPIOs, which are as GPIO
    // or not used at all but connected are configured as
    // GPIOs in input mode, except for Gouda reset pins
    // --------------------------------------------------
}


// =============================================================================
// hal_BoardSetup
// -----------------------------------------------------------------------------
/// Apply board dependent configuration to HAL
/// @param halCfg Pointer to HAL configuration structure (from the target
/// module).
// ============================================================================
PROTECTED VOID hal_BoardSetup(CONST HAL_CFG_CONFIG_T* halCfg)
{
    // Store the config pointer for later use in hal
    g_halCfg = halCfg;

#if defined(_FLASH_PROGRAMMER) && defined(FORCE_GPIO_INPUT_GPO_LOW)

    hal_BoardSetupFp(halCfg);

#else // ! (_FLASH_PROGRAMMER && FORCE_GPIO_INPUT_GPO_LOW)

    hal_BoardSetupGeneral(halCfg);

#endif //!(_FLASH_PROGRAMMER && FORCE_GPIO_INPUT_GPO_LOW)

    // Set the LPSCOs polarity from PMD
    // this is assuming xvc needs V_RF, anyway pal will get the real info
    // from xcv and configure LPS properly.
    hwp_tcu->LPS_PU_Ctrl |= pmd_ConfigureRfLowPower(TRUE, FALSE);
}


PUBLIC VOID hal_ConfigUSB_Host(BOOL enale)
{
    if (enale == TRUE)
    {
        // hwp_configRegs->IO_Drive2_Select &= ~CFG_REGS_USB_ID;

    }
    else
    {
        //hwp_configRegs->IO_Drive2_Select |= CFG_REGS_USB_ID;

    }
}


PUBLIC VOID hal_ConfigFmIo(BOOL enable)
{
}


PUBLIC VOID hal_ConfigBtIo(BOOL enable)
{
}

PUBLIC UINT32 hal_ConfigCamIntToGpio(void)
{
    UINT32 ret=0;
    ret =   hwp_iomux->pad_CAM_PWDN_cfg & IOMUX_PAD_CAM_PWDN_SEL_MASK
            | (hwp_iomux->pad_CAM_RSTB_cfg & IOMUX_PAD_CAM_RSTB_SEL_MASK)<<4
            | (hwp_iomux->pad_CAM_CLK_cfg   & IOMUX_PAD_CAM_CLK_SEL_MASK)<<8
            | (hwp_iomux->pad_CAM_CLK_cfg  & IOMUX_PAD_CAM_CLK_SEL_MASK)<<12
            | (hwp_iomux->pad_SPI_CAM_SCK_cfg & IOMUX_PAD_SPI_CAM_DI_0_SEL_MASK)<<16
            | (hwp_iomux->pad_SPI_CAM_DI_1_cfg & IOMUX_PAD_SPI_CAM_DI_1_SEL_MASK)<<20;

    hwp_iomux->pad_CAM_PWDN_cfg = (hwp_iomux->pad_CAM_PWDN_cfg & (~(IOMUX_PAD_CAM_PWDN_SEL_MASK))) | IOMUX_PAD_CAM_PWDN_SEL_FUN_GPIO_19_SEL;
    hwp_iomux->pad_CAM_RSTB_cfg = (hwp_iomux->pad_CAM_RSTB_cfg & (~(IOMUX_PAD_CAM_RSTB_SEL_MASK)))| IOMUX_PAD_CAM_RSTB_SEL_FUN_GPIO_20_SEL;
    hwp_iomux->pad_CAM_CLK_cfg = (hwp_iomux->pad_CAM_CLK_cfg & (~(IOMUX_PAD_CAM_CLK_SEL_MASK)))| IOMUX_PAD_CAM_CLK_SEL_FUN_GPIO_21_SEL;
    hwp_iomux->pad_SPI_CAM_SCK_cfg = (hwp_iomux->pad_SPI_CAM_SCK_cfg & (~(IOMUX_PAD_SPI_CAM_SCK_SEL_MASK)))| IOMUX_PAD_SPI_CAM_SCK_SEL_FUN_GPIO_22_SEL;
    hwp_iomux->pad_SPI_CAM_DI_0_cfg = (hwp_iomux->pad_SPI_CAM_SCK_cfg & (~(IOMUX_PAD_SPI_CAM_DI_0_SEL_MASK)))| IOMUX_PAD_SPI_CAM_DI_0_SEL_FUN_GPIO_23_SEL;
    hwp_iomux->pad_SPI_CAM_DI_1_cfg = (hwp_iomux->pad_SPI_CAM_DI_1_cfg & (~(IOMUX_PAD_SPI_CAM_DI_1_SEL_MASK)))| IOMUX_PAD_SPI_CAM_DI_1_SEL_FUN_GPIO_24_SEL;
    return ret;
}

PUBLIC VOID hal_ConfigResumCamIntfs(UINT32 cammux)
{
    hwp_iomux->pad_CAM_PWDN_cfg = (hwp_iomux->pad_CAM_PWDN_cfg & (~(IOMUX_PAD_CAM_PWDN_SEL_MASK))) | (cammux & IOMUX_PAD_CAM_PWDN_SEL_MASK);
    hwp_iomux->pad_CAM_RSTB_cfg = (hwp_iomux->pad_CAM_RSTB_cfg & (~(IOMUX_PAD_CAM_RSTB_SEL_MASK)))| ((cammux>>4) & IOMUX_PAD_CAM_RSTB_SEL_MASK);
    hwp_iomux->pad_CAM_CLK_cfg = (hwp_iomux->pad_CAM_CLK_cfg & (~(IOMUX_PAD_CAM_CLK_SEL_MASK)))| ((cammux>>8) & IOMUX_PAD_CAM_RSTB_SEL_MASK);
    hwp_iomux->pad_SPI_CAM_SCK_cfg = (hwp_iomux->pad_SPI_CAM_SCK_cfg & (~(IOMUX_PAD_SPI_CAM_SCK_SEL_MASK)))| ((cammux>>12) & IOMUX_PAD_CAM_RSTB_SEL_MASK);
    hwp_iomux->pad_SPI_CAM_DI_0_cfg = (hwp_iomux->pad_SPI_CAM_SCK_cfg & (~(IOMUX_PAD_SPI_CAM_DI_0_SEL_MASK)))| ((cammux>>16) & IOMUX_PAD_CAM_RSTB_SEL_MASK);
    hwp_iomux->pad_SPI_CAM_DI_1_cfg = (hwp_iomux->pad_SPI_CAM_DI_1_cfg & (~(IOMUX_PAD_SPI_CAM_DI_1_SEL_MASK)))| ((cammux>>20) & IOMUX_PAD_CAM_RSTB_SEL_MASK);

}

#ifdef JKT_WATCH_GLOBAL_FLAG
PUBLIC VOID hal_ConfigKeyin3ToGpio(VOID)
{
	hwp_iomux->pad_KEYIN_3_cfg = IOMUX_PAD_KEYIN_3_SEL(IOMUX_PAD_KEYIN_3_SEL_FUN_GPIO_28_SEL);
}
#endif /* JKT_WATCH_GLOBAL_FLAG */
