static void vvalue_strbuf_append_r4 ( wmem_strbuf_t * strbuf , void * ptr ) {
 float r4 = * ( float * ) ptr ;
 wmem_strbuf_append_printf ( strbuf , "%g" , ( double ) r4 ) ;
 }