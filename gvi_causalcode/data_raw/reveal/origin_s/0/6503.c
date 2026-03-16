static void fill_variance ( int64_t s2 , int64_t s , int c , var * v ) {
 v -> sum_square_error = s2 ;
 v -> sum_error = s ;
 v -> count = c ;
 if ( c > 0 ) v -> variance = ( int ) ( 256 * ( v -> sum_square_error - v -> sum_error * v -> sum_error / v -> count ) / v -> count ) ;
 else v -> variance = 0 ;
 }