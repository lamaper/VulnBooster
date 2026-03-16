static void vvalue_strbuf_append_i1 ( wmem_strbuf_t * strbuf , void * ptr ) {
 gint8 i1 = * ( gint8 * ) ptr ;
 wmem_strbuf_append_printf ( strbuf , "%d" , ( int ) i1 ) ;
 }