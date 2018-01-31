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










void Map202_Init()
{

    MapperInit = Map202_Init;


    MapperWrite = Map202_Write;


    MapperSram = Map0_Sram;


    MapperApu = Map202_Apu;


    MapperReadApu = Map0_ReadApu;


    MapperVSync = Map0_VSync;


    MapperHSync = Map0_HSync;


    MapperPPU = Map0_PPU;


    MapperRenderScreen = Map0_RenderScreen;


    SRAMBANK = SRAM;


    ROMBANK0 = ROMPAGE( 12 );
    ROMBANK1 = ROMPAGE( 13 );
    ROMBANK2 = ROMPAGE( 14 );
    ROMBANK3 = ROMPAGE( 15 );


    if ( NesHeader.byVRomSize > 0 )
    {
        for ( int nPage = 0; nPage < 8; ++nPage )
            PPUBANK[ nPage ] = VROMPAGE( nPage );
        InfoNES_SetupChr();
    }


    K6502_Set_Int_Wiring( 1, 1 );
}




void Map202_Apu( WORD wAddr, BYTE byData )
{
    Map202_WriteSub( wAddr, byData );
}




void Map202_Write( WORD wAddr, BYTE byData )
{
    Map202_WriteSub( wAddr, byData );
}




void Map202_WriteSub( WORD wAddr, BYTE byData )
{
    int bank = (wAddr>>1) & 0x07;


    ROMBANK0 = ROMPAGE(((bank<<1)+0) % (NesHeader.byRomSize<<1));
    ROMBANK1 = ROMPAGE(((bank<<1)+1) % (NesHeader.byRomSize<<1));

    if ((wAddr&0x0c) == 0x0c)
    {
        ROMBANK2 = ROMPAGE((((bank+1)<<1)+0) % (NesHeader.byRomSize<<1));
        ROMBANK3 = ROMPAGE((((bank+1)<<1)+1) % (NesHeader.byRomSize<<1));
    }
    else
    {
        ROMBANK2 = ROMPAGE((((bank+0)<<1)+0) % (NesHeader.byRomSize<<1));
        ROMBANK3 = ROMPAGE((((bank+0)<<1)+1) % (NesHeader.byRomSize<<1));
    }


    PPUBANK[0] = VROMPAGE(((bank<<3)+0) % (NesHeader.byVRomSize<<3));
    PPUBANK[1] = VROMPAGE(((bank<<3)+1) % (NesHeader.byVRomSize<<3));
    PPUBANK[2] = VROMPAGE(((bank<<3)+2) % (NesHeader.byVRomSize<<3));
    PPUBANK[3] = VROMPAGE(((bank<<3)+3) % (NesHeader.byVRomSize<<3));
    PPUBANK[4] = VROMPAGE(((bank<<3)+4) % (NesHeader.byVRomSize<<3));
    PPUBANK[5] = VROMPAGE(((bank<<3)+5) % (NesHeader.byVRomSize<<3));
    PPUBANK[6] = VROMPAGE(((bank<<3)+6) % (NesHeader.byVRomSize<<3));
    PPUBANK[7] = VROMPAGE(((bank<<3)+7) % (NesHeader.byVRomSize<<3));
    InfoNES_SetupChr();

    if ( wAddr & 0x01 )
    {
        InfoNES_Mirroring( 0 );
    }
    else
    {
        InfoNES_Mirroring( 1 );
    }
}

