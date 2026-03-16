static void steamdiscover_dissect_body_discovery ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , gint offset , gint bytes_left ) {
 gint len ;
 gint64 value ;
 protobuf_desc_t pb = {
 tvb , offset , bytes_left }
 ;
 protobuf_tag_t tag = {
 0 , 0 , 0 }
 ;
 while ( protobuf_iter_next ( & pb , & tag ) ) {
 switch ( tag . field_number ) {
 case STEAMDISCOVER_FN_DISCOVERY_SEQNUM : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_uint ( tree , hf_steam_ihs_discovery_body_discovery_seqnum , pb . tvb , pb . offset , len , ( guint32 ) value ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " Seq=%" G_GUINT32_FORMAT , ( guint32 ) value ) ;
 break ;
 case STEAMDISCOVER_FN_DISCOVERY_CLIENTIDS : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_uint64 ( tree , hf_steam_ihs_discovery_body_discovery_clientids , pb . tvb , pb . offset , len , value ) ;
 break ;
 default : len = protobuf_dissect_unknown_field ( & pb , & tag , pinfo , tree , NULL ) ;
 break ;
 }
 protobuf_seek_forward ( & pb , len ) ;
 }
 }