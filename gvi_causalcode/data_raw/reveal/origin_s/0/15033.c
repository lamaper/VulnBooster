static chr lexdigits ( struct vars * v , int base , int minlen , int maxlen ) {
 uchr n ;
 int len ;
 chr c ;
 int d ;
 const uchr ub = ( uchr ) base ;
 n = 0 ;
 for ( len = 0 ;
 len < maxlen && ! ATEOS ( ) ;
 len ++ ) {
 c = * v -> now ++ ;
 switch ( c ) {
 case CHR ( '0' ) : case CHR ( '1' ) : case CHR ( '2' ) : case CHR ( '3' ) : case CHR ( '4' ) : case CHR ( '5' ) : case CHR ( '6' ) : case CHR ( '7' ) : case CHR ( '8' ) : case CHR ( '9' ) : d = DIGITVAL ( c ) ;
 break ;
 case CHR ( 'a' ) : case CHR ( 'A' ) : d = 10 ;
 break ;
 case CHR ( 'b' ) : case CHR ( 'B' ) : d = 11 ;
 break ;
 case CHR ( 'c' ) : case CHR ( 'C' ) : d = 12 ;
 break ;
 case CHR ( 'd' ) : case CHR ( 'D' ) : d = 13 ;
 break ;
 case CHR ( 'e' ) : case CHR ( 'E' ) : d = 14 ;
 break ;
 case CHR ( 'f' ) : case CHR ( 'F' ) : d = 15 ;
 break ;
 default : v -> now -- ;
 d = - 1 ;
 break ;
 }
 if ( d >= base ) {
 v -> now -- ;
 d = - 1 ;
 }
 if ( d < 0 ) break ;
 n = n * ub + ( uchr ) d ;
 }
 if ( len < minlen ) ERR ( REG_EESCAPE ) ;
 return ( chr ) n ;
 }