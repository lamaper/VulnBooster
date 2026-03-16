void dissect_q931_user_user_ie ( tvbuff_t * tvb , packet_info * pinfo , int offset , int len , proto_tree * tree ) {
 guint8 octet ;
 tvbuff_t * next_tvb = NULL ;
 heur_dtbl_entry_t * hdtbl_entry ;
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_q931_user_protocol_discriminator , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 len -= 1 ;
 if ( len == 0 ) return ;
 switch ( octet ) {
 case Q931_PROTOCOL_DISCRIMINATOR_USER : next_tvb = tvb_new_subset_length ( tvb , offset , len ) ;
 proto_tree_add_uint_format_value ( tree , hf_q931_user_information_len , tvb , offset , len , len , "%d octets" , len ) ;
 if ( ! dissector_try_heuristic ( q931_user_heur_subdissector_list , next_tvb , pinfo , tree , & hdtbl_entry , NULL ) ) {
 call_data_dissector ( next_tvb , pinfo , tree ) ;
 }
 break ;
 case Q931_PROTOCOL_DISCRIMINATOR_IA5 : proto_tree_add_item ( tree , hf_q931_user_information_str , tvb , offset , len , ENC_NA | ENC_ASCII ) ;
 break ;
 default : proto_tree_add_item ( tree , hf_q931_user_information_bytes , tvb , offset , len , ENC_NA ) ;
 break ;
 }
 }