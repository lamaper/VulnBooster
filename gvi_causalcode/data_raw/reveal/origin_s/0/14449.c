TSReturnCode TSHttpTxnCntl ( TSHttpTxn txnp , TSHttpCntlType cntl , void * data ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 switch ( cntl ) {
 case TS_HTTP_CNTL_GET_LOGGING_MODE : {
 if ( data == nullptr ) {
 return TS_ERROR ;
 }
 intptr_t * rptr = ( intptr_t * ) data ;
 if ( sm -> t_state . api_info . logging_enabled ) {
 * rptr = ( intptr_t ) TS_HTTP_CNTL_ON ;
 }
 else {
 * rptr = ( intptr_t ) TS_HTTP_CNTL_OFF ;
 }
 return TS_SUCCESS ;
 }
 case TS_HTTP_CNTL_SET_LOGGING_MODE : if ( data != TS_HTTP_CNTL_ON && data != TS_HTTP_CNTL_OFF ) {
 return TS_ERROR ;
 }
 else {
 sm -> t_state . api_info . logging_enabled = ( bool ) data ;
 return TS_SUCCESS ;
 }
 break ;
 case TS_HTTP_CNTL_GET_INTERCEPT_RETRY_MODE : {
 if ( data == nullptr ) {
 return TS_ERROR ;
 }
 intptr_t * rptr = ( intptr_t * ) data ;
 if ( sm -> t_state . api_info . retry_intercept_failures ) {
 * rptr = ( intptr_t ) TS_HTTP_CNTL_ON ;
 }
 else {
 * rptr = ( intptr_t ) TS_HTTP_CNTL_OFF ;
 }
 return TS_SUCCESS ;
 }
 case TS_HTTP_CNTL_SET_INTERCEPT_RETRY_MODE : if ( data != TS_HTTP_CNTL_ON && data != TS_HTTP_CNTL_OFF ) {
 return TS_ERROR ;
 }
 else {
 sm -> t_state . api_info . retry_intercept_failures = ( bool ) data ;
 return TS_SUCCESS ;
 }
 default : return TS_ERROR ;
 }
 return TS_ERROR ;
 }