static void swap_block_ptr ( MACROBLOCK * x , PICK_MODE_CONTEXT * ctx , int m , int n , int min_plane , int max_plane ) {
 int i ;
 for ( i = min_plane ;
 i < max_plane ;
 ++ i ) {
 struct macroblock_plane * const p = & x -> plane [ i ] ;
 struct macroblockd_plane * const pd = & x -> e_mbd . plane [ i ] ;
 p -> coeff = ctx -> coeff_pbuf [ i ] [ m ] ;
 p -> qcoeff = ctx -> qcoeff_pbuf [ i ] [ m ] ;
 pd -> dqcoeff = ctx -> dqcoeff_pbuf [ i ] [ m ] ;
 p -> eobs = ctx -> eobs_pbuf [ i ] [ m ] ;
 ctx -> coeff_pbuf [ i ] [ m ] = ctx -> coeff_pbuf [ i ] [ n ] ;
 ctx -> qcoeff_pbuf [ i ] [ m ] = ctx -> qcoeff_pbuf [ i ] [ n ] ;
 ctx -> dqcoeff_pbuf [ i ] [ m ] = ctx -> dqcoeff_pbuf [ i ] [ n ] ;
 ctx -> eobs_pbuf [ i ] [ m ] = ctx -> eobs_pbuf [ i ] [ n ] ;
 ctx -> coeff_pbuf [ i ] [ n ] = p -> coeff ;
 ctx -> qcoeff_pbuf [ i ] [ n ] = p -> qcoeff ;
 ctx -> dqcoeff_pbuf [ i ] [ n ] = pd -> dqcoeff ;
 ctx -> eobs_pbuf [ i ] [ n ] = p -> eobs ;
 }
 }