static void vvalue_strbuf_append_i8 ( wmem_strbuf_t * strbuf , void * ptr ) {
 gint64 i8 = * ( gint64 * ) ptr ;
 wmem_strbuf_append_printf ( strbuf , "%" G_GINT64_MODIFIER "d" , i8 ) ;
 }