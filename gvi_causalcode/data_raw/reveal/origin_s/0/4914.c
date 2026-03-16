static gboolean purple_menu_cmp ( const char * a , const char * b ) {
 while ( * a && * b ) {
 while ( * a == '_' ) {
 a ++ ;
 }
 while ( * b == '_' ) {
 b ++ ;
 }
 if ( g_ascii_tolower ( * a ) != g_ascii_tolower ( * b ) ) {
 return FALSE ;
 }
 a ++ ;
 b ++ ;
 }
 return ( * a == '\0' && * b == '\0' ) ;
 }