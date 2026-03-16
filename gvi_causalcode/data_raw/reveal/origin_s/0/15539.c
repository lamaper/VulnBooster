static gboolean strcase_equal ( gconstpointer ka , gconstpointer kb ) {
 const char * a = ( const char * ) ka ;
 const char * b = ( const char * ) kb ;
 return g_ascii_strcasecmp ( a , b ) == 0 ;
 }