void ber_decode_as ( const gchar * syntax ) {
 if ( decode_as_syntax ) {
 g_free ( decode_as_syntax ) ;
 decode_as_syntax = NULL ;
 }
 if ( syntax ) decode_as_syntax = g_strdup ( syntax ) ;
 }