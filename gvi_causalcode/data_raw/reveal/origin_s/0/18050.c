static void dtap_mm_loc_upd_req ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 guint8 oct ;
 proto_tree * subtree ;
 proto_item * item ;
 curr_offset = offset ;
 curr_len = len ;
 is_uplink = IS_UPLINK_TRUE ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_gsm_common_elem [ DE_CIPH_KEY_SEQ_NUM ] , NULL , val_to_str_ext_const ( DE_CIPH_KEY_SEQ_NUM , & gsm_common_elem_strings_ext , "" ) ) ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_spare_bits , tvb , curr_offset << 3 , 1 , ENC_BIG_ENDIAN ) ;
 switch ( ( oct & 0x70 ) >> 4 ) {
 case 0x07 : proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_ciphering_key_sequence_number70 , tvb , curr_offset , 1 , oct , "No key is available" ) ;
 break ;
 default : proto_tree_add_item ( subtree , hf_gsm_a_dtap_ciphering_key_sequence_number70 , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 break ;
 }
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_gsm_dtap_elem [ DE_LOC_UPD_TYPE ] , & item , val_to_str_ext_const ( DE_LOC_UPD_TYPE , & gsm_dtap_elem_strings_ext , "" ) ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_follow_on_request , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) + 5 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_updating_type , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( item , " - %s" , val_to_str_const ( oct & 0x03 , gsm_a_dtap_updating_type_vals , "Reserved" ) ) ;
 curr_offset ++ ;
 curr_len -- ;
 if ( ( signed ) curr_len <= 0 ) return ;
 ELEM_MAND_V ( GSM_A_PDU_TYPE_COMMON , DE_LAI , NULL ) ;
 ELEM_MAND_V ( GSM_A_PDU_TYPE_COMMON , DE_MS_CM_1 , NULL ) ;
 ELEM_MAND_LV ( GSM_A_PDU_TYPE_COMMON , DE_MID , NULL ) ;
 ELEM_OPT_TLV ( 0x33 , GSM_A_PDU_TYPE_COMMON , DE_MS_CM_2 , " - Mobile station classmark for UMTS" ) ;
 ELEM_OPT_TV_SHORT ( 0xc0 , GSM_A_PDU_TYPE_DTAP , DE_ADD_UPD_PARAMS , NULL ) ;
 ELEM_OPT_TV_SHORT ( 0xD0 , GSM_A_PDU_TYPE_GM , DE_DEVICE_PROPERTIES , NULL ) ;
 ELEM_OPT_TV_SHORT ( 0xE0 , GSM_A_PDU_TYPE_COMMON , DE_MS_NET_FEAT_SUP , NULL ) ;
 EXTRANEOUS_DATA_CHECK ( curr_len , 0 , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 }