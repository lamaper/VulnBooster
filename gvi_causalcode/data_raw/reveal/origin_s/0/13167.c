static struct evhttp_connection * evhttp_get_request_connection ( struct evhttp * http , int fd , struct sockaddr * sa , socklen_t salen ) {
 struct evhttp_connection * evcon ;
 char * hostname = NULL , * portname = NULL ;
 name_from_addr ( sa , salen , & hostname , & portname ) ;
 if ( hostname == NULL || portname == NULL ) {
 if ( hostname ) free ( hostname ) ;
 if ( portname ) free ( portname ) ;
 return ( NULL ) ;
 }
 event_debug ( ( "%s: new request from %s:%s on %d\n" , __func__ , hostname , portname , fd ) ) ;
 evcon = evhttp_connection_new ( hostname , atoi ( portname ) ) ;
 free ( hostname ) ;
 free ( portname ) ;
 if ( evcon == NULL ) return ( NULL ) ;
 evhttp_connection_set_base ( evcon , http -> base ) ;
 evcon -> flags |= EVHTTP_CON_INCOMING ;
 evcon -> state = EVCON_READING_FIRSTLINE ;
 evcon -> fd = fd ;
 return ( evcon ) ;
 }