static void dtap_cc_congestion_control ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 guint8 oct ;
 proto_tree * subtree ;
 curr_offset = offset ;
 curr_len = len ;
 is_uplink = IS_UPLINK_FALSE ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , curr_offset << 3 , 4 , ENC_BIG_ENDIAN ) ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_gsm_dtap_elem [ DE_CONGESTION ] , NULL , val_to_str_ext_const ( DE_CONGESTION , & gsm_dtap_elem_strings_ext , "" ) ) ;
 proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_congestion_level , tvb , curr_offset , 1 , oct , "%s" , val_to_str_const ( oct & 0xF , gsm_a_dtap_congestion_level_vals , "Reserved" ) ) ;
 curr_offset ++ ;
 curr_len -- ;
 if ( ( signed ) curr_len <= 0 ) return ;
 ELEM_OPT_TLV ( 0x08 , GSM_A_PDU_TYPE_DTAP , DE_CAUSE , NULL ) ;
 EXTRANEOUS_DATA_CHECK ( curr_len , 0 , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 }