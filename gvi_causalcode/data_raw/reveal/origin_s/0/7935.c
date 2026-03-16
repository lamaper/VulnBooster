static Int decGetDigits ( Unit * uar , Int len ) {
 Unit * up = uar + ( len - 1 ) ;
 Int digits = ( len - 1 ) * DECDPUN + 1 ;



 up >= uar ;
 up -- ) {
 if ( * up == 0 ) {
 if ( digits == 1 ) break ;
 digits -= DECDPUN ;
 continue ;
 }

 digits ++ ;

 digits ++ ;

 digits ++ ;

 * up >= * pow ;
 pow ++ ) digits ++ ;

 }
 return digits ;
 }