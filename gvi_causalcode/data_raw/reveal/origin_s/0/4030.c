static int read_is_valid ( const uint8_t * start , size_t len , const uint8_t * end ) {
 return len != 0 && len <= ( size_t ) ( end - start ) ;
 }