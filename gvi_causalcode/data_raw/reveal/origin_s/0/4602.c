static double convert_one_string_to_scalar ( char * value , int rangelo , int rangehi ) {
 int slen = strlen ( value ) ;
 double num , denom , base ;
 if ( slen <= 0 ) return 0.0 ;
 if ( slen > 12 ) slen = 12 ;
 base = rangehi - rangelo + 1 ;
 num = 0.0 ;
 denom = base ;
 while ( slen -- > 0 ) {
 int ch = ( unsigned char ) * value ++ ;
 if ( ch < rangelo ) ch = rangelo - 1 ;
 else if ( ch > rangehi ) ch = rangehi + 1 ;
 num += ( ( double ) ( ch - rangelo ) ) / denom ;
 denom *= base ;
 }
 return num ;
 }