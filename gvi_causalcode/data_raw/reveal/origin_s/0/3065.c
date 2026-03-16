static void test_length ( header_field_info * hfinfo , tvbuff_t * tvb , gint start , gint length ) {
 gint size = length ;
 if ( ! tvb ) return ;
 if ( hfinfo -> type == FT_STRINGZ ) {
 if ( length == - 1 ) size = 0 ;
 }
 tvb_ensure_bytes_exist ( tvb , start , size ) ;
 }