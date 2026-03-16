TSReturnCode # if TS_USE_TLS_NPN TSNetAcceptNamedProtocol ( TSCont contp , const char * protocol ) {
 sdk_assert ( protocol != nullptr ) ;
 sdk_assert ( contp != nullptr ) ;
 sdk_assert ( sdk_sanity_check_continuation ( contp ) == TS_SUCCESS ) ;
 if ( ! ssl_register_protocol ( protocol , ( INKContInternal * ) contp ) ) {
 ssl_unregister_protocol ( protocol , ( INKContInternal * ) contp ) ;
 return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }

 return TS_ERROR ;
 }