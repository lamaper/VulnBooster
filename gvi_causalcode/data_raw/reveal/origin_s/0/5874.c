CURLcode Curl_http_readwrite_headers ( struct Curl_easy * data , struct connectdata * conn , ssize_t * nread , bool * stop_reading ) {
 CURLcode result ;
 struct SingleRequest * k = & data -> req ;
 do {
 size_t rest_length ;
 size_t full_length ;
 int writetype ;
 k -> str_start = k -> str ;
 k -> end_ptr = memchr ( k -> str_start , 0x0a , * nread ) ;
 if ( ! k -> end_ptr ) {
 result = header_append ( data , k , * nread ) ;
 if ( result ) return result ;
 if ( ! k -> headerline && ( k -> hbuflen > 5 ) ) {
 if ( ! checkprotoprefix ( data , conn , data -> state . headerbuff ) ) {
 k -> header = FALSE ;
 k -> badheader = HEADER_ALLBAD ;
 break ;
 }
 }
 break ;
 }
 rest_length = ( k -> end_ptr - k -> str ) + 1 ;
 * nread -= ( ssize_t ) rest_length ;
 k -> str = k -> end_ptr + 1 ;
 full_length = k -> str - k -> str_start ;
 result = header_append ( data , k , full_length ) ;
 if ( result ) return result ;
 k -> end_ptr = k -> hbufp ;
 k -> p = data -> state . headerbuff ;
 if ( ! k -> headerline ) {
 if ( ( k -> hbuflen > 5 ) && ! checkprotoprefix ( data , conn , data -> state . headerbuff ) ) {
 k -> header = FALSE ;
 if ( * nread ) k -> badheader = HEADER_PARTHEADER ;
 else {
 k -> badheader = HEADER_ALLBAD ;
 * nread = ( ssize_t ) rest_length ;
 }
 break ;
 }
 }
 if ( ( 0x0a == * k -> p ) || ( 0x0d == * k -> p ) ) {
 size_t headerlen ;

 * k -> p = '\r' ;
 k -> p ++ ;
 }
 if ( 0x0a == * k -> p ) {
 * k -> p = '\n' ;
 k -> p ++ ;
 }

 if ( '\n' == * k -> p ) k -> p ++ ;

 switch ( k -> httpcode ) {
 case 100 : k -> header = TRUE ;
 k -> headerline = 0 ;
 if ( k -> exp100 > EXP100_SEND_DATA ) {
 k -> exp100 = EXP100_SEND_DATA ;
 k -> keepon |= KEEP_SEND ;
 }
 break ;
 case 101 : if ( k -> upgr101 == UPGR101_REQUESTED ) {
 infof ( data , "Received 101\n" ) ;
 k -> upgr101 = UPGR101_RECEIVED ;
 k -> header = TRUE ;
 k -> headerline = 0 ;
 result = Curl_http2_switched ( conn , k -> str , * nread ) ;
 if ( result ) return result ;
 * nread = 0 ;
 }
 else {
 k -> header = FALSE ;
 }
 break ;
 default : k -> header = TRUE ;
 k -> headerline = 0 ;
 break ;
 }
 }
 else {
 k -> header = FALSE ;
 if ( ( k -> size == - 1 ) && ! k -> chunk && ! conn -> bits . close && ( conn -> httpversion == 11 ) && ! ( conn -> handler -> protocol & CURLPROTO_RTSP ) && data -> set . httpreq != HTTPREQ_HEAD ) {
 infof ( data , "no chunk, no close, no size. Assume close to " "signal end\n" ) ;
 streamclose ( conn , "HTTP: No end-of-message indicator" ) ;
 }
 }

 infof ( data , "Connection closure while negotiating auth (HTTP 1.0?)\n" ) ;
 data -> state . authproblem = TRUE ;
 }

 failf ( data , "The requested URL returned error: %d" , k -> httpcode ) ;
 return CURLE_HTTP_RETURNED_ERROR ;
 }
 writetype = CLIENTWRITE_HEADER ;
 if ( data -> set . include_header ) writetype |= CLIENTWRITE_BODY ;
 headerlen = k -> p - data -> state . headerbuff ;
 result = Curl_client_write ( conn , writetype , data -> state . headerbuff , headerlen ) ;
 if ( result ) return result ;
 data -> info . header_size += ( long ) headerlen ;
 data -> req . headerbytecount += ( long ) headerlen ;
 data -> req . deductheadercount = ( 100 <= k -> httpcode && 199 >= k -> httpcode ) ? data -> req . headerbytecount : 0 ;
 result = Curl_http_auth_act ( conn ) ;
 if ( result ) return result ;
 if ( k -> httpcode >= 300 ) {
 if ( ( ! conn -> bits . authneg ) && ! conn -> bits . close && ! conn -> bits . rewindaftersend ) {
 switch ( data -> set . httpreq ) {
 case HTTPREQ_PUT : case HTTPREQ_POST : case HTTPREQ_POST_FORM : if ( ! k -> upload_done ) {
 if ( data -> set . http_keep_sending_on_error ) {
 infof ( data , "HTTP error before end of send, keep sending\n" ) ;
 if ( k -> exp100 > EXP100_SEND_DATA ) {
 k -> exp100 = EXP100_SEND_DATA ;
 k -> keepon |= KEEP_SEND ;
 }
 }
 else {
 infof ( data , "HTTP error before end of send, stop sending\n" ) ;
 streamclose ( conn , "Stop sending data before everything sent" ) ;
 k -> upload_done = TRUE ;
 k -> keepon &= ~ KEEP_SEND ;
 if ( data -> state . expect100header ) k -> exp100 = EXP100_FAILED ;
 }
 }
 break ;
 default : break ;
 }
 }
 if ( conn -> bits . rewindaftersend ) {
 infof ( data , "Keep sending data to get tossed away!\n" ) ;
 k -> keepon |= KEEP_SEND ;
 }
 }
 if ( ! k -> header ) {
 if ( data -> set . opt_no_body ) * stop_reading = TRUE ;


 if ( k -> chunk ) k -> maxdownload = k -> size = - 1 ;
 }
 if ( - 1 != k -> size ) {
 Curl_pgrsSetDownloadSize ( data , k -> size ) ;
 k -> maxdownload = k -> size ;
 }
 if ( 0 == k -> maxdownload ) * stop_reading = TRUE ;
 if ( * stop_reading ) {
 k -> keepon &= ~ KEEP_RECV ;
 }
 if ( data -> set . verbose ) Curl_debug ( data , CURLINFO_HEADER_IN , k -> str_start , headerlen , conn ) ;
 break ;
 }
 k -> hbufp = data -> state . headerbuff ;
 k -> hbuflen = 0 ;
 continue ;
 }
 if ( ! k -> headerline ++ ) {
 int httpversion_major ;
 int rtspversion_major ;
 int nc = 0 ;

 char scratch [ SCRATCHSIZE + 1 ] ;
 strncpy ( & scratch [ 0 ] , k -> p , SCRATCHSIZE ) ;
 scratch [ SCRATCHSIZE ] = 0 ;
 res = Curl_convert_from_network ( data , & scratch [ 0 ] , SCRATCHSIZE ) ;
 if ( res ) return res ;

 nc = sscanf ( HEADER1 , " HTTP/%d.%d %d" , & httpversion_major , & conn -> httpversion , & k -> httpcode ) ;
 if ( nc == 1 && httpversion_major == 2 && == sscanf ( HEADER1 , " HTTP/2 %d" , & k -> httpcode ) ) {
 conn -> httpversion = 0 ;
 nc = 3 ;
 }
 if ( nc == 3 ) {
 conn -> httpversion += 10 * httpversion_major ;
 if ( k -> upgr101 == UPGR101_RECEIVED ) {
 if ( conn -> httpversion != 20 ) infof ( data , "Lying server, not serving HTTP/2\n" ) ;
 }
 }
 else {
 nc = sscanf ( HEADER1 , " HTTP %3d" , & k -> httpcode ) ;
 conn -> httpversion = 10 ;
 if ( ! nc ) {
 if ( checkhttpprefix ( data , k -> p ) ) {
 nc = 1 ;
 k -> httpcode = 200 ;
 conn -> httpversion = 10 ;
 }
 }
 }
 }
 else if ( conn -> handler -> protocol & CURLPROTO_RTSP ) {
 nc = sscanf ( HEADER1 , " RTSP/%d.%d %3d" , & rtspversion_major , & conn -> rtspversion , & k -> httpcode ) ;
 if ( nc == 3 ) {
 conn -> rtspversion += 10 * rtspversion_major ;
 conn -> httpversion = 11 ;
 }
 else {
 nc = 0 ;
 }
 }
 if ( nc ) {
 data -> info . httpcode = k -> httpcode ;
 data -> info . httpversion = conn -> httpversion ;
 if ( ! data -> state . httpversion || data -> state . httpversion > conn -> httpversion ) data -> state . httpversion = conn -> httpversion ;
 if ( data -> set . http_fail_on_error && ( k -> httpcode >= 400 ) && ( ( k -> httpcode != 401 ) || ! conn -> bits . user_passwd ) && ( ( k -> httpcode != 407 ) || ! conn -> bits . proxy_user_passwd ) ) {
 if ( data -> state . resume_from && ( data -> set . httpreq == HTTPREQ_GET ) && ( k -> httpcode == 416 ) ) {
 }
 else {
 print_http_error ( data ) ;
 return CURLE_HTTP_RETURNED_ERROR ;
 }
 }
 if ( conn -> httpversion == 10 ) {
 infof ( data , "HTTP 1.0, assume close after body\n" ) ;
 connclose ( conn , "HTTP/1.0 close after body" ) ;
 }
 else if ( conn -> httpversion == 20 || ( k -> upgr101 == UPGR101_REQUESTED && k -> httpcode == 101 ) ) {
 DEBUGF ( infof ( data , "HTTP/2 found, allow multiplexing\n" ) ) ;
 conn -> bundle -> multiuse = BUNDLE_MULTIPLEX ;
 }
 else if ( conn -> httpversion >= 11 && ! conn -> bits . close ) {
 DEBUGF ( infof ( data , "HTTP 1.1 or later with persistent connection, " "pipelining supported\n" ) ) ;
 if ( conn -> bundle ) {
 if ( ! Curl_pipeline_site_blacklisted ( data , conn ) ) conn -> bundle -> multiuse = BUNDLE_PIPELINING ;
 }
 }
 switch ( k -> httpcode ) {
 case 204 : case 304 : if ( data -> set . timecondition ) data -> info . timecond = TRUE ;
 k -> size = 0 ;
 k -> maxdownload = 0 ;
 k -> ignorecl = TRUE ;
 break ;
 default : break ;
 }
 }
 else {
 k -> header = FALSE ;
 break ;
 }
 }
 result = Curl_convert_from_network ( data , k -> p , strlen ( k -> p ) ) ;
 if ( result ) return result ;
 if ( ! k -> ignorecl && ! data -> set . ignorecl && checkprefix ( "Content-Length:" , k -> p ) ) {
 curl_off_t contentlength = curlx_strtoofft ( k -> p + 15 , NULL , 10 ) ;
 if ( data -> set . max_filesize && contentlength > data -> set . max_filesize ) {
 failf ( data , "Maximum file size exceeded" ) ;
 return CURLE_FILESIZE_EXCEEDED ;
 }
 if ( contentlength >= 0 ) {
 k -> size = contentlength ;
 k -> maxdownload = k -> size ;
 Curl_pgrsSetDownloadSize ( data , k -> size ) ;
 }
 else {
 streamclose ( conn , "negative content-length" ) ;
 infof ( data , "Negative content-length: %" CURL_FORMAT_CURL_OFF_T ", closing after transfer\n" , contentlength ) ;
 }
 }
 else if ( checkprefix ( "Content-Type:" , k -> p ) ) {
 char * contenttype = Curl_copy_header_value ( k -> p ) ;
 if ( ! contenttype ) return CURLE_OUT_OF_MEMORY ;
 if ( ! * contenttype ) free ( contenttype ) ;
 else {
 Curl_safefree ( data -> info . contenttype ) ;
 data -> info . contenttype = contenttype ;
 }
 }
 else if ( checkprefix ( "Server:" , k -> p ) ) {
 if ( conn -> httpversion < 20 ) {
 char * server_name = Curl_copy_header_value ( k -> p ) ;
 if ( conn -> bundle && ( conn -> bundle -> multiuse == BUNDLE_PIPELINING ) ) {
 if ( Curl_pipeline_server_blacklisted ( data , server_name ) ) conn -> bundle -> multiuse = BUNDLE_NO_MULTIUSE ;
 }
 free ( server_name ) ;
 }
 }
 else if ( ( conn -> httpversion == 10 ) && conn -> bits . httpproxy && Curl_compareheader ( k -> p , "Proxy-Connection:" , "keep-alive" ) ) {
 connkeep ( conn , "Proxy-Connection keep-alive" ) ;
 infof ( data , "HTTP/1.0 proxy connection set to keep alive!\n" ) ;
 }
 else if ( ( conn -> httpversion == 11 ) && conn -> bits . httpproxy && Curl_compareheader ( k -> p , "Proxy-Connection:" , "close" ) ) {
 connclose ( conn , "Proxy-Connection: asked to close after done" ) ;
 infof ( data , "HTTP/1.1 proxy connection set close!\n" ) ;
 }
 else if ( ( conn -> httpversion == 10 ) && Curl_compareheader ( k -> p , "Connection:" , "keep-alive" ) ) {
 connkeep ( conn , "Connection keep-alive" ) ;
 infof ( data , "HTTP/1.0 connection set to keep alive!\n" ) ;
 }
 else if ( Curl_compareheader ( k -> p , "Connection:" , "close" ) ) {
 streamclose ( conn , "Connection: close used" ) ;
 }
 else if ( checkprefix ( "Transfer-Encoding:" , k -> p ) ) {
 char * start ;
 start = k -> p + 18 ;
 for ( ;
 ;
 ) {
 while ( * start && ( ISSPACE ( * start ) || ( * start == ',' ) ) ) start ++ ;
 if ( checkprefix ( "chunked" , start ) ) {
 k -> chunk = TRUE ;
 Curl_httpchunk_init ( conn ) ;
 start += 7 ;
 }
 if ( k -> auto_decoding ) break ;
 if ( checkprefix ( "identity" , start ) ) {
 k -> auto_decoding = IDENTITY ;
 start += 8 ;
 }
 else if ( checkprefix ( "deflate" , start ) ) {
 k -> auto_decoding = DEFLATE ;
 start += 7 ;
 }
 else if ( checkprefix ( "gzip" , start ) ) {
 k -> auto_decoding = GZIP ;
 start += 4 ;
 }
 else if ( checkprefix ( "x-gzip" , start ) ) {
 k -> auto_decoding = GZIP ;
 start += 6 ;
 }
 else break ;
 }
 }
 else if ( checkprefix ( "Content-Encoding:" , k -> p ) && data -> set . str [ STRING_ENCODING ] ) {
 char * start ;
 start = k -> p + 17 ;
 while ( * start && ISSPACE ( * start ) ) start ++ ;
 if ( checkprefix ( "identity" , start ) ) k -> auto_decoding = IDENTITY ;
 else if ( checkprefix ( "deflate" , start ) ) k -> auto_decoding = DEFLATE ;
 else if ( checkprefix ( "gzip" , start ) || checkprefix ( "x-gzip" , start ) ) k -> auto_decoding = GZIP ;
 }
 else if ( checkprefix ( "Content-Range:" , k -> p ) ) {
 char * ptr = k -> p + 14 ;
 while ( * ptr && ! ISDIGIT ( * ptr ) && * ptr != '*' ) ptr ++ ;
 if ( ISDIGIT ( * ptr ) ) {
 k -> offset = curlx_strtoofft ( ptr , NULL , 10 ) ;
 if ( data -> state . resume_from == k -> offset ) k -> content_range = TRUE ;
 }
 else data -> state . resume_from = 0 ;
 }

 Curl_share_lock ( data , CURL_LOCK_DATA_COOKIE , CURL_LOCK_ACCESS_SINGLE ) ;
 Curl_cookie_add ( data , data -> cookies , TRUE , k -> p + 11 , conn -> allocptr . cookiehost ? conn -> allocptr . cookiehost : conn -> host . name , data -> state . path ) ;
 Curl_share_unlock ( data , CURL_LOCK_DATA_COOKIE ) ;
 }

 time_t secs = time ( NULL ) ;
 k -> timeofdoc = curl_getdate ( k -> p + strlen ( "Last-Modified:" ) , & secs ) ;
 if ( data -> set . get_filetime ) data -> info . filetime = ( long ) k -> timeofdoc ;
 }
 else if ( ( checkprefix ( "WWW-Authenticate:" , k -> p ) && ( 401 == k -> httpcode ) ) || ( checkprefix ( "Proxy-authenticate:" , k -> p ) && ( 407 == k -> httpcode ) ) ) {
 bool proxy = ( k -> httpcode == 407 ) ? TRUE : FALSE ;
 char * auth = Curl_copy_header_value ( k -> p ) ;
 if ( ! auth ) return CURLE_OUT_OF_MEMORY ;
 result = Curl_http_input_auth ( conn , proxy , auth ) ;
 free ( auth ) ;
 if ( result ) return result ;
 }
 else if ( ( k -> httpcode >= 300 && k -> httpcode < 400 ) && checkprefix ( "Location:" , k -> p ) && ! data -> req . location ) {
 char * location = Curl_copy_header_value ( k -> p ) ;
 if ( ! location ) return CURLE_OUT_OF_MEMORY ;
 if ( ! * location ) free ( location ) ;
 else {
 data -> req . location = location ;
 if ( data -> set . http_follow_location ) {
 DEBUGASSERT ( ! data -> req . newurl ) ;
 data -> req . newurl = strdup ( data -> req . location ) ;
 if ( ! data -> req . newurl ) return CURLE_OUT_OF_MEMORY ;
 result = http_perhapsrewind ( conn ) ;
 if ( result ) return result ;
 }
 }
 }
 else if ( conn -> handler -> protocol & CURLPROTO_RTSP ) {
 result = Curl_rtsp_parseheader ( conn , k -> p ) ;
 if ( result ) return result ;
 }
 writetype = CLIENTWRITE_HEADER ;
 if ( data -> set . include_header ) writetype |= CLIENTWRITE_BODY ;
 if ( data -> set . verbose ) Curl_debug ( data , CURLINFO_HEADER_IN , k -> p , ( size_t ) k -> hbuflen , conn ) ;
 result = Curl_client_write ( conn , writetype , k -> p , k -> hbuflen ) ;
 if ( result ) return result ;
 data -> info . header_size += ( long ) k -> hbuflen ;
 data -> req . headerbytecount += ( long ) k -> hbuflen ;
 k -> hbufp = data -> state . headerbuff ;
 k -> hbuflen = 0 ;
 }
 while ( * k -> str ) ;
 return CURLE_OK ;
 }