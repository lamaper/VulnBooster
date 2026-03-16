static void convert_string_to_scalar ( char * value , double * scaledvalue , char * lobound , double * scaledlobound , char * hibound , double * scaledhibound ) {
 int rangelo , rangehi ;
 char * sptr ;
 rangelo = rangehi = ( unsigned char ) hibound [ 0 ] ;
 for ( sptr = lobound ;
 * sptr ;
 sptr ++ ) {
 if ( rangelo > ( unsigned char ) * sptr ) rangelo = ( unsigned char ) * sptr ;
 if ( rangehi < ( unsigned char ) * sptr ) rangehi = ( unsigned char ) * sptr ;
 }
 for ( sptr = hibound ;
 * sptr ;
 sptr ++ ) {
 if ( rangelo > ( unsigned char ) * sptr ) rangelo = ( unsigned char ) * sptr ;
 if ( rangehi < ( unsigned char ) * sptr ) rangehi = ( unsigned char ) * sptr ;
 }
 if ( rangelo <= 'Z' && rangehi >= 'A' ) {
 if ( rangelo > 'A' ) rangelo = 'A' ;
 if ( rangehi < 'Z' ) rangehi = 'Z' ;
 }
 if ( rangelo <= 'z' && rangehi >= 'a' ) {
 if ( rangelo > 'a' ) rangelo = 'a' ;
 if ( rangehi < 'z' ) rangehi = 'z' ;
 }
 if ( rangelo <= '9' && rangehi >= '0' ) {
 if ( rangelo > '0' ) rangelo = '0' ;
 if ( rangehi < '9' ) rangehi = '9' ;
 }
 if ( rangehi - rangelo < 9 ) {
 rangelo = ' ' ;
 rangehi = 127 ;
 }
 while ( * lobound ) {
 if ( * lobound != * hibound || * lobound != * value ) break ;
 lobound ++ , hibound ++ , value ++ ;
 }
 * scaledvalue = convert_one_string_to_scalar ( value , rangelo , rangehi ) ;
 * scaledlobound = convert_one_string_to_scalar ( lobound , rangelo , rangehi ) ;
 * scaledhibound = convert_one_string_to_scalar ( hibound , rangelo , rangehi ) ;
 }