void compute_precache_lut ( uint8_t * output , uint16_t * table , int length ) {
 uint32_t v = 0 ;
 for ( v = 0 ;
 v < PRECACHE_OUTPUT_SIZE ;
 v ++ ) {
 output [ v ] = lut_interp_linear_precache_output ( v , table , length ) ;
 }
 }