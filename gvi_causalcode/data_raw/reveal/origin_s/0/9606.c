static guint16 de_bcd_num ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len , int header_field , const gchar * * extracted_address ) {
 guint8 extension ;
 guint32 curr_offset , num_string_len ;
 proto_item * item ;
 * extracted_address = NULL ;
 curr_offset = offset ;
 extension = tvb_get_guint8 ( tvb , curr_offset ) & 0x80 ;
 proto_tree_add_item ( tree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_type_of_number , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_numbering_plan_id , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 if ( ! extension ) {
 proto_tree_add_item ( tree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_present_ind , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) + 3 , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_screening_ind , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 }
 NO_MORE_DATA_CHECK ( len ) ;
 num_string_len = len - ( curr_offset - offset ) ;
 * extracted_address = tvb_bcd_dig_to_wmem_packet_str ( tvb , curr_offset , num_string_len , & Dgt_mbcd , FALSE ) ;
 item = proto_tree_add_string ( tree , header_field , tvb , curr_offset , num_string_len , * extracted_address ) ;
 if ( strchr ( * extracted_address , '?' ) ) {
 expert_add_info ( pinfo , item , & ei_gsm_a_dtap_end_mark_unexpected ) ;
 }
 return ( len ) ;
 }