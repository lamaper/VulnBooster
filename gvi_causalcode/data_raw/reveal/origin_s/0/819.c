static size_t readmoredata ( char * buffer , size_t size , size_t nitems , void * userp ) {
 struct connectdata * conn = ( struct connectdata * ) userp ;
 struct HTTP * http = conn -> data -> req . protop ;
 size_t fullsize = size * nitems ;
 if ( ! http -> postsize ) return 0 ;
 conn -> data -> req . forbidchunk = ( http -> sending == HTTPSEND_REQUEST ) ? TRUE : FALSE ;
 if ( http -> postsize <= ( curl_off_t ) fullsize ) {
 memcpy ( buffer , http -> postdata , ( size_t ) http -> postsize ) ;
 fullsize = ( size_t ) http -> postsize ;
 if ( http -> backup . postsize ) {
 http -> postdata = http -> backup . postdata ;
 http -> postsize = http -> backup . postsize ;
 conn -> data -> state . fread_func = http -> backup . fread_func ;
 conn -> data -> state . in = http -> backup . fread_in ;
 http -> sending ++ ;
 http -> backup . postsize = 0 ;
 }
 else http -> postsize = 0 ;
 return fullsize ;
 }
 memcpy ( buffer , http -> postdata , fullsize ) ;
 http -> postdata += fullsize ;
 http -> postsize -= fullsize ;
 return fullsize ;
 }