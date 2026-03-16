static void steamdiscover_dissect_body_streamingcancelrequest ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , gint offset , gint bytes_left ) {
 guint len ;
 gint64 value ;
 protobuf_desc_t pb = {
 tvb , offset , bytes_left }
 ;
 protobuf_tag_t tag = {
 0 , 0 , 0 }
 ;
 while ( protobuf_iter_next ( & pb , & tag ) ) {
 switch ( tag . field_number ) {
 case STEAMDISCOVER_FN_STREAMINGCANCELREQUEST_REQUESTID : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_uint ( tree , hf_steam_ihs_discovery_body_streamingcancelrequest_requestid , pb . tvb , pb . offset , len , ( guint32 ) value ) ;
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "%s, ID=%08x" , hf_steam_ihs_discovery_header_msgtype_strings [ STEAMDISCOVER_MSGTYPE_DEVICESTREAMINGCANCELREQUEST ] . strptr , ( guint32 ) value ) ;
 break ;
 default : len = protobuf_dissect_unknown_field ( & pb , & tag , pinfo , tree , NULL ) ;
 break ;
 }
 protobuf_seek_forward ( & pb , len ) ;
 }
 }