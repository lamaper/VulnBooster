static void vvalue_strbuf_append_blob ( wmem_strbuf_t * strbuf , void * ptr ) {
 struct data_blob * blob = ( struct data_blob * ) ptr ;
 wmem_strbuf_append_printf ( strbuf , "size: %d" , ( int ) blob -> size ) ;
 }