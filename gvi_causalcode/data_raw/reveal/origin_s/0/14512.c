TSVIO TSVConnReadVIOGet ( TSVConn connp ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( connp ) == TS_SUCCESS ) ;
 VConnection * vc = ( VConnection * ) connp ;
 TSVIO data ;
 if ( vc -> get_data ( TS_API_DATA_READ_VIO , & data ) ) {
 return data ;
 }
 return nullptr ;
 }