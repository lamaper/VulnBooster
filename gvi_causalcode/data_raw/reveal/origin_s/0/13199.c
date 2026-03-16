static guint16 de_network_name ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 guint8 oct ;
 guint32 curr_offset ;
 guint8 coding_scheme , num_spare_bits ;
 guint32 num_text_bits ;
 proto_item * item ;
 curr_offset = offset ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 proto_tree_add_item ( tree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 coding_scheme = ( oct & 0x70 ) >> 4 ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_coding_scheme , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_add_ci , tvb , curr_offset , 1 , ENC_NA ) ;
 num_spare_bits = oct & 0x07 ;
 item = proto_tree_add_item ( tree , hf_gsm_a_dtap_number_of_spare_bits , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 NO_MORE_DATA_CHECK ( len ) ;
 switch ( coding_scheme ) {
 case 0 : num_text_bits = ( ( len - 1 ) << 3 ) - num_spare_bits ;
 if ( num_spare_bits && ( num_text_bits % 7 ) ) {
 expert_add_info ( pinfo , item , & ei_gsm_a_dtap_text_string_not_multiple_of_7 ) ;
 }
 proto_tree_add_ts_23_038_7bits_item ( tree , hf_gsm_a_dtap_text_string , tvb , curr_offset << 3 , num_text_bits / 7 ) ;
 break ;
 case 1 : proto_tree_add_item ( tree , hf_gsm_a_dtap_text_string , tvb , curr_offset , len - 1 , ENC_UCS_2 | ENC_BIG_ENDIAN ) ;
 break ;
 default : proto_tree_add_expert ( tree , pinfo , & ei_gsm_a_dtap_coding_scheme , tvb , curr_offset , len - 1 ) ;
 }
 return ( len ) ;
 }