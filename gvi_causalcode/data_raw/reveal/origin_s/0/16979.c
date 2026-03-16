static const gchar * get_ber_oid_syntax ( const char * oid ) {
 return ( const char * ) g_hash_table_lookup ( syntax_table , oid ) ;
 }