void register_ber_oid_dissector ( const char * oid , dissector_t dissector , int proto , const char * name ) {
 dissector_handle_t dissector_handle ;
 dissector_handle = create_dissector_handle ( dissector , proto ) ;
 dissector_add_string ( "ber.oid" , oid , dissector_handle ) ;
 oid_add_from_string ( name , oid ) ;
 }