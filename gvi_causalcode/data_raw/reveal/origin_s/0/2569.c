static void dumpdbl ( FILE * cfff , double d ) {
 if ( d - rint ( d ) > - .00001 && d - rint ( d ) < .00001 ) dumpint ( cfff , ( int ) d ) ;
 else {
 char buffer [ 20 ] , * pt ;
 int sofar , n , odd ;
 sprintf ( buffer , "%g" , d ) ;
 sofar = 0 ;
 odd = true ;
 putc ( 30 , cfff ) ;
 for ( pt = buffer ;
 * pt ;
 ++ pt ) {
 if ( isdigit ( * pt ) ) n = * pt - '0' ;
 else if ( * pt == '.' ) n = 0xa ;
 else if ( * pt == '-' ) n = 0xe ;
 else if ( ( * pt == 'E' || * pt == 'e' ) && pt [ 1 ] == '-' ) {
 n = 0xc ;
 ++ pt ;
 }
 else if ( * pt == 'E' || * pt == 'e' ) n = 0xb ;
 else n = 0 ;
 if ( odd ) {
 sofar = n << 4 ;
 odd = false ;
 }
 else {
 putc ( sofar | n , cfff ) ;
 sofar = 0 ;
 odd = true ;
 }
 }
 if ( sofar == 0 ) putc ( 0xff , cfff ) ;
 else putc ( sofar | 0xf , cfff ) ;
 }
 }