int dissect_ber_integer64 ( gboolean implicit_tag , asn1_ctx_t * actx , proto_tree * tree , tvbuff_t * tvb , int offset , gint hf_id , gint64 * value ) {
 gint8 ber_class ;
 gboolean pc ;
 gint32 tag ;
 guint32 len ;
 gint64 val ;
 guint32 i ;
 gboolean used_too_many_bytes = FALSE ;
 guint8 first ;

 const char * name ;
 header_field_info * hfinfo ;
 if ( hf_id >= 0 ) {
 hfinfo = proto_registrar_get_nth ( hf_id ) ;
 name = hfinfo -> name ;
 }
 else {
 name = "unnamed" ;
 }
 if ( tvb_reported_length_remaining ( tvb , offset ) > 3 ) {
 printf ( "INTEGERnew dissect_ber_integer(%s) entered implicit_tag:%d offset:%d len:%d %02x:%02x:%02x\n" , name , implicit_tag , offset , tvb_reported_length_remaining ( tvb , offset ) , tvb_get_guint8 ( tvb , offset ) , tvb_get_guint8 ( tvb , offset + 1 ) , tvb_get_guint8 ( tvb , offset + 2 ) ) ;
 }
 else {
 printf ( "INTEGERnew dissect_ber_integer(%s) entered implicit_tag:%d \n" , name , implicit_tag ) ;
 }
 }

 * value = 0 ;
 }
 if ( ! implicit_tag ) {
 offset = dissect_ber_identifier ( actx -> pinfo , tree , tvb , offset , & ber_class , & pc , & tag ) ;
 offset = dissect_ber_length ( actx -> pinfo , tree , tvb , offset , & len , NULL ) ;
 }
 else {
 gint32 remaining = tvb_reported_length_remaining ( tvb , offset ) ;
 len = remaining > 0 ? remaining : 0 ;
 }
 first = tvb_get_guint8 ( tvb , offset ) ;
 if ( ( len > 9 ) || ( ( len == 9 ) && ( first != 0 ) ) ) {
 if ( hf_id >= 0 ) {
 header_field_info * hfinfo = proto_registrar_get_nth ( hf_id ) ;
 if ( hfinfo -> type != FT_BYTES ) hf_id = hf_ber_64bit_uint_as_bytes ;
 proto_tree_add_bytes_format ( tree , hf_id , tvb , offset , len , NULL , "%s: 0x%s" , hfinfo -> name , tvb_bytes_to_str ( wmem_packet_scope ( ) , tvb , offset , len ) ) ;
 }
 offset += len ;
 return offset ;
 }
 val = 0 ;
 if ( len > 0 ) {
 enum ftenum type = FT_INT32 ;
 if ( hf_id >= 0 ) {
 type = proto_registrar_get_ftype ( hf_id ) ;
 }
 if ( first & 0x80 && IS_FT_INT ( type ) ) {
 val = - 1 ;
 }
 if ( ( len > 1 ) && decode_warning_leading_zero_bits ) {
 guint8 second = tvb_get_guint8 ( tvb , offset + 1 ) ;
 if ( ( ( first == 0x00 ) && ( ( second & 0x80 ) == 0 ) ) || ( ( first == 0xff ) && ( ( second & 0x80 ) != 0 ) ) ) {
 used_too_many_bytes = TRUE ;
 }
 }
 for ( i = 0 ;
 i < len ;
 i ++ ) {
 val = ( ( guint64 ) val << 8 ) | tvb_get_guint8 ( tvb , offset ) ;
 offset ++ ;
 }
 }
 actx -> created_item = NULL ;
 if ( hf_id >= 0 ) {
 if ( ( len < 1 ) || ( len > 9 ) || ( ( len == 9 ) && ( first != 0 ) ) ) {
 proto_item * pi = proto_tree_add_string_format_value ( tree , hf_ber_error , tvb , offset - len , len , "invalid length" , "Can't handle integer length: %u" , len ) ;
 expert_add_info_format ( actx -> pinfo , pi , & ei_ber_error_length , "BER Error: Illegal integer length: %u" , len ) ;
 }
 else {
 header_field_info * hfi ;
 hfi = proto_registrar_get_nth ( hf_id ) ;
 switch ( hfi -> type ) {
 case FT_UINT8 : case FT_UINT16 : case FT_UINT24 : case FT_UINT32 : actx -> created_item = proto_tree_add_uint ( tree , hf_id , tvb , offset - len , len , ( guint32 ) val ) ;
 break ;
 case FT_INT8 : case FT_INT16 : case FT_INT24 : case FT_INT32 : actx -> created_item = proto_tree_add_int ( tree , hf_id , tvb , offset - len , len , ( gint32 ) val ) ;
 break ;
 case FT_INT64 : actx -> created_item = proto_tree_add_int64 ( tree , hf_id , tvb , offset - len , len , val ) ;
 break ;
 case FT_UINT64 : actx -> created_item = proto_tree_add_uint64 ( tree , hf_id , tvb , offset - len , len , ( guint64 ) val ) ;
 break ;
 default : DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 }
 if ( used_too_many_bytes ) {
 expert_add_info_format ( actx -> pinfo , actx -> created_item , & ei_ber_value_too_many_bytes , "Value is encoded with too many bytes(9 leading zero or one bits), hf_abbr: %s" , hfi -> abbrev ) ;
 }
 }
 }
 if ( value ) {
 * value = val ;
 }
 return offset ;
 }