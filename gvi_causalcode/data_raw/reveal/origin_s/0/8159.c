static void put_long ( void * addr , uint32_t l ) {
 char * pos = addr ;
 pos [ 0 ] = ( l >> 24 ) & 0xFF ;
 pos [ 1 ] = ( l >> 16 ) & 0xFF ;
 pos [ 2 ] = ( l >> 8 ) & 0xFF ;
 pos [ 3 ] = l & 0xFF ;
 }