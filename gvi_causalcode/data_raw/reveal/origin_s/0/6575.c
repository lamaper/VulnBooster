static void decApplyRound ( decNumber * dn , decContext * set , Int residue , uInt * status ) {
 Int bump ;
 if ( residue == 0 ) return ;
 bump = 0 ;
 switch ( set -> round ) {
 case DEC_ROUND_05UP : {
 Int lsd5 = * dn -> lsu % 5 ;
 if ( residue < 0 && lsd5 != 1 ) bump = - 1 ;
 else if ( residue > 0 && lsd5 == 0 ) bump = 1 ;
 break ;
 }
 case DEC_ROUND_DOWN : {
 if ( residue < 0 ) bump = - 1 ;
 break ;
 }
 case DEC_ROUND_HALF_DOWN : {
 if ( residue > 5 ) bump = 1 ;
 break ;
 }
 case DEC_ROUND_HALF_EVEN : {
 if ( residue > 5 ) bump = 1 ;
 else if ( residue == 5 ) {
 if ( * dn -> lsu & 0x01 ) bump = 1 ;
 }
 break ;
 }
 case DEC_ROUND_HALF_UP : {
 if ( residue >= 5 ) bump = 1 ;
 break ;
 }
 case DEC_ROUND_UP : {
 if ( residue > 0 ) bump = 1 ;
 break ;
 }
 case DEC_ROUND_CEILING : {
 if ( decNumberIsNegative ( dn ) ) {
 if ( residue < 0 ) bump = - 1 ;
 }
 else {
 if ( residue > 0 ) bump = 1 ;
 }
 break ;
 }
 case DEC_ROUND_FLOOR : {
 if ( ! decNumberIsNegative ( dn ) ) {
 if ( residue < 0 ) bump = - 1 ;
 }
 else {
 if ( residue > 0 ) bump = 1 ;
 }
 break ;
 }
 default : {
 * status |= DEC_Invalid_context ;


 }
 }
 if ( bump == 0 ) return ;
 if ( bump > 0 ) {
 Unit * up ;
 uInt count = dn -> digits ;
 for ( up = dn -> lsu ;
 ;
 up ++ ) {
 if ( count <= DECDPUN ) {
 if ( * up != powers [ count ] - 1 ) break ;
 * up = ( Unit ) powers [ count - 1 ] ;
 for ( up = up - 1 ;
 up >= dn -> lsu ;
 up -- ) * up = 0 ;
 dn -> exponent ++ ;
 if ( ( dn -> exponent + dn -> digits ) > set -> emax + 1 ) {
 decSetOverflow ( dn , set , status ) ;
 }
 return ;
 }
 if ( * up != DECDPUNMAX ) break ;
 count -= DECDPUN ;
 }
 }
 else {
 Unit * up , * sup ;
 uInt count = dn -> digits ;
 for ( up = dn -> lsu ;
 ;
 up ++ ) {
 if ( count <= DECDPUN ) {
 if ( * up != powers [ count - 1 ] ) break ;
 sup = up ;
 * up = ( Unit ) powers [ count ] - 1 ;
 for ( up = up - 1 ;
 up >= dn -> lsu ;
 up -- ) * up = ( Unit ) powers [ DECDPUN ] - 1 ;
 dn -> exponent -- ;
 if ( dn -> exponent + 1 == set -> emin - set -> digits + 1 ) {
 if ( count == 1 && dn -> digits == 1 ) * sup = 0 ;
 else {
 * sup = ( Unit ) powers [ count - 1 ] - 1 ;
 dn -> digits -- ;
 }
 dn -> exponent ++ ;
 * status |= DEC_Underflow | DEC_Subnormal | DEC_Inexact | DEC_Rounded ;
 }
 return ;
 }
 if ( * up != 0 ) break ;
 count -= DECDPUN ;
 }
 }
 decUnitAddSub ( dn -> lsu , D2U ( dn -> digits ) , uarrone , 1 , 0 , dn -> lsu , bump ) ;
 }