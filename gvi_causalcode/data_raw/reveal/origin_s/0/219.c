static int evhttp_append_to_last_header ( struct evkeyvalq * headers , const char * line ) {
 struct evkeyval * header = TAILQ_LAST ( headers , evkeyvalq ) ;
 char * newval ;
 size_t old_len , line_len ;
 if ( header == NULL ) return ( - 1 ) ;
 old_len = strlen ( header -> value ) ;
 line_len = strlen ( line ) ;
 newval = realloc ( header -> value , old_len + line_len + 1 ) ;
 if ( newval == NULL ) return ( - 1 ) ;
 memcpy ( newval + old_len , line , line_len + 1 ) ;
 header -> value = newval ;
 return ( 0 ) ;
 }