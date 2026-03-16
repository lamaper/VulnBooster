void proto_reg_handoff_ber ( void ) {
 guint i = 1 ;
 oid_add_from_string ( "asn1" , "2.1" ) ;
 oid_add_from_string ( "basic-encoding" , "2.1.1" ) ;
 dissector_add_uint ( "wtap_encap" , WTAP_ENCAP_BER , ber_handle ) ;
 ber_decode_as_foreach ( ber_add_syntax_name , & i ) ;
 if ( i > 1 ) qsort ( & syntax_names [ 1 ] , i - 1 , sizeof ( value_string ) , cmp_value_string ) ;
 syntax_names [ i ] . value = 0 ;
 syntax_names [ i ] . strptr = NULL ;
 dissector_add_for_decode_as ( "tcp.port" , ber_handle ) ;
 ber_update_oids ( ) ;
 }