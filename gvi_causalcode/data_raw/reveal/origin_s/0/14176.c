static void steamdiscover_dissect_body_proofresponse ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , gint offset , gint bytes_left ) {
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
 case STEAMDISCOVER_FN_PROOFRESPONSE_RESPONSE : STEAMDISCOVER_ENSURE_WIRETYPE ( PROTOBUF_WIRETYPE_LENGTHDELIMITED ) ;
 value = get_varint64 ( pb . tvb , pb . offset , pb . bytes_left , & len ) ;
 proto_tree_add_item ( tree , hf_steam_ihs_discovery_body_proofresponse_response , pb . tvb , pb . offset + len , ( gint ) value , ENC_NA ) ;
 len += ( gint ) value ;
 break ;
 default : len = protobuf_dissect_unknown_field ( & pb , & tag , pinfo , tree , NULL ) ;
 break ;
 }
 protobuf_seek_forward ( & pb , len ) ;
 }
 }