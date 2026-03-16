static inline uint8_t motion_arg ( motion_vect mot ) {
 uint8_t ax = 8 - ( ( uint8_t ) mot . d [ 0 ] ) ;
 uint8_t ay = 8 - ( ( uint8_t ) mot . d [ 1 ] ) ;
 return ( ( ax & 15 ) << 4 ) | ( ay & 15 ) ;
 }