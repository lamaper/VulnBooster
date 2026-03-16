static void vvalue_strbuf_append_ui4 ( wmem_strbuf_t * strbuf , void * ptr ) {
 guint32 ui4 = * ( guint32 * ) ptr ;
 wmem_strbuf_append_printf ( strbuf , "%d" , ui4 ) ;
 }