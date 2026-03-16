static int header_is_transfer_encoding ( ngx_str_t * key ) {
 return key -> len == sizeof ( "transfer-encoding" ) - 1 && ngx_tolower ( key -> data [ 0 ] ) == ( u_char ) 't' && ngx_tolower ( key -> data [ sizeof ( "transfer-encoding" ) - 2 ] ) == ( u_char ) 'g' && ngx_strncasecmp ( key -> data + 1 , ( u_char * ) "ransfer-encodin" , sizeof ( "ransfer-encodin" ) - 1 ) == 0 ;
 }