static void write_bootloader ( CPUMIPSState * env , uint8_t * base , int64_t kernel_entry ) {
 uint32_t * p ;
 p = ( uint32_t * ) base ;
 stl_raw ( p ++ , 0x0bf00160 ) ;
 stl_raw ( p ++ , 0x00000000 ) ;
 stl_raw ( base + 0x500 , 0xbfc00580 ) ;
 stl_raw ( base + 0x504 , 0xbfc0083c ) ;
 stl_raw ( base + 0x520 , 0xbfc00580 ) ;
 stl_raw ( base + 0x52c , 0xbfc00800 ) ;
 stl_raw ( base + 0x534 , 0xbfc00808 ) ;
 stl_raw ( base + 0x538 , 0xbfc00800 ) ;
 stl_raw ( base + 0x53c , 0xbfc00800 ) ;
 stl_raw ( base + 0x540 , 0xbfc00800 ) ;
 stl_raw ( base + 0x544 , 0xbfc00800 ) ;
 stl_raw ( base + 0x548 , 0xbfc00800 ) ;
 stl_raw ( base + 0x54c , 0xbfc00800 ) ;
 stl_raw ( base + 0x550 , 0xbfc00800 ) ;
 stl_raw ( base + 0x554 , 0xbfc00800 ) ;
 p = ( uint32_t * ) ( base + 0x580 ) ;
 stl_raw ( p ++ , 0x24040002 ) ;
 stl_raw ( p ++ , 0x3c1d0000 | ( ( ( ENVP_ADDR - 64 ) >> 16 ) & 0xffff ) ) ;
 stl_raw ( p ++ , 0x37bd0000 | ( ( ENVP_ADDR - 64 ) & 0xffff ) ) ;
 stl_raw ( p ++ , 0x3c050000 | ( ( ENVP_ADDR >> 16 ) & 0xffff ) ) ;
 stl_raw ( p ++ , 0x34a50000 | ( ENVP_ADDR & 0xffff ) ) ;
 stl_raw ( p ++ , 0x3c060000 | ( ( ( ENVP_ADDR + 8 ) >> 16 ) & 0xffff ) ) ;
 stl_raw ( p ++ , 0x34c60000 | ( ( ENVP_ADDR + 8 ) & 0xffff ) ) ;
 stl_raw ( p ++ , 0x3c070000 | ( loaderparams . ram_size >> 16 ) ) ;
 stl_raw ( p ++ , 0x34e70000 | ( loaderparams . ram_size & 0xffff ) ) ;
 stl_raw ( p ++ , 0x3c09b400 ) ;



 stl_raw ( p ++ , 0x3c09bbe0 ) ;


















 stl_raw ( p ++ , 0x3c1f0000 | ( ( kernel_entry >> 16 ) & 0xffff ) ) ;
 stl_raw ( p ++ , 0x37ff0000 | ( kernel_entry & 0xffff ) ) ;
 stl_raw ( p ++ , 0x03e00008 ) ;
 stl_raw ( p ++ , 0x00000000 ) ;
 p = ( uint32_t * ) ( base + 0x800 ) ;
 stl_raw ( p ++ , 0x03e00008 ) ;
 stl_raw ( p ++ , 0x24020000 ) ;
 stl_raw ( p ++ , 0x03e06821 ) ;
 stl_raw ( p ++ , 0x00805821 ) ;
 stl_raw ( p ++ , 0x00a05021 ) ;
 stl_raw ( p ++ , 0x91440000 ) ;
 stl_raw ( p ++ , 0x254a0001 ) ;
 stl_raw ( p ++ , 0x10800005 ) ;
 stl_raw ( p ++ , 0x00000000 ) ;
 stl_raw ( p ++ , 0x0ff0021c ) ;
 stl_raw ( p ++ , 0x00000000 ) ;
 stl_raw ( p ++ , 0x08000205 ) ;
 stl_raw ( p ++ , 0x00000000 ) ;
 stl_raw ( p ++ , 0x01a00008 ) ;
 stl_raw ( p ++ , 0x01602021 ) ;
 stl_raw ( p ++ , 0x03e06821 ) ;
 stl_raw ( p ++ , 0x00805821 ) ;
 stl_raw ( p ++ , 0x00a05021 ) ;
 stl_raw ( p ++ , 0x00c06021 ) ;
 stl_raw ( p ++ , 0x91440000 ) ;
 stl_raw ( p ++ , 0x0ff0021c ) ;
 stl_raw ( p ++ , 0x00000000 ) ;
 stl_raw ( p ++ , 0x254a0001 ) ;
 stl_raw ( p ++ , 0x258cffff ) ;
 stl_raw ( p ++ , 0x1580fffa ) ;
 stl_raw ( p ++ , 0x00000000 ) ;
 stl_raw ( p ++ , 0x01a00008 ) ;
 stl_raw ( p ++ , 0x01602021 ) ;
 stl_raw ( p ++ , 0x3c08b800 ) ;
 stl_raw ( p ++ , 0x350803f8 ) ;
 stl_raw ( p ++ , 0x91090005 ) ;
 stl_raw ( p ++ , 0x00000000 ) ;
 stl_raw ( p ++ , 0x31290040 ) ;
 stl_raw ( p ++ , 0x1120fffc ) ;
 stl_raw ( p ++ , 0x00000000 ) ;
 stl_raw ( p ++ , 0x03e00008 ) ;
 stl_raw ( p ++ , 0xa1040000 ) ;
 }