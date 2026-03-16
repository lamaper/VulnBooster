inline unsigned uint32_from_be ( const void * bytes ) {
 const unsigned char * b = ( const unsigned char * ) bytes ;
 return ( b [ 0 ] << 24 ) | ( b [ 1 ] << 16 ) | ( b [ 2 ] << 8 ) | b [ 3 ] ;
 }