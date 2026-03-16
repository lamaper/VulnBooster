static guint16 de_cc_cap ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 guint8 oct ;
 guint32 curr_offset ;
 curr_offset = offset ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 if ( ( ( oct & 0xf0 ) >> 4 ) == 0 ) {
 proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_maximum_number_of_supported_bearers , tvb , curr_offset , 1 , 0 , "1" ) ;
 }
 else {
 proto_tree_add_item ( tree , hf_gsm_a_dtap_maximum_number_of_supported_bearers , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 }
 proto_tree_add_item ( tree , hf_gsm_a_dtap_mcat , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_enicm , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_pcp , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_dtmf , tvb , curr_offset , 1 , ENC_NA ) ;
 curr_offset ++ ;
 NO_MORE_DATA_CHECK ( len ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , curr_offset << 3 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_max_num_of_speech_bearers , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 EXTRANEOUS_DATA_CHECK ( len , curr_offset - offset , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 return ( curr_offset - offset ) ;
 }