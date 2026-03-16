void register_ber_oid_dissector_handle ( const char * oid , dissector_handle_t dissector , int proto _U_ , const char * name ) {
 dissector_add_string ( "ber.oid" , oid , dissector ) ;
 oid_add_from_string ( name , oid ) ;
 }