float lut_interp_linear_float ( float value , float * table , size_t length ) {
 int upper , lower ;
 value = value * ( length - 1 ) ;
 upper = ceil ( value ) ;
 lower = floor ( value ) ;
 value = table [ upper ] * ( 1. - ( upper - value ) ) + table [ lower ] * ( upper - value ) ;
 return value ;
 }