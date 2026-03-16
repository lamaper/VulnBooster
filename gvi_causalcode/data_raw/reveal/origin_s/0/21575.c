static void free_symbols ( UChar * array [ ] , int32_t arrayLength ) {
 int32_t i ;
 for ( i = 0 ;
 i < arrayLength ;
 i ++ ) {
 free ( array [ i ] ) ;
 }
 }