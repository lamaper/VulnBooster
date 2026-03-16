static void steamdiscover_dissect_body_authresponse ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , gint offset , gint bytes_left ) {
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
 case STEAMDISCOVER_FN_AUTHRESPONSE_AUTHRESULT : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_uint64 ( tree , hf_steam_ihs_discovery_body_authresponse_authresult , pb . tvb , pb . offset , len , ( guint64 ) value ) ;
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "%s Result=%" G_GUINT64_FORMAT "(%s)" , hf_steam_ihs_discovery_header_msgtype_strings [ STEAMDISCOVER_MSGTYPE_DEVICEAUTHORIZATIONRESPONSE ] . strptr , ( guint64 ) value , val64_to_str_const ( ( guint64 ) value , hf_steam_ihs_discovery_body_authresponse_authresult_strings , "Unknown" ) ) ;
 break ;
 default : len = protobuf_dissect_unknown_field ( & pb , & tag , pinfo , tree , NULL ) ;
 break ;
 }
 protobuf_seek_forward ( & pb , len ) ;
 }
 }