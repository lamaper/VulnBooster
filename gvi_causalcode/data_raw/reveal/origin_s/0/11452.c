TSVConn TSTransformOutputVConnGet ( TSVConn connp ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( connp ) == TS_SUCCESS ) ;
 VConnection * vc = ( VConnection * ) connp ;
 TSVConn data ;
 vc -> get_data ( TS_API_DATA_OUTPUT_VC , & data ) ;
 return data ;
 }