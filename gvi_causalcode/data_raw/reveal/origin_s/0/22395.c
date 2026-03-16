static int transformable ( TSHttpTxn txnp , TransformTestData * data ) {
 TSMBuffer bufp ;
 TSMLoc hdr_loc ;
 if ( TSHttpTxnServerRespGet ( txnp , & bufp , & hdr_loc ) != TS_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnTransform" , "" , TC_FAIL , "[transformable]: TSHttpTxnServerRespGet return 0" ) ;
 }
 if ( TS_HTTP_STATUS_OK == TSHttpHdrStatusGet ( bufp , hdr_loc ) ) {
 return 1 ;
 }
 return 0 ;
 }