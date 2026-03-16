void compute_precache_linear ( uint8_t * output ) {
 uint32_t v = 0 ;
 for ( v = 0 ;
 v < PRECACHE_OUTPUT_SIZE ;
 v ++ ) {
 output [ v ] = v / ( PRECACHE_OUTPUT_SIZE / 256 ) ;
 }
 }