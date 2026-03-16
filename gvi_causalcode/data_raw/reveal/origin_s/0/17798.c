static void compute_precache_pow ( uint8_t * output , float gamma ) {
 uint32_t v = 0 ;
 for ( v = 0 ;
 v < PRECACHE_OUTPUT_SIZE ;
 v ++ ) {
 output [ v ] = 255. * pow ( v / ( double ) PRECACHE_OUTPUT_MAX , gamma ) ;
 }
 }