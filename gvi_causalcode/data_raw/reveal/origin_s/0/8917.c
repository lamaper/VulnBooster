static void vvalue_strbuf_append_str ( wmem_strbuf_t * strbuf , void * ptr ) {
 struct data_str * str = ( struct data_str * ) ptr ;
 wmem_strbuf_append_printf ( strbuf , "\"%s\"" , str -> str ) ;
 }