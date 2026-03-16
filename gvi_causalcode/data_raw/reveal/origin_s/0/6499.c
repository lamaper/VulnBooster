static void decSetCoeff ( decNumber * dn , decContext * set , const Unit * lsu , Int len , Int * residue , uInt * status ) {
 Int discard ;
 uInt cut ;
 const Unit * up ;
 Unit * target ;
 Int count ;


 if ( discard <= 0 ) {
 if ( dn -> lsu != lsu ) {
 count = len ;
 up = lsu ;
 for ( target = dn -> lsu ;
 count > 0 ;
 target ++ , up ++ , count -= DECDPUN ) * target = * up ;
 dn -> digits = len ;
 }
 if ( * residue != 0 ) * status |= ( DEC_Inexact | DEC_Rounded ) ;
 return ;
 }
 dn -> exponent += discard ;
 * status |= DEC_Rounded ;
 if ( * residue > 1 ) * residue = 1 ;
 if ( discard > len ) {
 if ( * residue <= 0 ) {
 count = len ;
 for ( up = lsu ;
 count > 0 ;
 up ++ , count -= DECDPUN ) if ( * up != 0 ) {
 * residue = 1 ;
 break ;
 }
 }
 if ( * residue != 0 ) * status |= DEC_Inexact ;
 * dn -> lsu = 0 ;
 dn -> digits = 1 ;
 return ;
 }
 count = 0 ;
 for ( up = lsu ;
 ;
 up ++ ) {
 count += DECDPUN ;
 if ( count >= discard ) break ;
 if ( * up != 0 ) * residue = 1 ;
 }
 cut = discard - ( count - DECDPUN ) - 1 ;
 if ( cut == DECDPUN - 1 ) {
 Unit half = ( Unit ) powers [ DECDPUN ] >> 1 ;
 if ( * up >= half ) {
 if ( * up > half ) * residue = 7 ;
 else * residue += 5 ;
 }
 else {
 if ( * up != 0 ) * residue = 3 ;
 }
 if ( set -> digits <= 0 ) {
 * dn -> lsu = 0 ;
 dn -> digits = 1 ;
 }
 else {
 count = set -> digits ;
 dn -> digits = count ;
 up ++ ;
 for ( target = dn -> lsu ;
 count > 0 ;
 target ++ , up ++ , count -= DECDPUN ) * target = * up ;
 }
 }
 else {
 uInt discard1 ;
 uInt quot , rem ;
 if ( cut == 0 ) quot = * up ;
 else {

 quot = QUOT10 ( * up , cut ) ;
 rem = * up - quot * powers [ cut ] ;

 quot = * up / powers [ cut ] ;

 }

 discard1 = quot - X10 ( temp ) ;
 quot = temp ;

 quot = quot / 10 ;

 cut ++ ;
 if ( set -> digits <= 0 ) {
 * dn -> lsu = 0 ;
 dn -> digits = 1 ;
 }
 else {
 count = set -> digits ;
 dn -> digits = count ;
 for ( target = dn -> lsu ;
 ;
 target ++ ) {
 * target = ( Unit ) quot ;
 count -= ( DECDPUN - cut ) ;
 if ( count <= 0 ) break ;
 up ++ ;
 quot = * up ;

 rem = * up - quot * powers [ cut ] ;

 quot = quot / powers [ cut ] ;

 count -= cut ;
 if ( count <= 0 ) break ;
 }
 }
 }
 if ( * residue != 0 ) * status |= DEC_Inexact ;
 return ;
 }