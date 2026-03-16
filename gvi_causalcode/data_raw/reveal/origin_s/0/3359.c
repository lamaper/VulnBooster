static void steamdiscover_dissect_body_streamingrequest ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , gint offset , gint bytes_left ) {
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
 case STEAMDISCOVER_FN_STREAMINGREQUEST_REQUESTID : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_uint ( tree , hf_steam_ihs_discovery_body_streamingrequest_requestid , pb . tvb , pb . offset , len , ( guint32 ) value ) ;
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "%s ID=%08x" , hf_steam_ihs_discovery_header_msgtype_strings [ STEAMDISCOVER_MSGTYPE_DEVICESTREAMINGREQUEST ] . strptr , ( guint32 ) value ) ;
 break ;
 case STEAMDISCOVER_FN_STREAMINGREQUEST_MAXIMUMRESOLUTIONX : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_int ( tree , hf_steam_ihs_discovery_body_streamingrequest_maximumresolutionx , pb . tvb , pb . offset , len , ( gint32 ) value ) ;
 break ;
 case STEAMDISCOVER_FN_STREAMINGREQUEST_MAXIMUMRESOLUTIONY : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_int ( tree , hf_steam_ihs_discovery_body_streamingrequest_maximumresolutiony , pb . tvb , pb . offset , len , ( gint32 ) value ) ;
 break ;
 case STEAMDISCOVER_FN_STREAMINGREQUEST_AUDIOCHANNELCOUNT : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_int ( tree , hf_steam_ihs_discovery_body_streamingrequest_audiochannelcount , pb . tvb , pb . offset , len , ( gint32 ) value ) ;
 break ;
 case STEAMDISCOVER_FN_STREAMINGREQUEST_DEVICEVERSION : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_LENGTHDELIMITED ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_item ( tree , hf_steam_ihs_discovery_body_streamingrequest_deviceversion , pb . tvb , pb . offset + len , ( gint ) value , ENC_UTF_8 | ENC_NA ) ;
 len += ( gint ) value ;
 break ;
 case STEAMDISCOVER_FN_STREAMINGREQUEST_STREAMDESKTOP : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_boolean ( tree , hf_steam_ihs_discovery_body_streamingrequest_streamdesktop , pb . tvb , pb . offset , len , ( gint32 ) value ) ;
 break ;
 case STEAMDISCOVER_FN_STREAMINGREQUEST_DEVICETOKEN : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_LENGTHDELIMITED ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_item ( tree , hf_steam_ihs_discovery_body_streamingrequest_devicetoken , pb . tvb , pb . offset + len , ( gint ) value , ENC_NA ) ;
 len += ( gint ) value ;
 break ;
 case STEAMDISCOVER_FN_STREAMINGREQUEST_PIN : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_LENGTHDELIMITED ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_item ( tree , hf_steam_ihs_discovery_body_streamingrequest_pin , pb . tvb , pb . offset + len , ( gint ) value , ENC_NA ) ;
 len += ( gint ) value ;
 break ;
 case STEAMDISCOVER_FN_STREAMINGREQUEST_ENABLEVIDEOSTREAMING : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_boolean ( tree , hf_steam_ihs_discovery_body_streamingrequest_enablevideostreaming , pb . tvb , pb . offset , len , ( gint32 ) value ) ;
 break ;
 case STEAMDISCOVER_FN_STREAMINGREQUEST_ENABLEAUDIOSTREAMING : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_boolean ( tree , hf_steam_ihs_discovery_body_streamingrequest_enableaudiostreaming , pb . tvb , pb . offset , len , ( gint32 ) value ) ;
 break ;
 case STEAMDISCOVER_FN_STREAMINGREQUEST_ENABLEINPUTSTREAMING : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_VARINT ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_boolean ( tree , hf_steam_ihs_discovery_body_streamingrequest_enableinputstreaming , pb . tvb , pb . offset , len , ( gint32 ) value ) ;
 break ;
 default : len = protobuf_dissect_unknown_field ( & pb , & tag , pinfo , tree , NULL ) ;
 break ;
 }
 protobuf_seek_forward ( & pb , len ) ;
 }
 }