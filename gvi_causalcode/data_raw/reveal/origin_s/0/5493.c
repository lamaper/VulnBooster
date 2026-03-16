static const char * qio_channel_websock_find_header ( QIOChannelWebsockHTTPHeader * hdrs , size_t nhdrs , const char * name ) {
 size_t i ;
 for ( i = 0 ;
 i < nhdrs ;
 i ++ ) {
 if ( g_str_equal ( hdrs [ i ] . name , name ) ) {
 return hdrs [ i ] . value ;
 }
 }
 return NULL ;
 }