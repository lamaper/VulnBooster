int evbuffer_expand ( struct evbuffer * buf , size_t datlen ) {
 size_t need = buf -> misalign + buf -> off + datlen ;
 if ( buf -> totallen >= need ) return ( 0 ) ;
 if ( buf -> misalign >= datlen ) {
 evbuffer_align ( buf ) ;
 }
 else {
 void * newbuf ;
 size_t length = buf -> totallen ;
 if ( length < 256 ) length = 256 ;
 while ( length < need ) length <<= 1 ;
 if ( buf -> orig_buffer != buf -> buffer ) evbuffer_align ( buf ) ;
 if ( ( newbuf = realloc ( buf -> buffer , length ) ) == NULL ) return ( - 1 ) ;
 buf -> orig_buffer = buf -> buffer = newbuf ;
 buf -> totallen = length ;
 }
 return ( 0 ) ;
 }