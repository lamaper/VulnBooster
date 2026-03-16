float lut_interp_linear ( double input_value , uint16_t * table , size_t length ) {
 int upper , lower ;
 float value ;
 input_value = input_value * ( length - 1 ) ;
 upper = ceil ( input_value ) ;
 lower = floor ( input_value ) ;
 value = table [ upper ] * ( 1. - ( upper - input_value ) ) + table [ lower ] * ( upper - input_value ) ;
 return value * ( 1.f / 65535.f ) ;
 }