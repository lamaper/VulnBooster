void register_ber_oid_syntax ( const char * oid , const char * name , const char * syntax ) {
 if ( syntax && * syntax ) g_hash_table_insert ( syntax_table , ( gpointer ) g_strdup ( oid ) , ( gpointer ) g_strdup ( syntax ) ) ;
 if ( name && * name ) register_ber_oid_name ( oid , name ) ;
 }