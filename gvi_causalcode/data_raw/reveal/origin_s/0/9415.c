char * TSMatcherLineName ( TSMatcherLine ml , int element ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) ml ) == TS_SUCCESS ) ;
 return ( ( ( matcher_line * ) ml ) -> line ) [ 0 ] [ element ] ;
 }