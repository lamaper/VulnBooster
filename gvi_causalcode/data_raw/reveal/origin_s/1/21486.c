CURLcode Curl_http ( struct connectdata * conn , bool * done ) {
 struct Curl_easy * data = conn -> data ;
 CURLcode result = CURLE_OK ;
 struct HTTP * http ;
 const char * ppath = data -> state . path ;
 bool paste_ftp_userpwd = FALSE ;
 char ftp_typecode [ sizeof ( "/;
type=?" ) ] = "" ;
 const char * host = conn -> host . name ;
 const char * te = "" ;
 const char * ptr ;
 const char * request ;
 Curl_HttpReq httpreq = data -> set . httpreq ;


 const char * httpstring ;
 Curl_send_buffer * req_buffer ;
 curl_off_t postsize = 0 ;
 int seekerr = CURL_SEEKFUNC_OK ;
 * done = TRUE ;
 if ( conn -> httpversion < 20 ) {
 switch ( conn -> negnpn ) {
 case CURL_HTTP_VERSION_2 : conn -> httpversion = 20 ;
 result = Curl_http2_switched ( conn , NULL , 0 ) ;
 if ( result ) return result ;
 break ;
 case CURL_HTTP_VERSION_1_1 : break ;
 default : # ifdef USE_NGHTTP2 if ( conn -> data -> set . httpversion == CURL_HTTP_VERSION_2_PRIOR_KNOWLEDGE ) {
 DEBUGF ( infof ( data , "HTTP/2 over clean TCP\n" ) ) ;
 conn -> httpversion = 20 ;
 result = Curl_http2_switched ( conn , NULL , 0 ) ;
 if ( result ) return result ;
 }

 }
 }
 else {
 result = Curl_http2_setup ( conn ) ;
 if ( result ) return result ;
 }
 http = data -> req . protop ;
 if ( ! data -> state . this_is_a_follow ) {
 free ( data -> state . first_host ) ;
 data -> state . first_host = strdup ( conn -> host . name ) ;
 if ( ! data -> state . first_host ) return CURLE_OUT_OF_MEMORY ;
 data -> state . first_remote_port = conn -> remote_port ;
 }
 http -> writebytecount = http -> readbytecount = 0 ;
 if ( ( conn -> handler -> protocol & ( PROTO_FAMILY_HTTP | CURLPROTO_FTP ) ) && data -> set . upload ) {
 httpreq = HTTPREQ_PUT ;
 }
 if ( data -> set . str [ STRING_CUSTOMREQUEST ] ) request = data -> set . str [ STRING_CUSTOMREQUEST ] ;
 else {
 if ( data -> set . opt_no_body ) request = "HEAD" ;
 else {
 DEBUGASSERT ( ( httpreq > HTTPREQ_NONE ) && ( httpreq < HTTPREQ_LAST ) ) ;
 switch ( httpreq ) {
 case HTTPREQ_POST : case HTTPREQ_POST_FORM : request = "POST" ;
 break ;
 case HTTPREQ_PUT : request = "PUT" ;
 break ;
 default : case HTTPREQ_GET : request = "GET" ;
 break ;
 case HTTPREQ_HEAD : request = "HEAD" ;
 break ;
 }
 }
 }
 if ( Curl_checkheaders ( conn , "User-Agent:" ) ) {
 free ( conn -> allocptr . uagent ) ;
 conn -> allocptr . uagent = NULL ;
 }
 result = Curl_http_output_auth ( conn , request , ppath , FALSE ) ;
 if ( result ) return result ;
 if ( ( data -> state . authhost . multi || data -> state . authproxy . multi ) && ( httpreq != HTTPREQ_GET ) && ( httpreq != HTTPREQ_HEAD ) ) {
 conn -> bits . authneg = TRUE ;
 }
 else conn -> bits . authneg = FALSE ;
 Curl_safefree ( conn -> allocptr . ref ) ;
 if ( data -> change . referer && ! Curl_checkheaders ( conn , "Referer:" ) ) {
 conn -> allocptr . ref = aprintf ( "Referer: %s\r\n" , data -> change . referer ) ;
 if ( ! conn -> allocptr . ref ) return CURLE_OUT_OF_MEMORY ;
 }
 else conn -> allocptr . ref = NULL ;


 Curl_safefree ( conn -> allocptr . accept_encoding ) ;
 conn -> allocptr . accept_encoding = aprintf ( "Accept-Encoding: %s\r\n" , data -> set . str [ STRING_ENCODING ] ) ;
 if ( ! conn -> allocptr . accept_encoding ) return CURLE_OUT_OF_MEMORY ;
 }
 else {
 Curl_safefree ( conn -> allocptr . accept_encoding ) ;
 conn -> allocptr . accept_encoding = NULL ;
 }

 char * cptr = Curl_checkheaders ( conn , "Connection:" ) ;

 conn -> allocptr . te = cptr ? aprintf ( "%s, TE\r\n" TE_HEADER , cptr ) : strdup ( "Connection: TE\r\n" TE_HEADER ) ;
 if ( ! conn -> allocptr . te ) return CURLE_OUT_OF_MEMORY ;
 }

 if ( ptr ) {
 data -> req . upload_chunky = Curl_compareheader ( ptr , "Transfer-Encoding:" , "chunked" ) ;
 }
 else {
 if ( ( conn -> handler -> protocol & PROTO_FAMILY_HTTP ) && data -> set . upload && ( data -> state . infilesize == - 1 ) ) {
 if ( conn -> bits . authneg ) ;
 else if ( use_http_1_1plus ( data , conn ) ) {
 data -> req . upload_chunky = TRUE ;
 }
 else {
 failf ( data , "Chunky upload is not supported by HTTP 1.0" ) ;
 return CURLE_UPLOAD_FAILED ;
 }
 }
 else {
 data -> req . upload_chunky = FALSE ;
 }
 if ( data -> req . upload_chunky ) te = "Transfer-Encoding: chunked\r\n" ;
 }
 Curl_safefree ( conn -> allocptr . host ) ;
 ptr = Curl_checkheaders ( conn , "Host:" ) ;
 if ( ptr && ( ! data -> state . this_is_a_follow || Curl_raw_equal ( data -> state . first_host , conn -> host . name ) ) ) {

 if ( ! cookiehost ) return CURLE_OUT_OF_MEMORY ;
 if ( ! * cookiehost ) free ( cookiehost ) ;
 else {
 int startsearch = 0 ;
 if ( * cookiehost == '[' ) {
 char * closingbracket ;
 memmove ( cookiehost , cookiehost + 1 , strlen ( cookiehost ) - 1 ) ;
 closingbracket = strchr ( cookiehost , ']' ) ;
 if ( closingbracket ) * closingbracket = 0 ;
 }
 else {
 char * colon = strchr ( cookiehost + startsearch , ':' ) ;
 if ( colon ) * colon = 0 ;
 }
 Curl_safefree ( conn -> allocptr . cookiehost ) ;
 conn -> allocptr . cookiehost = cookiehost ;
 }

 conn -> allocptr . host = aprintf ( "%s\r\n" , ptr ) ;
 if ( ! conn -> allocptr . host ) return CURLE_OUT_OF_MEMORY ;
 }
 else conn -> allocptr . host = NULL ;
 }
 else {
 if ( ( ( conn -> given -> protocol & CURLPROTO_HTTPS ) && ( conn -> remote_port == PORT_HTTPS ) ) || ( ( conn -> given -> protocol & CURLPROTO_HTTP ) && ( conn -> remote_port == PORT_HTTP ) ) ) conn -> allocptr . host = aprintf ( "Host: %s%s%s\r\n" , conn -> bits . ipv6_ip ? "[" : "" , host , conn -> bits . ipv6_ip ? "]" : "" ) ;
 else conn -> allocptr . host = aprintf ( "Host: %s%s%s:%hu\r\n" , conn -> bits . ipv6_ip ? "[" : "" , host , conn -> bits . ipv6_ip ? "]" : "" , conn -> remote_port ) ;
 if ( ! conn -> allocptr . host ) return CURLE_OUT_OF_MEMORY ;
 }

 if ( conn -> host . dispname != conn -> host . name ) {
 char * url = data -> change . url ;
 ptr = strstr ( url , conn -> host . dispname ) ;
 if ( ptr ) {
 size_t currlen = strlen ( conn -> host . dispname ) ;
 size_t newlen = strlen ( conn -> host . name ) ;
 size_t urllen = strlen ( url ) ;
 char * newurl ;
 newurl = malloc ( urllen + newlen - currlen + 1 ) ;
 if ( newurl ) {
 memcpy ( newurl , url , ptr - url ) ;
 memcpy ( newurl + ( ptr - url ) , conn -> host . name , newlen ) ;
 memcpy ( newurl + newlen + ( ptr - url ) , ptr + currlen , urllen - ( ptr - url ) - currlen + 1 ) ;
 if ( data -> change . url_alloc ) {
 Curl_safefree ( data -> change . url ) ;
 data -> change . url_alloc = FALSE ;
 }
 data -> change . url = newurl ;
 data -> change . url_alloc = TRUE ;
 }
 else return CURLE_OUT_OF_MEMORY ;
 }
 }
 ppath = data -> change . url ;
 if ( checkprefix ( "ftp://" , ppath ) ) {
 if ( data -> set . proxy_transfer_mode ) {
 char * type = strstr ( ppath , ";
type=" ) ;
 if ( type && type [ 6 ] && type [ 7 ] == 0 ) {
 switch ( Curl_raw_toupper ( type [ 6 ] ) ) {
 case 'A' : case 'D' : case 'I' : break ;
 default : type = NULL ;
 }
 }
 if ( ! type ) {
 char * p = ftp_typecode ;
 if ( ! * data -> state . path && ppath [ strlen ( ppath ) - 1 ] != '/' ) {
 * p ++ = '/' ;
 }
 snprintf ( p , sizeof ( ftp_typecode ) - 1 , ";
type=%c" , data -> set . prefer_ascii ? 'a' : 'i' ) ;
 }
 }
 if ( conn -> bits . user_passwd && ! conn -> bits . userpwd_in_url ) paste_ftp_userpwd = TRUE ;
 }
 }

 result = Curl_getformdata ( data , & http -> sendit , data -> set . httppost , Curl_checkheaders ( conn , "Content-Type:" ) , & http -> postsize ) ;
 if ( result ) return result ;
 }
 http -> p_accept = Curl_checkheaders ( conn , "Accept:" ) ? NULL : "Accept: */*\r\n" ;
 if ( ( ( HTTPREQ_POST == httpreq ) || ( HTTPREQ_POST_FORM == httpreq ) || ( HTTPREQ_PUT == httpreq ) ) && data -> state . resume_from ) {
 if ( data -> state . resume_from < 0 ) {
 data -> state . resume_from = 0 ;
 }
 if ( data -> state . resume_from && ! data -> state . this_is_a_follow ) {
 if ( conn -> seek_func ) {
 seekerr = conn -> seek_func ( conn -> seek_client , data -> state . resume_from , SEEK_SET ) ;
 }
 if ( seekerr != CURL_SEEKFUNC_OK ) {
 if ( seekerr != CURL_SEEKFUNC_CANTSEEK ) {
 failf ( data , "Could not seek stream" ) ;
 return CURLE_READ_ERROR ;
 }
 else {
 curl_off_t passed = 0 ;
 do {
 size_t readthisamountnow = ( data -> state . resume_from - passed > CURL_OFF_T_C ( BUFSIZE ) ) ? BUFSIZE : curlx_sotouz ( data -> state . resume_from - passed ) ;
 size_t actuallyread = data -> state . fread_func ( data -> state . buffer , 1 , readthisamountnow , data -> state . in ) ;
 passed += actuallyread ;
 if ( ( actuallyread == 0 ) || ( actuallyread > readthisamountnow ) ) {
 failf ( data , "Could only read %" CURL_FORMAT_CURL_OFF_T " bytes from the input" , passed ) ;
 return CURLE_READ_ERROR ;
 }
 }
 while ( passed < data -> state . resume_from ) ;
 }
 }
 if ( data -> state . infilesize > 0 ) {
 data -> state . infilesize -= data -> state . resume_from ;
 if ( data -> state . infilesize <= 0 ) {
 failf ( data , "File already completely uploaded" ) ;
 return CURLE_PARTIAL_FILE ;
 }
 }
 }
 }
 if ( data -> state . use_range ) {
 if ( ( ( httpreq == HTTPREQ_GET ) || ( httpreq == HTTPREQ_HEAD ) ) && ! Curl_checkheaders ( conn , "Range:" ) ) {
 free ( conn -> allocptr . rangeline ) ;
 conn -> allocptr . rangeline = aprintf ( "Range: bytes=%s\r\n" , data -> state . range ) ;
 }
 else if ( ( httpreq != HTTPREQ_GET ) && ! Curl_checkheaders ( conn , "Content-Range:" ) ) {
 free ( conn -> allocptr . rangeline ) ;
 if ( data -> set . set_resume_from < 0 ) {
 conn -> allocptr . rangeline = aprintf ( "Content-Range: bytes 0-%" CURL_FORMAT_CURL_OFF_T "/%" CURL_FORMAT_CURL_OFF_T "\r\n" , data -> state . infilesize - 1 , data -> state . infilesize ) ;
 }
 else if ( data -> state . resume_from ) {
 curl_off_t total_expected_size = data -> state . resume_from + data -> state . infilesize ;
 conn -> allocptr . rangeline = aprintf ( "Content-Range: bytes %s%" CURL_FORMAT_CURL_OFF_T "/%" CURL_FORMAT_CURL_OFF_T "\r\n" , data -> state . range , total_expected_size - 1 , total_expected_size ) ;
 }
 else {
 conn -> allocptr . rangeline = aprintf ( "Content-Range: bytes %s/%" CURL_FORMAT_CURL_OFF_T "\r\n" , data -> state . range , data -> state . infilesize ) ;
 }
 if ( ! conn -> allocptr . rangeline ) return CURLE_OUT_OF_MEMORY ;
 }
 }
 httpstring = use_http_1_1plus ( data , conn ) ? "1.1" : "1.0" ;
 req_buffer = Curl_add_buffer_init ( ) ;
 if ( ! req_buffer ) return CURLE_OUT_OF_MEMORY ;
 result = Curl_add_bufferf ( req_buffer , "%s " , request ) ;
 if ( result ) return result ;
 if ( paste_ftp_userpwd ) result = Curl_add_bufferf ( req_buffer , "ftp://%s:%s@%s" , conn -> user , conn -> passwd , ppath + sizeof ( "ftp://" ) - 1 ) ;
 else result = Curl_add_buffer ( req_buffer , ppath , strlen ( ppath ) ) ;
 if ( result ) return result ;
 result = Curl_add_bufferf ( req_buffer , "%s" " HTTP/%s\r\n" "%s" "%s" "%s" "%s" "%s" "%s" "%s" "%s" "%s" "%s" "%s" , ftp_typecode , httpstring , ( conn -> allocptr . host ? conn -> allocptr . host : "" ) , conn -> allocptr . proxyuserpwd ? conn -> allocptr . proxyuserpwd : "" , conn -> allocptr . userpwd ? conn -> allocptr . userpwd : "" , ( data -> state . use_range && conn -> allocptr . rangeline ) ? conn -> allocptr . rangeline : "" , ( data -> set . str [ STRING_USERAGENT ] && * data -> set . str [ STRING_USERAGENT ] && conn -> allocptr . uagent ) ? conn -> allocptr . uagent : "" , http -> p_accept ? http -> p_accept : "" , conn -> allocptr . te ? conn -> allocptr . te : "" , ( data -> set . str [ STRING_ENCODING ] && * data -> set . str [ STRING_ENCODING ] && conn -> allocptr . accept_encoding ) ? conn -> allocptr . accept_encoding : "" , ( data -> change . referer && conn -> allocptr . ref ) ? conn -> allocptr . ref : "" , ( conn -> bits . httpproxy && ! conn -> bits . tunnel_proxy && ! Curl_checkProxyheaders ( conn , "Proxy-Connection:" ) ) ? "Proxy-Connection: Keep-Alive\r\n" : "" , te ) ;
 Curl_safefree ( conn -> allocptr . userpwd ) ;
 switch ( data -> state . authproxy . picked ) {
 case CURLAUTH_NEGOTIATE : case CURLAUTH_NTLM : case CURLAUTH_NTLM_WB : Curl_safefree ( conn -> allocptr . proxyuserpwd ) ;
 break ;
 }
 if ( result ) return result ;
 if ( ! ( conn -> handler -> flags & PROTOPT_SSL ) && conn -> httpversion != 20 && ( data -> set . httpversion == CURL_HTTP_VERSION_2 ) ) {
 result = Curl_http2_request_upgrade ( req_buffer , conn ) ;
 if ( result ) return result ;
 }

 struct Cookie * co = NULL ;
 int count = 0 ;
 if ( data -> cookies ) {
 Curl_share_lock ( data , CURL_LOCK_DATA_COOKIE , CURL_LOCK_ACCESS_SINGLE ) ;
 co = Curl_cookie_getlist ( data -> cookies , conn -> allocptr . cookiehost ? conn -> allocptr . cookiehost : host , data -> state . path , ( conn -> handler -> protocol & CURLPROTO_HTTPS ) ? TRUE : FALSE ) ;
 Curl_share_unlock ( data , CURL_LOCK_DATA_COOKIE ) ;
 }
 if ( co ) {
 struct Cookie * store = co ;
 while ( co ) {
 if ( co -> value ) {
 if ( 0 == count ) {
 result = Curl_add_bufferf ( req_buffer , "Cookie: " ) ;
 if ( result ) break ;
 }
 result = Curl_add_bufferf ( req_buffer , "%s%s=%s" , count ? ";
 " : "" , co -> name , co -> value ) ;
 if ( result ) break ;
 count ++ ;
 }
 co = co -> next ;
 }
 Curl_cookie_freelist ( store , FALSE ) ;
 }
 if ( addcookies && ! result ) {
 if ( ! count ) result = Curl_add_bufferf ( req_buffer , "Cookie: " ) ;
 if ( ! result ) {
 result = Curl_add_bufferf ( req_buffer , "%s%s" , count ? ";
 " : "" , addcookies ) ;
 count ++ ;
 }
 }
 if ( count && ! result ) result = Curl_add_buffer ( req_buffer , "\r\n" , 2 ) ;
 if ( result ) return result ;
 }

 if ( result ) return result ;
 result = Curl_add_custom_headers ( conn , FALSE , req_buffer ) ;
 if ( result ) return result ;
 http -> postdata = NULL ;
 Curl_pgrsSetUploadSize ( data , - 1 ) ;
 switch ( httpreq ) {
 case HTTPREQ_POST_FORM : if ( ! http -> sendit || conn -> bits . authneg ) {
 result = Curl_add_bufferf ( req_buffer , "Content-Length: 0\r\n\r\n" ) ;
 if ( result ) return result ;
 result = Curl_add_buffer_send ( req_buffer , conn , & data -> info . request_size , 0 , FIRSTSOCKET ) ;
 if ( result ) failf ( data , "Failed sending POST request" ) ;
 else Curl_setup_transfer ( conn , FIRSTSOCKET , - 1 , TRUE , & http -> readbytecount , - 1 , NULL ) ;
 break ;
 }
 if ( Curl_FormInit ( & http -> form , http -> sendit ) ) {
 failf ( data , "Internal HTTP POST error!" ) ;
 return CURLE_HTTP_POST_ERROR ;
 }
 http -> form . fread_func = data -> state . fread_func ;
 data -> state . fread_func = ( curl_read_callback ) Curl_FormReader ;
 data -> state . in = & http -> form ;
 http -> sending = HTTPSEND_BODY ;
 if ( ! data -> req . upload_chunky && ! Curl_checkheaders ( conn , "Content-Length:" ) ) {
 result = Curl_add_bufferf ( req_buffer , "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n" , http -> postsize ) ;
 if ( result ) return result ;
 }
 result = expect100 ( data , conn , req_buffer ) ;
 if ( result ) return result ;
 {
 char * contentType ;
 size_t linelength = 0 ;
 contentType = Curl_formpostheader ( ( void * ) & http -> form , & linelength ) ;
 if ( ! contentType ) {
 failf ( data , "Could not get Content-Type header line!" ) ;
 return CURLE_HTTP_POST_ERROR ;
 }
 result = Curl_add_buffer ( req_buffer , contentType , linelength ) ;
 if ( result ) return result ;
 }
 result = Curl_add_buffer ( req_buffer , "\r\n" , 2 ) ;
 if ( result ) return result ;
 Curl_pgrsSetUploadSize ( data , http -> postsize ) ;
 result = Curl_add_buffer_send ( req_buffer , conn , & data -> info . request_size , 0 , FIRSTSOCKET ) ;
 if ( result ) failf ( data , "Failed sending POST request" ) ;
 else Curl_setup_transfer ( conn , FIRSTSOCKET , - 1 , TRUE , & http -> readbytecount , FIRSTSOCKET , & http -> writebytecount ) ;
 if ( result ) {
 Curl_formclean ( & http -> sendit ) ;
 return result ;
 }
 result = Curl_convert_form ( data , http -> sendit ) ;
 if ( result ) {
 Curl_formclean ( & http -> sendit ) ;
 return result ;
 }
 break ;
 case HTTPREQ_PUT : if ( conn -> bits . authneg ) postsize = 0 ;
 else postsize = data -> state . infilesize ;
 if ( ( postsize != - 1 ) && ! data -> req . upload_chunky && ! Curl_checkheaders ( conn , "Content-Length:" ) ) {
 result = Curl_add_bufferf ( req_buffer , "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n" , postsize ) ;
 if ( result ) return result ;
 }
 if ( postsize != 0 ) {
 result = expect100 ( data , conn , req_buffer ) ;
 if ( result ) return result ;
 }
 result = Curl_add_buffer ( req_buffer , "\r\n" , 2 ) ;
 if ( result ) return result ;
 Curl_pgrsSetUploadSize ( data , postsize ) ;
 result = Curl_add_buffer_send ( req_buffer , conn , & data -> info . request_size , 0 , FIRSTSOCKET ) ;
 if ( result ) failf ( data , "Failed sending PUT request" ) ;
 else Curl_setup_transfer ( conn , FIRSTSOCKET , - 1 , TRUE , & http -> readbytecount , postsize ? FIRSTSOCKET : - 1 , postsize ? & http -> writebytecount : NULL ) ;
 if ( result ) return result ;
 break ;
 case HTTPREQ_POST : if ( conn -> bits . authneg ) postsize = 0 ;
 else {
 postsize = ( data -> state . infilesize != - 1 ) ? data -> state . infilesize : ( data -> set . postfields ? ( curl_off_t ) strlen ( data -> set . postfields ) : - 1 ) ;
 }
 if ( ( postsize != - 1 ) && ! data -> req . upload_chunky && ! Curl_checkheaders ( conn , "Content-Length:" ) ) {
 result = Curl_add_bufferf ( req_buffer , "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n" , postsize ) ;
 if ( result ) return result ;
 }
 if ( ! Curl_checkheaders ( conn , "Content-Type:" ) ) {
 result = Curl_add_bufferf ( req_buffer , "Content-Type: application/" "x-www-form-urlencoded\r\n" ) ;
 if ( result ) return result ;
 }
 ptr = Curl_checkheaders ( conn , "Expect:" ) ;
 if ( ptr ) {
 data -> state . expect100header = Curl_compareheader ( ptr , "Expect:" , "100-continue" ) ;
 }
 else if ( postsize > TINY_INITIAL_POST_SIZE || postsize < 0 ) {
 result = expect100 ( data , conn , req_buffer ) ;
 if ( result ) return result ;
 }
 else data -> state . expect100header = FALSE ;
 if ( data -> set . postfields ) {
 if ( conn -> httpversion != 20 && ! data -> state . expect100header && ( postsize < MAX_INITIAL_POST_SIZE ) ) {
 result = Curl_add_buffer ( req_buffer , "\r\n" , 2 ) ;
 if ( result ) return result ;
 if ( ! data -> req . upload_chunky ) {
 result = Curl_add_buffer ( req_buffer , data -> set . postfields , ( size_t ) postsize ) ;
 included_body = postsize ;
 }
 else {
 if ( postsize ) {
 result = Curl_add_bufferf ( req_buffer , "%x\r\n" , ( int ) postsize ) ;
 if ( ! result ) {
 result = Curl_add_buffer ( req_buffer , data -> set . postfields , ( size_t ) postsize ) ;
 if ( ! result ) result = Curl_add_buffer ( req_buffer , "\r\n" , 2 ) ;
 included_body = postsize + 2 ;
 }
 }
 if ( ! result ) result = Curl_add_buffer ( req_buffer , "\x30\x0d\x0a\x0d\x0a" , 5 ) ;
 included_body += 5 ;
 }
 if ( result ) return result ;
 Curl_pgrsSetUploadSize ( data , postsize ) ;
 }
 else {
 http -> postsize = postsize ;
 http -> postdata = data -> set . postfields ;
 http -> sending = HTTPSEND_BODY ;
 data -> state . fread_func = ( curl_read_callback ) readmoredata ;
 data -> state . in = ( void * ) conn ;
 Curl_pgrsSetUploadSize ( data , http -> postsize ) ;
 result = Curl_add_buffer ( req_buffer , "\r\n" , 2 ) ;
 if ( result ) return result ;
 }
 }
 else {
 result = Curl_add_buffer ( req_buffer , "\r\n" , 2 ) ;
 if ( result ) return result ;
 if ( data -> req . upload_chunky && conn -> bits . authneg ) {
 result = Curl_add_buffer ( req_buffer , "\x30\x0d\x0a\x0d\x0a" , 5 ) ;
 if ( result ) return result ;
 }
 else if ( data -> state . infilesize ) {
 Curl_pgrsSetUploadSize ( data , postsize ? postsize : - 1 ) ;
 if ( ! conn -> bits . authneg ) {
 http -> postdata = ( char * ) & http -> postdata ;
 http -> postsize = postsize ;
 }
 }
 }
 result = Curl_add_buffer_send ( req_buffer , conn , & data -> info . request_size , ( size_t ) included_body , FIRSTSOCKET ) ;
 if ( result ) failf ( data , "Failed sending HTTP POST request" ) ;
 else Curl_setup_transfer ( conn , FIRSTSOCKET , - 1 , TRUE , & http -> readbytecount , http -> postdata ? FIRSTSOCKET : - 1 , http -> postdata ? & http -> writebytecount : NULL ) ;
 break ;
 default : result = Curl_add_buffer ( req_buffer , "\r\n" , 2 ) ;
 if ( result ) return result ;
 result = Curl_add_buffer_send ( req_buffer , conn , & data -> info . request_size , 0 , FIRSTSOCKET ) ;
 if ( result ) failf ( data , "Failed sending HTTP request" ) ;
 else Curl_setup_transfer ( conn , FIRSTSOCKET , - 1 , TRUE , & http -> readbytecount , http -> postdata ? FIRSTSOCKET : - 1 , http -> postdata ? & http -> writebytecount : NULL ) ;
 }
 if ( result ) return result ;
 if ( http -> writebytecount ) {
 Curl_pgrsSetUploadCounter ( data , http -> writebytecount ) ;
 if ( Curl_pgrsUpdate ( conn ) ) result = CURLE_ABORTED_BY_CALLBACK ;
 if ( http -> writebytecount >= postsize ) {
 infof ( data , "upload completely sent off: %" CURL_FORMAT_CURL_OFF_T " out of %" CURL_FORMAT_CURL_OFF_T " bytes\n" , http -> writebytecount , postsize ) ;
 data -> req . upload_done = TRUE ;
 data -> req . keepon &= ~ KEEP_SEND ;
 data -> req . exp100 = EXP100_SEND_DATA ;
 }
 }
 if ( ( conn -> httpversion == 20 ) && data -> req . upload_chunky ) data -> req . upload_chunky = FALSE ;
 return result ;
 }