static void steamdiscover_dissect_body_streamingresponse ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , gint offset , gint bytes_left ) {
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
 case STEAMDISCOVER_FN_STREAMINGRESPONSE_REQUESTID : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_uint ( tree , hf_steam_ihs_discovery_body_streamingresponse_requestid , pb . tvb , pb . offset , len , ( guint32 ) value ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " ID=%08x" , ( guint32 ) value ) ;
 break ;
 case STEAMDISCOVER_FN_STREAMINGRESPONSE_RESULT : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_uint64 ( tree , hf_steam_ihs_discovery_body_streamingresponse_result , pb . tvb , pb . offset , len , ( guint64 ) value ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " Result=%" G_GUINT64_FORMAT "(%s)" , ( guint64 ) value , val64_to_str_const ( ( guint64 ) value , hf_steam_ihs_discovery_body_streamingresponse_result_strings , "Unknown" ) ) ;
 break ;
 case STEAMDISCOVER_FN_STREAMINGRESPONSE_PORT : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_uint ( tree , hf_steam_ihs_discovery_body_streamingresponse_port , pb . tvb , pb . offset , len , ( guint32 ) value ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " Port=%" G_GUINT32_FORMAT , ( guint32 ) value ) ;
 break ;
 case STEAMDISCOVER_FN_STREAMINGRESPONSE_ENCRYPTEDSESSIONKEY : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_LENGTHDELIMITED ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_item ( tree , hf_steam_ihs_discovery_body_streamingresponse_encryptedsessionkey , pb . tvb , pb . offset + len , ( gint ) value , ENC_NA ) ;
 len += ( gint ) value ;
 break ;
 case STEAMDISCOVER_FN_STREAMINGRESPONSE_VIRTUALHERELICENSEDDEVICECOUNT : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_int ( tree , hf_steam_ihs_discovery_body_streamingresponse_virtualherelicenseddevicecount , pb . tvb , pb . offset , len , ( gint32 ) value ) ;
 break ;
 default : len = protobuf_dissect_unknown_field ( & pb , & tag , pinfo , tree , NULL ) ;
 break ;
 }
 protobuf_seek_forward ( & pb , len ) ;
 }
 }