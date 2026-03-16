static gint64 steamdiscover_dissect_header ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , gint offset , gint bytes_left ) {
 gint len ;
 gint64 value ;
 gint64 msg_type = - 1 ;
 protobuf_desc_t pb = {
 tvb , offset , bytes_left }
 ;
 protobuf_tag_t tag = {
 0 , 0 , 0 }
 ;
 while ( protobuf_iter_next ( & pb , & tag ) ) {
 switch ( tag . field_number ) {
 case STEAMDISCOVER_FN_HEADER_CLIENTID : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_uint64 ( tree , hf_steam_ihs_discovery_header_clientid , pb . tvb , pb . offset , len , ( guint64 ) value ) ;
 break ;
 case STEAMDISCOVER_FN_HEADER_MSGTYPE : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 msg_type = value ;
 proto_tree_add_uint64 ( tree , hf_steam_ihs_discovery_header_msgtype , pb . tvb , pb . offset , len , ( guint64 ) value ) ;
 break ;
 case STEAMDISCOVER_FN_HEADER_INSTANCEID : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_uint64 ( tree , hf_steam_ihs_discovery_header_instanceid , pb . tvb , pb . offset , len , ( guint64 ) value ) ;
 break ;
 default : len = protobuf_dissect_unknown_field ( & pb , & tag , pinfo , tree , NULL ) ;
 break ;
 }
 protobuf_seek_forward ( & pb , len ) ;
 }
 return msg_type ;
 }