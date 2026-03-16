static guint16 de_prog_ind ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint8 oct , coding_standard , progress_description ;
 guint32 curr_offset ;
 curr_offset = offset ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 coding_standard = ( oct & 0x60 ) >> 5 ;
 proto_tree_add_item ( tree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_prog_coding_standard , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) + 3 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_location , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 progress_description = oct & 0x7f ;
 proto_tree_add_item ( tree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 switch ( coding_standard ) {
 case 0 : proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_progress_description , tvb , curr_offset , 1 , progress_description , "%s (%u)" , val_to_str_ext_const ( progress_description , & q931_progress_description_vals_ext , "Reserved" ) , progress_description ) ;
 break ;
 case 1 : case 2 : proto_tree_add_item ( tree , hf_gsm_a_dtap_progress_description , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 break ;
 default : proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_progress_description , tvb , curr_offset , 1 , progress_description , "%s (%u)" , val_to_str_const ( progress_description , gsm_a_dtap_progress_description_vals , "Unspecific" ) , progress_description ) ;
 break ;
 }
 curr_offset ++ ;
 EXTRANEOUS_DATA_CHECK ( len , curr_offset - offset , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 return ( curr_offset - offset ) ;
 }