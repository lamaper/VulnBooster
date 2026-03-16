int evbuffer_expand ( struct evbuffer * buf , size_t datlen ) {
 size_t used = buf -> misalign + buf -> off ;
 assert ( buf -> totallen >= used ) ;
 if ( buf -> totallen - used >= datlen ) return ( 0 ) ;
 if ( datlen > SIZE_MAX - buf -> off ) return ( - 1 ) ;
 if ( buf -> totallen - buf -> off >= datlen ) {
 evbuffer_align ( buf ) ;
 }
 else {
 void * newbuf ;
 size_t length = buf -> totallen ;
 size_t need = buf -> off + datlen ;
 if ( length < 256 ) length = 256 ;
 if ( need < SIZE_MAX / 2 ) {
 while ( length < need ) {
 length <<= 1 ;
 }
 }
 else {
 length = need ;
 }
 if ( buf -> orig_buffer != buf -> buffer ) evbuffer_align ( buf ) ;
 if ( ( newbuf = realloc ( buf -> buffer , length ) ) == NULL ) return ( - 1 ) ;
 buf -> orig_buffer = buf -> buffer = newbuf ;
 buf -> totallen = length ;
 }
 return ( 0 ) ;
 }