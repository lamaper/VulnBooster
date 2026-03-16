static int decode_coeff ( RangeCoder * c , Model * m ) {
 int val , sign ;
 val = rac_get_model_sym ( c , m ) ;
 if ( val ) {
 sign = rac_get_bit ( c ) ;
 if ( val > 1 ) {
 val -- ;
 val = ( 1 << val ) + rac_get_bits ( c , val ) ;
 }
 if ( ! sign ) val = - val ;
 }
 return val ;
 }