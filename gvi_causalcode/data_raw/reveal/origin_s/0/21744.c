static uint8_t lut_interp_linear_precache_output ( uint32_t input_value , uint16_t * table , size_t length ) {
 uintptr_t value = ( input_value * ( length - 1 ) ) ;
 uint32_t upper = ( value + PRECACHE_OUTPUT_MAX - 1 ) / PRECACHE_OUTPUT_MAX ;
 uint32_t lower = value / PRECACHE_OUTPUT_MAX ;
 uint32_t interp = value % PRECACHE_OUTPUT_MAX ;
 value = ( table [ upper ] * ( interp ) + table [ lower ] * ( PRECACHE_OUTPUT_MAX - interp ) ) ;
 value += ( PRECACHE_OUTPUT_MAX * 65535 / 255 ) / 2 ;
 value /= ( PRECACHE_OUTPUT_MAX * 65535 / 255 ) ;
 return value ;
 }