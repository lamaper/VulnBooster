static void get_quant_quality ( NuvContext * c , int quality ) {
 int i ;
 quality = FFMAX ( quality , 1 ) ;
 for ( i = 0 ;
 i < 64 ;
 i ++ ) {
 c -> lq [ i ] = ( fallback_lquant [ i ] << 7 ) / quality ;
 c -> cq [ i ] = ( fallback_cquant [ i ] << 7 ) / quality ;
 }
 }