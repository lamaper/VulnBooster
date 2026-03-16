static int arith2_get_number ( ArithCoder * c , int n ) {
 int range = c -> high - c -> low + 1 ;
 int scale = av_log2 ( range ) - av_log2 ( n ) ;
 int val ;
 if ( n << scale > range ) scale -- ;
 n <<= scale ;
 val = arith2_get_scaled_value ( c -> value - c -> low , n , range ) >> scale ;
 arith2_rescale_interval ( c , range , val << scale , ( val + 1 ) << scale , n ) ;
 arith2_normalise ( c ) ;
 return val ;
 }