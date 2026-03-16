static void vvalue_strbuf_append_r8 ( wmem_strbuf_t * strbuf , void * ptr ) {
 double r8 = * ( double * ) ptr ;
 wmem_strbuf_append_printf ( strbuf , "%g" , r8 ) ;
 }