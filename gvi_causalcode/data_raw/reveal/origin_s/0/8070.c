void evhttp_set_cb ( struct evhttp * http , const char * uri , void ( * cb ) ( struct evhttp_request * , void * ) , void * cbarg ) {
 struct evhttp_cb * http_cb ;
 if ( ( http_cb = calloc ( 1 , sizeof ( struct evhttp_cb ) ) ) == NULL ) event_err ( 1 , "%s: calloc" , __func__ ) ;
 http_cb -> what = strdup ( uri ) ;
 http_cb -> cb = cb ;
 http_cb -> cbarg = cbarg ;
 TAILQ_INSERT_TAIL ( & http -> callbacks , http_cb , next ) ;
 }