static void vvalue_strbuf_append_ui2 ( wmem_strbuf_t * strbuf , void * ptr ) {
 guint16 ui2 = * ( guint16 * ) ptr ;
 wmem_strbuf_append_printf ( strbuf , "%u" , ( unsigned ) ui2 ) ;
 }