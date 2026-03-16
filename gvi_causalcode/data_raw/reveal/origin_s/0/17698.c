static gint protobuf_dissect_unknown_field ( protobuf_desc_t * pb , protobuf_tag_t * tag , packet_info * pinfo , proto_tree * tree , proto_item * * tiptr ) {
 gint len ;
 gint64 value ;
 proto_item * ti ;
 switch ( tag -> wire_type ) {
 case PROTOBUF_WIRETYPE_VARINT : value = get_varint64 ( pb -> tvb , pb -> offset , pb -> bytes_left , & len ) ;
 ti = proto_tree_add_uint64 ( tree , hf_steam_ihs_discovery_unknown_number , pb -> tvb , pb -> offset , len , ( guint64 ) value ) ;
 expert_add_info_format ( pinfo , ti , & ei_steam_ihs_discovery_unknown_number , "Unknown numeric protobuf field (wire type %d = %s)" , tag -> wire_type , protobuf_get_wiretype_name ( tag -> wire_type ) ) ;
 break ;
 case PROTOBUF_WIRETYPE_64BIT : len = 8 ;
 ti = proto_tree_add_item ( tree , hf_steam_ihs_discovery_unknown_number , pb -> tvb , pb -> offset + len , len , ENC_LITTLE_ENDIAN ) ;
 expert_add_info_format ( pinfo , ti , & ei_steam_ihs_discovery_unknown_number , "Unknown numeric protobuf field (wire type %d = %s)" , tag -> wire_type , protobuf_get_wiretype_name ( tag -> wire_type ) ) ;
 break ;
 case PROTOBUF_WIRETYPE_LENGTHDELIMITED : value = get_varint64 ( pb -> tvb , pb -> offset , pb -> bytes_left , & len ) ;
 if ( ( guint64 ) value > ( guint64 ) ( pb -> bytes_left - len ) ) {
 ti = proto_tree_add_item ( tree , hf_steam_ihs_discovery_unknown_data , pb -> tvb , pb -> offset + len , pb -> bytes_left - len , ENC_NA ) ;
 expert_add_info_format ( pinfo , ti , & ei_steam_ihs_discovery_invalid_length , "Length-delimited field %" G_GUINT64_FORMAT " has length prefix %" G_GUINT64_FORMAT ", but buffer is only %d bytes long." , tag -> field_number , ( guint64 ) value , ( pb -> bytes_left - len ) ) ;
 len = pb -> bytes_left ;
 }
 else {
 ti = proto_tree_add_item ( tree , hf_steam_ihs_discovery_unknown_data , pb -> tvb , pb -> offset + len , ( gint ) value , ENC_NA ) ;
 len += ( gint ) value ;
 }
 expert_add_info ( pinfo , ti , & ei_steam_ihs_discovery_unknown_lengthdelimited ) ;
 break ;
 case PROTOBUF_WIRETYPE_32BIT : len = 4 ;
 ti = proto_tree_add_item ( tree , hf_steam_ihs_discovery_unknown_number , pb -> tvb , pb -> offset + len , len , ENC_LITTLE_ENDIAN ) ;
 expert_add_info_format ( pinfo , ti , & ei_steam_ihs_discovery_unknown_number , "Unknown numeric protobuf field (wire type %d = %s)" , tag -> wire_type , protobuf_get_wiretype_name ( tag -> wire_type ) ) ;
 break ;
 default : len = pb -> bytes_left ;
 ti = proto_tree_add_item ( tree , hf_steam_ihs_discovery_unknown_data , pb -> tvb , pb -> offset , len , ENC_NA ) ;
 expert_add_info ( pinfo , ti , & ei_steam_ihs_discovery_unknown_data ) ;
 break ;
 }
 if ( tiptr != NULL ) {
 * tiptr = ti ;
 }
 return len ;
 }