static void vvalue_strbuf_append_bool ( wmem_strbuf_t * strbuf , void * ptr ) {
 guint16 val = * ( guint * ) ptr ;
 switch ( val ) {
 case 0 : wmem_strbuf_append ( strbuf , "False" ) ;
 break ;
 case 0xffff : wmem_strbuf_append ( strbuf , "True" ) ;
 break ;
 default : wmem_strbuf_append_printf ( strbuf , "Invalid (0x%4x)" , val ) ;
 }
 }