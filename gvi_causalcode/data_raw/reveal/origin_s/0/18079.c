static void make_bands ( int16_t * bands , int start , int stop , int num_bands ) {
 int k , previous , present ;
 float base , prod ;
 base = powf ( ( float ) stop / start , 1.0f / num_bands ) ;
 prod = start ;
 previous = start ;
 for ( k = 0 ;
 k < num_bands - 1 ;
 k ++ ) {
 prod *= base ;
 present = lrintf ( prod ) ;
 bands [ k ] = present - previous ;
 previous = present ;
 }
 bands [ num_bands - 1 ] = stop - previous ;
 }