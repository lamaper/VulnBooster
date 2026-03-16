static int rac_get_bit ( RangeCoder * c ) {
 int bit ;
 c -> range >>= 1 ;
 bit = ( c -> range <= c -> low ) ;
 if ( bit ) c -> low -= c -> range ;
 if ( c -> range < RAC_BOTTOM ) rac_normalise ( c ) ;
 return bit ;
 }