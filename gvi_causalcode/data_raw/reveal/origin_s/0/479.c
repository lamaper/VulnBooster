static void vvalue_strbuf_append_i2 ( wmem_strbuf_t * strbuf , void * ptr ) {
 gint16 i2 = * ( gint16 * ) ptr ;
 wmem_strbuf_append_printf ( strbuf , "%d" , ( int ) i2 ) ;
 }