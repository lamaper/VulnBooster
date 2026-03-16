inline void uint32_to_be ( void * bytes , unsigned integer ) {
 unsigned char * b = ( unsigned char * ) bytes ;
 b [ 0 ] = ( integer & 0xff000000 ) >> 24 ;
 b [ 1 ] = ( integer & 0x00ff0000 ) >> 16 ;
 b [ 2 ] = ( integer & 0x0000ff00 ) >> 8 ;
 b [ 3 ] = ( integer & 0x000000ff ) >> 0 ;
 }