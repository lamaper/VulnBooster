static gint protobuf_verify_wiretype ( protobuf_desc_t * pb , protobuf_tag_t * tag , packet_info * pinfo , proto_tree * tree , guint8 expected_wire_type ) {
 gint len ;
 gint64 len_prefix ;
 proto_item * ti = NULL ;
 if ( expected_wire_type == tag -> wire_type ) {
 if ( expected_wire_type == PROTOBUF_WIRETYPE_LENGTHDELIMITED ) {
 len_prefix = get_varint64 ( pb -> tvb , pb -> offset , pb -> bytes_left , & len ) ;
 if ( len_prefix < 0 || len_prefix > G_MAXINT ) {
 ti = proto_tree_add_item ( tree , hf_steam_ihs_discovery_unknown_data , pb -> tvb , pb -> offset + len , pb -> bytes_left - len , ENC_NA ) ;
 expert_add_info_format ( pinfo , ti , & ei_steam_ihs_discovery_invalid_length , "Length-delimited field %" G_GUINT64_FORMAT " has length prefix %" G_GINT64_FORMAT " outside valid range (0 <= x <= G_MAXINT)." , tag -> field_number , len_prefix ) ;
 return pb -> bytes_left ;
 }
 else if ( ( ( gint ) len_prefix ) > ( pb -> bytes_left - len ) ) {
 ti = proto_tree_add_item ( tree , hf_steam_ihs_discovery_unknown_data , pb -> tvb , pb -> offset + len , pb -> bytes_left - len , ENC_NA ) ;
 expert_add_info_format ( pinfo , ti , & ei_steam_ihs_discovery_invalid_length , "Length-delimited field %" G_GUINT64_FORMAT " has length prefix %" G_GINT64_FORMAT ", but buffer is only %d bytes long." , tag -> field_number , len_prefix , ( pb -> bytes_left - len ) ) ;
 return pb -> bytes_left ;
 }
 }
 return 0 ;
 }
 len = protobuf_dissect_unknown_field ( pb , tag , pinfo , tree , & ti ) ;
 expert_add_info_format ( pinfo , ti , & ei_steam_ihs_discovery_invalid_wiretype , "Expected wiretype %d (%s) for field %" G_GUINT64_FORMAT ", but got %d (%s) instead." , expected_wire_type , protobuf_get_wiretype_name ( expected_wire_type ) , tag -> field_number , tag -> wire_type , protobuf_get_wiretype_name ( tag -> wire_type ) ) ;
 return len ;
 }