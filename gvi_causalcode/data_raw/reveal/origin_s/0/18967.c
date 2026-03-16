static int is_single_file ( const char * outfile_pattern ) {
 const char * p = outfile_pattern ;
 do {
 p = strchr ( p , '%' ) ;
 if ( p && p [ 1 ] >= '1' && p [ 1 ] <= '9' ) return 0 ;
 if ( p ) p ++ ;
 }
 while ( p ) ;
 return 1 ;
 }