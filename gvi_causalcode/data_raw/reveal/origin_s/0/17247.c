inline static void simple_or_unavailable_server_retry ( HttpTransact : : State * s ) {
 HTTP_RELEASE_ASSERT ( ! s -> parent_result . parent_is_proxy ( ) ) ;
 HTTPStatus server_response = http_hdr_status_get ( s -> hdr_info . server_response . m_http ) ;
 DebugTxn ( "http_trans" , "[simple_or_unavailabe_server_retry] server_response = %d, simple_retry_attempts: %d, numParents:%d " , server_response , s -> current . simple_retry_attempts , s -> parent_params -> numParents ( & s -> parent_result ) ) ;
 if ( ( s -> parent_result . retry_type ( ) & PARENT_RETRY_SIMPLE ) && s -> current . simple_retry_attempts < s -> parent_result . max_retries ( PARENT_RETRY_SIMPLE ) && server_response == HTTP_STATUS_NOT_FOUND ) {
 DebugTxn ( "parent_select" , "RECEIVED A SIMPLE RETRY RESPONSE" ) ;
 if ( s -> current . simple_retry_attempts < s -> parent_params -> numParents ( & s -> parent_result ) ) {
 s -> current . state = HttpTransact : : PARENT_ORIGIN_RETRY ;
 s -> current . retry_type = PARENT_RETRY_SIMPLE ;
 return ;
 }
 else {
 DebugTxn ( "http_trans" , "PARENT_RETRY_SIMPLE: retried all parents, send response to client." ) ;
 return ;
 }
 }
 else if ( ( s -> parent_result . retry_type ( ) & PARENT_RETRY_UNAVAILABLE_SERVER ) && s -> current . unavailable_server_retry_attempts < s -> parent_result . max_retries ( PARENT_RETRY_UNAVAILABLE_SERVER ) && s -> parent_result . response_is_retryable ( server_response ) ) {
 DebugTxn ( "parent_select" , "RECEIVED A PARENT_RETRY_UNAVAILABLE_SERVER RESPONSE" ) ;
 if ( s -> current . unavailable_server_retry_attempts < s -> parent_params -> numParents ( & s -> parent_result ) ) {
 s -> current . state = HttpTransact : : PARENT_ORIGIN_RETRY ;
 s -> current . retry_type = PARENT_RETRY_UNAVAILABLE_SERVER ;
 return ;
 }
 else {
 DebugTxn ( "http_trans" , "PARENT_RETRY_UNAVAILABLE_SERVER: retried all parents, send error to client." ) ;
 return ;
 }
 }
 }