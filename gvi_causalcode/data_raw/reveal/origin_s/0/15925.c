int lbmpdm_dissect_lbmpdm_payload ( tvbuff_t * tvb , int offset , packet_info * pinfo , proto_tree * tree , guint64 channel ) {
 proto_item * subtree_item = NULL ;
 proto_tree * subtree = NULL ;
 proto_item * segments_item = NULL ;
 proto_tree * segments_tree = NULL ;
 proto_item * pi = NULL ;
 guint8 next_hdr ;
 int dissected_len = 0 ;
 int encoding ;
 int msglen = 0 ;
 int len_remaining = 0 ;
 int ofs = 0 ;
 int segment_len = 0 ;
 int datalen = 0 ;
 guint32 raw_msglen = 0 ;
 lbmpdm_msg_definition_id_t msgid ;
 if ( ! lbmpdm_verify_payload ( tvb , offset , & encoding , & raw_msglen ) ) {
 return ( 0 ) ;
 }
 msglen = ( int ) raw_msglen ;
 msgid . channel = channel ;
 msgid . msg_def_id = 0 ;
 msgid . ver_major = 0 ;
 msgid . ver_minor = 0 ;
 msgid . offset_table = NULL ;
 subtree_item = proto_tree_add_protocol_format ( tree , proto_lbmpdm , tvb , offset , msglen , "LBMPDM Protocol" ) ;
 subtree = proto_item_add_subtree ( subtree_item , ett_lbmpdm ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_magic , tvb , offset + O_LBMPDM_MSG_HDR_T_MAGIC , L_LBMPDM_MSG_HDR_T_MAGIC , encoding ) ;
 pi = proto_tree_add_string ( subtree , hf_lbmpdm_encoding , tvb , offset + O_LBMPDM_MSG_HDR_T_MAGIC , L_LBMPDM_MSG_HDR_T_MAGIC , ( ( encoding == ENC_BIG_ENDIAN ) ? "Big-Endian" : "Little-Endian" ) ) ;
 PROTO_ITEM_SET_GENERATED ( pi ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_ver , tvb , offset + O_LBMPDM_MSG_HDR_T_VER_TYPE , L_LBMPDM_MSG_HDR_T_VER_TYPE , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_type , tvb , offset + O_LBMPDM_MSG_HDR_T_VER_TYPE , L_LBMPDM_MSG_HDR_T_VER_TYPE , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_next_hdr , tvb , offset + O_LBMPDM_MSG_HDR_T_NEXT_HDR , L_LBMPDM_MSG_HDR_T_NEXT_HDR , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_def_major_ver , tvb , offset + O_LBMPDM_MSG_HDR_T_DEF_MAJOR_VER , L_LBMPDM_MSG_HDR_T_DEF_MAJOR_VER , encoding ) ;
 msgid . ver_major = tvb_get_guint8 ( tvb , offset + O_LBMPDM_MSG_HDR_T_DEF_MAJOR_VER ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_def_minor_ver , tvb , offset + O_LBMPDM_MSG_HDR_T_DEF_MINOR_VER , L_LBMPDM_MSG_HDR_T_DEF_MINOR_VER , encoding ) ;
 msgid . ver_minor = tvb_get_guint8 ( tvb , offset + O_LBMPDM_MSG_HDR_T_DEF_MINOR_VER ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_def_id , tvb , offset + O_LBMPDM_MSG_HDR_T_DEF_ID , L_LBMPDM_MSG_HDR_T_DEF_ID , encoding ) ;
 msgid . msg_def_id = lbmpdm_fetch_uint32_encoded ( tvb , offset + O_LBMPDM_MSG_HDR_T_DEF_ID , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_len , tvb , offset + O_LBMPDM_MSG_HDR_T_LEN , L_LBMPDM_MSG_HDR_T_LEN , encoding ) ;
 next_hdr = tvb_get_guint8 ( tvb , offset + O_LBMPDM_MSG_HDR_T_NEXT_HDR ) ;
 len_remaining = msglen - L_LBMPDM_MSG_HDR_T ;
 ofs = offset + L_LBMPDM_MSG_HDR_T ;
 dissected_len = L_LBMPDM_MSG_HDR_T ;
 datalen = msglen - L_LBMPDM_MSG_HDR_T ;
 if ( len_remaining > 0 ) {
 guint8 this_hdr = next_hdr ;
 segments_item = proto_tree_add_item ( subtree , hf_lbmpdm_segments , tvb , ofs , datalen , encoding ) ;
 segments_tree = proto_item_add_subtree ( segments_item , ett_lbmpdm_segments ) ;
 while ( ( this_hdr != PDM_HDR_TYPE_EOM ) && ( len_remaining >= L_LBMPDM_SEG_HDR_T ) ) {
 next_hdr = tvb_get_guint8 ( tvb , ofs + O_LBMPDM_SEG_HDR_T_NEXT_HDR ) ;
 switch ( this_hdr ) {
 case PDM_HDR_TYPE_DATA : segment_len = dissect_segment_data ( tvb , ofs , pinfo , segments_tree , & msgid , encoding ) ;
 break ;
 case PDM_HDR_TYPE_OFSTTBLE : segment_len = dissect_segment_ofstable ( tvb , ofs , pinfo , segments_tree , & ( msgid . offset_table ) , encoding ) ;
 break ;
 case PDM_HDR_TYPE_DEFN : segment_len = dissect_segment_defn ( tvb , ofs , pinfo , segments_tree , channel , encoding ) ;
 break ;
 default : segment_len = dissect_segment_unknown ( tvb , ofs , pinfo , segments_tree , encoding ) ;
 break ;
 }
 this_hdr = next_hdr ;
 dissected_len += segment_len ;
 len_remaining -= segment_len ;
 ofs += segment_len ;
 }
 }
 return ( dissected_len ) ;
 }