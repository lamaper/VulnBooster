void new_register_ber_oid_dissector ( const char * oid , new_dissector_t dissector , int proto , const char * name ) {
 dissector_handle_t dissector_handle ;
 dissector_handle = new_create_dissector_handle ( dissector , proto ) ;
 dissector_add_string ( "ber.oid" , oid , dissector_handle ) ;
 oid_add_from_string ( name , oid ) ;
 }