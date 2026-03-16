static Int decShiftToMost ( Unit * uar , Int digits , Int shift ) {
 Unit * target , * source , * first ;
 Int cut ;
 uInt next ;
 if ( shift == 0 ) return digits ;
 if ( ( digits + shift ) <= DECDPUN ) {
 * uar = ( Unit ) ( * uar * powers [ shift ] ) ;
 return digits + shift ;
 }
 next = 0 ;
 source = uar + D2U ( digits ) - 1 ;
 target = source + D2U ( shift ) ;
 cut = DECDPUN - MSUDIGITS ( shift ) ;
 if ( cut == 0 ) {
 for ( ;
 source >= uar ;
 source -- , target -- ) * target = * source ;
 }
 else {
 first = uar + D2U ( digits + shift ) - 1 ;
 for ( ;
 source >= uar ;
 source -- , target -- ) {

 uInt rem = * source - quot * powers [ cut ] ;
 next += quot ;

 next += * source / powers [ cut ] ;

 next = rem * powers [ DECDPUN - cut ] ;
 }
 }
 for ( ;
 target >= uar ;
 target -- ) {
 * target = ( Unit ) next ;
 next = 0 ;
 }
 return digits + shift ;
 }