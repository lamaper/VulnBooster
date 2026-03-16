static void decSetMaxValue ( decNumber * dn , decContext * set ) {
 Unit * up ;
 Int count = set -> digits ;
 dn -> digits = count ;
 for ( up = dn -> lsu ;
 ;
 up ++ ) {
 if ( count > DECDPUN ) * up = DECDPUNMAX ;
 else {
 * up = ( Unit ) ( powers [ count ] - 1 ) ;
 break ;
 }
 count -= DECDPUN ;
 }
 dn -> bits = 0 ;
 dn -> exponent = set -> emax - set -> digits + 1 ;
 }