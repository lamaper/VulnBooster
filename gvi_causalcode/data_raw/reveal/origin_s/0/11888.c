static char * strippath ( const char * fullfile ) {
 char * filename ;
 char * base ;
 filename = strdup ( fullfile ) ;
 if ( ! filename ) return NULL ;
 base = strdup ( basename ( filename ) ) ;
 free ( filename ) ;
 return base ;
 }