int TSVConnClosedGet ( TSVConn connp ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( connp ) == TS_SUCCESS ) ;
 VConnection * vc = ( VConnection * ) connp ;
 int data = 0 ;
 bool f = vc -> get_data ( TS_API_DATA_CLOSED , & data ) ;
 ink_assert ( f ) ;
 return data ;
 }