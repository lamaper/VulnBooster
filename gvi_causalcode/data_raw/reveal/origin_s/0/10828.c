static int rac_get_bits ( RangeCoder * c , int nbits ) {
 int val ;
 c -> range >>= nbits ;
 val = c -> low / c -> range ;
 c -> low -= c -> range * val ;
 if ( c -> range < RAC_BOTTOM ) rac_normalise ( c ) ;
 return val ;
 }