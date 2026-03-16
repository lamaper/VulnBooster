static gboolean dissect_mpa_req_rep ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , gint message_type ) {
 proto_tree * mpa_tree = NULL ;
 proto_tree * mpa_header_tree = NULL ;
 proto_item * mpa_item = NULL ;
 proto_item * mpa_header_item = NULL ;
 guint16 pd_length ;
 guint32 offset = 0 ;
 mpa_packetlist ( pinfo , message_type ) ;
 if ( tree ) {
 mpa_item = proto_tree_add_item ( tree , proto_iwarp_mpa , tvb , 0 , - 1 , ENC_NA ) ;
 mpa_tree = proto_item_add_subtree ( mpa_item , ett_mpa ) ;
 if ( message_type == MPA_REQUEST_FRAME ) {
 mpa_header_item = proto_tree_add_item ( mpa_tree , hf_mpa_req , tvb , offset , - 1 , ENC_NA ) ;
 mpa_header_tree = proto_item_add_subtree ( mpa_header_item , ett_mpa ) ;
 proto_tree_add_item ( mpa_header_tree , hf_mpa_key_req , tvb , offset , MPA_REQ_REP_KEY_LEN , ENC_NA ) ;
 }
 if ( message_type == MPA_REPLY_FRAME ) {
 mpa_header_item = proto_tree_add_item ( mpa_tree , hf_mpa_rep , tvb , offset , - 1 , ENC_NA ) ;
 mpa_header_tree = proto_item_add_subtree ( mpa_header_item , ett_mpa ) ;
 proto_tree_add_item ( mpa_header_tree , hf_mpa_key_rep , tvb , offset , MPA_REQ_REP_KEY_LEN , ENC_NA ) ;
 }
 offset += MPA_REQ_REP_KEY_LEN ;
 proto_tree_add_item ( mpa_header_tree , hf_mpa_flag_m , tvb , offset , MPA_REQ_REP_FLAG_LEN , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( mpa_header_tree , hf_mpa_flag_c , tvb , offset , MPA_REQ_REP_FLAG_LEN , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( mpa_header_tree , hf_mpa_flag_r , tvb , offset , MPA_REQ_REP_FLAG_LEN , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( mpa_header_tree , hf_mpa_flag_res , tvb , offset , MPA_REQ_REP_FLAG_LEN , ENC_BIG_ENDIAN ) ;
 offset += MPA_REQ_REP_FLAG_LEN ;
 proto_tree_add_item ( mpa_header_tree , hf_mpa_rev , tvb , offset , MPA_REQ_REP_REV_LEN , ENC_BIG_ENDIAN ) ;
 offset += MPA_REQ_REP_REV_LEN ;
 pd_length = tvb_get_ntohs ( tvb , offset ) ;
 if ( pd_length > MPA_MAX_PD_LENGTH ) {
 proto_tree_add_expert_format ( tree , pinfo , & ei_mpa_bad_length , tvb , offset , 2 , "[PD length field indicates more 512 bytes of Private Data]" ) ;
 return FALSE ;
 }
 proto_tree_add_uint ( mpa_header_tree , hf_mpa_pd_length , tvb , offset , MPA_REQ_REP_PDLENGTH_LEN , pd_length ) ;
 offset += MPA_REQ_REP_PDLENGTH_LEN ;
 if ( pd_length ) {
 proto_tree_add_item ( mpa_header_tree , hf_mpa_private_data , tvb , offset , pd_length , ENC_NA ) ;
 }
 }
 return TRUE ;
 }