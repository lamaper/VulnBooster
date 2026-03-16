void ber_set_filename ( gchar * filename ) {
 gchar * ptr ;
 if ( ber_filename ) {
 g_free ( ber_filename ) ;
 ber_filename = NULL ;
 }
 if ( filename ) {
 ber_filename = g_strdup ( filename ) ;
 if ( ( ptr = strrchr ( ber_filename , '.' ) ) != NULL ) {
 ber_decode_as ( get_ber_oid_syntax ( ptr ) ) ;
 }
 }
 }