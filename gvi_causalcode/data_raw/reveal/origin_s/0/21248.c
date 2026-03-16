static void config_request_output ( const char * key , const char * value , enum config_key_type type ATTR_UNUSED , void * context ) {
 struct ostream * output = context ;
 const char * p ;
 o_stream_nsend_str ( output , key ) ;
 o_stream_nsend_str ( output , "=" ) ;
 while ( ( p = strchr ( value , '\n' ) ) != NULL ) {
 o_stream_nsend ( output , value , p - value ) ;
 o_stream_nsend ( output , SETTING_STREAM_LF_CHAR , 1 ) ;
 value = p + 1 ;
 }
 o_stream_nsend_str ( output , value ) ;
 o_stream_nsend_str ( output , "\n" ) ;
 }