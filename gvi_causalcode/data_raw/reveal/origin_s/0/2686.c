gboolean oid_has_dissector ( const char * oid ) {
 return ( dissector_get_string_handle ( ber_oid_dissector_table , oid ) != NULL ) ;
 }