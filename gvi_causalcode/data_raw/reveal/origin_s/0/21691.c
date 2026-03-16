static Int decShiftToLeast ( Unit * uar , Int units , Int shift ) {
 Unit * target , * up ;
 Int cut , count ;
 Int quot , rem ;
 if ( shift == 0 ) return units ;
 if ( shift == units * DECDPUN ) {
 * uar = 0 ;
 return 1 ;
 }
 target = uar ;
 cut = MSUDIGITS ( shift ) ;
 if ( cut == DECDPUN ) {
 up = uar + D2U ( shift ) ;
 for ( ;
 up < uar + units ;
 target ++ , up ++ ) * target = * up ;
 return target - uar ;
 }
 up = uar + D2U ( shift - cut ) ;
 count = units * DECDPUN - shift ;



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
 return target - uar + 1 ;
 }