static const char * str_CBaseStorageVariant ( struct CBaseStorageVariant * value , gboolean print_type ) {
 wmem_strbuf_t * strbuf = wmem_strbuf_new ( wmem_packet_scope ( ) , "" ) ;
 if ( value == NULL ) {
 return "<NULL>" ;
 }
 if ( value -> type == NULL ) {
 return "<??" "?>" ;
 }
 if ( print_type ) {
 wmem_strbuf_append ( strbuf , value -> type -> str ) ;
 if ( value -> vType & 0xFF00 ) {
 wmem_strbuf_append_printf ( strbuf , "[%d]" , value -> vValue . vt_vector . len ) ;
 }
 wmem_strbuf_append ( strbuf , ": " ) ;
 }
 switch ( value -> vType & 0xFF00 ) {
 case 0 : value -> type -> strbuf_append ( strbuf , & value -> vValue ) ;
 break ;
 case VT_ARRAY : vvalue_strbuf_append_vector ( strbuf , value -> vValue . vt_array . vData , value -> type ) ;
 break ;
 case VT_VECTOR : vvalue_strbuf_append_vector ( strbuf , value -> vValue . vt_vector , value -> type ) ;
 break ;
 default : wmem_strbuf_append ( strbuf , "Invalid" ) ;
 }
 return wmem_strbuf_get_str ( strbuf ) ;
 }