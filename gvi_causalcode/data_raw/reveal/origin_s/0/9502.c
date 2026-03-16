TSVIO TSVConnRead ( TSVConn connp , TSCont contp , TSIOBuffer bufp , int64_t nbytes ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( connp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_iocore_structure ( contp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_iocore_structure ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( nbytes >= 0 ) ;
 FORCE_PLUGIN_SCOPED_MUTEX ( contp ) ;
 VConnection * vc = ( VConnection * ) connp ;
 return reinterpret_cast < TSVIO > ( vc -> do_io ( VIO : : READ , ( INKContInternal * ) contp , nbytes , ( MIOBuffer * ) bufp ) ) ;
 }