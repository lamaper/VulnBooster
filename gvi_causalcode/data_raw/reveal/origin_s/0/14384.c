static inline int binkb_get_value ( BinkContext * c , int bundle_num ) {
 int16_t ret ;
 const int bits = binkb_bundle_sizes [ bundle_num ] ;
 if ( bits <= 8 ) {
 int val = * c -> bundle [ bundle_num ] . cur_ptr ++ ;
 return binkb_bundle_signed [ bundle_num ] ? ( int8_t ) val : val ;
 }
 ret = * ( int16_t * ) c -> bundle [ bundle_num ] . cur_ptr ;
 c -> bundle [ bundle_num ] . cur_ptr += 2 ;
 return ret ;
 }