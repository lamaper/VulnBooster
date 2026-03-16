static double convert_one_bytea_to_scalar ( unsigned char * value , int valuelen , int rangelo , int rangehi ) {
 double num , denom , base ;
 if ( valuelen <= 0 ) return 0.0 ;
 if ( valuelen > 10 ) valuelen = 10 ;
 base = rangehi - rangelo + 1 ;
 num = 0.0 ;
 denom = base ;
 while ( valuelen -- > 0 ) {
 int ch = * value ++ ;
 if ( ch < rangelo ) ch = rangelo - 1 ;
 else if ( ch > rangehi ) ch = rangehi + 1 ;
 num += ( ( double ) ( ch - rangelo ) ) / denom ;
 denom *= base ;
 }
 return num ;
 }