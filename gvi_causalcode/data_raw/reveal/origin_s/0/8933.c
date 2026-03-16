static CURLcode dict_do ( struct connectdata * conn , bool * done ) {
 char * word ;
 char * eword ;
 char * ppath ;
 char * database = NULL ;
 char * strategy = NULL ;
 char * nthdef = NULL ;
 CURLcode result = CURLE_OK ;
 struct Curl_easy * data = conn -> data ;
 curl_socket_t sockfd = conn -> sock [ FIRSTSOCKET ] ;
 char * path = data -> state . path ;
 curl_off_t * bytecount = & data -> req . bytecount ;
 * done = TRUE ;
 if ( conn -> bits . user_passwd ) {
 }
 if ( Curl_raw_nequal ( path , DICT_MATCH , sizeof ( DICT_MATCH ) - 1 ) || Curl_raw_nequal ( path , DICT_MATCH2 , sizeof ( DICT_MATCH2 ) - 1 ) || Curl_raw_nequal ( path , DICT_MATCH3 , sizeof ( DICT_MATCH3 ) - 1 ) ) {
 word = strchr ( path , ':' ) ;
 if ( word ) {
 word ++ ;
 database = strchr ( word , ':' ) ;
 if ( database ) {
 * database ++ = ( char ) 0 ;
 strategy = strchr ( database , ':' ) ;
 if ( strategy ) {
 * strategy ++ = ( char ) 0 ;
 nthdef = strchr ( strategy , ':' ) ;
 if ( nthdef ) {
 * nthdef = ( char ) 0 ;
 }
 }
 }
 }
 if ( ( word == NULL ) || ( * word == ( char ) 0 ) ) {
 infof ( data , "lookup word is missing\n" ) ;
 word = ( char * ) "default" ;
 }
 if ( ( database == NULL ) || ( * database == ( char ) 0 ) ) {
 database = ( char * ) "!" ;
 }
 if ( ( strategy == NULL ) || ( * strategy == ( char ) 0 ) ) {
 strategy = ( char * ) "." ;
 }
 eword = unescape_word ( data , word ) ;
 if ( ! eword ) return CURLE_OUT_OF_MEMORY ;
 result = Curl_sendf ( sockfd , conn , "CLIENT " LIBCURL_NAME " " LIBCURL_VERSION "\r\n" "MATCH " "%s " "%s " "%s\r\n" "QUIT\r\n" , database , strategy , eword ) ;
 free ( eword ) ;
 if ( result ) {
 failf ( data , "Failed sending DICT request" ) ;
 return result ;
 }
 Curl_setup_transfer ( conn , FIRSTSOCKET , - 1 , FALSE , bytecount , - 1 , NULL ) ;
 }
 else if ( Curl_raw_nequal ( path , DICT_DEFINE , sizeof ( DICT_DEFINE ) - 1 ) || Curl_raw_nequal ( path , DICT_DEFINE2 , sizeof ( DICT_DEFINE2 ) - 1 ) || Curl_raw_nequal ( path , DICT_DEFINE3 , sizeof ( DICT_DEFINE3 ) - 1 ) ) {
 word = strchr ( path , ':' ) ;
 if ( word ) {
 word ++ ;
 database = strchr ( word , ':' ) ;
 if ( database ) {
 * database ++ = ( char ) 0 ;
 nthdef = strchr ( database , ':' ) ;
 if ( nthdef ) {
 * nthdef = ( char ) 0 ;
 }
 }
 }
 if ( ( word == NULL ) || ( * word == ( char ) 0 ) ) {
 infof ( data , "lookup word is missing\n" ) ;
 word = ( char * ) "default" ;
 }
 if ( ( database == NULL ) || ( * database == ( char ) 0 ) ) {
 database = ( char * ) "!" ;
 }
 eword = unescape_word ( data , word ) ;
 if ( ! eword ) return CURLE_OUT_OF_MEMORY ;
 result = Curl_sendf ( sockfd , conn , "CLIENT " LIBCURL_NAME " " LIBCURL_VERSION "\r\n" "DEFINE " "%s " "%s\r\n" "QUIT\r\n" , database , eword ) ;
 free ( eword ) ;
 if ( result ) {
 failf ( data , "Failed sending DICT request" ) ;
 return result ;
 }
 Curl_setup_transfer ( conn , FIRSTSOCKET , - 1 , FALSE , bytecount , - 1 , NULL ) ;
 }
 else {
 ppath = strchr ( path , '/' ) ;
 if ( ppath ) {
 int i ;
 ppath ++ ;
 for ( i = 0 ;
 ppath [ i ] ;
 i ++ ) {
 if ( ppath [ i ] == ':' ) ppath [ i ] = ' ' ;
 }
 result = Curl_sendf ( sockfd , conn , "CLIENT " LIBCURL_NAME " " LIBCURL_VERSION "\r\n" "%s\r\n" "QUIT\r\n" , ppath ) ;
 if ( result ) {
 failf ( data , "Failed sending DICT request" ) ;
 return result ;
 }
 Curl_setup_transfer ( conn , FIRSTSOCKET , - 1 , FALSE , bytecount , - 1 , NULL ) ;
 }
 }
 return CURLE_OK ;
 }