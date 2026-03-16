static const gchar * get_pcp_features_to_string ( guint16 feature_flags ) {
 const value_string * flag_under_test ;
 wmem_strbuf_t * string_buffer ;
 gsize string_length ;
 string_buffer = wmem_strbuf_new ( wmem_packet_scope ( ) , "" ) ;
 flag_under_test = & pcp_feature_flags [ 0 ] ;
 while ( flag_under_test -> value ) {
 if ( feature_flags & flag_under_test -> value ) {
 wmem_strbuf_append_printf ( string_buffer , "%s, " , flag_under_test -> strptr ) ;
 }
 flag_under_test ++ ;
 }
 string_length = wmem_strbuf_get_len ( string_buffer ) ;
 if ( string_length > 2 ) {
 wmem_strbuf_truncate ( string_buffer , string_length - 2 ) ;
 }
 return wmem_strbuf_get_str ( string_buffer ) ;
 }