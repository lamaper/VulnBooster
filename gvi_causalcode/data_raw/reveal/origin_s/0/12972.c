uint16_t lut_interp_linear16 ( uint16_t input_value , uint16_t * table , size_t length ) {
 uintptr_t value = ( input_value * ( length - 1 ) ) ;
 uint32_t upper = ( value + 65534 ) / 65535 ;
 uint32_t lower = value / 65535 ;
 uint32_t interp = value % 65535 ;
 value = ( table [ upper ] * ( interp ) + table [ lower ] * ( 65535 - interp ) ) / 65535 ;
 return value ;
 }