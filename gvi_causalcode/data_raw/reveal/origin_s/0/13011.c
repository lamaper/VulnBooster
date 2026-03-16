static gboolean contains_uppercase ( const char * s1 ) {
 const char * ch ;
 for ( ch = s1 ;
 * ch != '\0' ;
 ch ++ ) {
 if ( g_ascii_isupper ( * ch ) ) return TRUE ;
 }
 return FALSE ;
 }