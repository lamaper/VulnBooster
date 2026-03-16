static void merge ( GetBitContext * gb , uint8_t * dst , uint8_t * src , int size ) {
 uint8_t * src2 = src + size ;
 int size2 = size ;
 do {
 if ( ! get_bits1 ( gb ) ) {
 * dst ++ = * src ++ ;
 size -- ;
 }
 else {
 * dst ++ = * src2 ++ ;
 size2 -- ;
 }
 }
 while ( size && size2 ) ;
 while ( size -- ) * dst ++ = * src ++ ;
 while ( size2 -- ) * dst ++ = * src2 ++ ;
 }