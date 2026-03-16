static void check_reset_2nd_coeffs ( MACROBLOCKD * x , int type , ENTROPY_CONTEXT * a , ENTROPY_CONTEXT * l ) {
 int sum = 0 ;
 int i ;
 BLOCKD * bd = & x -> block [ 24 ] ;
 if ( bd -> dequant [ 0 ] >= 35 && bd -> dequant [ 1 ] >= 35 ) return ;
 for ( i = 0 ;
 i < ( * bd -> eob ) ;
 i ++ ) {
 int coef = bd -> dqcoeff [ vp8_default_zig_zag1d [ i ] ] ;
 sum += ( coef >= 0 ) ? coef : - coef ;
 if ( sum >= 35 ) return ;
 }
 if ( sum < 35 ) {
 for ( i = 0 ;
 i < ( * bd -> eob ) ;
 i ++ ) {
 int rc = vp8_default_zig_zag1d [ i ] ;
 bd -> qcoeff [ rc ] = 0 ;
 bd -> dqcoeff [ rc ] = 0 ;
 }
 * bd -> eob = 0 ;
 * a = * l = ( * bd -> eob != ! type ) ;
 }
 }