u_char * evbuffer_find ( struct evbuffer * buffer , const u_char * what , size_t len ) {
 u_char * search = buffer -> buffer , * end = search + buffer -> off ;
 u_char * p ;
 while ( search < end && ( p = memchr ( search , * what , end - search ) ) != NULL ) {
 if ( p + len > end ) break ;
 if ( memcmp ( p , what , len ) == 0 ) return ( p ) ;
 search = p + 1 ;
 }
 return ( NULL ) ;
 }