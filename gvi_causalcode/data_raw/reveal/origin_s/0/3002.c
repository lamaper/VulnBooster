static guint16 de_call_state ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint8 oct , coding_standard , call_state ;
 proto_tree * subtree ;
 subtree = proto_tree_add_subtree ( tree , tvb , offset , 1 , ett_gsm_dtap_elem [ DE_CALL_STATE ] , NULL , val_to_str_ext_const ( DE_CALL_STATE , & gsm_dtap_elem_strings_ext , "" ) ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_coding_standard , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 oct = tvb_get_guint8 ( tvb , offset ) ;
 coding_standard = ( oct & 0xc0 ) >> 6 ;
 call_state = oct & 0x3f ;
 switch ( coding_standard ) {
 case 0 : proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_call_state , tvb , offset , 1 , call_state , "%s (%u)" , val_to_str_ext_const ( call_state , & q931_call_state_vals_ext , "Reserved" ) , call_state ) ;
 break ;
 case 1 : case 2 : proto_tree_add_item ( subtree , hf_gsm_a_dtap_call_state , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 break ;
 default : proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_call_state , tvb , offset , 1 , call_state , "%s (%u)" , val_to_str_const ( call_state , gsm_a_dtap_call_state_vals , "Reserved" ) , call_state ) ;
 break ;
 }
 return ( 1 ) ;
 }