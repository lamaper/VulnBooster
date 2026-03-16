CURLcode Curl_http_done ( struct connectdata * conn , CURLcode status , bool premature ) {
 struct Curl_easy * data = conn -> data ;
 struct HTTP * http = data -> req . protop ;
 infof ( data , "Curl_http_done: called premature == %d\n" , premature ) ;
 Curl_unencode_cleanup ( conn ) ;

 if ( ( data -> req . httpcode != 401 ) && ( data -> req . httpcode != 407 ) && ! data -> set . connect_only ) streamclose ( conn , "Negotiate transfer completed" ) ;
 Curl_cleanup_negotiate ( data ) ;
 }

 conn -> seek_client = data -> set . seek_client ;
 if ( ! http ) return CURLE_OK ;
 if ( http -> send_buffer ) {
 Curl_add_buffer_free ( http -> send_buffer ) ;
 http -> send_buffer = NULL ;
 }
 Curl_http2_done ( conn , premature ) ;
 if ( HTTPREQ_POST_FORM == data -> set . httpreq ) {
 data -> req . bytecount = http -> readbytecount + http -> writebytecount ;
 Curl_formclean ( & http -> sendit ) ;
 if ( http -> form . fp ) {
 fclose ( http -> form . fp ) ;
 http -> form . fp = NULL ;
 }
 }
 else if ( HTTPREQ_PUT == data -> set . httpreq ) data -> req . bytecount = http -> readbytecount + http -> writebytecount ;
 if ( status ) return status ;
 if ( ! premature && ! conn -> bits . retry && ! data -> set . connect_only && ( http -> readbytecount + data -> req . headerbytecount - data -> req . deductheadercount ) <= 0 ) {
 failf ( data , "Empty reply from server" ) ;
 return CURLE_GOT_NOTHING ;
 }
 return CURLE_OK ;
 }