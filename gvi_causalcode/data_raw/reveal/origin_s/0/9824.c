static void vvalue_strbuf_append_ui1 ( wmem_strbuf_t * strbuf , void * ptr ) {
 guint8 ui1 = * ( guint8 * ) ptr ;
 wmem_strbuf_append_printf ( strbuf , "%u" , ( unsigned ) ui1 ) ;
 }