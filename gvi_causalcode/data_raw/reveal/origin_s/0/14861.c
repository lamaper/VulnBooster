static void vvalue_strbuf_append_ui8 ( wmem_strbuf_t * strbuf , void * ptr ) {
 guint64 ui8 = * ( guint64 * ) ptr ;
 wmem_strbuf_append_printf ( strbuf , "%" G_GINT64_MODIFIER "u" , ui8 ) ;
 }