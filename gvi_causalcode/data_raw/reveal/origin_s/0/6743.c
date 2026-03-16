static void compute_antialias ( MPADecodeContext * s , GranuleDef * g ) {
 INTFLOAT * ptr ;
 int n , i ;
 if ( g -> block_type == 2 ) {
 if ( ! g -> switch_point ) return ;
 n = 1 ;
 }
 else {
 n = SBLIMIT - 1 ;
 }
 ptr = g -> sb_hybrid + 18 ;
 for ( i = n ;
 i > 0 ;
 i -- ) {
 AA ( 0 ) ;
 AA ( 1 ) ;
 AA ( 2 ) ;
 AA ( 3 ) ;
 AA ( 4 ) ;
 AA ( 5 ) ;
 AA ( 6 ) ;
 AA ( 7 ) ;
 ptr += 18 ;
 }
 }