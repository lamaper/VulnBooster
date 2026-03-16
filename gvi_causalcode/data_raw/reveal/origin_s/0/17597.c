static void setup_BAT ( CPUPPCState * env , int BAT , uint32_t virtual , uint32_t physical , uint32_t size , int Vs , int Vp , int PP ) {
 uint32_t sz_bits , tmp_sz , align , tmp ;
 sz_bits = 0 ;
 align = 131072 ;
 for ( tmp_sz = size / 131072 ;
 tmp_sz != 1 ;
 tmp_sz = tmp_sz >> 1 ) {
 sz_bits = ( sz_bits << 1 ) + 1 ;
 align = align << 1 ;
 }
 tmp = virtual & ~ ( align - 1 ) ;
 tmp |= sz_bits << 2 ;
 tmp |= Vs << 1 ;
 tmp |= Vp ;
 env -> DBAT [ 0 ] [ BAT ] = tmp ;
 env -> IBAT [ 0 ] [ BAT ] = tmp ;
 tmp = physical & ~ ( align - 1 ) ;
 tmp |= 0 ;
 tmp |= PP ;
 env -> DBAT [ 1 ] [ BAT ] = tmp ;
 env -> IBAT [ 1 ] [ BAT ] = tmp ;
 printf ( "Set BATU0 to 0x%08x BATL0 to 0x%08x\n" , env -> DBAT [ 0 ] [ BAT ] , env -> DBAT [ 1 ] [ BAT ] ) ;
 }