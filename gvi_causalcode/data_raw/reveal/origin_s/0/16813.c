CURLcode Curl_add_buffer_send ( Curl_send_buffer * in , struct connectdata * conn , long * bytes_written , size_t included_body_bytes , int socketindex ) {
 ssize_t amount ;
 CURLcode result ;
 char * ptr ;
 size_t size ;
 struct HTTP * http = conn -> data -> req . protop ;
 size_t sendsize ;
 curl_socket_t sockfd ;
 size_t headersize ;
 DEBUGASSERT ( socketindex <= SECONDARYSOCKET ) ;
 sockfd = conn -> sock [ socketindex ] ;
 ptr = in -> buffer ;
 size = in -> size_used ;
 headersize = size - included_body_bytes ;
 DEBUGASSERT ( size > included_body_bytes ) ;
 result = Curl_convert_to_network ( conn -> data , ptr , headersize ) ;
 if ( result ) {
 Curl_add_buffer_free ( in ) ;
 return result ;
 }
 if ( ( conn -> handler -> flags & PROTOPT_SSL ) && conn -> httpversion != 20 ) {
 sendsize = ( size > CURL_MAX_WRITE_SIZE ) ? CURL_MAX_WRITE_SIZE : size ;
 memcpy ( conn -> data -> state . uploadbuffer , ptr , sendsize ) ;
 ptr = conn -> data -> state . uploadbuffer ;
 }
 else sendsize = size ;
 result = Curl_write ( conn , sockfd , ptr , sendsize , & amount ) ;
 if ( ! result ) {
 size_t headlen = ( size_t ) amount > headersize ? headersize : ( size_t ) amount ;
 size_t bodylen = amount - headlen ;
 if ( conn -> data -> set . verbose ) {
 Curl_debug ( conn -> data , CURLINFO_HEADER_OUT , ptr , headlen , conn ) ;
 if ( bodylen ) {
 Curl_debug ( conn -> data , CURLINFO_DATA_OUT , ptr + headlen , bodylen , conn ) ;
 }
 }
 * bytes_written += ( long ) amount ;
 if ( http ) {
 http -> writebytecount += bodylen ;
 if ( ( size_t ) amount != size ) {
 size -= amount ;
 ptr = in -> buffer + amount ;
 http -> backup . fread_func = conn -> data -> state . fread_func ;
 http -> backup . fread_in = conn -> data -> state . in ;
 http -> backup . postdata = http -> postdata ;
 http -> backup . postsize = http -> postsize ;
 conn -> data -> state . fread_func = ( curl_read_callback ) readmoredata ;
 conn -> data -> state . in = ( void * ) conn ;
 http -> postdata = ptr ;
 http -> postsize = ( curl_off_t ) size ;
 http -> send_buffer = in ;
 http -> sending = HTTPSEND_REQUEST ;
 return CURLE_OK ;
 }
 http -> sending = HTTPSEND_BODY ;
 }
 else {
 if ( ( size_t ) amount != size ) return CURLE_SEND_ERROR ;
 else Curl_pipeline_leave_write ( conn ) ;
 }
 }
 Curl_add_buffer_free ( in ) ;
 return result ;
 }