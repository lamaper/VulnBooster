void register_ber_syntax_dissector ( const char * syntax , int proto , dissector_t dissector ) {
 dissector_handle_t dissector_handle ;
 dissector_handle = create_dissector_handle ( dissector , proto ) ;
 dissector_add_string ( "ber.syntax" , syntax , dissector_handle ) ;
 }