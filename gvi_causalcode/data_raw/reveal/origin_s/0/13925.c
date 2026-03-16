static void vvalue_strbuf_append_i4 ( wmem_strbuf_t * strbuf , void * ptr ) {
 gint32 i4 = * ( gint32 * ) ptr ;
 wmem_strbuf_append_printf ( strbuf , "%d" , i4 ) ;
 }