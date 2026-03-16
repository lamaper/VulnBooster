static void dissect_iax2 ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree ) {
 proto_item * iax2_item ;
 proto_tree * iax2_tree ;
 proto_tree * full_mini_subtree = NULL ;
 guint32 offset = 0 , len ;
 guint16 scallno = 0 ;
 guint16 stmp ;
 packet_type type ;
 proto_item * full_mini_base ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , PROTO_TAG_IAX2 ) ;
 col_clear ( pinfo -> cinfo , COL_INFO ) ;
 iax2_item = proto_tree_add_item ( tree , proto_iax2 , tvb , offset , - 1 , ENC_NA ) ;
 iax2_tree = proto_item_add_subtree ( iax2_item , ett_iax2 ) ;
 stmp = tvb_get_ntohs ( tvb , offset ) ;
 if ( stmp == 0 ) {
 offset += 2 ;
 stmp = tvb_get_ntohs ( tvb , offset ) ;
 if ( stmp & 0x8000 ) {
 type = IAX2_MINI_VIDEO_PACKET ;
 scallno = stmp & 0x7FFF ;
 offset += 2 ;
 }
 else {
 type = IAX2_TRUNK_PACKET ;
 }
 }
 else {
 scallno = tvb_get_ntohs ( tvb , offset ) ;
 offset += 2 ;
 if ( scallno & 0x8000 ) type = IAX2_FULL_PACKET ;
 else {
 type = IAX2_MINI_VOICE_PACKET ;
 }
 scallno &= 0x7FFF ;
 }
 full_mini_base = proto_tree_add_uint ( iax2_tree , hf_iax2_packet_type , tvb , 0 , offset , type ) ;
 full_mini_subtree = proto_item_add_subtree ( full_mini_base , ett_iax2_full_mini_subtree ) ;
 if ( scallno != 0 ) proto_tree_add_item ( full_mini_subtree , hf_iax2_scallno , tvb , offset - 2 , 2 , ENC_BIG_ENDIAN ) ;
 iax2_info -> ptype = type ;
 iax2_info -> scallno = 0 ;
 iax2_info -> dcallno = 0 ;
 iax2_info -> ftype = 0 ;
 iax2_info -> csub = 0 ;
 iax2_info -> payload_len = 0 ;
 iax2_info -> timestamp = 0 ;
 iax2_info -> callState = VOIP_NO_STATE ;
 iax2_info -> messageName = NULL ;
 iax2_info -> callingParty = NULL ;
 iax2_info -> calledParty = NULL ;
 iax2_info -> payload_data = NULL ;
 switch ( type ) {
 case IAX2_FULL_PACKET : len = dissect_fullpacket ( tvb , offset , scallno , pinfo , full_mini_subtree , tree ) ;
 break ;
 case IAX2_MINI_VOICE_PACKET : iax2_info -> messageName = "MINI_VOICE_PACKET" ;
 len = dissect_minipacket ( tvb , offset , scallno , pinfo , full_mini_subtree , tree ) ;
 break ;
 case IAX2_MINI_VIDEO_PACKET : iax2_info -> messageName = "MINI_VIDEO_PACKET" ;
 len = dissect_minivideopacket ( tvb , offset , scallno , pinfo , full_mini_subtree , tree ) ;
 break ;
 case IAX2_TRUNK_PACKET : iax2_info -> messageName = "TRUNK_PACKET" ;
 len = dissect_trunkpacket ( tvb , offset , scallno , pinfo , full_mini_subtree , tree ) ;
 break ;
 default : len = 0 ;
 }
 proto_item_set_len ( iax2_item , len ) ;
 tap_queue_packet ( iax2_tap , pinfo , iax2_info ) ;
 }